# TrustZone NoRTOS Project

This ARM Cortex-M33 secure/non-secure example project that shows the setup
for TrustZone for ARMv8-M applications. The application uses CMSIS and can
be executed on a Fixed Virtual Platform (FVP) simulation model.

The application demonstrates function calls between secure and non-secure state.

Secure application:

- Setup code and start non-secure application.

Non-secure application:

- Calls a secure function from non-secure state.
- Calls a secure function that call back to a non-secure function.

Output: Variables used in this application can be viewed in the Debugger Watch window.

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

- `NoRTOS.csolution.yml` defines the hardware target and build-types (along with the compiler).
- `CM33_ns.cproject.yml` lists the required packs and defines the source files and software components for the non-secure application.
- `CM33_s.cproject.yml` lists the required packs and defines the source files and software components for the secure application.

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

The `NoRTOS.csolution.yml` solution files defines `Debug` build-type and `FVP` target-type.  
To build this configuration using Arm Compiler 6 toolchain execute the following command:

```bash
cbuild NoRTOS.csolution.yml --packs --context .Debug+FVP --toolchain AC6
```

> **Note**  
> During the build process required packs may be downloaded (`--pack` flag).

By default the project does not specify the toolchain and one can build the project by specifying the AC6, GCC, CLANG or IAR toolchain.

Examples:

- Build with GCC

  ```sh
  cbuild NoRTOS.csolution.yml --packs --context .Debug+FVP --toolchain GCC
  ```

- Build with IAR

  ```sh
  cbuild NoRTOS.csolution.yml --packs --context .Debug+FVP --toolchain IAR
  ```
