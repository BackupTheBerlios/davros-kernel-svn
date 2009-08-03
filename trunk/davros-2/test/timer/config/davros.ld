MEMORY
{
	ram (rwx)		: ORIGIN = 0x01800000, LENGTH = 0x08000000
	rs_vect (rwx)	: ORIGIN = 0x00000100, LENGTH = 0x100	/* Reset vector */
	sc_vect (rwx)	: ORIGIN = 0x00000c00, LENGTH = 0x100	/* Syscall vector */
}

SECTIONS
{
	.dv_vector_syscall	: { *(.dv_vector_syscall) } > sc_vect
	.text     			: { *(.text*)    } > ram
	.rodata   			: { *(.rodata*)  } > ram
	.data     			: { *(.data*)    } > ram
	.bss      			: { *(.bss*)     } > ram
}
