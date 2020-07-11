VENDOR	?=st
CHIP	?=stm32f10x
CPU		?=ARM_CM3
DEBUG	?=1
USE_OS	?=1

core-y += app/

LINKER_FILE ?=linker.ld

KBUILD_CFLAGS := -mthumb -mcpu=cortex-m3 -march=armv7-m \
	-DSTM32F10X_MD -DCHIP_STM32F10X -DGCC_ARMCM3 \


KBUILD_CPPFLAGS :=
LIB_LDFLAGS :=

