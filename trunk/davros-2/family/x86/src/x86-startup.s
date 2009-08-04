/*	x86-startup.s - entry point for cold boot for x86 CPU
 *
 *	Copyright 2009 David Haworth
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
*/

#include <davros/config.h>
#include <x86-asm.h>
#include <x86-core.h>
#include <davros/process.h>

#ifdef __DV_IDENT
__DV_IDENT("$Id$")
#endif

/*==============================================================================
 *  __dv_x86_startup - assembler startup code for x86 family processors
 *==============================================================================
*/
	.global	__dv_x86_startup
	.extern	__dv_C_startup
	.extern	__dv_startup
	.extern	__dv_kernel_sp

	.text

	.align	4
__dv_x86_startup:
	jmp	cold_boot		/* all we can do here. the boot word must be next */

/*	MULTIBOOT header for GRUB
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

	movl	$__dv_kernel_sp,%esp
	movl	$0,%ebp

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

	pushl	$(FLAG_1)
	popfl

	movl	$0,%edx
	movl	$0x0008,%eax
	movl	$__DV_MSR_SYSENTER_CS,%ecx
	wrmsr

	movl	%esp,%eax
	movl	$__DV_MSR_SYSENTER_SP,%ecx
	wrmsr

	movl	$__dv_syscall,%eax
	movl	$__DV_MSR_SYSENTER_PC,%ecx
	wrmsr

	movl	$_continue,%edx
	movl	%esp,%ecx
	sysexit

_continue:
	call	__dv_C_startup
	call	__dv_startup
	jmp		__dv_x86_startup		/* Can't boot. Try again */

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
