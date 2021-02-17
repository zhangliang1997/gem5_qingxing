from m5.params import *
from m5.SimObject import SimObject
from m5.objects.ClockedObject import ClockedObject
from m5.proxy import *

class ZLCache(ClockedObject):
    type='ZLCache'
    cxx_header='learning_gem5/zl_part2/zl_cache.hh'

    latency=Param.Cycles(1, "cycles taken on a hit or to reslove a miss")

    size=Param.MemorySize("16kB", "the size of the cache")

    system=Param.System(Parent.any, "the system this cache is part of")

    cpu_side=ResponsePort("cpu side port")

    mem_side=RequestPort("mem port")


