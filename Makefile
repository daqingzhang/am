V		?=0
ifeq ($(V),1)
QUIET	:=
ECHO	:=@\#
else
QUIET	:=@
ECHO	:=@echo
endif
export ECHO QUIET

MK_INFO ?=1

# Directory
###########################################################################
T	?=__default_tgt
ifeq ($(T),)
$(error target {T} is not specified, please select a target in $(CURDIR)/config/ )
endif

ifeq ($(wildcard config/$(T)),)
$(error invalid target T=$(T), please select a target in $(CURDIR)/config/ )
endif
export TARGET :=$(T)

ifeq ($(MAKELEVEL),0)
TOPDIR	:=$(CURDIR)
else
TOPDIR	:=$(shell pwd)
endif

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
export TOPDIR OUTDIR

# Compile Flags
##########################################################################
core-y		:=
CFLAGS		:=
KBUILD_CFLAGS	:=
KBUILD_CPPFLAGS	:=
LIB_LDFLAGS	:=
COMMON_FLAGS	:=
lib-dir		:=

include config/$(T)/target.mk
include config/common.mk

PLATDIR	?= platform/$(VENDOR)/$(CHIP)
export VENDOR CHIP CPU

include compile.mk

CFLAGS +=$(COMMON_FLAGS) $(KBUILD_CFLAGS) \
	-I$(TOPDIR)/platform/cmsis/inc \
	-I$(TOPDIR)/$(PLATDIR)/lib/inc \
	-I$(TOPDIR)/common/inc \

lib-dir	+= app/ platform/
ifneq ($(core-y),)
lib-dir	+= $(core-y)
endif

ifeq ($(RTOS),1)
lib-dir +=system/
ifeq ($(OS_TYPE),FreeRTOS)
CFLAGS  += -I$(TOPDIR)/system/FreeRTOS/config \
	-I$(TOPDIR)/system/FreeRTOS/Source/include \
	-I$(TOPDIR)/system/FreeRTOS/Source/portable/GCC/$(CPU) \
	-I$(TOPDIR)/system \

endif
endif

lib-dir :=$(strip $(lib-dir))
$(info lib-dir=$(lib-dir))

TARGET_ELF	:= $(T).elf
TARGET_BIN	:= $(T).bin
TARGET_HEX	:= $(T).hex
TARGET_MAP	:= $(T).map
TARGET_SYM	:= $(T).syms
TARGET_SEC	:= $(T).sec
TARGET_LST	:= $(T).lst

LDFLAGS := \
	-Lapp \
	-Lconfig/$(T) \
	-L$(PLATDIR) \
	-Lsystem \


LDFLAGS := $(CFLAGS) $(LIB_LDFLAGS) \
	-T $(TOPDIR)/scripts/linker/$(LINKER_FILE) \
	-Wl,-nostdlib,--relax,-Map=$(OUTDIR)/$(TARGET_MAP),--gc-sections \
	-nostartfiles -ffast-math -lgcc \


DPFLAGS := --disassemble-all \
	--section=.text --section=.test.startup --section=.data \


export CFLAGS LDFLAGS

# Compile Commands
########################################################################
ifeq ($(MK_INFO),1)
$(info )
$(info TOPDIR=$(TOPDIR))
$(info OUTDIR=$(OUTDIR))
$(info TARGET=$(TARGET))
$(info ARCH=$(ARCH) CPU=$(CPU) VENDOR=$(VENDOR) CHIP=$(CHIP))
$(info CFLAGS=$(CFLAGS))
$(info LDFLAGS=$(LDFLAGS))
$(info DPFLAGS=$(DPFLAGS))
$(info )
endif

define sub-make
	@for i in $(lib-dir); do \
		$(MAKE) -C $$i -j8; \
	done;
endef

define sub-clean
	@for i in $(lib-dir); do \
		$(MAKE) -C $$i $1; \
	done;
endef

export LIB_FILE ?= builtin.a
lib-files := $(addsuffix $(LIB_FILE),$(lib-dir))
$(info lib-files=$(lib-files))

TARGETS :=$(TARGET_BIN) $(TARGET_HEX) $(TARGET_ELF) $(TARGET_SYM) $(TARGET_LST) $(TARGET_SEC)

all: $(TARGETS)
	$(ECHO) "GEN $^"
	$(ECHO) "Done !"

$(TARGET_SYM): $(TARGET_ELF)
	$(QUIET)$(OBJDUMP) -t $(OUTDIR)/$< > $(OUTDIR)/$@

$(TARGET_SEC): $(TARGET_ELF)
	$(QUIET)$(OBJDUMP) -h $(OUTDIR)/$< > $(OUTDIR)/$@

$(TARGET_LST): $(TARGET_ELF)
	$(QUIET)$(OBJDUMP) $(DPFLAGS) $(OUTDIR)/$< > $(OUTDIR)/$@

$(TARGET_BIN): $(TARGET_ELF)
	$(QUIET)$(OBJCOPY) -O binary $(OUTDIR)/$< $(OUTDIR)/$@

$(TARGET_HEX): $(TARGET_ELF)
	$(QUIET)$(OBJCOPY) -O ihex $(OUTDIR)/$< $(OUTDIR)/$@

$(TARGET_ELF):
	$(call sub-make)
	$(QUIET)$(CC) $(LDFLAGS) -o $(OUTDIR)/$@ $(PLATDIR)/cpu/start.o $(lib-files)

PHONY	+= clean app platform system common

clean:
	$(call sub-clean, clean)
	$(shell cd $(O) && rm -rf $(T))

.PHONY:	$(PHONY)
