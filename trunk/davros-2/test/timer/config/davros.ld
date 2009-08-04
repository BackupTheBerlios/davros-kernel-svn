
SECTIONS
{
	. = 0x00100000;

	.text     			: { *(.text*)    } > ram
	.rodata   			: { *(.rodata*)  } > ram

	.data     			: { *(.data*)    } > ram
	.bss      			: { *(.bss*)     } > ram
}
