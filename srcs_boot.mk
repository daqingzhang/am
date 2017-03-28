AOBJS	:= \
	./arch/$(ARCH)/$(CHIP_NAME)/cpu/start.o		\
	./arch/$(ARCH)/$(CHIP_NAME)/lib/core_reg.o	\

ARCH_COBJS := \
	./arch/$(ARCH)/$(CHIP_NAME)/lib/interrupts.o	\
	./arch/$(ARCH)/$(CHIP_NAME)/lib/string.o	\
	./arch/$(ARCH)/$(CHIP_NAME)/lib/timer.o		\
	./arch/$(ARCH)/$(CHIP_NAME)/lib/serial.o	\
	./arch/$(ARCH)/$(CHIP_NAME)/lib/board.o	\

DRV_COBJS := \
	./drivers/$(CHIP_NAME)/stm32f10x_system.o	\
	./drivers/$(CHIP_NAME)/stm32f10x_rcc.o		\
	./drivers/$(CHIP_NAME)/stm32f10x_gpio.o		\
	./drivers/$(CHIP_NAME)/stm32f10x_spi.o		\
	./drivers/$(CHIP_NAME)/stm32f10x_usart.o	\

DEV_COBJS := \
	./device/$(CHIP_NAME)/sensor.o	\
	./device/$(CHIP_NAME)/motor.o	\
	./device/$(CHIP_NAME)/key.o	\
	./device/$(CHIP_NAME)/dc_motor.o	\
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
	./application/common/hook.o	\
	./application/common/fsm_v2.o

ifneq ($(findstring led,$(APP_NAME)),)
APP_COBJS += \
	./application/led/main.o	\
	./application/led/led_fsm.o	\
	./application/led/led_task.o
endif

ifneq ($(findstring key,$(APP_NAME)),)
APP_COBJS += \
	./application/key/main.o	\
	./application/key/key_task.o
endif

ifneq ($(findstring vehicle,$(APP_NAME)),)
APP_COBJS += \
	./application/vehicle/main.o	\
	./application/vehicle/task_motor.o
endif


COBJS	:= \
	$(ARCH_COBJS)	\
	$(DRV_COBJS)	\
	$(DEV_COBJS)	\
	$(SYS_COBJS)	\
	$(APP_COBJS)	\

