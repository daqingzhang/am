export OS_TYPE	?= FreeRTOS
export ARCH	?= arm

ifeq ($(RTOS),1)
export RTOS
endif

ifeq ($(DEBUG),1)
KBUILD_CFLAGS	+= -DDEBUG
endif

ifeq ($(CHIP),stm32f10x)
CPU ?= ARM_CM3
else
CPU ?= ARM_CM4
endif

ifeq ($(CPU),ARM_CM3)
COMMON_FLAGS += -mcpu=cortex-m3
else if ($(CPU),ARM_CM4))
COMMON_FLAGS += -mcpu=cortex-m4
else
$(error invalud CPU=$(CPU))
endif

COMMON_FLAGS += -g -Os -Wall -Werror -static \
	-mthumb -march=armv7-m \
	-fno-common -fno-builtin-printf -fno-exceptions \
	--specs=nano.specs -specs=nosys.specs -lnosys \
	-fmessage-length=0 -fsigned-char -std=gnu99 \
	-ffunction-sections -fdata-sections \


