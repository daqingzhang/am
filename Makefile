V		?=1
ARCH	?=arm
CPU		?=armv7
VENDOR	?=st
CHIP	?=stm32f10x
USE_OS	?=0

ifneq ($(V),1)
ECHO	:=@\#
QUIET	:=
else
ECHO	:=@echo
QUIET	:=@
endif

ifeq ($(MAKELEVEL),0)
TOPDIR	:=$(CURDIR)
else
TOPDIR	:=$(shell pwd)
endif

ifeq ($(T),)
$(error target {T} is not specified)
endif

ifeq ($(wildcard target/$(T)),)
$(error invalid target T=$(T))
endif

TARGET		:= $(T)

ifneq ($(O),)
OUTDIR	:=$(CURDIR)/$(O)
else
OUTDIR	:=$(CURDIR)/out
endif

export ECHO QUIET TARGET TOPDIR OUTDIR

TARGET_ELF	:= $(TARGET).elf
TARGET_BIN	:= $(TARGET).bin
TARGET_HEX	:= $(TARGET).hex
TARGET_MAP	:= $(TARGET).map
TARGET_SYM	:= $(TARGET).syms
TARGET_SEC	:= $(TARGET).sec
TARGET_LST	:= $(TARGET).lst

include target/$(T)/config/driver.mk
include target/$(T)/config/device.mk
include target/$(T)/config/system.mk
include target/$(T)/config/target.mk

include config.mk

export CHIP ARCH CPU VENDOR

ARCHDIR	:= arch/$(ARCH)/$(CPU)/$(VENDOR)/$(CHIP)
LIBDIR	:= $(ARCHDIR)
#LIBDIR	+= app
#LIBDIR	+= device
#LIBDIR	+= drivers
#LIBDIR	+= system
#LIBDIR	+= common
#LIBDIR	+= target/$(TARGET)/source

CCFLAGS		:= -g -mthumb -mcpu=cortex-m3 -march=armv7-m
CCFLAGS		+= -O2 -Wall -Werror -static -fno-common -fno-builtin-printf

LDFLAGS		:= -T $(ARCHDIR)/linker.ld
LDFLAGS		+= -Wl,-nostdlib,--relax,-Map=$(TARGET_MAP),--gc-sections
LDFLAGS		+= -nostartfiles -ffast-math -lgcc

DUMP_FLAGS	:= --disassemble-all
DUMP_FLAGS	+= --section=.text --section=.test.startup --section=.data

export CCFLAGS LDFLAGS DUMP_FLAGS

OS_FLAGS	:=
ifneq ($(USE_OS),0)
OS_FLAGS	:= -DGCC_ARMCM3
OS_FLAGS	+= -DCONFIG_USE_FREERTOS
endif

#$(info TOPDIR=$(TOPDIR) TARGET=$(TARGET) CHIP=$(CHIP) \
		ARCH=$(ARCH) CPU=$(CPU) VENDOR=$(VENDOR))

define sub-make
	@for i in $(LIBDIR); do \
		$(MAKE) -C $$i; \
	done;
endef

define sub-clean
	@for i in $(LIBDIR); do \
		$(MAKE) -C $$i $1; \
	done;
endef

all: $(TARGET_ELF)
	@echo "Build Done !"

$(TARGET_SYM): $(TARGET_ELF)
	$(OBJDUMP) -t $< > $@

$(TARGET_SEC): $(TARGET_ELF)
	$(OBJDUMP) -h $< > $@

$(TARGET_LST): $(TARGET_ELF)
	$(OBJDUMP) $(DUMP_FLAGS) $< > $@

$(TARGET_BIN): $(TARGET_ELF)
	$(OBJCOPY) -O binary $< $@

$(TARGET_HEX): $(TARGET_ELF)
	$(OBJCOPY) -O ihex $< $@

$(TARGET_ELF):
	$(call sub-make)
#	$(CC) $^ -o $@ $(LDFLAGS)

PHONY	+= clean

clean:
	$(call sub-clean, clean)

.PHONY:	$(PHONY)
