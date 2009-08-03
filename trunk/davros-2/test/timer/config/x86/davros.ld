MEMORY
{
	ram (rwx)		: ORIGIN = 0x00000000, LENGTH = 0x08000000
}

SECTIONS
{
	.dv_vector			: { *(Vectors)   } > ram
	.text     			: { *(.text*)    } > ram
	.rodata   			: { *(.rodata*)  } > ram
	.data     			: { *(.data*)    } > ram
	.bss      			: { *(.bss*)     } > ram
}
