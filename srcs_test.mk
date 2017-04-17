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
	./device/$(CHIP_NAME)/key.o	\
	./device/$(CHIP_NAME)/dc_motor.o	\
	./device/$(CHIP_NAME)/infra.o	\
	./device/$(CHIP_NAME)/speaker.o	\
	./device/$(CHIP_NAME)/lcd_displib.o	\
	./device/$(CHIP_NAME)/lcd.o	\
	./device/$(CHIP_NAME)/led.o	\

COMM_COBJS := \
	./common/fsm_v2.o \
	./common/sensor.o \
	./common/motor.o \

ifneq ($(findstring test,$(APP_NAME)),)
APP_COBJS := \
	./application/test/main.o	\
	./application/test/test.o
endif

COBJS	:= \
	$(ARCH_COBJS)	\
	$(DRV_COBJS)	\
	$(COMM_COBJS)	\
	$(DEV_COBJS)	\
	$(APP_COBJS)

