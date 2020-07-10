###########################################################
# ODIR	:=$(OUTDIR)/$(TARGET)/app
# ODIR	:=$(shell mkdir -p $(ODIR) && cd $(ODIR) && pwd)
# 
# ifeq ($(wildcard $(ODIR)),)
# $(error mkdir $(ODIR) failed)
# endif
# $(shell mkdir -p $(ODIR)/init)

###########################################################
# TOPDIR:	top directory of project
# INC:		directory of header file
# LIB:		library name will be generated
# AOBJS:	object file name by assembler source file
# COBJS:	object file name by c source file

###########################################################
INC		:=-I$(TOPDIR)/common/inc
INC		+=-I$(TOPDIR)/arch/$(CHIP)/lib/inc
INC		+=-I$(CURDIR)/init

LIB		:=libapp.a

AOBJS	:=$(patsubst %.S,%.o,$(wildcard init/*.S))
COBJS	:=$(patsubst %.c,%.o,$(wildcard init/*.c))
