from m5.params import *
from m5.SimObject import SimObject

class ZlObject(SimObject):
    type='ZlObject'
    cxx_header="learning_gem5/zl_part2/zl_object.hh"
    time_to_wait=Param.Latency("time to wait")
    number_of_fires=Param.Int(1, "number of fires")