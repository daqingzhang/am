AOBJS	:= \
	./arch/$(ARCH)/$(CHIP_NAME)/cpu/start.o		\
	./arch/$(ARCH)/$(CHIP_NAME)/lib/core_reg.o	\

ARCH_COBJS := \
	./arch/$(ARCH)/$(CHIP_NAME)/lib/interrupts.o	\
	./arch/$(ARCH)/$(CHIP_NAME)/lib/string.o	\
	./arch/$(ARCH)/$(CHIP_NAME)/lib/timer.o		\

DRV_COBJS := \
	./drivers/$(CHIP_NAME)/stm32f10x_system.o	\
	./drivers/$(CHIP_NAME)/stm32f10x_rcc.o		\
	./drivers/$(CHIP_NAME)/stm32f10x_gpio.o		\
	./drivers/$(CHIP_NAME)/stm32f10x_spi.o		\
	./drivers/$(CHIP_NAME)/stm32f10x_usart.o	\

DEV_COBJS := \
	./device/$(CHIP_NAME)/serial.o	\
	./device/$(CHIP_NAME)/key.o	\
	./device/$(CHIP_NAME)/motor.o	\
	./device/$(CHIP_NAME)/infra.o	\
	./device/$(CHIP_NAME)/speaker.o	\
	./device/$(CHIP_NAME)/lcd_displib.o	\
	./device/$(CHIP_NAME)/lcd.o	\
	./device/$(CHIP_NAME)/led.o	\

SYS_COBJS := \
	./system/$(OS_NAME)/Source/list.o	\
	./system/$(OS_NAME)/Source/tasks.o	\
	./system/$(OS_NAME)/Source/timers.o	\
	./system/$(OS_NAME)/Source/queue.o	\
	./system/$(OS_NAME)/Source/croutine.o	\
	./system/$(OS_NAME)/Source/event_groups.o	\
	./system/$(OS_NAME)/Source/portable/MemMang/heap_2.o	\
	./system/$(OS_NAME)/Source/portable/GCC/ARM_CM3/port.o	\

APP_COBJS := \
	./application/$(APP_NAME)/main.o	\
	./application/$(APP_NAME)/test.o	\
	./application/$(APP_NAME)/hook.o	\
	./application/$(APP_NAME)/fsm.o		\
	./application/$(APP_NAME)/led_fsm.o	\
	./application/$(APP_NAME)/led_task.o	\
	./application/$(APP_NAME)/key_task.o	\

COBJS	:= \
	$(ARCH_COBJS)	\
	$(DRV_COBJS)	\
	$(DEV_COBJS)	\
	$(SYS_COBJS)	\
	$(APP_COBJS)	\

