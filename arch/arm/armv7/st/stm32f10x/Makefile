ifeq ($(TOPDIR),)
$(error invalid TOPDIR)
endif

ifeq ($(OUTDIR),)
$(error invalid OUTDIR)
endif

ifeq ($(TARGET),)
$(error invalid TARGET)
endif

#####################################################################
# ODIR	:=$(OUTDIR)/$(TARGET)/arch/$(ARCH)/$(CPU)/$(VENDOR)/$(CHIP)
# ODIR	:=$(shell mkdir -p $(ODIR) && cd $(ODIR) && pwd)
#
# ifeq ($(wildcard $(ODIR)),)
# $(error mkdir $(ODIR) failed)
# endif
#####################################################################

#####################################################################
CPUDIR	:=cpu
HALDIR	:=hal
LIBDIR	:=lib

INC	:=-I$(CPUDIR)/inc
INC	+=-I$(HALDIR)/inc
INC	+=-I$(LIBDIR)/inc
INC	+=-I$(TOPDIR)/common/inc

LIB	:=libarch.a

AOBJS	:=$(patsubst %.S,%.o,$(wildcard $(CPUDIR)/*.S))
AOBJS	+=$(patsubst %.S,%.o,$(wildcard $(HALDIR)/*.S))
AOBJS	+=$(patsubst %.S,%.o,$(wildcard $(LIBDIR)/*.S))

COBJS	:=$(patsubst %.c,%.o,$(wildcard $(CPUDIR)/*.c))
COBJS	+=$(patsubst %.c,%.o,$(wildcard $(HALDIR)/*.c))
COBJS	+=$(patsubst %.c,%.o,$(wildcard $(LIBDIR)/*.c))
#####################################################################

include $(TOPDIR)/config.mk

CCFLAGS	+=$(INC) $(OS_FLAGS) -DSTM32F10X_MD

all: $(LIB)
	$(ECHO) "build $(notdir $^) done"

$(LIB): $(AOBJS) $(COBJS)
	$(call cc_cmd,AR,$(notdir $@))
	$(QUIET)$(AR) -r $@ $^
	$(QUIET)$(AR) -d $@ start.o

%.o: %.c
	$(call cc_cmd,CC,$(notdir $@))
	$(QUIET)$(CC) $(CCFLAGS) -c $< -o $@

%.o: %.S
	$(call cc_cmd,CC,$(notdir $@))
	$(QUIET)$(CC) $(CCFLAGS) -c $< -o $@

clean:
	$(QUIET)rm -f $(LIB)
	$(QUIET)rm -rf $(COBJS) $(AOBJS)
	$(ECHO) "clean done"

.PHONY: clean
