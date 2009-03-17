/*	vectors.s - interrupt and exception vectors for tricore
 *
 *	Copyright 2001 David Haworth
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
 *	This file reserves space for the interrupt and exception vectors.
 *
 *	The vector tables have some rather special alignment requirements:
 *
 *	- Each vector must be at most 8 words (32 bytes) long, and must be
 *	  aligned on a 32-byte boundary.
 *	- The entire interrupt vector table must be aligned so that all
 *	  vectors can be reached by oring the offset with the base address.
 *	  At worst case (all 256 vectors required) this means that the table
 *	  is 32*256 bytes = 8 KBytes long, and must be aligned on an 8K boundary.
 *	  The best thing to do is to place it at the start of RAM.
 *	- The exception vector table has 8 entries, and must be aligned
 *	  on a 32*8 byte = 256 byte boundary.
*/

#include "arch-kernel.h"
#include "tricore-core.h"
#include "modules/tricore-csfr.h"

	.section	"davros_vectors","aw"

	.globl	interrupt_table
	.type	interrupt_table,@object

interrupt_table:
	.rept	__DAVROS_NVECTORS
	.align	5
	.code32
	bisr	__DAVROS_INTPRIO		/*	Enables interrupts */
	jl		interrupt_handler		/*	Go to common code */
	.word	0						/*	Interrupt type */
	.word	0						/*	Address of C handler */
	.word	0						/*	Parameter for C handler */
	.endr

	.align	8

	.globl	exception_table
	.type	exception_table,@object

exception_table:
	.align	5						/*	Class 0: MMU traps */
	svlcx
	mov		%d4,0
	j		exception_handler

	.align	5						/*	Class 1: Internal protection traps */
	svlcx
	mov		%d4,1
	j		exception_handler

	.align	5						/*	Class 2: Instruction error traps */
	svlcx
	mov		%d4,2
	j		exception_handler

	.align	5						/*	Class 3: Context-handling traps */
	jeq		%d15,EXC_TIN_CSU,process_return
	svlcx
	mov		%d4,3
	j		exception_handler

	.align	5						/*	Class 4: Bus & peripheral traps */
	svlcx
	mov		%d4,4
	j		exception_handler

	.align	5						/*	Class 5: Assertion traps */
	svlcx
	mov		%d4,5
	j		exception_handler

	.align	5						/*	Class 6: System calls */
	svlcx
	mov		%d4,6
	j		exception_handler

	.align	5						/*	Class 7: NMI */
	rfe								/* FIXME */
	svlcx
	mov		%d4,7
	j		exception_handler		/*	FIXME: needs to be better */

/*
 *	exception_handler() - handle (most) exceptions
 *
 *	This routine handles most exceptions by calling the C exception
 *	handler.
 *	This function must not be called - it is jumped to from the exception
 *	vectors.
*/
exception_handler:
	mov		%d5,%d15
	dsync
	nop
	nop
	_MFCR	%d6,PCXI
	call	tricore_exception		/* (class, tin, pcxi) */
	rslcx
	rfe

/*	process_return() - handle a process' main function returning
 *
 *	This routine handles the context list underflow exception that
 *	occurs when a process' main function returns. The return value
 *	in d2 is passed as the parameter to exit().
 *	The exception vector must not save the lower context.
*/
process_return:
	mov		%d4,%d2
	j		__davros_exit

/*	interrupt_handler() - handle an interrupt
 *
 *	This routine handles a normal interrupt. It is jumped to from the
 *	interrupt vector using a jl instruction, so the a11 register contains
 *	the address of the rest of the vector.
 *	This routine must never be called.
 *
 *	FIXME: first version is for Comer-style handling.
 *	There's work to do here for nested interrupts and reentrant kernel
 *	work.
*/
interrupt_handler:
#if 0
	mov.d	%d4,%a11
	call	debug_interrupt
#endif
	ld.a	%a2,[%a11]IVEC_A11(IVEC_HANDLER)
	jz.a	%a2,no_attach
	ld.w	%d4,[%a11]IVEC_A11(IVEC_PARAM)
	mov.a	%a4,%d4					/* Supports int & * parameters */
	calli	%a2
	call	__davros_reschedule
	rslcx
	rfe

no_attach:							/* Flag an unused interrupt exception */
	mov		%d4,8
	mov.d	%d5,%a11
	extr.u	%d5,%d5,5,8				/*	Extract interrupt number */
	dsync
	nop
	nop
	_MFCR	%d6,PCXI
	call	tricore_exception		/* (class, tin, pcxi) */
	rslcx
	rfe
