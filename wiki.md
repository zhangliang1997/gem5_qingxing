Q1:  
zl@zl:~/gem5$ scons build/X86/gem5.opt -j9  
scons: Reading SConscript files ...  
ImportError: No module named six:  
  File "/home/zl/gem5/SConstruct", line 100:  
    from m5.util import compareVersions, readCommand, readCommandWithReturn  
  File "/home/zl/gem5/src/python/m5/util/__init__.py", line 46:  
    from six import string_types  

Solution: pip install six

Q2:  
scons: done building targets.  
*** Summary of Warnings ***  
Warning: Your compiler doesn't support incremental linking and lto at the same time, so lto is being disabled. To force lto on anyway, use the --force-lto option. That will disable partiallinking. 
Warning: Header file <png.h> not found.  
         This host has no libpng library.  
         Disabling support for PNG framebuffers.  
  
Solution: haven't solved

Q3: fatal: Port <orphan System>.cache.cpu_side is already connected to <orphan System>.cpu.icache_port, cannot connect <orphan System>.cpu.dcache_port  

Solution: firstly, in .py file, cpu_side should be VectorResponsePort type.  
Secondly, after modify .py file, you should recompile gem5
  
  use state modified (M) to denote an L1 block that one core can write and read,  
use state shared (S) to denote an L1 block that one or more cores can only read, and  
have GetM and GetS denote coherence requests to obtain a block in M and S, respectively.  

Q4:  
why we need transaction buffer entry?   

Q5:  
```
A: transition(IS_D, {DataDirNoAcks, DataOwner}, S) {
        writeDataToCache;
        deallocateTBE;
        externalLoadHit;
        popResponseQueue;
}

transition({IM_AD, IM_A}, {Load, Store, Replacement, FwdGetS, FwdGetM}) {
    stall;
}

B: transition({IM_AD, SM_AD}, {DataDirNoAcks, DataOwner}, M) {
    writeDataToCache;
    deallocateTBE;
    externalStoreHit;
    popResponseQueue;
}
```    
when trigger DataDirNoAcks, how to choose between A and B
