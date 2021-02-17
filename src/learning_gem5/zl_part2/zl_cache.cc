#include "learning_gem5/zl_part2/zl_cache.hh"

#include <cstdio>

#include "base/random.hh"
#include "debug/ZLCache.hh"
#include "sim/system.hh"

ZLCache::ZLCache(ZLCacheParams *params):
    ClockedObject(params),
    latency(params->latency),
    blockSize(params->system->cacheLineSize()),
    capacity(params->size / blockSize),
    blocked(false),
    originalPacket(nullptr),
    waitingPortId(-1),
    memPort(params->name+".mem_side", this),
    stats(this)
{
    DPRINTF(ZLCache,  "zl: %s\n", __FUNCTION__);
    for (int i=0;i<params->port_cpu_side_connection_count;++i)
        cpuPorts.emplace_back(name()+csprintf(".cpu_side[%d]", i),
            this, i
        );
}

Port&
ZLCache::getPort(const std::string &if_name, PortID idx)
{
    DPRINTF(ZLCache,  "zl: %s\n", __FUNCTION__);
    if (if_name=="mem_side")
        return memPort;
    else if (if_name=="cpu_side"&&idx<cpuPorts.size())
        return cpuPorts[idx];
    else
        return  ClockedObject::getPort(if_name, idx);
}
void
ZLCache::CPUSidePort::sendPacket(PacketPtr pkt)
{
    panic_if(blockedPacket!=nullptr, "should never try to send if blocked");
    DPRINTF(ZLCache,  "zl: %s\n", __FUNCTION__);
    if (!sendTimingResp(pkt))
        blockedPacket=pkt;
}



AddrRangeList
ZLCache::CPUSidePort::getAddrRanges() const
{
    DPRINTF(ZLCache,  "zl: %s\n", __FUNCTION__);
    return owner->getAddrRanges();
}

void
ZLCache::CPUSidePort::trySendRetry()
{
    DPRINTF(ZLCache,  "zl: %s\n", __FUNCTION__);
    if (needRetry && blockedPacket==nullptr)
    {
        needRetry=false;
        sendRetryReq();
    }
}
void
ZLCache::CPUSidePort::recvFunctional(PacketPtr pkt)
{
    DPRINTF(ZLCache,  "zl: %s\n", __FUNCTION__);
    owner->handleFunctional(pkt);
}

bool
ZLCache::CPUSidePort::recvTimingReq(PacketPtr pkt)
{
    DPRINTF(ZLCache,  "zl: %s\n", __FUNCTION__);
    if (blockedPacket || needRetry){
        needRetry=true;
        return false;
    }

    if (!owner->handleRequest(pkt, idx)){
        needRetry=true;
        return false;
    }
    return true;
}

void
ZLCache::CPUSidePort::recvRespRetry()
{
    DPRINTF(ZLCache,  "zl: %s\n", __FUNCTION__);
    assert(blockedPacket!=nullptr);

    PacketPtr pkt=blockedPacket;
    blockedPacket=nullptr;

    sendPacket(pkt);

    trySendRetry();
}

void
ZLCache::MemSidePort::sendPacket(PacketPtr pkt)
{
    //DPRINTF(ZLCache, "zl: %s\n",__FUNCTION__);
    if (!sendTimingReq(pkt))
        blockedPacket=pkt;
}

bool
ZLCache::MemSidePort::recvTimingResp(PacketPtr pkt)
{
    DPRINTF(ZLCache,  "zl: %s\n", __FUNCTION__);
    return owner->handleResponse(pkt);
}

void
ZLCache::MemSidePort::recvReqRetry()
{
    DPRINTF(ZLCache,  "zl: %s\n", __FUNCTION__);
    assert(blockedPacket != nullptr);

    PacketPtr pkt=blockedPacket;
    blockedPacket=nullptr;

    sendPacket(pkt);
}

void
ZLCache::MemSidePort::recvRangeChange()
{
    DPRINTF(ZLCache,  "zl: %s\n", __FUNCTION__);
    owner->sendRangeChange();
}

bool
ZLCache::handleRequest(PacketPtr pkt, int portId)
{
    if (blocked) return false;
    DPRINTF(ZLCache,  "zl: %s\n", __FUNCTION__);
    blocked=true;
    assert(waitingPortId==-1);
    waitingPortId=portId;

    schedule(new EventFunctionWrapper([this, pkt]{accessTiming(pkt);},
                                    name()+".accessEvent", true),
                                    clockEdge(latency));

    return true;

}

bool
ZLCache::handleResponse(PacketPtr pkt)
{
    DPRINTF(ZLCache,  "zl: %s\n", __FUNCTION__);
    assert(blocked);

    insert(pkt);

    if (originalPacket != nullptr) {
        bool hit M5_VAR_USED = accessFunctional(originalPacket);
        originalPacket->makeResponse();
        delete pkt;
        pkt = originalPacket;
        originalPacket = nullptr;
    }
    sendResponse(pkt);

    return true;

}

void
ZLCache::sendResponse(PacketPtr pkt)
{
    assert(blocked);
    DPRINTF(ZLCache,  "zl: %s\n", __FUNCTION__);
    int port=waitingPortId;

    blocked=false;
    waitingPortId=-1;
    cpuPorts[port].sendPacket(pkt);

    for (auto& port : cpuPorts){
        port.trySendRetry();
    }
}

void
ZLCache::handleFunctional(PacketPtr pkt)
{
    if (accessFunctional(pkt)){
        pkt->makeResponse();
    }else{
        memPort.sendFunctional(pkt);
    }
}

void
ZLCache::accessTiming(PacketPtr pkt)
{
    DPRINTF(ZLCache,  "zl: %s\n", __FUNCTION__);
    bool hit=accessFunctional(pkt);
    if (hit){
        pkt->makeResponse();
        sendResponse(pkt);
    }else{
        missTime=curTick();

        Addr addr=pkt->getAddr();
        Addr block_addr=pkt->getBlockAddr(blockSize);
        unsigned size=pkt->getSize();
        if (addr == block_addr && size == blockSize) {
            memPort.sendPacket(pkt);
        } else {
            MemCmd cmd;
            if (pkt->isWrite() || pkt->isRead()) {
                cmd = MemCmd::ReadReq;
            } else {
                panic("Unknown packet type in upgrade size");
            }

            PacketPtr new_pkt = new Packet(pkt->req, cmd, blockSize);
            new_pkt->allocate();

            assert(new_pkt->getAddr() == new_pkt->getBlockAddr(blockSize));

            originalPacket = pkt;

            memPort.sendPacket(new_pkt);
        }

    }
}

bool
ZLCache::accessFunctional(PacketPtr pkt)
{
    DPRINTF(ZLCache,  "zl: %s\n", __FUNCTION__);
    Addr block_addr = pkt->getBlockAddr(blockSize);
    auto it = cacheStore.find(block_addr);
    if (it != cacheStore.end()) {
        if (pkt->isWrite()) {
            // Write the data into the block in the cache
            pkt->writeDataToBlock(it->second, blockSize);
        } else if (pkt->isRead()) {
            // Read the data out of the cache block into the packet
            pkt->setDataFromBlock(it->second, blockSize);
        } else {
            panic("Unknown packet type!");
        }
        return true;
    }
    return false;
}

void
ZLCache::insert(PacketPtr pkt)
{
    DPRINTF(ZLCache,  "zl: %s\n", __FUNCTION__);
    // The packet should be aligned.
    assert(pkt->getAddr() ==  pkt->getBlockAddr(blockSize));
    // The address should not be in the cache
    assert(cacheStore.find(pkt->getAddr()) == cacheStore.end());
    // The pkt should be a response
    assert(pkt->isResponse());

    if (cacheStore.size() >= capacity) {
        // Select random thing to evict. This is a little convoluted since we
        // are using a std::unordered_map. See http://bit.ly/2hrnLP2
        int bucket, bucket_size;
        do {
            bucket = random_mt.random(0, (int)cacheStore.bucket_count() - 1);
        } while ( (bucket_size = cacheStore.bucket_size(bucket)) == 0 );
        auto block = std::next(cacheStore.begin(bucket),
                               random_mt.random(0, bucket_size - 1));


        // Write back the data.
        // Create a new request-packet pair
        RequestPtr req = std::make_shared<Request>(
            block->first, blockSize, 0, 0);

        PacketPtr new_pkt = new Packet(req, MemCmd::WritebackDirty, blockSize);
        new_pkt->dataDynamic(block->second); // This will be deleted later

        // Send the write to memory
        memPort.sendPacket(new_pkt);

        // Delete this entry
        cacheStore.erase(block->first);
    }


    // Allocate space for the cache block data
    uint8_t *data = new uint8_t[blockSize];

    // Insert the data and address into the cache store
    cacheStore[pkt->getAddr()] = data;

    // Write the data into the cache
    pkt->writeDataToBlock(data, blockSize);
}

AddrRangeList
ZLCache::getAddrRanges() const
{
    DPRINTF(ZLCache,  "zl: %s\n", __FUNCTION__);
    memPort.getAddrRanges();
}

void
ZLCache::sendRangeChange() const
{
    DPRINTF(ZLCache,  "zl: %s\n", __FUNCTION__);
    for (auto& port: cpuPorts)
        port.sendRangeChange();
}

ZLCache::ZLCacheStats::ZLCacheStats(Stats::Group *parent):
    Stats::Group(parent),
    ADD_STAT(hits, "number of hits"),
    ADD_STAT(misses, "number of misses"),
    ADD_STAT(missLatency, "ticks for misses to the cache"),
    ADD_STAT(hitRatio, "hit ratio", hits/(hits+misses))
{
    missLatency.init(16);
}

ZLCache*
ZLCacheParams::create()
{
    return new ZLCache(this);
}
