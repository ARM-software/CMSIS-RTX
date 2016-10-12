/*
 * Copyright (c) 2013-2016 ARM Limited. All rights reserved.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the License); you may
 * not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an AS IS BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * -----------------------------------------------------------------------------
 *
 * Project:     CMSIS-RTOS RTX
 * Title:       RTX Library Configuration
 *
 * -----------------------------------------------------------------------------
 */

#include "cmsis_os2.h"
#include "rtx_os.h"


// Thread Configuration
// ====================

#if (((OS_STACK_SIZE & 7) != 0) || (OS_STACK_SIZE < 72))
#error "Invalid default Thread Stack size!"
#endif

#if (((OS_IDLE_THREAD_STACK_SIZE & 7) != 0) || (OS_IDLE_THREAD_STACK_SIZE < 72))
#error "Invalid Idle Thread Stack size!"
#endif


#if (OS_THREAD_OBJ_MEM != 0)

#define OS_THREAD_DEF_STACK_NUM (OS_THREAD_NUM - OS_THREAD_USER_STACK_NUM)

#if ((OS_THREAD_NUM == 0) || (OS_THREAD_NUM < OS_THREAD_USER_STACK_NUM))
#error "Invalid number of user Threads!"
#endif

#if ((OS_THREAD_USER_STACK_NUM != 0) && (OS_THREAD_USER_STACK_SIZE == 0))
#error "Total Stack size must not be zero!"
#endif

#if ((OS_THREAD_USER_STACK_SIZE != 0) && \
   (((OS_THREAD_USER_STACK_SIZE & 7) != 0) || \
     (OS_THREAD_USER_STACK_SIZE < (72*OS_THREAD_USER_STACK_NUM))))
#error "Invalid total Stack size!"
#endif

// Thread Control Blocks
static os_thread_t os_thread_cb[OS_THREAD_NUM] \
__attribute__((section(".bss.os.thread.cb")));

// Thread Default Stack
#if (OS_THREAD_DEF_STACK_NUM != 0)
static uint64_t os_thread_def_stack[OS_THREAD_DEF_STACK_NUM*(OS_STACK_SIZE/8)] \
__attribute__((section(".bss.os.thread.stack")));
#endif

// Memory Pool for Thread Control Blocks
static os_mp_info_t os_mpi_thread \
__attribute__((section(".bss.os.thread.mpi"))) =
{ (uint32_t)OS_THREAD_NUM, 0U, (uint32_t)os_ThreadCbSize, &os_thread_cb, NULL, NULL };

// Memory Pool for Thread Default Stack
#if (OS_THREAD_DEF_STACK_NUM != 0)
static os_mp_info_t os_mpi_def_stack \
__attribute__((section(".bss.os.thread.mpi"))) =
{ (uint32_t)OS_THREAD_DEF_STACK_NUM, 0U, (uint32_t)OS_STACK_SIZE, &os_thread_def_stack, NULL, NULL };
#endif

// Memory Pool for Thread Stack
#if (OS_THREAD_USER_STACK_SIZE != 0)
static uint64_t os_thread_stack[OS_THREAD_USER_STACK_SIZE/8] \
__attribute__((section(".bss.os.thread.stack")));
#endif

#endif  // (OS_THREAD_OBJ_MEM != 0)


// Stack overrun checking
#if (OS_STACK_CHECK == 0)
// Override library function
void os_ThreadStackCheck (void);
void os_ThreadStackCheck (void) {}
#endif


// Idle Thread Control Block
static os_thread_t os_idle_thread_cb \
__attribute__((section(".bss.os.thread.cb")));

// Idle Thread Stack
static uint64_t os_idle_thread_stack[OS_IDLE_THREAD_STACK_SIZE/8] \
__attribute__((section(".bss.os.thread.stack")));

// Idle Thread Attributes
static const osThreadAttr_t os_idle_thread_attr = {
  NULL,
  osThreadDetached,
  &os_idle_thread_cb,
  (uint32_t)sizeof(os_idle_thread_cb),
  &os_idle_thread_stack,
  (uint32_t)sizeof(os_idle_thread_stack),
  osPriorityIdle,
  0U, 0U
};


// Timer Configuration
// ===================

#if (OS_TIMER_OBJ_MEM != 0)

#if (OS_TIMER_NUM == 0)
#error "Invalid number of Timer objects!"
#endif

// Timer Control Blocks
static os_timer_t os_timer_cb[OS_TIMER_NUM] \
__attribute__((section(".bss.os.timer.cb")));

// Memory Pool for Timer Control Blocks
static os_mp_info_t os_mpi_timer \
__attribute__((section(".bss.os.timer.mpi"))) =
{ (uint32_t)OS_TIMER_NUM, 0U, (uint32_t)os_TimerCbSize, &os_timer_cb, NULL, NULL };

#endif  // (OS_TIMER_OBJ_MEM != 0)


#if ((OS_TIMER_THREAD_STACK_SIZE != 0) && (OS_TIMER_CB_QUEUE != 0))

#if (((OS_TIMER_THREAD_STACK_SIZE & 7) != 0) || (OS_TIMER_THREAD_STACK_SIZE < 96))
#error "Invalid Timer Thread Stack size!"
#endif

// Timer Thread Control Block
static os_thread_t os_timer_thread_cb \
__attribute__((section(".bss.os.thread.cb")));

// Timer Thread Stack
static uint64_t os_timer_thread_stack[OS_TIMER_THREAD_STACK_SIZE/8] \
__attribute__((section(".bss.os.thread.stack")));

// Timer Thread Attributes
static const osThreadAttr_t os_timer_thread_attr = {
  NULL,
  osThreadDetached,
  &os_timer_thread_cb,
  (uint32_t)sizeof(os_timer_thread_cb),
  &os_timer_thread_stack,
  (uint32_t)sizeof(os_timer_thread_stack),
  (osPriority_t)OS_TIMER_THREAD_PRIO,
  0U, 0U
};

// Timer Message Queue Control Block
static os_message_queue_t os_timer_mq_cb \
__attribute__((section(".bss.os.msgqueue.cb")));

// Timer Message Queue Data
static uint32_t os_timer_mq_data[os_MessageQueueMemSize(OS_TIMER_CB_QUEUE,8)/4] \
__attribute__((section(".bss.os.msgqueue.mem")));

// Timer Message Queue Attributes
static const osMessageQueueAttr_t os_timer_mq_attr = {
  NULL,
  0U,
  &os_timer_mq_cb,
  (uint32_t)sizeof(os_timer_mq_cb),
  &os_timer_mq_data,
  (uint32_t)sizeof(os_timer_mq_data)
};

#endif  // ((OS_TIMER_THREAD_STACK_SIZE != 0) && (OS_TIMER_CB_QUEUE != 0))


// Event Flags Configuration
// =========================

#if (OS_EVFLAGS_OBJ_MEM != 0)

#if (OS_EVFLAGS_NUM == 0)
#error "Invalid number of Event Flags objects!"
#endif

// Event Flags Control Blocks
static os_event_flags_t os_ef_cb[OS_EVFLAGS_NUM] \
__attribute__((section(".bss.os.evflags.cb")));

// Memory Pool for Event Flags Control Blocks
static os_mp_info_t os_mpi_ef \
__attribute__((section(".bss.os.evflags.mpi"))) =
{ (uint32_t)OS_EVFLAGS_NUM, 0U, (uint32_t)os_EventFlagsCbSize, &os_ef_cb, NULL, NULL };

#endif  // (OS_EVFLAGS_OBJ_MEM != 0)


// Mutex Configuration
// ===================

#if (OS_MUTEX_OBJ_MEM != 0)

#if (OS_MUTEX_NUM == 0)
#error "Invalid number of Mutex objects!"
#endif

// Mutex Control Blocks
static os_mutex_t os_mutex_cb[OS_MUTEX_NUM] \
__attribute__((section(".bss.os.mutex.cb")));

// Memory Pool for Mutex Control Blocks
static os_mp_info_t os_mpi_mutex \
__attribute__((section(".bss.os.mutex.mpi"))) =
{ (uint32_t)OS_MUTEX_NUM, 0U, (uint32_t)os_MutexCbSize, &os_mutex_cb, NULL, NULL };

#endif  // (OS_MUTEX_OBJ_MEM != 0)


// Semaphore Configuration
// =======================

#if (OS_SEMAPHORE_OBJ_MEM != 0)

#if (OS_SEMAPHORE_NUM == 0)
#error "Invalid number of Semaphore objects!"
#endif

// Semaphore Control Blocks
static os_semaphore_t os_semaphore_cb[OS_SEMAPHORE_NUM] \
__attribute__((section(".bss.os.semaphore.cb")));

// Memory Pool for Semaphore Control Blocks
static os_mp_info_t os_mpi_semaphore \
__attribute__((section(".bss.os.semaphore.mpi"))) =
{ (uint32_t)OS_SEMAPHORE_NUM, 0U, (uint32_t)os_SemaphoreCbSize, &os_semaphore_cb, NULL, NULL };

#endif  // (OS_SEMAPHORE_OBJ_MEM != 0)


// Memory Pool Configuration
// =========================

#if (OS_MEMPOOL_OBJ_MEM != 0)

#if (OS_MEMPOOL_NUM == 0)
#error "Invalid number of Memory Pool objects!"
#endif

// Memory Pool Control Blocks
static os_memory_pool_t os_mp_cb[OS_MEMPOOL_NUM] \
__attribute__((section(".bss.os.mempool.cb")));

// Memory Pool for Memory Pool Control Blocks
static os_mp_info_t os_mpi_mp \
__attribute__((section(".bss.os.mempool.mpi"))) =
{ (uint32_t)OS_MEMPOOL_NUM, 0U, (uint32_t)os_MemoryPoolCbSize, &os_mp_cb, NULL, NULL };

// Memory Pool for Memory Pool Data Storage
#if (OS_MEMPOOL_DATA_SIZE != 0)
#if ((OS_MEMPOOL_DATA_SIZE & 3) != 0)
#error "Invalid Data Memory size for Memory Pools!"
#endif
static uint32_t os_mp_data[OS_MEMPOOL_DATA_SIZE/4] \
__attribute__((section(".bss.os.mempool.mem")));
#endif

#endif  // (OS_MEMPOOL_OBJ_MEM != 0)


// Message Queue Configuration
// ===========================

#if (OS_MSGQUEUE_OBJ_MEM != 0)

#if (OS_MSGQUEUE_NUM == 0)
#error "Invalid number of Message Queue objects!"
#endif

// Message Queue Control Blocks
static os_message_queue_t os_mq_cb[OS_MSGQUEUE_NUM] \
__attribute__((section(".bss.os.msgqueue.cb")));

// Memory Pool for Message Queue Control Blocks
static os_mp_info_t os_mpi_mq \
__attribute__((section(".bss.os.msgqueue.mpi"))) =
{ (uint32_t)OS_MSGQUEUE_NUM, 0U, (uint32_t)os_MessageQueueCbSize, &os_mq_cb, NULL, NULL };

// Memory Pool for Message Queue Data Storage
#if (OS_MSGQUEUE_DATA_SIZE != 0)
#if ((OS_MSGQUEUE_DATA_SIZE & 3) != 0)
#error "Invalid Data Memory size for Message Queues!"
#endif
static uint32_t os_mq_data[OS_MSGQUEUE_DATA_SIZE/4] \
__attribute__((section(".bss.os.msgqueue.mem")));
#endif

#endif  // (OS_MSGQUEUE_OBJ_MEM != 0)


// System Configuration
// ====================

// Dynamic Memory
#if (OS_DYNAMIC_MEM_SIZE != 0)
#if ((OS_DYNAMIC_MEM_SIZE & 7) != 0)
#error "Invalid Dynamic Memory size!"
#endif
static uint64_t os_mem[OS_DYNAMIC_MEM_SIZE/8] \
__attribute__((section(".bss.os")));
#endif

// ISR FIFO Queue
static void *os_isr_queue[OS_ISR_FIFO_QUEUE] \
__attribute__((section(".bss.os")));


// OS Configuration
// ================

const os_config_t os_Config = {
  0U   // Flags
#if (OS_PRIVILEGE_MODE != 0)
  | os_ConfigPrivilegedMode
#endif
#if (OS_STACK_CHECK != 0)
  | os_ConfigStackCheck
#endif
#if (OS_STACK_WATERMARK != 0)
  | os_ConfigStackWatermark
#endif
  ,
#if (OS_ROBIN_ENABLE != 0)
  (uint32_t)OS_ROBIN_TIMEOUT,
#else
  0U,
#endif
  { &os_isr_queue[0], sizeof(os_isr_queue)/sizeof(void *), 0U },
  { 
    // Memory Pools (Variable Block Size)
#if ((OS_THREAD_OBJ_MEM != 0) && (OS_THREAD_USER_STACK_SIZE != 0))
    &os_thread_stack, (uint32_t)OS_THREAD_USER_STACK_SIZE,
#else
    NULL, 0U,
#endif
#if ((OS_MEMPOOL_OBJ_MEM != 0) && (OS_MEMPOOL_DATA_SIZE != 0))
    &os_mp_data, (uint32_t)OS_MEMPOOL_DATA_SIZE,
#else
    NULL, 0U,
#endif
#if ((OS_MSGQUEUE_OBJ_MEM != 0) && (OS_MSGQUEUE_DATA_SIZE != 0))
    &os_mq_data, (uint32_t)OS_MSGQUEUE_DATA_SIZE,
#else
    NULL, 0U,
#endif
#if (OS_DYNAMIC_MEM_SIZE != 0)
    &os_mem, (uint32_t)OS_DYNAMIC_MEM_SIZE,
#else
    NULL, 0U
#endif
  },
  {
    // Memory Pools (Fixed Block Size)
#if (OS_THREAD_OBJ_MEM != 0)
#if (OS_THREAD_DEF_STACK_NUM != 0)
    &os_mpi_def_stack,
#else
    NULL,
#endif
    &os_mpi_thread,
#else
    NULL, 
    NULL,
#endif
#if (OS_TIMER_OBJ_MEM != 0)
    &os_mpi_timer,
#else
    NULL,
#endif
#if (OS_EVFLAGS_OBJ_MEM != 0)
    &os_mpi_ef,
#else
    NULL,
#endif
#if (OS_MUTEX_OBJ_MEM != 0)
    &os_mpi_mutex,
#else
    NULL,
#endif
#if (OS_SEMAPHORE_OBJ_MEM != 0)
    &os_mpi_semaphore,
#else
    NULL,
#endif
#if (OS_MEMPOOL_OBJ_MEM != 0)
    &os_mpi_mp,
#else
    NULL,
#endif
#if (OS_MSGQUEUE_OBJ_MEM != 0)
    &os_mpi_mq,
#else
    NULL,
#endif
  },
  (uint32_t)OS_STACK_SIZE,
  &os_idle_thread_attr,
#if ((OS_TIMER_THREAD_STACK_SIZE != 0) && (OS_TIMER_CB_QUEUE != 0))
  &os_timer_thread_attr,
  &os_timer_mq_attr,
  (uint32_t)OS_TIMER_CB_QUEUE
#else
  NULL,
  NULL,
  0U
#endif
};


// Non weak reference to library irq_cm module
extern       uint8_t  os_irq_cm;
extern const uint8_t *os_irq_cm_ref;
       const uint8_t* os_irq_cm_ref = &os_irq_cm;


// OS Initialization
// =================

#if  defined(__CC_ARM) || \
    (defined(__ARMCC_VERSION) && (__ARMCC_VERSION >= 6010050))

#ifndef __MICROLIB
void _platform_post_stackheap_init (void);
void _platform_post_stackheap_init (void) {
  osKernelInitialize();
}
#endif

#elif defined (__GNUC__)

void software_init_hook (void);
void software_init_hook (void) {
  osKernelInitialize();
}

#endif


// C/C++ Standard Library Multithreading Interface
// ===============================================

#if (( defined(__CC_ARM) || \
      (defined(__ARMCC_VERSION) && (__ARMCC_VERSION >= 6010050))) && \
      !defined(__MICROLIB))

#define LIBSPACE_SIZE 96

// Memory for libspace
static uint32_t os_libspace[OS_THREAD_LIBSPACE_NUM+1][LIBSPACE_SIZE/sizeof(uint32_t)] \
__attribute__((section(".bss.os")));

// Thread IDs for libspace
static uint32_t os_libspace_id[OS_THREAD_LIBSPACE_NUM] \
__attribute__((section(".bss.os")));

// Check if Kernel has been started
static uint32_t os_kernel_is_active (void) {
  static uint8_t os_kernel_active = 0U;

  if (os_kernel_active == 0U) {
    if (osKernelGetState() > osKernelReady) {
      os_kernel_active = 1U;
      return 1U;
    }
    return 0U;
  } else {
    return 1U;
  }
}

// Provide libspace for current thread
void *__user_perthread_libspace (void);
void *__user_perthread_libspace (void) {
  uint32_t id;
  uint32_t n;

  if (!os_kernel_is_active()) {
    return (void *)&os_libspace[OS_THREAD_LIBSPACE_NUM][0];
  }

  id = osThreadGetId();
  for (n = 0U; n < OS_THREAD_LIBSPACE_NUM; n++) {
    if (os_libspace_id[n] == 0U) {
      os_libspace_id[n] = id;
      return (void *)&os_libspace[n][0];
    }
    if (os_libspace_id[n] == id) {
      return (void *)&os_libspace[n][0];
    }
  }

  if (n == OS_THREAD_LIBSPACE_NUM) {
    os_Error(os_ErrorClibSpace, (void *)id);
  }

  return (void *)&os_libspace[n][0];
}

// Mutex identifier
typedef uint32_t mutex;

// Initialize mutex
int _mutex_initialize(mutex *m);
int _mutex_initialize(mutex *m) {
  *m = osMutexNew(NULL);
  if (*m == (mutex)NULL) {
    os_Error(os_ErrorClibMutex, m);
    return 0;
  }
  return 1;
}

// Acquire mutex
void _mutex_acquire(mutex *m);
void _mutex_acquire(mutex *m) {
  if (os_kernel_is_active()) {
    osMutexAcquire(*m, osWaitForever);
  }
}

// Release mutex
void _mutex_release(mutex *m);
void _mutex_release(mutex *m) {
  if (os_kernel_is_active()) {
    osMutexRelease(*m);
  }
}

// Free mutex
void _mutex_free(mutex *m);
void _mutex_free(mutex *m) {
  osMutexDelete(*m);
}

#endif
