include $(TOPDIR)/compile.mk

obj-y +=$(patsubst %.c,%.o,$(wildcard src/*.c))

ifeq ($(SVR_MOD_TERM),1)
obj-y +=$(patsubst %.c,%.o,$(wildcard term/*.c))
CFLAGS += -I$(CURDIR)/term -DSVR_MOD_TERM
endif

lib-y :=$(LIB_FILE)

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
	$(QUIET)rm -f $(lib-y) $(obj-y)
	$(ECHO) "clean done"

.PHONY: clean
