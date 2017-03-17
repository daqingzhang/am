CHIP_NAME	:=$(CHIP)
OS_NAME		:=$(SYSTEM)
APP_NAME	:=$(APPS)
ARCH		:=armv7

#==============================================================================
# Directory
#==============================================================================
OUT_DIR		:=out/$(APP_NAME)
OUT_OBJS_DIR	:=$(OUT_DIR)/objs

APP_DIR		:=application
APP_TASK_DIR	:=$(APP_DIR)/$(APP_NAME)
APP_TASK_INC	:=$(APP_DIR)/$(APP_NAME)/include
APP_INC		:=$(APP_DIR)/include

DEV_INC		:=device/include
DRV_INC		:=drivers/$(CHIP_NAME)/include
ARCH_INC	:=arch/$(ARCH)/$(CHIP_NAME)/include
ARCH_CPU_INC	:=arch/$(ARCH)/$(CHIP_NAME)/cpu/include

SYS_CFG_INC	:=system/$(OS_NAME)/config
SYS_SRC_INC	:=system/$(OS_NAME)/Source/include
SYS_PORT_INC	:=system/$(OS_NAME)/Source/portable/GCC/ARM_CM3
SYS_MEM_INC	:=system/$(OS_NAME)/Source/portable/MemMang

INCS		+= -I$(APP_INC)
INCS		+= -I$(APP_DIR)
INCS		+= -I$(APP_TASK_INC)
INCS		+= -I$(APP_TASK_DIR)
INCS		+= -I$(DEV_INC)
INCS		+= -I$(DRV_INC)
INCS		+= -I$(ARCH_INC)
INCS		+= -I$(ARCH_CPU_INC)
INCS		+= -I$(SYS_CFG_INC)
INCS		+= -I$(SYS_SRC_INC)
INCS		+= -I$(SYS_PORT_INC)
INCS		+= -I$(SYS_MEM_INC)

#==============================================================================
# Target Files
#==============================================================================
TARGET		:= boot
TARGET_ELF	:= $(TARGET).elf
TARGET_BIN	:= $(TARGET).bin
TARGET_HEX	:= $(TARGET).hex
TARGET_MAP	:= $(TARGET).map
TARGET_SYM	:= $(TARGET).syms
TARGET_SEC	:= $(TARGET).sec
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

LD_OPTS		:= -T linker_boot.ld $(INCS)
LD_OPTS		+= -Wl,-nostdlib,--relax,-Map=$(TARGET_MAP),--gc-sections
LD_OPTS		+= -nostartfiles -ffast-math -lgcc

OBJDUMP_OPTS	:= --disassemble-all
OBJDUMP_OPTS	+= --section=.text --section=.test.startup --section=.data

#==============================================================================
# Macro Definitions
#==============================================================================
TARGET_DEFS	:= -DHOST_DEBUG=1
TARGET_DEFS	+= -DSTM32F10X_MD
TARGET_DEFS	+= -DGCC_ARMCM3
TARGET_DEFS	+= -DCONFIG_USE_FREERTOS

#==============================================================================
# Source Files
#==============================================================================
include srcs_boot.mk

#==============================================================================
# Entrance
#==============================================================================
all: $(TARGET_ELF_DUMP) $(TARGET_HEX_DUMP) $(TARGET_BIN_DUMP)
	@#mv -f $(TARGET_ELF) $(OUT_DIR)/
	@#mv -f $(TARGET_BIN) $(OUT_DIR)/
	@#mv -f $(TARGET_HEX) $(OUT_DIR)/
	@#mv -f $(TARGET_MAP) $(OUT_DIR)/
	@#mv -f $(TARGET_SYM) $(OUT_DIR)/
	@#mv -f $(TARGET_SEC) $(OUT_DIR)/
	@#mv -f $(TARGET_ELF_DUMP) $(OUT_DIR)/
	@#mv -f $(TARGET_BIN_DUMP) $(OUT_DIR)/
	@#mv -f $(TARGET_HEX_DUMP) $(OUT_DIR)/
	@echo "Build Done !"
$(TARGET_BIN_DUMP): $(TARGET_BIN)
	xxd $< > $@

$(TARGET_HEX_DUMP): $(TARGET_HEX)
	hexdump $< > $@

$(TARGET_ELF_DUMP): $(TARGET_ELF)
	$(OBJDUMP) $(OBJDUMP_OPTS) $< > $@
	$(OBJDUMP) -t $< > $(TARGET_SYM)
	$(OBJDUMP) -h $< > $(TARGET_SEC)

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
	rm -f $(OUT_OBJS_DIR)/*.o
	rm -f $(OUT_DIR)/$(TARGET_ELF)
	rm -f $(OUT_DIR)/$(TARGET_BIN)
	rm -f $(OUT_DIR)/$(TARGET_HEX)
	rm -f $(OUT_DIR)/$(TARGET_MAP)
	rm -f $(OUT_DIR)/$(TARGET_SYM)
	rm -f $(OUT_DIR)/$(TARGET_SEC)
	rm -f $(OUT_DIR)/$(TARGET_ELF_DUMP)
	rm -f $(OUT_DIR)/$(TARGET_BIN_DUMP)
	rm -f $(OUT_DIR)/$(TARGET_HEX_DUMP)
	rm -f $(TARGET_SEC)
	rm -f $(TARGET_SYM)
	rm -f $(TARGET_BIN)
	rm -f $(TARGET_HEX)
	rm -f $(TARGET_MAP)
	rm -f $(TARGET_ELF)
	rm -f $(TARGET_ELF_DUMP)
	rm -f $(TARGET_BIN_DUMP)
	rm -f $(TARGET_HEX_DUMP)
	rm -f application/$(APP_NAME)/*.o
	rm -f arch/$(ARCH)/$(CHIP_NAME)/cpu/*.o
	rm -f arch/$(ARCH)/$(CHIP_NAME)/lib/*.o
	rm -f drivers/$(CHIP_NAME)/*.o
	rm -f device/$(CHIP_NAME)/*.o
	rm -f system/$(OS_NAME)/Source/*.o
	rm -f system/$(OS_NAME)/Source/portable/MemMang/*.o
	rm -f system/$(OS_NAME)/Source/portable/GCC/ARM_CM3/*.o

