export OS_TYPE	?= FreeRTOS
export ARCH	?= arm

ifeq ($(RTOS),1)
export RTOS
endif

ifeq ($(DEBUG),1)
KBUILD_CFLAGS	+= -DDEBUG
endif

COMMON_FLAGS += -g -O2 -Wall -Werror -static -fno-common -fno-builtin-printf

