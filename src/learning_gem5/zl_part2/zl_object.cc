#include "learning_gem5/zl_part2/zl_object.hh"

#include <iostream>

#include "base/trace.hh"
#include "debug/zlzl.hh"

ZlObject::ZlObject(ZlObjectParams *params) :
    SimObject(params),
    event([this]{processEvent();}, name()),
    latency(params->time_to_wait),
    timesLeft(params->number_of_fires)
{
    std::cout << "Hello World! From a zl!" << std::endl;
    DPRINTF(zlzl, "zzzzzzzzzzzzzzzllllllllllllllll\n");
}

ZlObject*
ZlObjectParams::create()
{
    return new ZlObject(this);
}

void ZlObject::processEvent()
{
    DPRINTF(zlzl, "process event\n");
    timesLeft--;
    if (timesLeft<=0)
    {
        DPRINTF(zlzl, "done firing\n");
    }
    else
    {
        schedule(event, curTick()+latency);
    }

}

void ZlObject::startup()
{
    schedule(event, 100);
}
