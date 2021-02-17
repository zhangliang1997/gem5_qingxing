#include "mem/cache/tags/nmru.hh"

#include "base/random.hh"
#include "mem/cache/base.hh"

NMRU::NMRU(const params *p):
        BaseSetAssoc(p)
{}

CacheBlk*
NMRU::accessBlock(Addr addr, bool is_secure, Cycles& latency)
{
    CacheBlk *blk=BaseSetAssoc::accessBlock(addr, is_secure, latency);
    if (blk!=nullptr){
        getSet().[blk->set].moveToHead(blk);
    }
    return blk;

}

CacheBlk*
NMRU::findVictim(Addr addr)
{
    CacheBlk *blk=BaseSetAssoc::findVictim(addr);

    if (blk->isValid())
    {
        int idx = random_mt.random<int>(1, assoc - 1);
        blk = sets[extractSet(addr)].blks[idx];
    }
    return blk;
}

NMRU::insertBlock(PacketPtr pkt, CacheBlk *blk)
{
    BaseSetAssoc::insertBlock(pkt, blk);

    int set = extractSet(pkt->getAddr());
    sets[set].moveToHead(blk);
}

NMRU::invalidate(CacheBlk *blk)
{
    BaseSetAssoc::invalidate(blk);

    // should be evicted before valid blocks
    int set = blk->set;
    sets[set].moveToTail(blk);

}

NMRU*
NMRUParams::create()
{
    return new NMRU(this);
}
