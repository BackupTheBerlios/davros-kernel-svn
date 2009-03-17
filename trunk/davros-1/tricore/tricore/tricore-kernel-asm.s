/*	tricore-kernel-asm.s - kernel assembler functions for Tricore
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
 *	This file contains the Tricore kernel functions that are written
 *	in assembly language.
*/

#include "tricore.h"
#include "modules/tricore-csfr.h"
#include "modules/tricore-pwr.h"
#include "tricore-core.h"

	.extern	free_csa

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
 *	%a4 and the incoming process by %a5.
 *	This version saves the lower context onto the context list,
 *	then merely saves the PCXI register.
*/
	.globl	__arch_ctxsw
	.type	__arch_ctxsw,@function
	.globl	__callee.__arch_ctxsw.da.v.pp
	.type	__callee.__arch_ctxsw.da.v.pp,@function

__arch_ctxsw:
__callee.__arch_ctxsw.da.v.pp:
	svlcx
	dsync
	nop
	nop
	isync
	_MFCR	%d2,PCXI
	jz.a	%a4, suicide
	st.w	[%a4]0,%d2
	ld.w	%d2,[%a5]0
	_MTCR	PCXI,%d2
	_MFCR	%d2,PSW		/* Clear the call depth counter so we can use rfe */
	andn	%d2,%d2,PSW_CDC
	_MTCR	PSW,%d2
	rslcx
	rfe

suicide:
	mov.aa	%a15,%a5
	mov		%d4,%d2
	mov		%d5,0
	call	free_csa
	ld.w	%d2,[%a15]0
	_MTCR	PCXI,%d2
	_MFCR	%d2,PSW		/* Clear the call depth counter so we can use rfe */
	andn	%d2,%d2,PSW_CDC
	_MTCR	PSW,%d2
	rslcx
	rfe
