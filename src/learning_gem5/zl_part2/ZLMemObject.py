from m5.params import *
from m5.SimObject import SimObject

class ZLMemObject(SimObject):
    type="ZLMemObject"
    cxx_header="learning_gem5/zl_part2/zl_mem_object.hh"

    inst_port=SlavePort("cpu side inst port")
    data_port=SlavePort("cpu side data port")

    mem_side=MasterPort("mem side")