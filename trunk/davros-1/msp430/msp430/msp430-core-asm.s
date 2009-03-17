/*	msp430-core-asm.s - core assembler functions for MSP430
 *
 *	$Id$
 *	Copyright 2004 David Haworth
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
 *	This file contains some common MSP430 assembler functions
 *
 *	$Log: msp430-core-asm.s,v $
 *	Revision 1.1  2004/05/11 20:50:06  dave
 *	New file for msp430 port.
 *	
*/

#include "msp430.h"
#include "msp430-core.h"

	.text
	.align	2

/*
 *	disable_interrupts() - clears the GIE bit of SR, returns old SR value
 *
 *	uint16_t disable_interrupts(void);
*/
	.globl	disable_interrupts
	.type	disable_interrupts,@function

disable_interrupts:
	mov		SR,r15
	dint
	ret

/*
 *	enable_interrupts() - sets the GIE bit of SR, returns old SR value
 *
 *	uint16_t enable_interrupts(void);
*/
	.globl	enable_interrupts
	.type	enable_interrupts,@function

enable_interrupts:
	mov		SR,r15
	eint
	ret

/*
 *	restore_interrupts() - restores an old SR value as returned by interrupt functions
 *
 *	uint16_t restore_interrupts(uint16_t old);
*/
	.globl	restore_interrupts
	.type	restore_interrupts,@function

restore_interrupts:
	mov		SR,r14
	mov		r15,SR
	mov		r14,r15
	ret

/*
 *	__arch_setstack() - sets the stackpointer of the current thread
 *
 *	This function modifies the stack pointer of the current
 *	thread.
 *	The calling function must never return!
 *
 *	void __arch_setstack(memaddr_t stk);
*/
	.globl	__arch_setstack
	.type	__arch_setstack,@function

__arch_setstack:
	pop		r14			/* Get return address off old stack */
	mov		r15,SP		/* Set stack pointer */
	push	r14			/* Push return address onto new stack */
	ret
