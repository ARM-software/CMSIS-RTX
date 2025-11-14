# Overview

Keil RTX version 5 (RTX5) is a real-time operating system (RTOS) for Arm Cortex-M and Cortex-A processor-based devices
that implements the [**CMSIS-RTOS2 API**](https://arm-software.github.io/CMSIS_6/latest/RTOS2/index.html) as its native
interface.

The following sections of the documentation provide further details:

- [Create an RTX5 project](https://arm-software.github.io/CMSIS-RTX/latest/cre_rtx_proj.html) explains how to setup an
  RTX v5 project in Keil MDK.
- [Configure RTX5](https://arm-software.github.io/CMSIS-RTX/latest/config_rtx5.html) describes configuration parameters
  of CMSIS-RTOS RTX v5.
- [Tutorial](https://arm-software.github.io/CMSIS-RTX/latest/rtos2_tutorial.html) is an introduction into the usage of
  Keil RTX5 based on real-life examples.
- [Theory of operation](https://arm-software.github.io/CMSIS-RTX/latest/theory_of_operation.html) provides general
  information about the operation of CMSIS-RTOS RTX v5.
- [Building the RTX5 library](https://arm-software.github.io/CMSIS-RTX/latest/cre_rtx_proj.html#creating_RTX5_LIB)
  explains how to build your own CMSIS-RTOS RTX v5 library.
- [MISRA C:2012 compliance](https://arm-software.github.io/CMSIS-RTX/latest/misraCompliance5.html) describes the
  violations to the MISRA standard.
- [Revision history](https://arm-software.github.io/CMSIS-RTX/latest/rev_hist.html) lists the changes made in each
  version of CMSIS-RTX.
- [System requirements](https://arm-software.github.io/CMSIS-RTX/latest/rtx_system_reqs.html) lists hardware, software,
  and resource requirements, as well as supported toolchains.

## CMSIS-Pack contents

```
  📦
  ┣ 📂 Config                   Configuration file templates
  ┣ 📂 Documentation            Pre-built documentation
  ┣ 📂 Examples                 Example projects (MDK uVision and CMSIS-Toolbox)
  ┣ 📂 Include                  Public header files of RTX software component
  ┣ 📂 Library                  Project files to build pre-built libraries
  ┣ 📂 Source                   Private header and source files of RTX software component
  ┣ 📂 Template                 User code template files
  ┣ 📄 ARM.CMSIS-RTX.pdsc       Pack description file
  ┣ 📄 ARM.CMSIS-RTX.sha1       Checksums of all the files
  ┣ 📄 LICENSE                  Apache 2.0 license file
  ┗ 📄 RTX5.scvd                Software Component View Description file for Keil RTX5
```

## Links

- [Documentation](https://arm-software.github.io/CMSIS-RTX/latest/index.html)
- [Examples](https://github.com/Arm-Examples/#cmsis-toolbox-examples)
- [Repository](https://github.com/ARM-software/CMSIS-RTX)
- [Issues](https://github.com/ARM-software/CMSIS-RTX/issues)
