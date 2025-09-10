/*
 * Copyright (c) 2013-2025 ARM Limited. All rights reserved.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the License); you may
 * not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an AS IS BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * ----------------------------------------------------------------------
 *
 * interface.c      Secure/non-secure callable application code
 *
 * Version 1.0
 *    Initial Release
 *---------------------------------------------------------------------------*/


#include <arm_cmse.h>     // CMSE definitions
#include "interface.h"    // Header file with secure interface API

/* typedef for non-secure callback functions */
typedef int (*funcptr_NS)(int) __attribute__((cmse_nonsecure_call));

/* Non-secure callable (entry) function */
__attribute__((cmse_nonsecure_entry))
int func1(int x) { 
  return x+3; 
}

/* Non-secure callable (entry) function, calling a non-secure callback function */
__attribute__((cmse_nonsecure_entry))
int func2(funcptr callback, int x) {
  funcptr_NS callback_NS;               // non-secure callback function pointer
  int y;

  /* return function pointer with cleared LSB */
  callback_NS = (funcptr_NS)cmse_nsfptr_create(callback);

  y = callback_NS (x+1);

  return (y+2);
}
