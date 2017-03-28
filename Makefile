REL_OUT	:=out
CHIPS	:=stm32f10x
SYSTEMS	:=FreeRTOS

all:

led: cleanled
	mkdir -p $(REL_OUT) $(REL_OUT)/led $(REL_OUT)/led/objs
	make -f Makefile.boot CHIP=$(CHIPS) SYSTEM=$(SYSTEMS) APPS=led

key: cleankey
	mkdir -p $(REL_OUT) $(REL_OUT)/key $(REL_OUT)/key/objs
	make -f Makefile.boot CHIP=$(CHIPS) SYSTEM=$(SYSTEMS) APPS=key

vehicle: clean_vehicle
	mkdir -p $(REL_OUT) $(REL_OUT)/key $(REL_OUT)/vehicle/objs
	make -f Makefile.boot CHIP=$(CHIPS) SYSTEM=$(SYSTEMS) APPS=vehicle

cleankey:
	make -f Makefile.boot clean CHIP=$(CHIPS) SYSTEM=$(SYSTEMS) APPS=key

cleanled:
	make -f Makefile.boot clean CHIP=$(CHIPS) SYSTEM=$(SYSTEMS) APPS=led

clean_vehicle:
	make -f Makefile.boot clean CHIP=$(CHIPS) SYSTEM=$(SYSTEMS) APPS=vehicle

clean: cleankey cleanled clean_vehicle

.PHONY: led key vehicle clean
