# Revision History {#RTX5RevisionHistory}

<table class="cmtable" summary="Revision History">
    <tr>
      <th>Version</th>
      <th>Description</th>
    </tr>
    <tr>
      <td>V5.7.0</td>
      <td>
       - Based on CMSIS-RTOS API V2.2.0.
       - Added support for Process Isolation: MPU Protected Zones, Safety Classes, Thread Watchdogs.
       - Requires Device:OS Tick:SysTick component.
       - Reduced component variants: Library (Library_NS replacement), Source (Source_NS replacement).
       - Removed support for legacy Arm Compiler 5.
       - Fixed osMessageQueueGetSpace when called from ISR after osMessageQueuePut and before returning from ISR.
       </td>
    </tr>
    <tr>
      <td>V5.5.5</td>
      <td>
       - Added de-allocation of Arm C library thread data (libspace) when thread is terminated.
       - Updated SysTick implementation for OS Tick (initial count value).
       - Added Thread Entry wrapper (compatible with GDB stack unwind).
      </td>
    </tr>
    <tr>
      <td>V5.5.4</td>
      <td>
       - Fixed potential register R1 corruption when calling OS functions from threads multiple times with same arguments (when using high level compiler optimizations).
       - Fixed timer interval when periodic timer is restarted.
       - Added Floating-point initialization for Arm C Library.
       - Minor code optimizations in \ref osMessageQueuePut / \ref osMessageQueueGet.
      </td>
    </tr>
    <tr>
      <td>V5.5.3</td>
      <td>
       - CVE-2021-27431 vulnerability mitigation.
       - Added OS Initialization for IAR.
       - Fixed \ref osDelay / \ref osDelayUntil error handling.
       - Fixed Round-Robin (timeout value is not reset when switching to higher priority threads).
       - Fixed \ref osThreadJoin (when terminating thread which is waiting to be joined).
       - Fixed Message Queue Data allocation size when using object specific memory allocation.
       - Fixed Mutex priority inversion (when mixing mutexes with and without priority inherit).
       - Enhanced stack overrun checking.
       - Updated \ref osKernelResume handling (processing past sleep ticks).
       - Updated configuration (Event Recorder).
       - Reorganized and optimized IRQ modules.
      </td>
    </tr>
    <tr>
      <td>V5.5.2</td>
      <td>
       - Added support for Cortex-M55.
       - Fixed thread priority restore on mutex acquire timeout (when priority inherit is used).
       - Enhanced support for Armv8-M (specifying thread TrustZone module identifier is optional).
       - Updated configuration default values (Global Dynamic Memory and Thread Stack).
      </td>
    </tr>
    <tr>
      <td>V5.5.1</td>
      <td>
       - Fixed \ref osMutexRelease issue (thread owning multiple mutexes).
       - Improved \ref osThreadJoin robustness (user programing errors).
      </td>
    </tr>
    <tr>
      <td>V5.5.0</td>
      <td>
       - Updated and enhanced generated events (reorganized components).
       - Updated configuration (Event Recorder).
       - Updated Component Viewer (improved performance).
       - Minor code optimizations.
      </td>
    </tr>
    <tr>
      <td>V5.4.0</td>
      <td>
       - Based on CMSIS-RTOS API V2.1.3.
       - Added support for Event Recorder initialization and filter setup.
       - Added support to use RTOS as Event Recorder Time Stamp source.
       - Fixed osDelayUntil longest delay (limited to 2^31-1).
       - Fixed optimization issue when using GCC optimization level 3.
       - Fixed osMemoryPoolAlloc to avoid potential race condition.
       - Restructured exception handling for Cortex-A devices.
       - Minor code optimizations (removed unnecessary checks).
      </td>
    </tr>
    <tr>
      <td>V5.3.0</td>
      <td>
       - Added Object Memory usage counters.
       - Added support for additional external configuration file.
       - Added user configurable names for system threads (Idle and Timer).
       - Added support for OS sections when using ARMCC5.
       - Added callback for MPU integration (experimental)
       - Increased default thread stack sizes to 256 bytes.
       - Fixed stack context display for running thread in SCVD.
       - Enhanced MISRA Compliance.
      </td>
    </tr>
    <tr>
      <td>V5.2.3</td>
      <td>
       - Based on CMSIS-RTOS API V2.1.2.
       - Added TrustZone Module Identifier configuration for Idle and Timer Thread.
       - Moved SVC/PendSV handler priority setup from osKernelInitialize to osKernelStart (User Priority Grouping can be updated after osKernelInitialize but before osKernelStart).
       - Corrected SysTick and PendSV handlers for ARMv8-M Baseline.
       - Corrected memory allocation for stack and data when "Object specific Memory allocation" configuration is used.
       - Added support for ARMv8-M IAR compiler.
      </td>
    </tr>
    <tr>
      <td>V5.2.2</td>
      <td>
       - Corrected IRQ and SVC exception handlers for Cortex-A.
      </td>
    </tr>
    <tr>
      <td>V5.2.1</td>
      <td>
       - Corrected SysTick and SVC Interrupt Priority for Cortex-M.
      </td>
    </tr>
    <tr>
      <td>V5.2.0</td>
      <td>
       - Based on CMSIS-RTOS API V2.1.1.
       - Added support for Cortex-A.
       - Using OS Tick API for RTX Kernel Timer Tick.
       - Fixed potential corruption of terminated threads list.
       - Corrected MessageQueue to use actual message length (before padding).
       - Corrected parameters for ThreadEnumerate and MessageQueueInserted events.
       - Timer Thread creation moved to osKernelStart.
      </td>
    </tr>
    <tr>
      <td>V5.1.0</td>
      <td>
       - Based on CMSIS-RTOS API V2.1.0.
       - Added support for Event recording.
       - Added support for IAR compiler.
       - Updated configuration files: RTX_Config.h for the configuration settings and RTX_config.c for implementing the \ref rtx5_specific.
       - osRtx name-space for RTX specific symbols.
      </td>
    </tr>
    <tr>
      <td>V5.0.0</td>
      <td>
       Initial release compliant to CMSIS-RTOS2.\n
      </td>
    </tr>
</table>
