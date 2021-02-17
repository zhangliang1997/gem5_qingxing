#ifndef __ZL_MEM_OBJECT_HH_
#define __ZL_MEM_OBJECT_HH_

#include "mem/port.hh"
#include "params/ZLMemObject.hh"
#include "sim/sim_object.hh"

class ZLMemObject: public SimObject
{
private:
    class CPUSidePort: public ResponsePort
    {
        private:
            ZLMemObject *owner;
            bool needRetry;
            PacketPtr blockedPacket;
        public:

            CPUSidePort(const std::string &name, ZLMemObject *owner):
            ResponsePort(name, owner), owner(owner), needRetry(false),
            blockedPacket(nullptr)
            { }

            void sendPacket(PacketPtr pkt);

            AddrRangeList getAddrRanges() const override;

            void trySendRetry();

        protected:

            Tick recvAtomic(PacketPtr pkt) override
            {
                panic("recvAtomic unimpl");
            }

            void recvFunctional(PacketPtr pkt) override;

            bool recvTimingReq(PacketPtr pkt) override;

            void recvRespRetry() override;

    };
    class MemSidePort : public RequestPort
    {
      private:
        ZLMemObject *owner;

        PacketPtr blockedPacket;

      public:
        MemSidePort(const std::string& name, ZLMemObject *owner) :
            RequestPort(name, owner), owner(owner), blockedPacket(nullptr)
        { }

        void sendPacket(PacketPtr pkt);

      protected:
        bool recvTimingResp(PacketPtr pkt) override;

        void recvReqRetry() override;

        void recvRangeChange() override;
    };

    bool handleRequest(PacketPtr pkt);

    bool handleResponse(PacketPtr pkt);

    void handleFunctional(PacketPtr pkt);

    AddrRangeList getAddrRanges() const;

    void sendRangeChange();

    CPUSidePort instPort;
    CPUSidePort dataPort;
    MemSidePort memSide;

    bool blocked;

public:
    ZLMemObject(ZLMemObjectParams *p);
     Port &getPort(const std::string &if_name,
                  PortID idx=InvalidPortID) override;

};



#endif
