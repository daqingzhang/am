REL_OUT		:=out

all: clean led

led:
	mkdir -p $(REL_OUT) $(REL_OUT)/led $(REL_OUT)/led/objs
	make -f Makefile.boot CHIP=stm32f10x SYSTEM=FreeRTOS APPS=led

clean:
	make -f Makefile.boot clean CHIP=stm32f10x SYSTEM=FreeRTOS APPS=led

.PHONY: led boot clean
