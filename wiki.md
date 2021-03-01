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

Q:  
 scons build/ARM_MESI_Two_Level/gem.opt -j8  
 Checking whether __x86_64__ is declared... (cached) yes
Building in /home/zl/gem5/build/ARM_MESI_Two_Level
Using saved variables file /home/zl/gem5/build/variables/ARM_MESI_Two_Level
scons: done reading SConscript files.
scons: Building targets ...
scons: *** Do not know how to make File target `build/ARM_MESI_Two_Level/gem.opt' (/home/zl/gem5/build/ARM_MESI_Two_Level/gem.opt).  Stop.
scons: building terminated because of errors.

scons build/ARM_MESI_Two_Level/gem"5".opt -j8


Q:TypeError: 'float' object cannot be interpreted as an integer
assert (options.num_cpus % options.num_clusters == 0)
    num_cpus_per_cluster = options.num_cpus // options.num_clusters

    assert (options.num_l2caches % options.num_clusters == 0)
    num_l2caches_per_cluster = options.num_l2caches // options.num_clusters

s:'/'->'//'

Q: push code to github

Script:  
scons build/ARM_MESI_Two_Level/gem.opt -j8  
scons build/ARM_MESI_Three_Level/gem.opt -j8
./build/ARM/gem5.opt configs/example/se.py --help   
build/ARM_MESI_Two_Level/gem5.opt configs/example/se.py -n 2 --cpu-type=TimingSimpleCPU  --ruby --caches --l1d_size=4kB --l1i_size=4kB --l2cache --l2_size=2MB -c 'tests/test-progs/hello/bin/arm/linux/hello;tests/test-progs/hello/bin/arm/linux/hello'  
build/ARM_MESI_Two_Level/gem5.opt configs/example/se.py -n 8 --cpu-type=TimingSimpleCPU --ruby -c 'tests/test-progs/hello/bin/arm/linux/hello;tests/test-progs/hello/bin/arm/linux/hello;tests/test-progs/hello/bin/arm/linux/hello;tests/test-progs/hello/bin/arm/linux/hello;tests/test-progs/hello/bin/arm/linux/hello;tests/test-progs/hello/bin/arm/linux/hello;tests/test-progs/hello/bin/arm/linux/hello;tests/test-progs/hello/bin/arm/linux/hello'  

build/ARM_MESI_Three_Level/gem5.opt configs/example/se.py -n 8 --num-clusters=2 --num-l2caches=2 --cpu-type=TimingSimpleCPU --ruby -c 'tests/test-progs/hello/bin/arm/linux/hello;tests/test-progs/hello/bin/arm/linux/hello;tests/test-progs/hello/bin/arm/linux/hello;tests/test-progs/hello/bin/arm/linux/hello;tests/test-progs/hello/bin/arm/linux/hello;tests/test-progs/hello/bin/arm/linux/hello;tests/test-progs/hello/bin/arm/linux/hello;tests/test-progs/hello/bin/arm/linux/hello'  

Firstly, we need to compile mesi_two_level cahche coherency protocol,   
Secondly, we should study se.py script. se.py can set the number of cores.(number of cpu or core? we need to understand the real meaning of '-n'
).

To test multicore configuration, we need to prepare benchmark. 
try to arm fs simulation  
3. cache inclusive exclusive non-inclusive   
https://blog.csdn.net/wyj7260/article/details/8515245  
4. how to understand config of system?  
5. ./build/ARM/gem5.opt configs/example/arm/fs_bigLITTLE.py \
    --caches \
    --big-cpus=2 --little-cpus=2\
    --bootloader="$IMG_ROOT/binaries/boot.arm64" \
    --kernel="$IMG_ROOT/binaries/vmlinux.arm64" \
    --disk="$IMG_ROOT/disks/linaro-minimal-aarch64.img"   
