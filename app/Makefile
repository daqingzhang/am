ifeq ($(TOPDIR),)
$(error invalid TOPDIR)
endif

ifeq ($(OUTDIR),)
$(error invalid OUTDIR)
endif

ifeq ($(TARGET),)
$(error invalid TARGET)
endif


###########################################################
# ODIR	:=$(OUTDIR)/$(TARGET)/app
# ODIR	:=$(shell mkdir -p $(ODIR) && cd $(ODIR) && pwd)
# 
# ifeq ($(wildcard $(ODIR)),)
# $(error mkdir $(ODIR) failed)
# endif
# $(shell mkdir -p $(ODIR)/init)
###########################################################

###########################################################
INC		:=-I$(TOPDIR)/common/inc
INC		+=-I$(TOPDIR)/arch/$(ARCH)/$(CPU)/$(VENDOR)/$(CHIP)/lib/inc

LIB		:=libapp.a

SRCDIR	:=init
AOBJS	:=$(patsubst %.S,%.o,$(wildcard $(SRCDIR)/*.S))
COBJS	:=$(patsubst %.c,%.o,$(wildcard $(SRCDIR)/*.c))

include $(TOPDIR)/config.mk

CCFLAGS	+=$(INC)
###########################################################

all: $(LIB)
	$(ECHO) "build $(notdir $^) done"

$(LIB): $(AOBJS) $(COBJS)
	$(call cc_cmd,AR,$(notdir $@))
	$(QUIET)$(AR) -r $@ $^

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
