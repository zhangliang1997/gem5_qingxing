#ifndef __ZL_CACHE_HH__
#define __ZL_CACHE_HH__

#include <unordered_map>
#include <vector>

#include "base/statistics.hh"
#include "mem/port.hh"
#include "params/ZLCache.hh"
#include "sim/clocked_object.hh"

class ZLCache: public ClockedObject
{
    private:

    class CPUSidePort: public ResponsePort
    {
        private:

            int idx;

            ZLCache *owner;

            PacketPtr blockedPacket;

            bool needRetry;

        protected:

            Tick recvAtomic(PacketPtr pkt) override
            {
                panic("recvAtomic unimpl.");
            }

            void recvFunctional(PacketPtr pkt) override;

            bool recvTimingReq(PacketPtr pkt) override;

            void recvRespRetry() override;

        public:

            CPUSidePort(const std::string &name, ZLCache *owner, int idx):
                ResponsePort(name, owner),
                idx(idx),
                owner(owner),
                blockedPacket(nullptr),
                needRetry(false)
            {}

            void sendPacket(PacketPtr pkt);

            AddrRangeList getAddrRanges() const override;

            void trySendRetry();



    };

    class MemSidePort: public RequestPort
    {
        private:

            ZLCache *owner;

            PacketPtr blockedPacket;

        protected:



            bool recvTimingResp(PacketPtr pkt) override;

            void recvReqRetry() override;

            void recvRangeChange() override;

        public:

            MemSidePort(const std::string &name, ZLCache *owner):
                RequestPort(name, owner),
                owner(owner),
                blockedPacket(nullptr)
            {}

            void sendPacket(PacketPtr pkt);
    };


    protected:
        struct ZLCacheStats: public Stats::Group
        {
            ZLCacheStats(Stats::Group *parent);
            Stats::Scalar hits;
            Stats::Scalar misses;
            Stats::Histogram missLatency;
            Stats::Formula hitRatio;
        }stats;

    public:

        ZLCache(ZLCacheParams *p);

        bool handleRequest(PacketPtr pkt, int port_id);

        bool handleResponse(PacketPtr pkt);

        void sendResponse(PacketPtr pkt);

        void handleFunctional(PacketPtr pkt);

        void accessTiming(PacketPtr pkt);

        bool accessFunctional(PacketPtr pkt);

        void insert(PacketPtr pkt);

        AddrRangeList getAddrRanges() const;

        void sendRangeChange() const;

        const Cycles latency;

        const unsigned blockSize;

        const unsigned capacity;

        std::vector<CPUSidePort> cpuPorts;

        MemSidePort memPort;

        bool blocked;

        PacketPtr originalPacket;

        int waitingPortId;

        Tick missTime;

        std::unordered_map<Addr, uint8_t*> cacheStore;

        Port &getPort(const std::string &if_name,
                      PortID idx=InvalidPortID) override;
};



#endif
