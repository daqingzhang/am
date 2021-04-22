ifeq ($(ARCH),arm)
CROSS_COMPILE	:=arm-none-eabi
else
CROSS_COMPILE	:=
endif

CC	:= $(CROSS_COMPILE)-gcc
LD	:= $(CROSS_COMPILE)-ld
AS	:= $(CROSS_COMPILE)-as
AR	:= $(CROSS_COMPILE)-ar
GDB	:= $(CROSS_COMPILE)-gdb
OBJCOPY := $(CROSS_COMPILE)-objcopy
OBJDUMP := $(CROSS_COMPILE)-objdump

define cc_cmd
	$(ECHO) $1	$2
endef


