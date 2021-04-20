include $(TOPDIR)/compile.mk

lib-y := $(addsuffix .a,$(addprefix lib,$(notdir $(CURDIR))))

obj-y +=$(patsubst %.S,%.o,$(wildcard init/*.S))
obj-y +=$(patsubst %.c,%.o,$(wildcard init/*.c))

CFLAGS	+=-Iinit/

all: $(lib-y)
	$(ECHO) "build $(notdir $^) done"

$(lib-y): $(obj-y)
	$(call cc_cmd,AR,$(notdir $@))
	$(QUIET)$(AR) -r $@ $^

%.o: %.c
	$(call cc_cmd,CC,$(notdir $@))
	$(QUIET)$(CC) $(CFLAGS) -c $< -o $@

%.o: %.S
	$(call cc_cmd,CC,$(notdir $@))
	$(QUIET)$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(QUIET)rm -f $(lib-y) init/*.o
	$(ECHO) "clean done"

.PHONY: clean
