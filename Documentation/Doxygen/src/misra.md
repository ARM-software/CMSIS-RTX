# MISRA C:2012 Compliance {#misraCompliance5}

The RTX5 C source files use [MISRA C:2012](https://misra.org.uk/) guidelines as underlying coding standard.

For MISRA validation, [PC-lint](https://pclintplus.com) V9.00L is used with configuration for Arm Compiler V6. Refer to [Setup for PC-Lint](https://developer.arm.com/documentation/101407/latest/Utilities/PC-lint-and-MISRA-Validation) for more information.

The PC-Lint is configured with the following configuration file: RTX_Library.lnt:

- MISRA rules setup and configuration:
  - MISRQ_C_2012_Config.lnt; all rules enabled
  - includes definition file: au-misra3.lnt (12-Jun-2014)
- Arm Compiler V6 configuration file: co-ARMCC-6.lnt (20-Mar-2017)

- Additional compiler configuration:

  ```
   +d__has_builtin(x)=(0)
   -esym(526,__builtin_*)
   -esym(628,__builtin_*)
   -esym(718,__builtin_*)
   -esym(746,__builtin_*)
   -sem(__CLZ, pure)
   +doffsetof(t,m)=((size_t)&((t*)0)->m)
   -emacro((413,923,9078),offsetof)
  ```

- Additional project configuration:

  ```
    --uEVR_RTX_DISABLE
  ```

The C source code is annotated with PC-Lint control comments to allows MISRA deviations. These deviations with the underlying design decisions are described in the following.

## Deviations {#misra_deviations}

The RTX source code has the following deviations from MISRA:

- \ref MISRA_1
- \ref MISRA_2
- \ref MISRA_3
- \ref MISRA_4
- \ref MISRA_5
- \ref MISRA_6
- \ref MISRA_7
- \ref MISRA_8
- \ref MISRA_9
- \ref MISRA_10
- \ref MISRA_11
- \ref MISRA_12
- \ref MISRA_13

All source code deviations are clearly marked and in summary these deviations affect the following MISRA rules:

- [MISRA 2012 Directive  4.9,  advisory]: A function should be used in preference to a function-like macro where yet are interchangeable
- [MISRA 2012 Rule       1.3,  required]: There shall be no occurrence of undefined or critical unspecified behavior
- [MISRA 2012 Rule      10.3,  required]: Expression assigned to a narrower or different essential type
- [MISRA 2012 Rule      10.5,  advisory]: Impermissible cast; cannot cast from 'essentially unsigned' to 'essentially enum\<i\>'
- [MISRA 2012 Rule      11.1,  required]: Conversions shall not be performed between a pointer to a function and any other type
- [MISRA 2012 Rule      11.3,  required]: A cast shall not be performed between a pointer to object type and a pointer to a different object type
- [MISRA 2012 Rule      11.4,  advisory]: A conversion should not be performed between a pointer to object and an integer type
- [MISRA 2012 Rule      11.5,  advisory]: A conversion should not be performed from pointer to void into pointer to object
- [MISRA 2012 Rule      11.6,  required]: A cast shall not be performed between pointer to void and an arithmetic type
- [MISRA 2012 Rule      15.5,  advisory]: A function should have a single point of exit at the end
- [MISRA 2012 Rule      20.10, advisory]: The # and ## preprocessor operators should not be used

In the following all deviations are described in detail.

## [MISRA Note 1]: Return statements for parameter checking {#MISRA_1}

Return statements are used at the beginning of several functions to validate parameter values and object states.

The function returns immediately without any side-effects and typically an error status is set. This structure keeps the source code better structured and easier to understand.

This design decision implies the following MISRA deviation:

- [MISRA 2012 Rule      15.5,  advisory]: A function should have a single point of exit at the end

All locations in the source code are marked with:

```
  //lint -e{904} "Return statement before end of function" [MISRA Note 1]
```

## [MISRA Note 2]: Object identifiers are void pointers {#MISRA_2}

CMSIS-RTOS is independent of an underlying RTOS implementation. The object identifiers are therefore defined as void pointers to:

- allow application programs that are agnostic from an underlying RTOS implementation.
- avoid accidentally accesses an RTOS control block from an application program.

This design decisions imply the following MISRA deviations:

- [MISRA 2012 Rule      11.3,  required]: A cast shall not be performed between a pointer to object type and a pointer to a different object type
- [MISRA 2012 Rule      11.5,  advisory]: A conversion should not be performed from pointer to void into pointer to object

All locations in the source code are marked with:

```
  //lint -e{9079} -e{9087} "cast from pointer to void to pointer to object type" [MISRA Note 2]
```

In the RTX5 implementation the required pointer conversions are implemented in the header file rtx_lib.h with the following inline functions:

```c
osRtxThread_t       *osRtxThreadId (osThread_t thread_id);
osRtxTimer_t        *osRtxTimerId (osTimer_t timer_id);
osRtxEventFlags_t   *osRtxEventFlagsId (osEventFlags_t ef_id);
osRtxMutex_t        *osRtxMutexId (osMutex_t mutex_id);
osRtxSemaphore_t    *osRtxSemaphoreId (osSemaphore_t semaphore_id);
osRtxMemoryPool_t   *osRtxMemoryPoolId (osMemoryPoolId_t mp_id);
osRtxMessageQueue_t *osRtxMessageQueueId(osMessageQueueId_t mq_id);
```

## [MISRA Note 3]: Conversion to unified object control blocks {#MISRA_3}

RTX uses a unified object control block structure that contains common object members.

The unified control blocks use a fixed layout at the beginning of the structure and starts always with an object identifier. This allows common object functions that receive a pointer to a unified object control block and reference only the pointer or the members in the fixed layout. Using common object functions and data (for example the ISR queue) reduces code complexity and keeps the source code better structured.  Refer also to \ref MISRA_4

This design decisions imply the following MISRA deviations:

- [MISRA 2012 Rule      11.3,  required]: A cast shall not be performed between a pointer to object type and a pointer to a different object type
- [MISRA 2012 Rule      11.5,  advisory]: A conversion should not be performed from pointer to void into pointer to object

All locations in the source code are marked with:

```
  //lint -e{9079} -e{9087} "cast from pointer to void to pointer to object type" [MISRA Note 3]
```

In the RTX5 implementation the required pointer conversions are implemented in the header file \em rtx_lib.h with the following inline function:

```c
osRtxObject_t *osRtxObject (void *object);
```

## [MISRA Note 4]: Conversion from unified object control blocks {#MISRA_4}

RTX uses a unified object control block structure that contains common object members. Refer to \ref MISRA_3 for more information.

To process specific control block data, pointer conversions are required.

This design decisions imply the following MISRA deviations:

- [MISRA 2012 Rule       1.3,  required]: There shall be no occurrence of undefined or critical unspecified behavior
- [MISRA 2012 Rule      11.3,  required]: A cast shall not be performed between a pointer to object type and a pointer to a different object type

In addition PC-Lint issues:

- Info  826: Suspicious pointer-to-pointer conversion (area too small)

All locations in the source code are marked with:

```
  //lint -e{740} -e{826} -e{9087} "cast from pointer to generic object to specific object" [MISRA Note 4]
```

In the RTX5 source code the required pointer conversions are implemented in the header file \em rtx_lib.h with the following inline functions:

```c
osRtxThread_t       *osRtxThreadObject (osRtxObject_t *object);
osRtxTimer_t        *osRtxTimerObject (osRtxObject_t *object);
osRtxEventFlags_t   *osRtxEventFlagsObject (osRtxObject_t *object);
osRtxMutex_t        *osRtxMutexObject (osRtxObject_t *object);
osRtxSemaphore_t    *osRtxSemaphoreObject (osRtxObject_t *object);
osRtxMemoryPool_t   *osRtxMemoryPoolObject (osRtxObject_t *object);
osRtxMessageQueue_t *osRtxMessageQueueObject (osRtxObject_t *object);
osRtxMessage_t      *osRtxMessageObject (osRtxObject_t *object);
```

## [MISRA Note 5]: Conversion to object types {#MISRA_5}

The RTX5 kernel has common memory management functions that use void pointers. These memory allocation functions return a void pointer which is correctly aligned for object types.

This design decision implies the following MISRA deviations:

- [MISRA 2012 Rule      11.5,  advisory]: A conversion should not be performed from pointer to void into pointer to object

All locations in the source code are marked with:

```
  //lint -e{9079} "conversion from pointer to void to pointer to other type" [MISRA Note 5]
```

Code example:

```c
  os_thread_t  *thread;
   :
  //lint -e{9079} "conversion from pointer to void to pointer to other type" [MISRA Note 5]
  thread = osRtxMemoryPoolAlloc(osRtxInfo.mpi.thread);
```

## [MISRA Note 6]: Conversion from user provided storage {#MISRA_6}

CMSIS-RTOS2 and RTX5 support user provided storage for object control blocks, stack, and data storage. The API uses void pointers to define the location of this user provided storage. It is therefore
required to cast the void pointer to underlying storage types. Alignment restrictions of user provided storage are checked before accessing memory. Refer also to \ref MISRA_7.

This design decisions imply the following MISRA deviations:

- [MISRA 2012 Rule      11.3,  required]: A cast shall not be performed between a pointer to object type and a pointer to a different object type
- [MISRA 2012 Rule      11.5,  advisory]: A conversion should not be performed from pointer to void into pointer to object

All locations in the source code are marked with:

```
  //lint -e{9079} "conversion from pointer to void to pointer to other type" [MISRA Note 6]
```

Code example:

```c
static osTimerId_t svcRtxTimerNew (osTimerFunc_t func, osTimerType_t type, void *argument, const osTimerAttr_t *attr) {
  os_timer_t *timer;
    :
  if (attr != NULL) {
    :
    //lint -e{9079} "conversion from pointer to void to pointer to other type" [MISRA Note 6]
    timer = attr->cb_mem;
    :
```

## [MISRA Note 7]: Check for proper pointer alignment {#MISRA_7}

RTX5 verifies the alignment of user provided storage for object control blocks, stack, and data storage. Refer also to \ref MISRA_6 for more information.

This design decision implies the following MISRA deviations:

- [MISRA 2012 Rule      11.4,  advisory]: A conversion should not be performed between a pointer to object and an integer type
- [MISRA 2012 Rule      11.6,  required]: A cast shall not be performed between pointer to void and an arithmetic type

All locations in the source code are marked with:

```
  //lint -e{923} -e{9078} "cast from pointer to unsigned int" [MISRA Note 7]
```

Code example:

```c
static osThreadId_t svcRtxThreadNew (osThreadFunc_t func, void *argument, const osThreadAttr_t *attr) {
    :
  void         *stack_mem;
    :
  if (stack_mem != NULL) {
    //lint -e{923} "cast from pointer to unsigned int" [MISRA Note 7]
    if ((((uint32_t)stack_mem & 7U) != 0U) || (stack_size == 0U)) {
    :
```

## [MISRA Note 8]: Memory allocation management {#MISRA_8}

RTX5 implements memory allocation functions which require pointer arithmetic to manage memory.

The structure with the type \em mem_block_t that is used to menage memory allocation blocks is defined in \em rtx_memory.c

This design decision implies the following MISRA deviations:

- [MISRA 2012 Rule      11.4,  advisory]: A conversion should not be performed between a pointer to object and an integer type
- [MISRA 2012 Rule      11.6,  required]: A cast shall not be performed between pointer to void and an arithmetic type

All locations in the source code are marked with:

```
  //lint -e{923} -e{9078} "cast from pointer to unsigned int" [MISRA Note 8]
```

The required pointer arithmetic is implemented in \em rtx_memory.c with the following function:

```c
__STATIC_INLINE mem_block_t *MemBlockPtr (void *mem, uint32_t offset) {
  uint32_t     addr;
  mem_block_t *ptr;

  //lint --e{923} --e{9078} "cast between pointer and unsigned int" [MISRA Note 8]
  addr = (uint32_t)mem + offset;
  ptr  = (mem_block_t *)addr;

  return ptr;
}
```

## [MISRA Note 9]: Pointer conversions for register access {#MISRA_9}

The CMSIS-Core peripheral register blocks are accessed using a structure. The memory address of this structure is specified as unsigned integer number. Pointer conversions are required to access the specific registers.

This design decision implies the following MISRA deviations:

- [MISRA 2012 Rule      11.4,  advisory]: A conversion should not be performed between a pointer to object and an integer type
- [MISRA 2012 Rule      11.6,  required]: A cast shall not be performed between pointer to void and an arithmetic type

All locations in the source code are marked with:

```
  //lint -emacro((923,9078),SCB) "cast from unsigned long to pointer" [MISRA Note 9]
```

Code example:

```c
#define SCS_BASE  (0xE000E000UL)
#define SCB      ((SCB_Type *)SCB_BASE)
typedef struct {...} SCB_Type;

SCB->... = ...;
```

## [MISRA Note 10]: SVC calls use function-like macros {#MISRA_10}

RTX5 is using SVC (Service Calls) to switch between thread mode (for user code execution) and handler mode (for RTOS kernel execution).

The SVC function call mechanism is implemented with assembly instructions to construct the code for SVC. The source code uses C macros and are designed as C function-like macros to generate parameter passing for variables depending on macro parameters. An alternative replacement code would be complex. The C macros use multiple '##' operators however it has been verified that the order of evaluation is irrelevant and result of macro expansion is always predictable.

This design decision implies the following MISRA deviations:

- [MISRA 2012 Directive  4.9,  advisory]: A function should be used in preference to a function-like macro where yet are interchangeable
- [MISRA 2012 Rule       1.3,  required]: There shall be no occurrence of undefined or critical unspecified behavior
- [MISRA 2012 Rule      20.10, advisory]: The # and ## preprocessor operators should not be used

The relevant source code is in the file \em rtx_core_cm.h and is marked with:

```
  //lint -save -e9023 -e9024 -e9026 "Function-like macros using '#/##'" [MISRA Note 10]
```

## [MISRA Note 11]: SVC calls use assembly code {#MISRA_11}

The SVC (Service Call) functions are constructed as a mix of C and inline assembly as it is required to access CPU registers for parameter passing. The function parameters are mapped to the CPU registers R0..R3 and SVC function number to CPU register R12 (or R7). For assembly inter-working the function parameters are casted to unsigned int values.

The function return value after SVC call is mapped to the CPU register R0. Return value is casted from unsigned int to the target value.

It has been verified that this method has no side-effects and is well defined.

This design decision implies the following MISRA deviations:

- [MISRA 2012 Rule      10.3,  required]: Expression assigned to a narrower or different essential type
- [MISRA 2012 Rule      10.5,  advisory]: Impermissible cast; cannot cast from 'essentially unsigned' to 'essentially enum\<i\>'
- [MISRA 2012 Rule      11.1,  required]: Conversions shall not be performed between a pointer to a function and any other type
- [MISRA 2012 Rule      11.4,  advisory]: A conversion should not be performed between a pointer to object and an integer type
- [MISRA 2012 Rule      11.6,  required]: A cast shall not be performed between pointer to void and an arithmetic type

SVC functions are marked as library modules and not processed by PC-lint. The relevant source code is marked with:

```
  //lint ++flb "Library Begin" [MISRA Note 11]
    :
  //lint --flb "Library End"
```

Code example:

```c
//  Service Calls definitions
//lint ++flb "Library Begin" [MISRA Note 11]
SVC0_1(Delay,      osStatus_t, uint32_t)
SVC0_1(DelayUntil, osStatus_t, uint32_t)
//lint --flb "Library End"
```

PC-lint does not process ASM input/output operand lists and therefore falsely identifies issues:

- Last value assigned to variable not used
- Symbol not subsequently referenced

\todo: what has been done to mitigate that?

## [MISRA Note 12]: Usage of exclusive access instructions {#MISRA_12}

The RTX5 implementation uses the CPU instructions LDREX and STREX (when supported by the processor) to implement atomic operations.

These atomic operations eliminate the requirement for interrupt lock-outs. The atomic operations are implemented using inline assembly.

PC-lint cannot process assembler instructions including the input/output operand lists and therefore falsely identifies issues:

- Symbol not initialized
- Symbol not subsequently referenced
- Symbol not referenced
- Pointer parameter could be declared as pointing to const

It has been verified that atomic operations have no side-effects and are well defined.

The functions that implement atomic instructions are marked as library modules and not processed by PC-lint. The relevant source code is marked with:

```
  //lint ++flb "Library Begin" [MISRA Note 12]
    :
  //lint --flb "Library End"
```

## [MISRA Note 13]: Usage of Event Recorder {#MISRA_13}

The Event Recorder is a generic event logger and the related functions are called to record an event.

The function parameters are 32-bit id, 32-bit values, pointer to void (data) and are recorded as 32-bit numbers. The parameters for the Event Recorder may require cast operations to unsigned int which however has no side-effects and is well defined.

The return value indicates success or failure. There is no need to check the return value since no action is taken when an Event Recorder function fail. The EventID macro (part of external Event Recorder) constructs the ID based on input parameters which are shifted, masked with '&' and combined with '|'. Zero value input parameters are valid and cause zero used with '&' and '|'.

The usage of the Event Recorder implies the following MISRA deviations:

- [MISRA 2012 Rule      11.1,  required]: Conversions shall not be performed between a pointer to a function and any other type
- [MISRA 2012 Rule      11.4,  advisory]: A conversion should not be performed between a pointer to object and an integer type
- [MISRA 2012 Rule      11.6,  required]: A cast shall not be performed between pointer to void and an arithmetic type

In addition PC-Lint issues:

- Info  835: A zero has been given as left argument to operator '&'
- Info  845: The right argument to operator '|' is certain to be 0

The functions that call the Event Recorder are in the module \em rtx_evr.c and the related PC-Lint messages are disabled with:

```
  //lint -e923 -e9074 -e9078 -emacro((835,845),EventID) [MISRA Note 13]
```
