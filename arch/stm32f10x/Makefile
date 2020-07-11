include $(TOPDIR)/config.mk

#####################################################################
LIB	:=libarch.a

AOBJS	:=$(patsubst %.S,%.o,$(wildcard cpu/*.S))
AOBJS	+=$(patsubst %.S,%.o,$(wildcard hal/*.S))
AOBJS	+=$(patsubst %.S,%.o,$(wildcard lib/*.S))

COBJS	:=$(patsubst %.c,%.o,$(wildcard cpu/*.c))
COBJS	+=$(patsubst %.c,%.o,$(wildcard hal/*.c))
COBJS	+=$(patsubst %.c,%.o,$(wildcard lib/*.c))
#####################################################################

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
