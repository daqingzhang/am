###########################################################
# TOPDIR:	top directory of project
# INC:		directory of header file
# LIB:		library name will be generated
# AOBJS:	object file name by assembler source file
# COBJS:	object file name by c source file

###########################################################
INC		:=-I$(TOPDIR)/common/inc
INC		+=-I$(TOPDIR)/arch/$(CHIP)/lib/inc
INC		+=-I$(TOPDIR)/$(TARGET)/source

LIB		:=libtgt.a

AOBJS	:=$(patsubst %.S,%.o,$(wildcard *.S))
COBJS	:=$(patsubst %.c,%.o,$(wildcard *.c))
