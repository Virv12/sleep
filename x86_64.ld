OUTPUT_FORMAT("elf64-x86-64", "elf64-x86-64", "elf64-x86-64")
OUTPUT_ARCH(i386:x86-64)
ENTRY(_start)

SECTIONS {
	. = 0x400000 + SIZEOF_HEADERS;
	.text : { *(.text*) }
	.data : { *(.rodata*) *(.data*) *(.bss*) }
	/DISCARD/ : { *(.note*) }
}
