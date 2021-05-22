#include <common.h>
#include <stm32f10x_system.h>
#include <system_arm.h>

static uint32_t cpu_irq_disable = 0;
static uint32_t cpu_irq_lock = 0;

//#define INT_LOCK_EXCEPTION

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
	unsigned int hfsr = system_get_hfsr();
	unsigned int cfsr = system_get_cfsr();

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
	printf("HFSR:%8x    CFSR:%8x\n",hfsr,cfsr);
}

uint32_t int_lock_global(void)
{
	uint32_t pri = __get_PRIMASK();

	if ((pri & 0x1) == 0) {
		__disable_irq();
	}
	return pri;
}

void int_unlock_global(uint32_t pri)
{
	if ((pri & 0x1) == 0) {
		__enable_irq();
	}
}

uint32_t int_lock_part(void)
{
	uint32_t pri = __get_BASEPRI();
	__set_BASEPRI(((IRQ_PRIORITY_HIGHPLUS << (8 - __NVIC_PRIO_BITS)) & (uint32_t)0xFFUL));
	return pri;
}

void int_unlock_part(uint32_t pri)
{
	__set_BASEPRI(pri);
}

uint32_t int_lock(void)
{
#ifdef INT_LOCK_EXCEPTION
	return int_lock_part();
#else
	return int_lock_global();
#endif
}

void int_unlock(uint32_t pri)
{
#ifdef INT_LOCK_EXCEPTION
	int_lock_part(pri);
#else
	int_unlock_global(pri);
#endif
}

void interrupts_disable(void)
{
	if (!cpu_irq_disable) {
		cpu_irq_lock = int_lock();
		cpu_irq_disable = 1;
	}
}

void interrupts_enable(void)
{
	if (cpu_irq_disable) {
		cpu_irq_disable = 0;
		int_unlock(cpu_irq_lock);
	}
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
