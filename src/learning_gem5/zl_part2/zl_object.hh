#ifndef __LEARNING_GEM5_HELLO_OBJECT_HH__
#define __LEARNING_GEM5_HELLO_OBJECT_HH__

#include "params/ZlObject.hh"
#include "sim/sim_object.hh"

class ZlObject : public SimObject
{
  private:
    EventFunctionWrapper event;
    void processEvent();
    Tick latency;
    int timesLeft;
  public:
    ZlObject(ZlObjectParams *p);
    void startup();
};

#endif // __LEARNING_GEM5_HELLO_OBJECT_HH__