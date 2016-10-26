/*
 * Copyright (c) 2016 ARM Limited. All rights reserved.
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
 * Title:       ARMv8M Mainline Exception handlers
 *
 * -----------------------------------------------------------------------------
 */


        .file    "irq_armv8mml.s"
        .syntax  unified

        .ifndef  __DOMAIN_NS
        .equ     __DOMAIN_NS, 0
        .endif

        .ifndef  __FPU_USED
        .equ     __FPU_USED,  0
        .endif

        .equ     I_T_RUN_OFS, 28        // osInfo.thread.run offset
        .equ     TCB_SM_OFS,  48        // TCB.stack_mem offset
        .equ     TCB_SP_OFS,  56        // TCB.SP offset
        .equ     TCB_SF_OFS,  34        // TCB.stack_frame offset
        .equ     TCB_TZM_OFS, 60        // TCB.tz_memory offset

        .section ".rodata"
        .global  os_irq_cm              // Non weak library reference
os_irq_cm:
        .byte    0


        .thumb
        .section ".text"
        .align   2


        .thumb_func
        .type    SVC_Handler, %function
        .global  SVC_Handler
        .fnstart
        .cantunwind
SVC_Handler:

        MRS      R0,PSP                 // Get PSP
        LDR      R1,[R0,#24]            // Load saved PC from stack
        LDRB     R1,[R1,#-2]            // Load SVC number
        CBNZ     R1,SVC_User            // Branch if not SVC 0

        PUSH     {R0,LR}                // Save PSP and EXC_RETURN
        LDM      R0,{R0-R3,R12}         // Load function parameters and address from stack
        BLX      R12                    // Call service function
        POP      {R12,LR}               // Restore PSP and EXC_RETURN
        STR      R0,[R12]               // Store function return value

SVC_Context:
        LDR      R3,=os_Info+I_T_RUN_OFS// Load address of os_Info.run
        LDM      R3,{R1,R2}             // Load os_Info.thread.run: curr & next
        CMP      R1,R2                  // Check if thread switch is required
        IT       EQ
        BXEQ     LR                     // Exit when threads are the same

        .if      __FPU_USED == 1
        CBNZ     R1,SVC_ContextSave     // Branch if running thread is not deleted
        TST      LR,#0x10               // Check if extended stack frame
        BNE      SVC_ContextSwitch
        LDR      R1,=0xE000EF34         // FPCCR Address
        LDR      R0,[R1]                // Load FPCCR
        BIC      R0,#1                  // Clear LSPACT (Lazy state)
        STR      R0,[R1]                // Store FPCCR
        B        SVC_ContextSwitch
        .else
        CBZ      R1,SVC_ContextSwitch   // Branch if running thread is deleted
        .endif

SVC_ContextSave:
        STMDB    R12!,{R4-R11}          // Save R4..R11
        .if      __FPU_USED == 1
        TST      LR,#0x10               // Check if extended stack frame
        IT       EQ
        VSTMDBEQ R12!,{S16-S31}         //  Save VFP S16.S31
        .endif

        STR      R12,[R1,#TCB_SP_OFS]   // Store SP
        STRB     LR, [R1,#TCB_SF_OFS]   // Store stack frame information

SVC_ContextSwitch:
        STR      R2,[R3]                // os_Info.thread.run: curr = next

SVC_ContextRestore:
        .if      __DOMAIN_NS == 1
        LDR      R0,[R2,#TCB_TZM_OFS]   // Load TrustZone memory identifier
        CBZ      R0,SVC_ContextRestore1 // Branch if there is no secure context
        PUSH     {R2,R3}                // Save registers
        BL       TZ_LoadContext_S       // Load secure context
        POP      {R2,R3}                // Restore registers
        .endif

SVC_ContextRestore1:
        LDR      R0,[R2,#TCB_SM_OFS]    // Load stack memory base
        LDRB     R1,[R2,#TCB_SF_OFS]    // Load stack frame information
        MSR      PSPLIM,R0              // Set PSPLIM
        LDR      R0,[R2,#TCB_SP_OFS]    // Load SP
        ORR      LR,R1,#0xFFFFFF00      // Set EXC_RETURN

        .if      __DOMAIN_NS == 1
        TST      LR,#0x40               // Check domain of interrupted thread
        BNE      SVC_ContextRestore2    // Branch if secure
        .endif

        .if      __FPU_USED == 1
        TST      LR,#0x10               // Check if extended stack frame
        IT       EQ
        VLDMIAEQ R0!,{S16-S31}          //  Restore VFP S16..S31
        .endif
        LDMIA    R0!,{R4-R11}           // Restore R4..R11

SVC_ContextRestore2:
        MSR      PSP,R0                 // Set PSP

SVC_Exit:
        BX       LR                     // Exit from handler

SVC_User:
        PUSH     {R4,LR}                // Save registers
        LDR      R2,=os_UserSVC_Table   // Load address of SVC table
        LDR      R3,[R2]                // Load SVC maximum number
        CMP      R1,R3                  // Check SVC number range
        BHI      SVC_Done               // Branch if out of range

        LDR      R4,[R2,R1,LSL #2]      // Load address of SVC function

        LDM      R0,{R0-R3}             // Load function parameters from stack
        BLX      R4                     // Call service function
        MRS      R4,PSP                 // Get PSP
        STR      R0,[R4]                // Store function return value

SVC_Done:
        POP      {R4,PC}                // Return from handler

        .fnend
        .size    SVC_Handler, .-SVC_Handler


        .thumb_func
        .type    PendSV_Handler, %function
        .global  PendSV_Handler
        .fnstart
        .cantunwind
PendSV_Handler:

        PUSH     {R4,LR}                // Save EXC_RETURN
        BL       os_PendSV_Handler      // Call os_PendSV_Handler
        POP      {R4,LR}                // Restore EXC_RETURN
        B        Sys_Context

        .fnend
        .size    PendSV_Handler, .-PendSV_Handler


        .thumb_func
        .type    SysTick_Handler, %function
        .global  SysTick_Handler
        .fnstart
        .cantunwind
SysTick_Handler:

        PUSH     {R4,LR}                // Save EXC_RETURN
        BL       os_Tick_Handler        // Call os_Tick_Handler
        POP      {R4,LR}                // Restore EXC_RETURN
        B        Sys_Context

        .fnend
        .size   SysTick_Handler, .-SysTick_Handler


        .thumb_func
        .type    Sys_Context, %function
        .global  Sys_Context
        .fnstart
        .cantunwind
Sys_Context:

        LDR      R3,=os_Info+I_T_RUN_OFS// Load address of os_Info.run
        LDM      R3,{R1,R2}             // Load os_Info.thread.run: curr & next
        CMP      R1,R2                  // Check if thread switch is required
        IT       EQ
        BXEQ     LR                     // Exit when threads are the same

Sys_ContextSave:
        .if      __DOMAIN_NS == 1
        TST      LR,#0x40               // Check domain of interrupted thread
        BEQ      Sys_ContextSave1       // Branch if non-secure
        LDR      R0,[R1,#TCB_TZM_OFS]   // Load TrustZone memory identifier
        PUSH     {R1,R2,R3,LR}          // Save registers and EXC_RETURN
        BL       TZ_StoreContext_S      // Store secure context
        POP      {R1,R2,R3,LR}          // Restore registers and EXC_RETURN
        MRS      R0,PSP                 // Get PSP
        B        Sys_ContextSave2
        .endif

Sys_ContextSave1:
        MRS      R0,PSP                 // Get PSP
        STMDB    R0!,{R4-R11}           // Save R4..R11
        .if      __FPU_USED == 1
        TST      LR,#0x10               // Check if extended stack frame
        IT       EQ
        VSTMDBEQ R0!,{S16-S31}          //  Save VFP S16.S31
        .endif

Sys_ContextSave2:
        STR      R0,[R1,#TCB_SP_OFS]    // Store SP
        STRB     LR,[R1,#TCB_SF_OFS]    // Store stack frame information

Sys_ContextSwitch:
        STR      R2,[R3]                // os_Info.run: curr = next

Sys_ContextRestore:
        .if      __DOMAIN_NS == 1
        LDR      R0,[R2,#TCB_TZM_OFS]   // Load TrustZone memory identifier
        CBZ      R0,Sys_ContextRestore1 // Branch if there is no secure context
        PUSH     {R2,R3}                // Save registers
        BL       TZ_LoadContext_S       // Load secure context
        POP      {R2,R3}                // Restore registers
        .endif

Sys_ContextRestore1:
        LDR      R0,[R2,#TCB_SM_OFS]    // Load stack memory base
        LDRB     R1,[R2,#TCB_SF_OFS]    // Load stack frame information
        MSR      PSPLIM,R0              // Set PSPLIM
        LDR      R0,[R2,#TCB_SP_OFS]    // Load SP
        ORR      LR,R1,#0xFFFFFF00      // Set EXC_RETURN

        .if      __DOMAIN_NS == 1
        TST      LR,#0x40               // Check domain of interrupted thread
        BNE      Sys_ContextRestore2    // Branch if secure
        .endif

        .if      __FPU_USED == 1
        TST      LR,#0x10               // Check if extended stack frame
        IT       EQ
        VLDMIAEQ R0!,{S16-S31}          //  Restore VFP S16..S31
        .endif
        LDMIA    R0!,{R4-R11}           // Restore R4..R11

Sys_ContextRestore2:
        MSR      PSP,R0                 // Set PSP

Sys_ContextExit:
        BX       LR                     // Exit from handler

        .fnend
        .size    Sys_Context, .-Sys_Context


        .end
