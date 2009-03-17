/*	vectors.s - interrupt and exception vectors for tricore
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
 *	This file reserves space for the interrupt and exception vectors.
 *
 *	The x86 CPU has 256 interrupt and trap vectors. Each vector is
 * 	the address of a handler routine that must save/restore
 *	registers that it uses, and return using the iret instruction.
 *	The first 32 vectors (0..31) are reserved for CPU use - effectivly
 *	they are the exception vectors. The other 224 are open for general
 *	use.
 *
 *	For Davros, we program the trap vectors to point to specially-crafted
 *	assembler stubs, most of which simply load some exception code and
 *	jump to a common handler. The rest of the vectors are initialised
 *	to point to an unknown handler routine.
 *	In addition, we define a configurable number of interrupt stubs
 *	to handle the hardware interrupts. These are allocated as required
 *	by the attach_interrupt function.
 *
*/

#include "arch-kernel.h"
#include "x86-core.h"

	.section	"davros_vectors","aw"

	.globl	handler_table
	.type	handler_table,@object
	.globl	__davros_trap_00
	.type	__davros_trap_00,@object
	.globl	__davros_trap_01
	.type	__davros_trap_01,@object
	.globl	__davros_trap_unknown
	.type	__davros_trap_unknown,@object

	.text
	.align	4

__davros_trap_00:
	pushl	%eax
	mov		$0,%eax
	jmp		exception_handler

__davros_trap_01:
	pushl	%eax
	mov		$1,%eax
	jmp		exception_handler

__davros_trap_02:
	pushl	%eax
	mov		$2,%eax
	jmp		exception_handler

__davros_trap_03:
	pushl	%eax
	mov		$3,%eax
	jmp		exception_handler

__davros_trap_04:
	pushl	%eax
	mov		$4,%eax
	jmp		exception_handler

__davros_trap_05:
	pushl	%eax
	mov		$5,%eax
	jmp		exception_handler

__davros_trap_06:
	pushl	%eax
	mov		$6,%eax
	jmp		exception_handler

__davros_trap_07:
	pushl	%eax
	mov		$7,%eax
	jmp		exception_handler

__davros_trap_08:
	pushl	%eax
	mov		$8,%eax
	jmp		exception_handler

__davros_trap_09:
	pushl	%eax
	mov		$9,%eax
	jmp		exception_handler

__davros_trap_10:
	pushl	%eax
	mov		$10,%eax
	jmp		exception_handler

__davros_trap_11:
	pushl	%eax
	mov		$11,%eax
	jmp		exception_handler

__davros_trap_12:
	pushl	%eax
	mov		$12,%eax
	jmp		exception_handler

__davros_trap_13:
	pushl	%eax
	mov		$13,%eax
	jmp		exception_handler

__davros_trap_14:
	pushl	%eax
	mov		$14,%eax
	jmp		exception_handler

__davros_trap_15:
	pushl	%eax
	mov		$15,%eax
	jmp		exception_handler

__davros_trap_16:
	pushl	%eax
	mov		$16,%eax
	jmp		exception_handler

__davros_trap_17:
	pushl	%eax
	mov		$17,%eax
	jmp		exception_handler

__davros_trap_18:
	pushl	%eax
	mov		$18,%eax
	jmp		exception_handler

__davros_trap_19:
	pushl	%eax
	mov		$19,%eax
	jmp		exception_handler

__davros_trap_20:
	pushl	%eax
	mov		$20,%eax
	jmp		exception_handler

__davros_trap_21:
	pushl	%eax
	mov		$21,%eax
	jmp		exception_handler

__davros_trap_22:
	pushl	%eax
	mov		$22,%eax
	jmp		exception_handler

__davros_trap_23:
	pushl	%eax
	mov		$23,%eax
	jmp		exception_handler

__davros_trap_24:
	pushl	%eax
	mov		$24,%eax
	jmp		exception_handler

__davros_trap_25:
	pushl	%eax
	mov		$25,%eax
	jmp		exception_handler

__davros_trap_26:
	pushl	%eax
	mov		$26,%eax
	jmp		exception_handler

__davros_trap_27:
	pushl	%eax
	mov		$27,%eax
	jmp		exception_handler

__davros_trap_28:
	pushl	%eax
	mov		$28,%eax
	jmp		exception_handler

__davros_trap_29:
	pushl	%eax
	mov		$29,%eax
	jmp		exception_handler

__davros_trap_30:
	pushl	%eax
	mov		$30,%eax
	jmp		exception_handler

__davros_trap_31:
	pushl	%eax
	mov		$31,%eax
	jmp		exception_handler

__davros_trap_unknown:
	pushl	%eax
	mov		$0xff,%eax
	jmp		exception_handler

/*
 *	exception_handler() - handle (most) exceptions
 *
 *	This routine handles most exceptions by calling the C exception
 *	handler.
 *	This function must not be called - it is jumped to from the exception
 *	vectors.
*/
exception_handler:
	pushl	%ebx
	pushl	%ecx
	pushl	%edx
	pushl	%ebp
	pushl	%esi
	pushl	%edi

call_x86_exception:
	movl	%esp,%ebx
	pushl	%ebx
	pushl	%eax
	call	x86_exception		/* (trapno, sp) */
	popl	%eax
	popl	%eax

	popl	%edi
	popl	%esi
	popl	%ebp
	popl	%edx
	popl	%ecx
	popl	%ebx
	popl	%eax
	iret


	.align	4

handler_table:
	.rept	__DAVROS_NHANDLERS
	pushl	%eax
	call	interrupt_handler
	.word	0			/*	Interrupt number */
	.long	0			/*  C handler */
	.long	0			/*	Parameter for C handler */
	.endr

/*	interrupt_handler() - handle an interrupt
 *
 *	This routine handles a normal interrupt. It is "called" from the
 *	interrupt handler stub so that popping the top of the stack 
 *	gives a pointer to the handler descriptor. eax has already been
 *	saved.
 *	This routine must never be called.
 *
 *	FIXME: first version is for Comer-style handling.
 *	There's work to do here for nested interrupts and reentrant kernel
 *	work.
*/

interrupt_handler:
	popl	%eax		/* get back "return" address = address of descriptor */
	pushl	%ebx		/* preserve rest of registers */
	pushl	%ecx
	pushl	%edx
	pushl	%ebp
	pushl	%esi
	pushl	%edi

	mov		%eax,%ebp
	mov		2(%ebp),%ebx
	cmpl	$0,%ebx
	je		no_attach
	mov		6(%ebp),%eax
	pushl	%eax
	call	*%ebx
	popl	%eax

	call	__davros_reschedule
	popl	%edi
	popl	%esi
	popl	%ebp
	popl	%edx
	popl	%ecx
	popl	%ebx
	popl	%eax
	iret

no_attach:							/* Flag an unused interrupt exception */
	mov		0(%ebp),%eax
	jmp		call_x86_exception
