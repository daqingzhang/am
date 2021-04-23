export OS_TYPE	?= FreeRTOS
export ARCH	?= arm

ifeq ($(RTOS),1)
export RTOS
endif

ifeq ($(DEBUG),1)
KBUILD_CFLAGS	+= -DDEBUG
endif

COMMON_FLAGS += -g -O2 -Wall -Werror -Wall -static \
	-mthumb -mcpu=cortex-m3 -march=armv7-m \
	-fno-common -fno-builtin-printf -fno-exceptions \
	--specs=nano.specs -specs=nosys.specs -lnosys \
	-fmessage-length=0 -fsigned-char -std=gnu99 \
	-ffunction-sections -fdata-sections -fshort-wchar \

