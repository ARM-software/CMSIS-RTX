# Overview {#mainpage}

Keil RTX version 5 (RTX5) is a real-time operating system (RTOS) for Arm Cortex-M and Cortex-A processor-based devices that implements the [CMSIS-RTOS2 API](https://arm-software.github.io/CMSIS_6/latest/RTOS2/html/index.html) as its native interface.

The following sections provide further details:
 - \ref RTX5RevisionHistory lists the  explains how to setup an RTX v5 project in Keil MDK.
 - \ref rtx_system_reqs lists hardware, software, and resource requirements, as well as supported toolchains.
 - \ref theory_of_operation provides general information about the operation of CMSIS-RTOS RTX v5.
 - \ref config_rtx5 describes configuration parameters of CMSIS-RTOS RTX v5.
 - \ref cre_rtx_proj explains how to setup an RTX v5 project in Keil MDK.
\ifnot FuSaRTS
 - \ref creating_RTX5_LIB explains how to build your own CMSIS-RTOS RTX v5 library.
\endif
 - \ref misraCompliance5 describes the violations to the MISRA standard.
 - \ref rtos2_tutorial is an introduction into the usage of Keil RTX5 based on real-life examples.

## Access to CMSIS-RTX {#rtx_access}

CMSIS-RTX kernel is actively maintained in [**CMSIS-RTX GitHub repository**](https://github.com/ARM-software/CMSIS-RTX) and is also provided as a standalone delivery in [CMSIS-Pack format](https://open-cmsis-pack.github.io/Open-CMSIS-Pack-Spec/main/html/index.html).

The table below explains the content of the **ARM::CMSIS-RTX** Pack. 

File/Directory                        | Content 
:-------------------------------------|:---------------------------------------------------------
📄 ARM.CMSIS-RTX.pdsc                 | Pack description file in CMSIS-Pack format
📄 LICENSE                            | License Agreement (Apache 2.0)
📂 CMSIS                              | Software components folder
 ┣ 📂 Documentation                   | A local copy of this documentation
 ┗ 📂 RTOS2                           | RTOS implementation files
&emsp;&nbsp; ┣ 📂 RTX                 | Directory with RTX specific files.
&emsp;&emsp;&nbsp; ┣ 📂 Config        | RTX configuration files **RTX_Config.h** and **RTX_Config.c**
&emsp;&emsp;&nbsp; ┣ 📂 Examples      | Keil MDK uVision example projects
&emsp;&emsp;&nbsp; ┣ 📂 Examples_IAR  | IAR Embedded Workbench Example projects
&emsp;&emsp;&nbsp; ┣ 📂 Include       | Public header files of RTX software component
&emsp;&emsp;&nbsp; ┣ 📂 Library       | Project files to build pre-built libraries
&emsp;&emsp;&nbsp; ┣ 📂 Source        | Private header and source files of RTX software component
&emsp;&emsp;&nbsp; ┣ 📂 Template      | User code templates for creating application projects with CMSIS-RTX
&emsp;&emsp;&nbsp; ┗ 📄 RTX5.scvd     | SCVD file for RTOS-aware debugging with [Component Viewer and Event Recorder](https://arm-software.github.io/CMSIS-View/latest/index.html)
&emsp;&nbsp; ┗ 📂 Source               | Generic RTOS2 source files
&emsp;&emsp;&nbsp; ┗ 📄 os_systick.c   | OS tick implementation using Cortex-M SysTick timer


## License {#rtx_license}

CMSIS-RTX is provided free of charge by Arm under the [Apache 2.0 License](https://raw.githubusercontent.com/ARM-software/CMSIS-RTX/main/LICENSE).
