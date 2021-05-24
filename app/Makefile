include $(TOPDIR)/compile.mk

obj-y +=$(patsubst %.S,%.o,$(wildcard src/*.S))
obj-y +=$(patsubst %.c,%.o,$(wildcard src/*.c))

dep-y +=$(obj-y:.o=.d)
CFLAGS += -MMD

lib-y :=$(LIB_FILE)

all: $(lib-y)
	$(ECHO) "build $(notdir $^) done"

$(lib-y): $(obj-y) $(dep-y)
	$(call cc_cmd,AR,$(notdir $@))
	$(QUIET)$(AR) -r $@ $^

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
	$(QUIET)rm -rf $(lib-y) $(obj-y) $(dep-y) *.o *.a *.d
	$(ECHO) "clean done"

.PHONY: clean
