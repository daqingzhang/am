include $(TOPDIR)/compile.mk

ifeq ($(OS_TYPE), FreeRTOS)
obj-y	:=$(patsubst %.c,%.o,$(wildcard FreeRTOS/Source/portable/GCC/ARM_CM3/*.c))
obj-y	:=$(patsubst %.c,%.o,$(wildcard FreeRTOS/Source/*.c))
endif
$(info "OS_TYPE=$(OS_TYPE)")

CFLAGS += -I../platform/$(VENDOR)/$(CHIP)/lib/inc

lib-y	:= $(LIB_FILE)

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
