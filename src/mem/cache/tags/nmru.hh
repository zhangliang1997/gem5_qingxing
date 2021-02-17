
#include "mem/cache/tags/base_set_assoc.hh"
#include "params/NMRU.hh"

class NMRU : public BaseSetAssoc
{
private:

public:

    typedef NMRUParams params;

    NMRU(const params *p);
    ~NMRU();

    CacheBlk* accessBlock(Addr addr, bool is_secure, Cycles& latency);
    CacheBlk* findVictim(Addr addr) const;
    void insertBlock(PacketPtr pkt, CacheBlk *blk);
    void invalidate(CacheBlk *blk);
};


