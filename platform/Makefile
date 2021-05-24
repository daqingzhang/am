include $(TOPDIR)/compile.mk

CPU_TYPE :=$(subst _,,$(CPU))

obj-y +=$(patsubst %.S,%.o,$(wildcard cmsis/src/startup_$(CPU_TYPE).S))
obj-y +=$(patsubst %.c,%.o,$(wildcard cmsis/src/system_ARMCMx.c))
obj-y +=$(patsubst %.S,%.o,$(wildcard $(VENDOR)/$(CHIP)/hal/*.S))
obj-y +=$(patsubst %.c,%.o,$(wildcard $(VENDOR)/$(CHIP)/hal/*.c))
obj-y +=$(patsubst %.S,%.o,$(wildcard $(VENDOR)/$(CHIP)/lib/*.S))
obj-y +=$(patsubst %.c,%.o,$(wildcard $(VENDOR)/$(CHIP)/lib/*.c))
obj-y +=$(patsubst %.c,%.o,$(wildcard main/*.c))

FAULT_FLAGS :=

USAGE_FAULT ?= 1
ifeq ($(USAGE_FAULT),1)
FAULT_FLAGS += -DUSAGE_FAULT
endif

BUS_FAULT ?= 1
ifeq ($(BUS_FAULT),1)
FAULT_FLAGS += -DBUS_FAULT
endif

MEM_FAULT ?= 1
ifeq ($(MEM_FAULT),1)
FAULT_FLAGS += -DMEM_FAULT
endif

CFLAGS += -I$(VENDOR)/$(CHIP)/hal/inc \
	-D$(CPU_TYPE) $(FAULT_FLAGS)\

dep-y +=$(obj-y:.o=.d)
CFLAGS += -MMD

lib-y :=$(LIB_FILE)

all: $(lib-y)
	$(ECHO) "build $(notdir $^) done"

$(lib-y): $(obj-y) $(dep-y)
	$(call cc_cmd,AR,$(notdir $@))
	$(QUIET)$(AR) -r $@ $^
	$(QUIET)$(AR) -d $@ start.o

%.d: %.c
	$(QUIET)$(CC) $(CFLAGS) -c -MT $< -MD -MP -MF $@

%.d: %.S
	$(QUIET)$(CC) $(CFLAGS) -c -MT $< -MD -MP -MF $@

-include $(dep-y)

%.o: %.c %.d
	$(call cc_cmd,CC,$(notdir $@))
	$(QUIET)$(CC) $(CFLAGS) -c $< -o $@

%.o: %.S %.d
	$(call cc_cmd,CC,$(notdir $@))
	$(QUIET)$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(QUIET)rm -f $(lib-y) $(obj-y) $(dep-y)
	$(ECHO) "clean done"

.PHONY: clean
