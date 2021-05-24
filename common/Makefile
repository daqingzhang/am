include $(TOPDIR)/compile.mk

obj-y +=$(patsubst %.c,%.o,$(wildcard *.c))

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

%.o: %.c
	$(call cc_cmd,CC,$(notdir $@))
	$(QUIET)$(CC) $(CFLAGS) -c $< -o $@

%.o: %.S
	$(call cc_cmd,CC,$(notdir $@))
	$(QUIET)$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(QUIET)rm -f $(lib-y) $(obj-y) $(dep-y)
	$(ECHO) "clean done"

.PHONY: clean
