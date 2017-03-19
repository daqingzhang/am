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

static void bad_mode(void)
{
	rprintf("Hang ...\n");
	while(1)
		;
}

static const char *exception_vect_str[] =
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

static void show_regs(const struct pt_regs *regs, const char *exception_str)
{
	unsigned long flags;

	flags = regs->ARM_cpsr;

	rprintf("cpsr:%8x pc:%8x  lr:%8x r12: %8x\n",
		regs->ARM_cpsr, regs->ARM_pc, regs->ARM_lr, regs->ARM_r12);

	rprintf("r3 : %8x  r2 : %8x  r1 : %8x  r0: %8x\n",
		regs->ARM_r3, regs->ARM_r2, regs->ARM_r1, regs->ARM_r0);

	rprintf("Flags: %c%c%c%c%c\n",
		flags & CC_N_BIT ? 'N' : 'n',
		flags & CC_Z_BIT ? 'Z' : 'z',
		flags & CC_C_BIT ? 'C' : 'c',
		flags & CC_V_BIT ? 'V' : 'v',
		flags & CC_T_BIT ? 'T' : 't');

	rprintf("%s ID: %3x\n", exception_str, flags & EXCP_ID_MASK);
}

#define IRQ_FRAME_OFFS	0x08
#define GET_SP_ADDR(offs)	(__get_SP() + offs)

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
	show_regs((const struct pt_regs *)GET_SP_ADDR(IRQ_FRAME_OFFS),
			exception_vect_str[EXCP_ID_NMI]);
	//bad_mode();
}

void HardFault_Handler(void)
{
	show_regs((const struct pt_regs *)GET_SP_ADDR(IRQ_FRAME_OFFS),
			exception_vect_str[EXCP_ID_HARD_FAULT]);
	bad_mode();
}

void MemManage_Handler(void)
{
	show_regs((const struct pt_regs *)GET_SP_ADDR(IRQ_FRAME_OFFS),
			exception_vect_str[EXCP_ID_MEM_MANAGE]);
	bad_mode();
}

void BusFault_Handler(void)
{
	show_regs((const struct pt_regs *)GET_SP_ADDR(IRQ_FRAME_OFFS),
			exception_vect_str[EXCP_ID_BUS_FAULT]);
	bad_mode();
}

void UsageFault_Handler(void)
{
	show_regs((const struct pt_regs *)GET_SP_ADDR(IRQ_FRAME_OFFS),
			exception_vect_str[EXCP_ID_USAGE_FAULT]);
	bad_mode();
}

void DebugMon_Handler(void)
{
	show_regs((const struct pt_regs *)GET_SP_ADDR(IRQ_FRAME_OFFS),
			exception_vect_str[EXCP_ID_DEBUG_MONITOR]);
	bad_mode();
}

#ifndef CONFIG_USE_FREERTOS
void SVC_Handler(void)
{
	show_regs((const struct pt_regs *)__get_SP(),
			exception_vect_str[EXCP_ID_NMI]);
	bad_mode();
}

void PendSV_Handler(void)
{
	show_regs((const struct pt_regs *)__get_SP(),
			exception_vect_str[EXCP_ID_NMI]);
	bad_mode();
}

void SysTick_Handler(void)
{
	static int tick = 0;
	unsigned int reg = SysTick->CTRL;

	system_systick_clr_pending();
	rprintf("%x, %d\n", reg,tick++);
}
#endif
