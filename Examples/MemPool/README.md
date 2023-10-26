# MemPool

Simple RTX Kernel based example which shows how to use a memory pool for dynamic object allocation. 

Can be executed on a Fixed Virtual Platform (FVP) simulation model.

## Prerequisites

- [Keil MDK - Professional Edition - V5.38 or higher](https://developer.arm.com/tools-and-software/embedded/keil-mdk) 
  includes IDE, building tools (Arm Compiler for Embedded) and simulators
- alternatively:
  - [CMSIS-Toolbox](https://github.com/Open-CMSIS-Pack/cmsis-toolbox) command-line building tools
  - Toolchains:
    - [Arm Compiler for Embedded](https://developer.arm.com/Tools%20and%20Software/Arm%20Compiler%20for%20Embedded) (commercial) or
    - [Arm GNU Toolchain](https://developer.arm.com/Tools%20and%20Software/GNU%20Toolchain) (community supported) or
    - [Arm LLVM Embedded Toolchain](https://learn.arm.com/install-guides/llvm-embedded/) (community supported) or
    - [IAR Compiler for Arm](https://www.iar.com/ewarm) (commercial)
  - [Fixed Virtual Platforms (FVPs)](https://developer.arm.com/Tools%20and%20Software/Fixed%20Virtual%20Platforms) simulation models

## Build using CMSIS-Toolbox

Build command syntax:

`cbuild MemPool.csolution.yml --update-rte [--toolchain <toolchain>]`

| toolchain     |
|:--------------|
| AC6 (default) |
| GCC           |
| CLANG         |
| IAR           |

Examples:

- Build with AC6
  ```sh
  cbuild MemPool.csolution.yml --update-rte
  ```
- Build with GCC
  ```sh
  cbuild MemPool.csolution.yml --update-rte --toolchain GCC
  ```

- Build with IAR
  ```sh
  cbuild MemPool.csolution.yml --update-rte --toolchain IAR
  ```

## Run using FVP

Run command syntax:

`<model-executable> -f ./fvp_config.txt <image>`

Examples:

- Run on model for Cortex-M3 (AC6 image)
```sh
FVP_MPS2_Cortex-M3 -f ./fvp_config.txt ./out/MemPool/Simulator/MemPool.axf
```

- Run on model for Cortex-M3 (GCC/CLANG image)
```sh
FVP_MPS2_Cortex-M3 -f ./fvp_config.txt ./out/MemPool/Simulator/MemPool.elf
```

- Run on model for Cortex-M3 (IAR image)
```sh
FVP_MPS2_Cortex-M3 -f ./fvp_config.txt ./out/MemPool/Simulator/MemPool.out
```
