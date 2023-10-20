# Create an RTX5 Project {#cre_rtx_proj}

\if FuSaRTS
FuSa RTX5 installation and project setup are explained in \ref fusa_rtx_installation.
\endif

\ifnot FuSaRTS
The steps to create a microcontroller application using RTX5 are:
- Create a new project and select a microcontroller device.
- In the Manage Run-Time Environment window, select <b>CMSIS\::CORE</b> and <b>CMSIS\::RTOS2 (API)\::Keil RTX5</b>. You can
  choose to either add RTX as a library (Variant: \b Library) or to add the full source code (Variant: \b Source - required
  if using the <a href="https://www.keil.com/pack/doc/compiler/EventRecorder/html/index.html" target="_blank"><b>Event Recorder</b></a>):

   \image html manage_rte_output.png

- If the <b>Validation Output</b> requires other components to be present, try to use the \b Resolve button.
- Click \b OK. In the \b Project window, you will see the files that have been automatically added to you project, such as
  \b %RTX_Config.h, \b %RTX_Config.c, the library or the source code files, as well as the system and startup files:

   \image html project_window.png

- If using the Variant: \b Source as stated above, you have to assure to use at least C99 compiler mode (Project Options -> C/C++ -> C99 Mode).   
- You can add template files to the project by right-clicking on <b>Source Group 1</b> and selecting
  <b>Add New Item to 'Source Group 1'</b>. In the new window, click on <b>User Code Template</b>. On the right-hand side
  you will see all available template files for CMSIS-RTOS RTX:
  
   \image html add_item.png

- \ref config_rtx5 "Configure" RTX5 to the application's needs using the \b %RTX_Config.h file.

\endif



\if ARMCA 
## Additional requirements for RTX on Cortex-A {#cre_rtx_cortexa}

Cortex-A based microcontrollers are less unified with respect to the interrupt and timer implementations used compared to 
M-class devices. Thus RTX requires additional components when an A-class device is used, namely
<a href="https://arm-software.github.io/CMSIS_6/latest/Core_A/html/group__irq__ctrl__gr.html"><b>CMSIS-Core IRQ Controller (API)</b></a> and \ref CMSIS_RTOS_TickAPI "OS Tick (API)"
implementations. 

\image html manage_rte_cortex-a.png

The default implementations provided along with CMSIS are 
- Arm <a href="https://arm-software.github.io/CMSIS_6/latest/Core_A/html/group__GIC__functions.html">Generic Interrupt Controller (GIC)</a>
- Arm Cortex-A5, Cortex-A9 <a href="https://arm-software.github.io/CMSIS_6/latest/Core_A/html/group__PTM__timer__functions.html">Private Timer (PTIM)</a>
- Arm Cortex-A7 <a href="https://arm-software.github.io/CMSIS_6/latest/Core_A/html/Core_A/html/group__PL1__timer__functions.html">Generic Physical Timer (GTIM)</a>

For devices not implementing GIC, PTIM nor GTIM please refer to the according device family pack and select the
proper implementations.

\endif

## Add support for RTX specific functions {#cre_rtx_proj_specifics}

If you require some of the \ref rtx5_specific "RTX specific functions" in your application code, \#include the
\ref rtx_os_h "header file rtx_os.h". This enables \ref lowPower "low-power" and \ref TickLess "tick-less" operation modes.

## RTX5 Header File {#rtx_os_h}

Every implementation of the CMSIS-RTOS2 API can bring its own additional features. RTX5 adds a couple of
\ref rtx5_specific "functions" for the idle more, for error notifications, and special system timer functions. It is also
using macros for control block and memory sizes.

If you require some of the RTX specific functions in your application code, include the header file rtx_os.h:

```c
#include "rtx_os.h"
```

## Add Event Recorder Visibility {#cre_rtx_proj_er}

\ifnot FuSaRTS
RTX5 interfaces to the <a href="https://www.keil.com/pack/doc/compiler/EventRecorder/html/index.html" target="_blank"><b>Event Recorder</b></a> 
to provide event information which helps you to understand and analyze the operation.

- To use the Event Recorder together with RTX5, select the software component <b>Compiler:Event Recorder</b>.
- Select the \b Source variant of the software component <b>CMSIS:RTOS2 (API):Keil RTX5</b>.

  \image html event_recorder_rte.png "Component selection for Event Recorder"
  
- Enable the related settings under \ref evtrecConfig.
- Build the application code and download it to the debug hardware.
\endif
Once the target application generates event information, it can be viewed in the µVision debugger using the \b Event \b Recorder.

\ifnot FuSaRTS
# Building the RTX5 Library {#creating_RTX5_LIB}

The CMSIS Pack contains a µVision project for building the complete set of RTX5 libraries. This project can also be used as
a reference for building the RTX5 libraries using a tool-chain of your choice.

-# Open the project \b RTX_CM.uvprojx from the pack folder <b>CMSIS/RTOS2/RTX/Library/ARM/MDK</b> in µVision.
-# Select the project target that matches your device's processor core. 
   \n The project provides target configuration for all supported Cortex-M targets supported by RTX5.
-# You can find out about the required preprocessor defines in the dialogs <b>Options for Target - C/C++</b> and
   <b>Options for Target - Asm</b>. Note the need to use at least the C99 compiler mode when building RTX from source.
-# From the <b>Project</b> window you find the list of source files required for a complete library build.
-# Build the library of your choice using \b Project - \b Build \b Target (or press F7).

\image html own_lib_projwin.png "Project with files for Armv8-M Mainline"
\endif