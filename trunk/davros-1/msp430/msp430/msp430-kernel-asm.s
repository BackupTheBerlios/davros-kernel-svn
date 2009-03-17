/*	msp430-kernel-asm.s - kernel assembler functions for MSP430
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
 *	This file contains the MSP430 kernel functions that are written
 *	in assembly language.
 *
 *	$Log: msp430-kernel-asm.s,v $
 *	Revision 1.1  2004/05/11 20:50:06  dave
 *	New file for msp430 port.
 *	
*/

#include "msp430.h"
#include "msp430-core.h"
#include "arch-kernel.h"

	.text
	.align	2

/*
 *	__arch_ctxsw() - the context switch
 *
 *	This routine performs the context switch by saving all the
 *	registers into the outgoing process' table and restoring the
 *	registers for the incoming process.
 *
 *	void __arch_ctxsw(__arch_ctxtreg_t *,__arch_ctxtreg_t *);
 *
 *	Thus the outgoing process' register structure is pointed to by
 *	r15 and the incoming process by r14.
 *	This version pushes all the registers onto the stack,
 *	then merely saves the SP register.
*/
	.globl	__arch_ctxsw
	.type	__arch_ctxsw,@function

__arch_ctxsw:
	push	SR
	push	r4
	push	r5
	push	r6
	push	r7
	push	r8
	push	r9
	push	r10
	push	r11
	push	r12
	push	r13
	push	r14
	push	r15
	tst		r15
	jz		_ctxsw_nosave
	mov		SP,__MSP_CTXT_SP(r15)
_ctxsw_nosave:
	mov		__MSP_CTXT_SP(r14),SP
	pop		r15
	pop		r14
	pop		r13
	pop		r12
	pop		r11
	pop		r10
	pop		r9
	pop		r8
	pop		r7
	pop		r6
	pop		r5
	pop		r4
	pop		SR
	ret
