/*	entry.s - entry point for cold boot for x86 CPU
 *
 *	Copyright 2002 David Haworth
 *
 *	This file is free software; you can redistribute it and/or modify
 *	it under the terms of the GNU General Public License as published by
 *	the Free Software Foundation; either version 2, or (at your option)
 *	any later version.
 *
 *	It is distributed in the hope that it will be useful,
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *	GNU General Public License for more details.
 *
 *	You should have received a copy of the GNU General Public License
 *	along with this program; see the file COPYING.  If not, write to
 *	the Free Software Foundation, 59 Temple Place - Suite 330,
 *	Boston, MA 02111-1307, USA.
 *
 *
 *	This file contains the entry code for x86 programs. We assume
 *	that some kind of bootloader has already placed our system
 *	in RAM, and that the CPU is running in native mode.
 *
 *	Before we can execute any C functions, we must perform the following
 *	initialisations:
 *		- initialise the GDT and all the segment selectors
 *
 *	The boot routine expects some configuration to be supplied via
 *	the board-config.h file. The following macros are expected:
 *
 *	Macro					Notes
 *	COPYRIGHT_YEAR			String for the copyright notice.
 *	COPYRIGHT_AUTHOR		String for the copyright notice.
 *	BOOT_STACK				Where to put the stack (high end!).
 *	BOOT_INIT_CPU			Function to intialise the CPU
 *	BOOT_MAIN				C entry point for program.
*/

#include "x86.h"
#include "x86-core.h"

/*
 *	Default values for unsupplied configuration macros
*/
#if !defined(COPYRIGHT_YEAR)
#define COPYRIGHT_YEAR		"2002"
#endif
#if !defined(COPYRIGHT_AUTHOR)
#define COPYRIGHT_AUTHOR	"David Haworth"
#endif
#if !defined(BOOT_MAIN)
#define BOOT_MAIN			main
#endif


/*
 * entry - entry point for x86 cold-boot
*/

	.text

	.globl	entry
	.type	entry,@function

	.extern	BOOT_MAIN

	.align	4
entry:
	jmp	cold_boot		/* all we can do here. the boot word must be next */

	.align	4
/*	Copyright notice.
	Inserted as early as possible in the ROM.
*/
_copyright:
	.ascii	"Copyright "
	.ascii	COPYRIGHT_YEAR
	.ascii	" "
	.ascii	COPYRIGHT_AUTHOR
	.ascii	". "
_gpl:
	.asciz	"Released under the Gnu General Public License."

/*	MULTIBOOT header
 *
 *	FIXME: need some #defines for this. Also conditional compilation.
*/
	.align	4
	.long	0x1badb002		/* Magic number */
	.long	0				/* Flags */
	.long	-0x1badb002		/* Checksum */

	.align	4
cold_boot:
	cli

	movl	$_boot_stack_end,%esp
	movl	$0,%ebp
	pushl	$(FLAG_1)
	popfl

	movl	$_gdtr,%eax
	lgdt	(%eax)

#if 0
	/* 	For some reason we can't do this. But CS seems to contain
	 *	the right value (0x0008) anyway
	*/
	movw	$0x0008,%ax
	movw	%ax,%cs
#endif

	movw	$0x0010,%ax
	movw	%ax,%ds
	movw	%ax,%es
	movw	%ax,%fs
	movw	%ax,%gs
	movw	%ax,%ss

/*	A function to initialise the rest of the CPU is called.
 *	We only call this routines if it is defined.
*/

#if defined(BOOT_INIT_CPU)
	.extern	BOOT_INIT_CPU
	call	BOOT_INIT_CPU
#endif

/*	Jump to C entry point.
*/
	call	BOOT_MAIN
	jmp		entry		/* Can't boot. Try again */

	.data
	.align	4
_boot_stack_start:
	.fill	1024,4,0
_boot_stack_end:
	.long	0xdeafc0de



/*
 *	The global descriptor table for a flat memory model
*/
	.globl	_gdt
	.type	_gdt,@object

	.align	8
_gdtr:
	.word	23		/* 3 * 8 - 1 */
	.long	_gdt

	.align	8
_gdt:
	/*	0:	Null descriptor */
	.long	0
	.long	0

	/*	1 (0x0008):	Code descriptor */
	.long	DT0_LIMIT
	.long	DT1_G | DT1_DB | DT1_LIMIT | DT1_P | DT1_S | DT1_TYPE_CR

	/*	2 (0x0010):	Data descriptor */
	.long	DT0_LIMIT
	.long	DT1_G | DT1_DB | DT1_LIMIT | DT1_P | DT1_S | DT1_TYPE_DW

#if 0
	/*	3 (0x0018):	Another code descriptor */
	.long	DT0_LIMIT
	.long	DT1_G | DT1_DB | DT1_LIMIT | DT1_P | DT1_S | DT1_TYPE_CR

	/*	4 (0x0020):	Interrupt code descriptor */
	.long	DT0_LIMIT
	.long	DT1_G | DT1_DB | DT1_LIMIT | DT1_P | DT1_S | DT1_TYPE_CR
#endif
