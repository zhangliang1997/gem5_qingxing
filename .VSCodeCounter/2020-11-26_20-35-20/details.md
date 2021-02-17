# Details

Date : 2020-11-26 20:35:20

Directory /home/zl/gem5/src/gpu-compute

Total : 69 files,  13208 codes, 5091 comments, 2922 blanks, all 21221 lines

[summary](results.md)

## Files
| filename | language | code | comment | blank | total |
| :--- | :--- | ---: | ---: | ---: | ---: |
| [src/gpu-compute/GPU.py](/src/gpu-compute/GPU.py) | Python | 183 | 38 | 34 | 255 |
| [src/gpu-compute/GPUStaticInstFlags.py](/src/gpu-compute/GPUStaticInstFlags.py) | Python | 64 | 39 | 12 | 115 |
| [src/gpu-compute/LdsState.py](/src/gpu-compute/LdsState.py) | Python | 14 | 30 | 4 | 48 |
| [src/gpu-compute/X86GPUTLB.py](/src/gpu-compute/X86GPUTLB.py) | Python | 45 | 30 | 8 | 83 |
| [src/gpu-compute/comm.cc](/src/gpu-compute/comm.cc) | C++ | 92 | 44 | 19 | 155 |
| [src/gpu-compute/comm.hh](/src/gpu-compute/comm.hh) | C++ | 42 | 70 | 12 | 124 |
| [src/gpu-compute/compute_unit.cc](/src/gpu-compute/compute_unit.cc) | C++ | 1,941 | 297 | 415 | 2,653 |
| [src/gpu-compute/compute_unit.hh](/src/gpu-compute/compute_unit.hh) | C++ | 650 | 269 | 164 | 1,083 |
| [src/gpu-compute/dispatcher.cc](/src/gpu-compute/dispatcher.cc) | C++ | 207 | 105 | 56 | 368 |
| [src/gpu-compute/dispatcher.hh](/src/gpu-compute/dispatcher.hh) | C++ | 45 | 44 | 11 | 100 |
| [src/gpu-compute/exec_stage.cc](/src/gpu-compute/exec_stage.cc) | C++ | 197 | 41 | 25 | 263 |
| [src/gpu-compute/exec_stage.hh](/src/gpu-compute/exec_stage.hh) | C++ | 55 | 46 | 15 | 116 |
| [src/gpu-compute/fetch_stage.cc](/src/gpu-compute/fetch_stage.cc) | C++ | 58 | 32 | 13 | 103 |
| [src/gpu-compute/fetch_stage.hh](/src/gpu-compute/fetch_stage.hh) | C++ | 27 | 40 | 11 | 78 |
| [src/gpu-compute/fetch_unit.cc](/src/gpu-compute/fetch_unit.cc) | C++ | 403 | 138 | 97 | 638 |
| [src/gpu-compute/fetch_unit.hh](/src/gpu-compute/fetch_unit.hh) | C++ | 112 | 123 | 34 | 269 |
| [src/gpu-compute/global_memory_pipeline.cc](/src/gpu-compute/global_memory_pipeline.cc) | C++ | 176 | 77 | 41 | 294 |
| [src/gpu-compute/global_memory_pipeline.hh](/src/gpu-compute/global_memory_pipeline.hh) | C++ | 46 | 83 | 21 | 150 |
| [src/gpu-compute/gpu_command_processor.cc](/src/gpu-compute/gpu_command_processor.cc) | C++ | 100 | 101 | 29 | 230 |
| [src/gpu-compute/gpu_command_processor.hh](/src/gpu-compute/gpu_command_processor.hh) | C++ | 71 | 74 | 21 | 166 |
| [src/gpu-compute/gpu_compute_driver.cc](/src/gpu-compute/gpu_compute_driver.cc) | C++ | 321 | 59 | 39 | 419 |
| [src/gpu-compute/gpu_compute_driver.hh](/src/gpu-compute/gpu_compute_driver.hh) | C++ | 19 | 57 | 8 | 84 |
| [src/gpu-compute/gpu_dyn_inst.cc](/src/gpu-compute/gpu_dyn_inst.cc) | C++ | 767 | 106 | 121 | 994 |
| [src/gpu-compute/gpu_dyn_inst.hh](/src/gpu-compute/gpu_dyn_inst.hh) | C++ | 284 | 98 | 64 | 446 |
| [src/gpu-compute/gpu_exec_context.cc](/src/gpu-compute/gpu_exec_context.cc) | C++ | 28 | 32 | 7 | 67 |
| [src/gpu-compute/gpu_exec_context.hh](/src/gpu-compute/gpu_exec_context.hh) | C++ | 26 | 32 | 9 | 67 |
| [src/gpu-compute/gpu_static_inst.cc](/src/gpu-compute/gpu_static_inst.cc) | C++ | 84 | 32 | 14 | 130 |
| [src/gpu-compute/gpu_static_inst.hh](/src/gpu-compute/gpu_static_inst.hh) | C++ | 211 | 62 | 50 | 323 |
| [src/gpu-compute/gpu_tlb.cc](/src/gpu-compute/gpu_tlb.cc) | C++ | 1,014 | 236 | 274 | 1,524 |
| [src/gpu-compute/gpu_tlb.hh](/src/gpu-compute/gpu_tlb.hh) | C++ | 209 | 150 | 74 | 433 |
| [src/gpu-compute/hsa_queue_entry.hh](/src/gpu-compute/hsa_queue_entry.hh) | C++ | 311 | 113 | 57 | 481 |
| [src/gpu-compute/kernel_code.hh](/src/gpu-compute/kernel_code.hh) | C++ | 116 | 65 | 12 | 193 |
| [src/gpu-compute/lds_state.cc](/src/gpu-compute/lds_state.cc) | C++ | 193 | 97 | 41 | 331 |
| [src/gpu-compute/lds_state.hh](/src/gpu-compute/lds_state.hh) | C++ | 328 | 116 | 95 | 539 |
| [src/gpu-compute/local_memory_pipeline.cc](/src/gpu-compute/local_memory_pipeline.cc) | C++ | 76 | 38 | 22 | 136 |
| [src/gpu-compute/local_memory_pipeline.hh](/src/gpu-compute/local_memory_pipeline.hh) | C++ | 42 | 43 | 16 | 101 |
| [src/gpu-compute/misc.hh](/src/gpu-compute/misc.hh) | C++ | 110 | 39 | 26 | 175 |
| [src/gpu-compute/of_scheduling_policy.hh](/src/gpu-compute/of_scheduling_policy.hh) | C++ | 34 | 36 | 11 | 81 |
| [src/gpu-compute/pool_manager.cc](/src/gpu-compute/pool_manager.cc) | C++ | 6 | 32 | 3 | 41 |
| [src/gpu-compute/pool_manager.hh](/src/gpu-compute/pool_manager.hh) | C++ | 25 | 35 | 9 | 69 |
| [src/gpu-compute/register_file.cc](/src/gpu-compute/register_file.cc) | C++ | 150 | 41 | 33 | 224 |
| [src/gpu-compute/register_file.hh](/src/gpu-compute/register_file.hh) | C++ | 73 | 72 | 27 | 172 |
| [src/gpu-compute/register_manager.cc](/src/gpu-compute/register_manager.cc) | C++ | 90 | 38 | 16 | 144 |
| [src/gpu-compute/register_manager.hh](/src/gpu-compute/register_manager.hh) | C++ | 36 | 42 | 17 | 95 |
| [src/gpu-compute/register_manager_policy.hh](/src/gpu-compute/register_manager_policy.hh) | C++ | 23 | 51 | 13 | 87 |
| [src/gpu-compute/rr_scheduling_policy.hh](/src/gpu-compute/rr_scheduling_policy.hh) | C++ | 25 | 41 | 9 | 75 |
| [src/gpu-compute/scalar_memory_pipeline.cc](/src/gpu-compute/scalar_memory_pipeline.cc) | C++ | 87 | 42 | 21 | 150 |
| [src/gpu-compute/scalar_memory_pipeline.hh](/src/gpu-compute/scalar_memory_pipeline.hh) | C++ | 44 | 52 | 18 | 114 |
| [src/gpu-compute/scalar_register_file.cc](/src/gpu-compute/scalar_register_file.cc) | C++ | 107 | 37 | 21 | 165 |
| [src/gpu-compute/scalar_register_file.hh](/src/gpu-compute/scalar_register_file.hh) | C++ | 52 | 39 | 14 | 105 |
| [src/gpu-compute/schedule_stage.cc](/src/gpu-compute/schedule_stage.cc) | C++ | 647 | 166 | 67 | 880 |
| [src/gpu-compute/schedule_stage.hh](/src/gpu-compute/schedule_stage.hh) | C++ | 108 | 90 | 29 | 227 |
| [src/gpu-compute/scheduler.cc](/src/gpu-compute/scheduler.cc) | C++ | 24 | 32 | 6 | 62 |
| [src/gpu-compute/scheduler.hh](/src/gpu-compute/scheduler.hh) | C++ | 16 | 36 | 8 | 60 |
| [src/gpu-compute/scheduling_policy.hh](/src/gpu-compute/scheduling_policy.hh) | C++ | 22 | 43 | 8 | 73 |
| [src/gpu-compute/scoreboard_check_stage.cc](/src/gpu-compute/scoreboard_check_stage.cc) | C++ | 177 | 88 | 20 | 285 |
| [src/gpu-compute/scoreboard_check_stage.hh](/src/gpu-compute/scoreboard_check_stage.hh) | C++ | 43 | 47 | 14 | 104 |
| [src/gpu-compute/shader.cc](/src/gpu-compute/shader.cc) | C++ | 418 | 88 | 93 | 599 |
| [src/gpu-compute/shader.hh](/src/gpu-compute/shader.hh) | C++ | 174 | 78 | 55 | 307 |
| [src/gpu-compute/simple_pool_manager.cc](/src/gpu-compute/simple_pool_manager.cc) | C++ | 63 | 34 | 14 | 111 |
| [src/gpu-compute/simple_pool_manager.hh](/src/gpu-compute/simple_pool_manager.hh) | C++ | 26 | 38 | 8 | 72 |
| [src/gpu-compute/static_register_manager_policy.cc](/src/gpu-compute/static_register_manager_policy.cc) | C++ | 120 | 42 | 27 | 189 |
| [src/gpu-compute/static_register_manager_policy.hh](/src/gpu-compute/static_register_manager_policy.hh) | C++ | 19 | 34 | 13 | 66 |
| [src/gpu-compute/tlb_coalescer.cc](/src/gpu-compute/tlb_coalescer.cc) | C++ | 319 | 140 | 104 | 563 |
| [src/gpu-compute/tlb_coalescer.hh](/src/gpu-compute/tlb_coalescer.hh) | C++ | 99 | 84 | 34 | 217 |
| [src/gpu-compute/vector_register_file.cc](/src/gpu-compute/vector_register_file.cc) | C++ | 146 | 49 | 21 | 216 |
| [src/gpu-compute/vector_register_file.hh](/src/gpu-compute/vector_register_file.hh) | C++ | 59 | 36 | 15 | 110 |
| [src/gpu-compute/wavefront.cc](/src/gpu-compute/wavefront.cc) | C++ | 1,130 | 175 | 156 | 1,461 |
| [src/gpu-compute/wavefront.hh](/src/gpu-compute/wavefront.hh) | C++ | 179 | 137 | 47 | 363 |

[summary](results.md)