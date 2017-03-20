REL_OUT		:=out

all:

led: cleanled
	mkdir -p $(REL_OUT) $(REL_OUT)/led $(REL_OUT)/led/objs
	make -f Makefile.boot CHIP=stm32f10x SYSTEM=FreeRTOS APPS=led
key: cleankey
	mkdir -p $(REL_OUT) $(REL_OUT)/key $(REL_OUT)/key/objs
	make -f Makefile.boot CHIP=stm32f10x SYSTEM=FreeRTOS APPS=key

cleankey:
	make -f Makefile.boot clean CHIP=stm32f10x SYSTEM=FreeRTOS APPS=key
cleanled:
	make -f Makefile.boot clean CHIP=stm32f10x SYSTEM=FreeRTOS APPS=led

clean: cleankey cleanled

.PHONY: led key clean
