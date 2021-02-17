#include "learning_gem5/zl_part2/zl_mem_object.hh"

#include "base/trace.hh"
#include "debug/ZLMemObject.hh"

ZLMemObject::ZLMemObject(ZLMemObjectParams *params):
    SimObject(params),
    instPort(params->name+".inst_port", this),
    dataPort(params->name+".data_port", this),
    memSide(params->name+".mem_side", this),
    blocked(false)
    {}

Port
&ZLMemObject::getPort(const std::string &if_name, PortID idx)
{
    if (if_name=="mem_side")
        return memSide;
    else if (if_name=="inst_port")
        return instPort;
    else if (if_name=="data_port")
        return dataPort;
    else
        return SimObject::getPort(if_name, idx);
}

void
ZLMemObject::CPUSidePort::sendPacket(PacketPtr pkt)
{
    if (!sendTimingResp(pkt))
        blockedPacket=pkt;
}

AddrRangeList
ZLMemObject::CPUSidePort::getAddrRanges() const
{
    return owner->getAddrRanges();
}

void
ZLMemObject::CPUSidePort::trySendRetry()
{
    if (needRetry&&blockedPacket==nullptr)
    {
        needRetry=false;
        sendRetryReq();
    }
}

void
ZLMemObject::CPUSidePort::recvFunctional(PacketPtr pkt)
{
    return owner->handleFunctional(pkt);
}

bool
ZLMemObject::CPUSidePort::recvTimingReq(PacketPtr pkt)
{
    if (!owner->handleRequest(pkt)){
        needRetry=true;
        return false;
    }else{
        return true;
    }
}

void
ZLMemObject::CPUSidePort::recvRespRetry()
{
    PacketPtr pkt=blockedPacket;
    blockedPacket=nullptr;
    sendPacket(pkt);
}

void
ZLMemObject::MemSidePort::sendPacket(PacketPtr pkt)
{
    if (!sendTimingReq(pkt))
        blockedPacket=pkt;
}

bool
ZLMemObject::MemSidePort::recvTimingResp(PacketPtr pkt)
{
    return owner->handleResponse(pkt);
}

void
ZLMemObject::MemSidePort::recvReqRetry()
{
    assert(blockedPacket!=nullptr);

    PacketPtr pkt=blockedPacket;
    blockedPacket=nullptr;
    sendPacket(pkt);
}

void
ZLMemObject::MemSidePort::recvRangeChange()
{
    owner->sendRangeChange();
}

bool
ZLMemObject::handleRequest(PacketPtr pkt)
{
    if (blocked){
        return false;
    }
    DPRINTF(ZLMemObject, "request for addr %#x\n", pkt->getAddr());
    blocked=true;
    memSide.sendPacket(pkt);
    return true;
}


bool
ZLMemObject::handleResponse(PacketPtr pkt)
{
    blocked=false;
    DPRINTF(ZLMemObject, "response for addr %#x\n", pkt->getAddr());
    if (pkt->req->isInstFetch())
        instPort.sendPacket(pkt);
    else
        dataPort.sendPacket(pkt);

    instPort.trySendRetry();
    dataPort.trySendRetry();

    return true;
}

void
ZLMemObject::handleFunctional(PacketPtr pkt)
{
    memSide.sendFunctional(pkt);
}

AddrRangeList
ZLMemObject::getAddrRanges() const
{
    return memSide.getAddrRanges();
}

void
ZLMemObject::sendRangeChange()
{
    instPort.sendRangeChange();
    dataPort.sendRangeChange();
}



ZLMemObject*
ZLMemObjectParams::create()
{
    return new ZLMemObject(this);
}
