#include <common.h>
#include <stm32f10x_system.h>
#include <system_arm.h>

enum exception_id
{
	EXCP_ID_RSV0 = 0,
	EXCP_ID_RESET,
	EXCP_ID_NMI,
	EXCP_ID_HARD_FAULT,
	EXCP_ID_MEM_MANAGE,
	EXCP_ID_BUS_FAULT,
	EXCP_ID_USAGE_FAULT,
	EXCP_ID_RSV1,
	EXCP_ID_RSV2,
	EXCP_ID_RSV3,
	EXCP_ID_RSV4,
	EXCP_ID_SVC,
	EXCP_ID_DEBUG_MONITOR,
	EXCP_ID_RSV5,
	EXCP_ID_PEND_SV,
	EXCP_ID_SYS_TICK,
	EXCP_ID_EXT_INT,
};

static const char *excp_vect_str[] =
{
	"rsv0",
	"Reset",
	"NMI",
	"HardFault",
	"MemManage",
	"BusFault",
	"UsageFault",
	"rsv1",
	"rsv2",
	"rsv3",
	"rsv4",
	"SVC",
	"DebugMonitor",
	"rsv5",
	"PendSV",
	"SysTick",
	"Interrupts",
};

static void bad_mode(int id)
{
	printf("exception: %s, Hang ...\n",excp_vect_str[id]);
	while(1)
	;
}

void show_regs(const struct pt_regs *regs)
{
	unsigned long flags = regs->ARM_cpsr;

	printf("XPSR:%8x RetAddr:%8x LR:%8x R12:%8x\n",
		regs->ARM_cpsr, regs->ARM_pc, regs->ARM_lr, regs->ARM_r12);
	printf("  R3:%8x      R2:%8x R1:%8x  R0:%8x\n",
		regs->ARM_r3, regs->ARM_r2, regs->ARM_r1, regs->ARM_r0);
	printf("Flags: %c%c%c%c%c\n",
		flags & CC_N_BIT ? 'N' : 'n',
		flags & CC_Z_BIT ? 'Z' : 'z',
		flags & CC_C_BIT ? 'C' : 'c',
		flags & CC_V_BIT ? 'V' : 'v',
		flags & CC_T_BIT ? 'T' : 't');
}

int interrupts_enable(void)
{
	__enable_irq();
	return 0;
}

void inerrupts_disable(void)
{
	__disable_irq();
}

void NMI_Handler(void)
{
	bad_mode(EXCP_ID_NMI);
}

void HardFault_Handler(void *regs_ptr)
{
	show_regs(regs_ptr);
	bad_mode(EXCP_ID_HARD_FAULT);
}

void MemManage_Handler(void)
{
	bad_mode(EXCP_ID_MEM_MANAGE);
}

void BusFault_Handler(void *regs_ptr)
{
	show_regs(regs_ptr);
	bad_mode(EXCP_ID_BUS_FAULT);
}

void UsageFault_Handler(void *regs_ptr)
{
	show_regs(regs_ptr);
	bad_mode(EXCP_ID_USAGE_FAULT);
}

void DebugMon_Handler(void)
{
	bad_mode(EXCP_ID_DEBUG_MONITOR);
}

#ifndef CONFIG_USE_FREERTOS
void SVC_Handler(void)
{
	bad_mode(EXCP_ID_SVC);
}

void PendSV_Handler(void)
{
	bad_mode(EXCP_ID_PEND_SV);
}

void SysTick_Handler(void)
{
	static int tick = 0;
	unsigned int reg = SysTick->CTRL;

	system_systick_clr_pending();
	printf("%x, %d\n", reg,tick++);
}
#endif
