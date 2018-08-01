ifeq ($(TOPDIR),)
$(error invalid TOPDIR)
endif

ifeq ($(OUTDIR),)
$(error invalid OUTDIR)
endif

ifeq ($(TARGET),)
$(error invalid TARGET)
endif

include $(CURDIR)/config.mk
include $(TOPDIR)/config.mk

ifeq ($(LIB),)
$(error invalid LIB)
endif

CCFLAGS	+=$(INC) $(OS_FLAGS) -DSTM32F10X_MD
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
