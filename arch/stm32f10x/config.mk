#####################################################################
# ODIR	:=$(OUTDIR)/$(TARGET)/arch/$(ARCH)/$(CPU)/$(VENDOR)/$(CHIP)
# ODIR	:=$(shell mkdir -p $(ODIR) && cd $(ODIR) && pwd)
#
# ifeq ($(wildcard $(ODIR)),)
# $(error mkdir $(ODIR) failed)
# endif

#####################################################################
# TOPDIR:	top directory of project
# INC:		directory of header file
# LIB:		library name will be generated
# AOBJS:	object file name by assembler source file
# COBJS:	object file name by c source file

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
