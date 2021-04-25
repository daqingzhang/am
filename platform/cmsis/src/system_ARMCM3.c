/**************************************************************************//**
 * @file     system_ARMCM3.c
 * @brief    CMSIS Device System Source File for
 *           ARMCM3 Device
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

#include "ARMCM3.h"
#include "mem_location.h"
#include "common.h"

/*----------------------------------------------------------------------------
  Define clocks
 *----------------------------------------------------------------------------*/
#define  SYSTEM_CLOCK    (8000000)

/*----------------------------------------------------------------------------
  System Core Clock Variable
 *----------------------------------------------------------------------------*/
uint32_t SystemCoreClock = SYSTEM_CLOCK;  /* System Core Clock Frequency */


/*----------------------------------------------------------------------------
  System Core Clock update function
 *----------------------------------------------------------------------------*/
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

  board_init();
}
