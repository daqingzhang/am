include $(TOPDIR)/compile.mk

obj-y +=$(patsubst %.S,%.o,$(wildcard cmsis/src/startup_ARMCM3.S))
obj-y +=$(patsubst %.c,%.o,$(wildcard cmsis/src/system_ARMCM3.c))
obj-y +=$(patsubst %.S,%.o,$(wildcard $(VENDOR)/$(CHIP)/hal/*.S))
obj-y +=$(patsubst %.c,%.o,$(wildcard $(VENDOR)/$(CHIP)/hal/*.c))
obj-y +=$(patsubst %.S,%.o,$(wildcard $(VENDOR)/$(CHIP)/lib/*.S))
obj-y +=$(patsubst %.c,%.o,$(wildcard $(VENDOR)/$(CHIP)/lib/*.c))
obj-y +=$(patsubst %.c,%.o,$(wildcard main/*.c))

CFLAGS += -I$(VENDOR)/$(CHIP)/hal/inc \
	-I$(VENDOR)/$(CHIP)/inc \
	-I$(TOPDIR)/app \
	-I$(TOPDIR)/platform/cmsis/inc \

lib-y :=$(LIB_FILE)

all: $(lib-y)
	$(ECHO) "build $(notdir $^) done"

$(lib-y): $(obj-y)
	$(call cc_cmd,AR,$(notdir $@))
	$(QUIET)$(AR) -r $@ $^
	$(QUIET)$(AR) -d $@ start.o

%.o: %.c
	$(call cc_cmd,CC,$(notdir $@))
	$(QUIET)$(CC) $(CFLAGS) -c $< -o $@

%.o: %.S
	$(call cc_cmd,CC,$(notdir $@))
	$(QUIET)$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(QUIET)rm -f $(lib-y) $(obj-y)
	$(ECHO) "clean done"

.PHONY: clean
