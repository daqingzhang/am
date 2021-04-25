/**************************************************************************//**
 * @file     system_ARMCM3.c
 * @brief    CMSIS Device System Source File for
 *           ARMCMx Device
 * @version  V5.3.1
 * @date     09. July 2018
 ******************************************************************************/
/*
 * Copyright (c) 2009-2018 Arm Limited. All rights reserved.
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
 */

#ifdef ARMCM3
  #include "ARMCM3.h"
#elif defined (ARMCM4)
  #include "ARMCM4.h"
#elif defined (ARMCM4_FP)
  #include "ARMCM4_FP.h"
#else
  #error "CPU not matched"
#endif

#include "mem_location.h"
#include "common.h"

#define  SYSTEM_CLOCK    (8000000)

uint32_t SystemCoreClock = SYSTEM_CLOCK;  /* System Core Clock Frequency */

void SystemCoreClockUpdate (void)
{
  SystemCoreClock = SYSTEM_CLOCK;
}

#define NVIC_BASE_IRQ_NUM  (16)
#define NVIC_CORE_IRQ_NUM  (32)
#define NVIC_IRQ_TOTAL_NUM (NVIC_BASE_IRQ_NUM + NVIC_CORE_IRQ_NUM)

static void NVIC_default_handler(void)
{
    asm volatile("_loop:; nop; nop; nop; nop;; b _loop;");
}

#define FAULT_HANDLER    __attribute__((weak,alias("NVIC_default_handler")))
#define VECTOR_LOC       __attribute__((section(".vector_table")))

void FAULT_HANDLER Reset_Handler(void);
void FAULT_HANDLER NMI_Handler(void);
void FAULT_HANDLER HardFault_Handler(void);
void FAULT_HANDLER MemManage_Handler(void);
void FAULT_HANDLER BusFault_Handler(void);
void FAULT_HANDLER UsageFault_Handler(void);
void FAULT_HANDLER SecureFault_Handler(void);
void FAULT_HANDLER SVC_Handler(void);
void FAULT_HANDLER DebugMon_Handler(void);
void FAULT_HANDLER PendSV_Handler(void);
void FAULT_HANDLER SysTick_Handler(void);
extern uint32_t __StackTop[];

static BOOT_RODATA_FLASH_LOC const uint32_t fault_handlers[NVIC_BASE_IRQ_NUM] =
{
    (uint32_t)__StackTop,
    (uint32_t)Reset_Handler,
    (uint32_t)NMI_Handler,
    (uint32_t)HardFault_Handler,
    (uint32_t)MemManage_Handler,
    (uint32_t)BusFault_Handler,
    (uint32_t)UsageFault_Handler,
    (uint32_t)SecureFault_Handler,
    (uint32_t)NVIC_default_handler,
    (uint32_t)NVIC_default_handler,
    (uint32_t)NVIC_default_handler,
    (uint32_t)SVC_Handler,
    (uint32_t)DebugMon_Handler,
    (uint32_t)NVIC_default_handler,
    (uint32_t)PendSV_Handler,
    (uint32_t)SysTick_Handler,
};

static uint32_t VECTOR_LOC vector_table[NVIC_IRQ_TOTAL_NUM];

void NVIC_InitVectors(void)
{
    int i;
    for (i = 0;i < NVIC_IRQ_TOTAL_NUM; i++) {
        vector_table[i] = i < ARRAY_SIZE(fault_handlers) ? fault_handlers[i] : (uint32_t)NVIC_default_handler;
    }
    SCB->VTOR = (uint32_t)vector_table;
    __DSB();
}

void BootInit(void)
{
}

/*----------------------------------------------------------------------------
  System initialization function
 *----------------------------------------------------------------------------*/

void SystemInit (void)
{
  SystemCoreClock = SYSTEM_CLOCK;

#if defined (__FPU_USED) && (__FPU_USED == 1U)
  SCB->CPACR |= ((3U << 10U*2U) |           /* enable CP10 Full Access */
                 (3U << 11U*2U)  );         /* enable CP11 Full Access */
#endif

#ifdef UNALIGNED_ACCESS
    SCB->CCR &= ~SCB_CCR_UNALIGN_TRP_Msk;
#else
    SCB->CCR |= SCB_CCR_UNALIGN_TRP_Msk;
#endif

#ifdef USAGE_FAULT
    SCB->SHCSR |= SCB_SHCSR_USGFAULTENA_Msk;
    NVIC_SetPriority(UsageFault_IRQn, IRQ_PRIORITY_REALTIME);
#else
    SCB->SHCSR &= ~SCB_SHCSR_USGFAULTENA_Msk;
#endif
#ifdef BUS_FAULT
    SCB->SHCSR |= SCB_SHCSR_BUSFAULTENA_Msk;
    NVIC_SetPriority(BusFault_IRQn, IRQ_PRIORITY_REALTIME);
#else
    SCB->SHCSR &= ~SCB_SHCSR_BUSFAULTENA_Msk;
#endif
#ifdef MEM_FAULT
    SCB->SHCSR |= SCB_SHCSR_MEMFAULTENA_Msk;
    NVIC_SetPriority(MemoryManagement_IRQn, IRQ_PRIORITY_REALTIME);
#else
    SCB->SHCSR &= ~SCB_SHCSR_MEMFAULTENA_Msk;
#endif

    board_init();
}
