include $(TOPDIR)/compile.mk

ifeq ($(OS_TYPE), FreeRTOS)
obj-y	:=$(patsubst %.c,%.o,$(wildcard FreeRTOS/Source/portable/GCC/ARM_CM3/*.c))
obj-y	:=$(patsubst %.c,%.o,$(wildcard FreeRTOS/Source/*.c))

CFLAGS  += -I$(TOPDIR)/system/FreeRTOS/config \
	-I$(TOPDIR)/system/FreeRTOS/Source/include \
	-I$(TOPDIR)/system/FreeRTOS/Source/portable/GCC/$(CPU) \
	-I$(TOPDIR)/system \

endif

CFLAGS += -I../platform/$(VENDOR)/$(CHIP)/inc

dep-y	+=$(obj-y:.o=.d)
CFLAGS += -MMD

lib-y	:= $(LIB_FILE)

all: $(lib-y)
	$(ECHO) "build $(notdir $^) done"

$(lib-y): $(obj-y) $(dep-y)
	$(call cc_cmd,AR,$(notdir $@))
	$(QUIET)$(AR) -r $@ $^
	$(QUIET)$(AR) -d $@ start.o

%.d: %.c
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
