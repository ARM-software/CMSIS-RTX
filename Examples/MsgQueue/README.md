# MsgQueue

Simple RTX Kernel based example which shows how to use a message queue to send data from one thread to another.
The message receiver thread prints the message contents to the debug output window. 

Can be executed on a Fixed Virtual Platform (FVP) simulation model.

## Prerequisites

- [Arm Keil MDK v6](https://developer.arm.com/tools-and-software/embedded/keil-mdk)
  includes IDE, building tools (Arm Compiler for Embedded) and simulators
- alternatively:
  - [CMSIS-Toolbox](https://github.com/Open-CMSIS-Pack/cmsis-toolbox) command-line building tools
  - Toolchains:
    - [Arm Compiler for Embedded](https://developer.arm.com/downloads/view/ACOMPE) (commercial) or
    - [Arm GNU Toolchain](https://developer.arm.com/downloads/-/arm-gnu-toolchain-downloads) (community supported) or
    - [Arm LLVM Embedded Toolchain](https://github.com/ARM-software/LLVM-embedded-toolchain-for-Arm) (community supported) or
    - [IAR Compiler for Arm](https://www.iar.com/embedded-development-tools) (commercial)
  - [Fixed Virtual Platforms (FVPs)](https://developer.arm.com/Tools%20and%20Software/Fixed%20Virtual%20Platforms) simulation models

## Project Structure

The project is generated using the [CMSIS-Toolbox](https://open-cmsis-pack.github.io/cmsis-toolbox/) and
is defined in [`csolution`](https://open-cmsis-pack.github.io/cmsis-toolbox/YML-Input-Format/) format:

- `MsgQueue.csolution.yml` defines the hardware target and build-types (along with the compiler).
- `MsgQueue.cproject.yml` lists the required packs and defines the source files and software components.

## Build project in VS Code

[Arm Keil Studio Pack Extensions](https://marketplace.visualstudio.com/items?itemName=Arm.keil-studio-pack) for VS Code
include all required tools and interfaces to build the `csolution` projects.

> - See [Arm Keil Studio for VS Code Extensions User Guide](https://mdk-packs.github.io/vscode-cmsis-solution-docs/index.html)
>   for more information about using the Keil Studio extensions.

To build a project using Keil Studio extensions open [CMSIS view](https://mdk-packs.github.io/vscode-cmsis-solution-docs/userinterface.html),
open "Manage Solution Settings" view and verify that "Active Target", "Active Projects" and "Build Type" are selected.

You can execute the build by [selecting "Build"](https://mdk-packs.github.io/vscode-cmsis-solution-docs/userinterface.html#3-actions-available-through-the-cmsis-view)
from the CMSIS view.

## Build Project from the Command Line

[CMSIS-Toolbox](https://open-cmsis-pack.github.io/cmsis-toolbox/) provides [cbuild](https://open-cmsis-pack.github.io/cmsis-toolbox/build-tools/)
command-line tool that builds `csolution` projects.

The `MsgQueue.csolution.yml` solution files defines `Debug` build-type and `FVP` target-type.  
To build this configuration using Arm Compiler 6 toolchain execute the following command:

```bash
cbuild MsgQueue.csolution.yml --packs --context MsgQueue.Debug+FVP --toolchain AC6
```

> **Note**  
> During the build process required packs may be downloaded (`--pack` flag).

By default the project does not specify the toolchain and one can build the project by specifying the AC6, GCC, CLANG or IAR toolchain.

Examples:

- Build with GCC

  ```sh
  cbuild MsgQueue.csolution.yml --packs --context MsgQueue.Debug+FVP --toolchain GCC
  ```

- Build with IAR

  ```sh
  cbuild MsgQueue.csolution.yml --packs --context MsgQueue.Debug+FVP --toolchain IAR
  ```

## Run using FVP

The project is configured for execution on Arm Virtual Hardware which removes the requirement for a physical hardware board.

To execute application image on Arm Virtual Hardware use below command syntax:

`<model-executable> -f ./fvp_config.txt <image>`

Examples:

- Run on model for Cortex-M3 (AC6 image)

  ```sh
  FVP_MPS2_Cortex-M3 -f ./fvp_config.txt ./out/MsgQueue/FVP/Debug/MsgQueue.axf
  ```

- Run on model for Cortex-M3 (GCC/CLANG image)

  ```sh
  FVP_MPS2_Cortex-M3 -f ./fvp_config.txt ./out/MsgQueue/FVP/Debug/MsgQueue.elf
  ```

- Run on model for Cortex-M3 (IAR image)

  ```sh
  FVP_MPS2_Cortex-M3 -f ./fvp_config.txt ./out/MsgQueue/FVP/Debug/MsgQueue.out
  ```
