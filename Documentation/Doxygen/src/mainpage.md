# Overview {#mainpage}

Keil RTX version 5 (RTX5) is a real-time operating system (RTOS) for Arm Cortex-M and Cortex-A processor-based devices that implements the [**CMSIS-RTOS2 API**](https://arm-software.github.io/CMSIS_6/latest/RTOS2/index.html) as its native interface.

The following sections provide further details:

- \ref rev_hist lists the changes made in each version of CMSIS-RTX.
- \ref rtx_system_reqs lists hardware, software, and resource requirements, as well as supported toolchains.
- \ref theory_of_operation provides general information about the operation of CMSIS-RTOS RTX v5.
- \ref cre_rtx_proj explains how to setup an RTX v5 project in Keil MDK.
\ifnot FuSaRTS
- \ref creating_RTX5_LIB explains how to build your own CMSIS-RTOS RTX v5 library.
\endif
- \ref config_rtx5 describes configuration parameters of CMSIS-RTOS RTX v5.
- \ref misraCompliance5 describes the violations to the MISRA standard.
- \ref rtos2_tutorial is an introduction into the usage of Keil RTX5 based on real-life examples.

## Access to CMSIS-RTX {#rtx_access}

CMSIS-RTX kernel is actively maintained in [**CMSIS-RTX GitHub repository**](https://github.com/ARM-software/CMSIS-RTX) and is also provided as a standalone [**CMSIS-RTX pack**](https://www.keil.arm.com/packs/cmsis-rtx-arm/versions/) in the [CMSIS-Pack format](https://open-cmsis-pack.github.io/Open-CMSIS-Pack-Spec/main/html/index.html).

> **Note**
>
> - CMSIS-RTX replaces and extends RTX5 implementation previously provided as part of *ARM::CMSIS* pack.
> - See [Migrating projects from CMSIS v5 to CMSIS v6](https://learn.arm.com/learning-paths/microcontrollers/project-migration-cmsis-v6) for a guidance on updating existing projects to CMSIS-RTX.

The table below explains the content of the **ARM::CMSIS-RTX** Pack.

 File/Directory        | Content
:----------------------|:---------------------------------------------------------
 📂 Config             | RTX configuration files **RTX_Config.h** and **RTX_Config.c**
 📂 Documentation      | A local copy of this documentation
 📂 Examples           | Example projects (MDK uVision and CMSIS-Toolbox)
 📂 Include            | Public header files of RTX software component
 📂 Library            | Library project files and pre-built libraries
 📂 Source             | Private header and source files of RTX software component
 📂 Template           | User code templates for creating application projects with CMSIS-RTX
 📄 ARM.CMSIS-RTX.pdsc | Pack description file in CMSIS-Pack format
 📄 LICENSE            | License Agreement (Apache 2.0)
 📄 RTX5.scvd          | SCVD file for RTOS-aware debugging with [Component Viewer and Event Recorder](https://arm-software.github.io/CMSIS-View/latest/index.html)

See [CMSIS Documentation](https://arm-software.github.io/CMSIS_6/) for an overview of CMSIS software components, tools and specifications.

## Security Considerations {#rtx_security}

RTX5 has not been designed with strong security considerations in mind. The implementation has a focus on high code
quality assured by applying coding rules according to [MISRA-C:2012](https://misra.org.uk/) and checking compliance
using [CodeQL](https://codeql.github.com/). The analysis results are published on
[GitHub Code scanning page](https://github.com/ARM-software/CMSIS-RTX/security/code-scanning).

Users of RTX5 are strongly advised to run security analysis for their applications if any kind of exposure is given.
The main security assumption made for RTX5 is no untrusted code is ever executed on a device. This assumption is
expected to apply to the vast majority of use cases of an embedded RTOS like RTX5.

For use cases (such as firmware update) where the firmware image (or parts of it) can be modified/updated by an
untrusted user, the application developer must implement appropriate security measures to prevent execution of
untrusted code.

For use cases where executing untrusted code is required (like customizable plugins), the application developer must
carfully analyze the execution sandbox boundaries. Given that untrusted code is executed within an unprivileged
RTX5 thread, it must be assured that no RTOS operation can be used to run untrusted code as part of a service call
nor interrupt routine, see \ref safetyConfig_safety.

## License {#rtx_license}

CMSIS-RTX is provided free of charge by Arm under the [Apache 2.0 License](https://raw.githubusercontent.com/ARM-software/CMSIS-RTX/main/LICENSE).
