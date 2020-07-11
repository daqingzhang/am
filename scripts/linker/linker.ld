OUTPUT_FORMAT("elf32-littlearm","elf32-littlearm","elf32-littlearm")
OUTPUT_ARCH(arm)
ENTRY(_start)

MEMORY
{
	flash (rx) : ORIGIN = 0x08000000, LENGTH = 0x1F800 /* 126K FLASH*/
	ram   (rw) : ORIGIN = 0x20000000, LENGTH = 0x5000  /* 20KB RAM*/
}

ASSERT(ORIGIN(flash) == ALIGN(ORIGIN(flash), 0x80), "ERROR: flash memory is not aligned !");

SECTIONS
{
	.vect_table : {
		__isr_vect_start__ = . ;
		KEEP(*(.vect_table))
		. = ALIGN(4);
		__isr_vect_end__ = . ;
	} >flash

	.text : AT (ADDR(.text)) {
		__text_start__ = . ;
		*(.text)
		*(SORT_BY_NAME(.text.*))
		. = ALIGN(4);
		__text_end__ = . ;
	} >flash

	__rodata_start__ = . ;
	.rodata : {
		*(.g_rodata)
		*(SORT_BY_ALIGNMENT(SORT_BY_NAME(.rodata*)))
		. = ALIGN(4);
	} >flash

	__exidx_start = . ;
	.ARM.exidx : {
		*(.ARM.exidx*)
		*(.gnu.linkonce.armexidx.*)
	} >flash
	__exidx_end = . ;

	.rel.dyn : {
		. = ALIGN(4);
		__reldyn_start__ = . ;
		*(.rel*)
		. = ALIGN(4);
		__reldyn_end__ = . ;
	} >flash
	__rodata_end__ = . ;
	__flash_end__ = . ;

	.data : AT (__rodata_end__) {
		. = ALIGN(4);
		__data_start__ = . ;
		*(.data)
		*(SORT_BY_NAME(.data.*))
		*(.text_sram)
		*(SORT_BY_NAME(.text_sram.*))
		. = ALIGN(4);
		__data_end__ = . ;
	} >ram

	.bss (NOLOAD) : {
		__bss_start__ = . ;
		*(.shbss)
		*(.bss .bss.*)
		*(COMMON)
		. = ALIGN(8);
		*(.ram.b)
		. = ALIGN(4);
		__bss_end__ = . ;
	} >ram
	__ram_end__ = . ;

	.stack_dummy (.) (COPY) : {
		. = 0x1000 ;
		. = ALIGN(8);
	} > ram

	.gdata (.) (COPY) : {
		. = 0x100;
		. = ALIGN(4);
	} >ram

    __StackTop = ORIGIN(ram) + LENGTH(ram) - SIZEOF(.gdata);
	__StackLimit = __StackTop - SIZEOF(.stack_dummy) ;

    __gdata_start = ORIGIN(ram) + LENGTH(ram) - SIZEOF(.gdata);
	__gdata_end = ORIGIN(ram) + LENGTH(ram);
	__gdata_size = SIZEOF(.gdata);

	__free_ram = __StackLimit - __ram_end__;

	/DISCARD/ : { *(.note.GNU-stack) }
	/DISCARD/ : { *(.gnu_debuglink) }
/*
	/DISCARD/ : { *(.dynamic*) }
	/DISCARD/ : { *(.dynstr*) }
	/DISCARD/ : { *(.plt*) }
	/DISCARD/ : { *(.interp*) }
	/DISCARD/ : { *(.gnu*) }
*/
}

ASSERT(__StackLimit > __ram_end__, "region RAM overflowed with stack");
ASSERT(__flash_end__ < (ORIGIN(flash) + LENGTH(flash)), "ERROR: no enough space for store code in FLASH !");
ASSERT(__ram_end__ < (ORIGIN(ram) + LENGTH(ram)), "ERROR: no enough space for store data in RAM!");

