ARCH	?=arm
CPU		?=armv7
VENDOR	?=st
CHIP	?=stm32f10x
V		?=0

USE_OS	?=0

ifeq ($(V),1)
QUIET	:=
ECHO	:=@\#
else
QUIET	:=@
ECHO	:=@echo
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

ifeq ($(O),)
O	:=out
endif

OUTDIR	:=$(shell mkdir -p $(O)/$(T) && cd $(O)/$(T) && pwd)
OUTDIR	:=$(subst $(CURDIR)/,,$(OUTDIR))

ifeq ($(OUTDIR),)
$(error mkdir OUTDIR failed)
else
$(info OUTDIR=$(OUTDIR) done)
endif

export ECHO QUIET TARGET TOPDIR OUTDIR

TARGET_ELF	:= $(TARGET).elf
TARGET_BIN	:= $(TARGET).bin
TARGET_HEX	:= $(TARGET).hex
TARGET_MAP	:= $(TARGET).map
TARGET_SYM	:= $(TARGET).syms
TARGET_SEC	:= $(TARGET).sec
TARGET_LST	:= $(TARGET).lst

include config.mk

export CHIP ARCH CPU VENDOR

ARCHDIR	:= arch/$(ARCH)/$(CPU)/$(VENDOR)/$(CHIP)
APPDIR	:= app
TGTDIR	:= target/$(T)/source

LIBDIR	:= $(ARCHDIR)
LIBDIR	+= $(APPDIR)
LIBDIR	+= $(TGTDIR)
#LIBDIR	+= device
#LIBDIR	+= drivers
#LIBDIR	+= system
#LIBDIR	+= common

INC		:=-I$(ARCHDIR)/cpu/inc
INC		+=-I$(ARCHDIR)/hal/inc
INC		+=-I$(ARCHDIR)/lib/inc

CCFLAGS		:= -g -mthumb -mcpu=cortex-m3 -march=armv7-m
CCFLAGS		+= -O2 -Wall -Werror -static -fno-common -fno-builtin-printf

LDFLAGS		:= -T $(ARCHDIR)/linker.ld
LDFLAGS		+= $(INC) -L$(APPDIR) -L$(ARCHDIR) -L$(TGTDIR)
LDFLAGS		+= -Wl,-nostdlib,--relax,-Map=$(OUTDIR)/$(TARGET_MAP),--gc-sections
LDFLAGS		+= -nostartfiles -ffast-math -lgcc

DUMP_FLAGS	:= --disassemble-all
DUMP_FLAGS	+= --section=.text --section=.test.startup --section=.data

export CCFLAGS LDFLAGS DUMP_FLAGS

include target/$(T)/config/driver.mk
include target/$(T)/config/device.mk
include target/$(T)/config/system.mk
include target/$(T)/config/target.mk

ifneq ($(USE_OS),0)
OS_FLAGS	:= -DGCC_ARMCM3
OS_FLAGS	+= -DCONFIG_USE_FREERTOS
else
OS_FLAGS	:=
endif

export OS_FLAGS USE_OS

#$(info TOPDIR=$(TOPDIR) TARGET=$(TARGET) CHIP=$(CHIP) \
		ARCH=$(ARCH) CPU=$(CPU) VENDOR=$(VENDOR))

define sub-make
	@for i in $(LIBDIR); do \
		$(MAKE) -C $$i -j4; \
	done;
endef

define sub-clean
	@for i in $(LIBDIR); do \
		$(MAKE) -C $$i $1; \
	done;
endef

TARGETS :=$(TARGET_BIN) $(TARGET_HEX) $(TARGET_ELF) \
			$(TARGET_SYM) $(TARGET_LST) $(TARGET_SEC)

all: $(TARGETS)
	$(ECHO) "GEN $^"
	$(ECHO) "Done !"

$(TARGET_SYM): $(TARGET_ELF)
	$(QUIET)$(OBJDUMP) -t $(OUTDIR)/$< > $(OUTDIR)/$@

$(TARGET_SEC): $(TARGET_ELF)
	$(QUIET)$(OBJDUMP) -h $(OUTDIR)/$< > $(OUTDIR)/$@

$(TARGET_LST): $(TARGET_ELF)
	$(QUIET)$(OBJDUMP) $(DUMP_FLAGS) $(OUTDIR)/$< > $(OUTDIR)/$@

$(TARGET_BIN): $(TARGET_ELF)
	$(QUIET)$(OBJCOPY) -O binary $(OUTDIR)/$< $(OUTDIR)/$@

$(TARGET_HEX): $(TARGET_ELF)
	$(QUIET)$(OBJCOPY) -O ihex $(OUTDIR)/$< $(OUTDIR)/$@

$(TARGET_ELF):
	$(call sub-make)
	$(QUIET)$(CC) $(LDFLAGS) -o $(OUTDIR)/$@ $(ARCHDIR)/cpu/start.o \
			-lapp -larch -ltgt

PHONY	+= clean app arch

clean:
	$(call sub-clean, clean)
	$(shell cd $(O) && rm -rf $(T))

.PHONY:	$(PHONY)
