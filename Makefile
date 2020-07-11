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
#################################################################################
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
#################################################################################
COMM_FLAGS	:=

include config/$(T)/target.mk

ARCH	?=arm

ifeq ($(CHIP),stm32f10x)
CPU		:=ARM_CM3
COMM_FLAGS 	+=-DSTM32F10X_MD
COMM_FLAGS	+= -mthumb -mcpu=cortex-m3 -march=armv7-m
else
$(error "unknown CHIP=$(CHIP)")
endif
export ARCH CPU

ifeq ($(DEBUG),1)
COMM_FLAGS	+=-DDEBUG
endif

OS_TYPE ?=FreeRTOS
ifeq ($(USE_OS),1)
ifeq ($(CHIP),stm32f10x)
COMM_FLAGS	+= -DGCC_ARMCM3
endif
COMM_FLAGS	+= -D$(OS_TYPE)

ifeq ($(OS_TYPE),FreeRTOS)
COMM_FLAGS  += -I$(TOPDIR)/system/FreeRTOS/config \
	-I$(TOPDIR)/system/FreeRTOS/Source/include \
	-I$(TOPDIR)/system/FreeRTOS/Source/portable/GCC/$(CPU) \

endif
lib-dir +=system
endif

TARGET_ELF	:= $(T).elf
TARGET_BIN	:= $(T).bin
TARGET_HEX	:= $(T).hex
TARGET_MAP	:= $(T).map
TARGET_SYM	:= $(T).syms
TARGET_SEC	:= $(T).sec
TARGET_LST	:= $(T).lst

include config.mk

ARCHDIR	:= arch/$(CHIP)

lib-dir	+= \
	app \
	config/$(T) \
	$(ARCHDIR) \

INC	:= \
	-I$(TOPDIR)/$(ARCHDIR)/cpu/inc \
	-I$(TOPDIR)/$(ARCHDIR)/hal/inc \
	-I$(TOPDIR)/$(ARCHDIR)/lib/inc \
	-I$(TOPDIR)/$(ARCHDIR) \
	-I$(TOPDIR)/app \
	-I$(TOPDIR)/config/$(T) \
	-I$(TOPDIR)/common/inc \

INC_LD	:= \
	-Lapp \
	-Lconfig/$(T) \
	-L$(ARCHDIR) \

LDFLAGS		:=
LDFLAGS		+= $(INC) $(INC_LD) $(LIB_LDFLAGS)
LDFLAGS		+= -T $(ARCHDIR)/linker.ld
LDFLAGS		+= -Wl,-nostdlib,--relax,-Map=$(OUTDIR)/$(TARGET_MAP),--gc-sections
LDFLAGS		+= -nostartfiles -ffast-math -lgcc

DUMP_FLAGS  :=
DUMP_FLAGS	+= --disassemble-all
DUMP_FLAGS	+= --section=.text --section=.test.startup --section=.data

CCFLAGS	:=
CCFLAGS += $(INC) $(COMM_FLAGS) $(KBUILD_CFLAGS)
CCFLAGS	+= -g -O2 -Wall -Werror -static -fno-common -fno-builtin-printf

CPPFLAGS	:= $(INC) $(COMM_FLAGS) $(KBUILD_CPPFLAGS)

export CCFLAGS CPPFLAGS LDFLAGS DUMP_FLAGS

# Compile Commands
#################################################################################
ifeq ($(MK_INFO),1)
$(info )
$(info TOPDIR=$(TOPDIR))
$(info OUTDIR=$(OUTDIR))
$(info TARGET=$(TARGET))
$(info ARCH=$(ARCH) CPU=$(CPU) VENDOR=$(VENDOR) CHIP=$(CHIP))
$(info CCFLAGS=$(CCFLAGS))
$(info LDFLAGS=$(LDFLAGS))
$(info DUMP_FLAGS=$(DUMP_FLAGS))
$(info )
endif

define sub-make
	@for i in $(lib-dir); do \
		$(MAKE) -C $$i -j4; \
	done;
endef

define sub-clean
	@for i in $(lib-dir); do \
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
