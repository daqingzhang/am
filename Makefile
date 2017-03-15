REL_OUT		:=out
REL_OBJS	:=$(REL_OUT)/objs
REL_OUT_APP	:=$(REL_OBJS)/application
REL_OUT_ARCH	:=$(REL_OBJS)/arch
REL_OUT_DEV	:=$(REL_OBJS)/device
REL_OUT_DRV	:=$(REL_OBJS)/drivers
REL_OUT_SYS	:=$(REL_OBJS)/system

all: clean boot

boot:
	mkdir -p $(REL_OUT) $(REL_OBJS) $(REL_OUT_APP) $(REL_OUT_ARCH) $(REL_OUT_DEV) $(REL_OUT_DRV) $(REL_OUT_SYS)
	make -f Makefile.boot PREFIX=stm32f10x SYSTEM=FreeRTOS

clean:
	make -f Makefile.boot clean
