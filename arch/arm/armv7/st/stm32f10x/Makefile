ifeq ($(TOPDIR),)
$(error invalid TOPDIR=$(TOPDIR))
endif

CPUDIR	:=$(CURDIR)/cpu
HALDIR	:=$(CURDIR)/hal
LIBDIR	:=$(CURDIR)/lib

INC	:=-I$(CPUDIR)/inc
INC	+=-I$(HALDIR)/inc
INC	+=-I$(LIBDIR)/inc
INC	+=-I$(TOPDIR)/common/inc

ODIR	:=$(OUTDIR)/arch/$(ARCH)/$(CPU)/$(VENDOR)/$(CHIP)
ODIR	:=$(shell mkdir -p $(ODIR) && cd $(ODIR) && pwd)

ifeq ($(wildcard $(ODIR)),)
$(error mkdir $(ODIR) failed)
endif

$(shell mkdir -p $(ODIR)/cpu)
$(shell mkdir -p $(ODIR)/hal)
$(shell mkdir -p $(ODIR)/lib)

AOBJS	:=$(patsubst %.S,%.o,$(wildcard $(CPUDIR)/*.S))
COBJS	:=$(patsubst %.c,%.o,$(wildcard $(CPUDIR)/*.c))
COBJS	+=$(patsubst %.c,%.o,$(wildcard $(HALDIR)/*.c))
COBJS	+=$(patsubst %.c,%.o,$(wildcard $(LIBDIR)/*.c))

include $(TOPDIR)/config.mk

CCFLAGS	+=-DSTM32F10X_MD $(INC)

LIB	:=$(ODIR)/libarch.a

all: $(LIB)
	$(ECHO) "build $^ done"

$(LIB): $(AOBJS) $(COBJS)
	$(call cc_cmd,AR,$(notdir $@))
	@$(AR) -r $@ $^

%.o: %.c
	$(call cc_cmd,CC,$(notdir $@))
	@$(CC) $(CCFLAGS) -c $< -o $@

%.o: %.S
	$(call cc_cmd,CC,$(notdir $@))
	@$(CC) $(CCFLAGS) -c $< -o $@

clean:
	@rm -f $(LIB)
	@rm -rf $(CPUDIR)/*.o $(HALDIR)/*.o $(LIBDIR)/*.o

.PHONY: all clean
