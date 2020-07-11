include $(TOPDIR)/config.mk

###########################################################
# TOPDIR:	top directory of project
# INC:		directory of header file
# LIB:		library name will be generated
# AOBJS:	object file name by assembler source file
# COBJS:	object file name by c source file

###########################################################
LIB		:=libtgt.a
AOBJS	:=$(patsubst %.S,%.o,$(wildcard *.S))
COBJS	:=$(patsubst %.c,%.o,$(wildcard *.c))

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
