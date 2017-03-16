ARCH		:=armv7
CHIP_NAME	:=$(PREFIX)
OS_NAME		:=$(SYSTEM)

#==============================================================================
# Directory
#==============================================================================
OS_DIR		:=system/$(OS_NAME)
APP_DIR		:=application
DEV_INC		:=device/include
DRV_INC		:=drivers/$(CHIP_NAME)/include
APP_INC		:=application/include
ARCH_INC	:=arch/$(ARCH)/$(CHIP_NAME)/include

SYS_CFG_INC	:=$(OS_DIR)/config
SYS_SRC_INC	:=$(OS_DIR)/Source/include
SYS_PORT_INC	:=$(OS_DIR)/Source/portable/GCC/ARM_CM3
SYS_MEM_INC	:=$(OS_DIR)/Source/portable/MemMang

INCS		:= -I$(DEV_INC)
INCS		+= -I$(DRV_INC)
INCS		+= -I$(APP_INC)
INCS		+= -I$(APP_DIR)
INCS		+= -I$(ARCH_INC)
INCS		+= -I$(SYS_CFG_INC)
INCS		+= -I$(SYS_SRC_INC)
INCS		+= -I$(SYS_PORT_INC)
INCS		+= -I$(SYS_MEM_INC)

DIR_OUT		:=out
DIR_OBJS	:=$(DIR_OUT)/objs
DIR_OUT_APP	:=$(DIR_OBJS)/application
DIR_OUT_ARCH	:=$(DIR_OBJS)/arch
DIR_OUT_DEV	:=$(DIR_OBJS)/device
DIR_OUT_DRV	:=$(DIR_OBJS)/drivers
DIR_OUT_SYS	:=$(DIR_OBJS)/system

#==============================================================================
# Target Files
#==============================================================================
TARGET		:= boot
TARGET_ELF	:= $(TARGET).elf
TARGET_BIN	:= $(TARGET).bin
TARGET_HEX	:= $(TARGET).hex
TARGET_MAP	:= $(TARGET).map
TARGET_SYM	:= $(TARGET).symbols
TARGET_SEC	:= $(TARGET).section
TARGET_ELF_DUMP := $(TARGET_ELF).dump
TARGET_BIN_DUMP := $(TARGET_BIN).dump
TARGET_HEX_DUMP := $(TARGET_HEX).dump

#==============================================================================
# Compiler
#==============================================================================
TC	:= arm-none-eabi
CC	:= $(TC)-gcc
LD	:= $(TC)-ld
AS	:= $(TC)-as
AR	:= $(TC)-ar
GDB	:= $(TC)-gdb
OBJCOPY := $(TC)-objcopy
OBJDUMP := $(TC)-objdump

CC_OPTS		:= -g -mthumb -mcpu=cortex-m3 -march=armv7-m
CC_OPTS		+= -O2 -Wall -static -fno-common -fno-builtin-printf

LD_OPTS		:= -T boot_stm.ld $(INCS)
LD_OPTS		+= -Wl,-nostdlib,--relax,-Map=$(TARGET_MAP),--gc-sections
LD_OPTS		+= -nostartfiles -ffast-math -lgcc

OBJDUMP_OPTS	:= --disassemble-all
OBJDUMP_OPTS	+= --section=.text --section=.test.startup --section=.data

#==============================================================================
# Macro Definitions
#==============================================================================
TARGET_DEFS	:= -DHOST_DEBUG=1
TARGET_DEFS	+= -DSTM32F10X_MD
TARGET_DEFS	+= -DCONFIG_USE_FREERTOS
TARGET_DEFS	+= -DGCC_ARMCM3
#TARGET_DEFS	+= -DCONFIG_TASK_INFO
#TARGET_DEFS	+= -DCONFIG_TEST_MOTOR
#TARGET_DEFS	+= -DCONFIG_TEST_SPEAKER
#TARGET_DEFS	+= -DCONFIG_TEST_INFRA

#==============================================================================
# Source Files
#==============================================================================
include srcs_boot_stm.mk

#==============================================================================
# Entrance
#==============================================================================
all: $(TARGET_ELF_DUMP) $(TARGET_HEX_DUMP) $(TARGET_BIN_DUMP)
	@echo "Build Done !"
$(TARGET_BIN_DUMP): $(TARGET_BIN)
	xxd $< > $@

$(TARGET_HEX_DUMP): $(TARGET_HEX)
	hexdump $< > $@

$(TARGET_ELF_DUMP): $(TARGET_ELF)
	$(OBJDUMP) $(OBJDUMP_OPTS) $< > $@
	$(OBJDUMP) -t $< > $(TARGET_SYM)
	$(OBJDUMP) -h $< > $(TARGET_SEC)
	$(OBJDUMP) -h $<

$(TARGET_BIN): $(TARGET_ELF)
	$(OBJCOPY) -O binary $< $@

$(TARGET_HEX): $(TARGET_ELF)
	$(OBJCOPY) -O ihex $< $@

$(TARGET_ELF): $(COBJS) $(AOBJS)
	$(CC) $^ -o $@ $(LD_OPTS)

%.o: %.c
	$(CC) $(CC_OPTS) $(TARGET_DEFS) \
		-c $(INCS) $< -o $@

%.o: %.S
	$(CC) $(CC_OPTS) $(TARGET_DEFS) \
		-c $(INCS) $< -o $@


clean:
	@echo "clean done ."
