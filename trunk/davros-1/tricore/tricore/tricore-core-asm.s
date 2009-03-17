/*	tricore-core-asm.s - core assembler functions for Tricore
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
 *	This file contains some common Tricore assembler functions
*/

#include "tricore.h"
#include "modules/tricore-csfr.h"
#include "modules/tricore-pwr.h"
#include "tricore-core.h"

	.text
	.align	2

/*
 *	disable_interrupts() - clears the IE bit of ICR, returns old ICR value
 *
 *	uint32_t disable_interrupts(void);
*/
	.globl	disable_interrupts
	.type	disable_interrupts,@function
	.globl	__callee.disable_interrupts.da.i.v
	.type	__callee.disable_interrupts.da.i.v,@function

disable_interrupts:
__callee.disable_interrupts.da.i.v:
	_MFCR	%d2,ICR
	disable
	ret

/*
 *	enable_interrupts() - sets the IE bit of ICR, returns old ICR value
 *
 *	uint32_t enable_interrupts(void);
*/
	.globl	enable_interrupts
	.type	enable_interrupts,@function
	.globl	__callee.enable_interrupts.da.i.v
	.type	__callee.enable_interrupts.da.i.v,@function

enable_interrupts:
__callee.enable_interrupts.da.i.v:
	_MFCR	%d2,ICR
	enable
	ret

/*
 *	restore_interrupts() - restores an old ICR value as returned by interrupt functions
 *
 *	uint32_t restore_interrupts(uint32_t old);
*/
	.globl	restore_interrupts
	.type	restore_interrupts,@function
	.globl	__callee.restore_interrupts.da.i.i
	.type	__callee.restore_interrupts.da.i.i,@function

restore_interrupts:
__callee.restore_interrupts.da.i.i:
	_MFCR	%d2,ICR
	insert	%d14,%d2,%d4,0,9
	_MTCR	ICR,%d14
	ret

/*
 *	set_cpu_priority() - sets current CPU priority to parameter in d4 (0..255)
 *
 *	uint32_t set_cpu_priority(uint32_t prio);
*/
	.globl	set_cpu_priority
	.type	set_cpu_priority,@function
	.globl	__callee.set_cpu_priority.da.i.i
	.type	__callee.set_cpu_priority.da.i.i,@function

set_cpu_priority:
__callee.set_cpu_priority.da.i.i:
	_MFCR	%d2,ICR
	insert	%d14,%d2,%d4,0,8
	_MTCR	ICR,%d14
	ret

/*
 *	get_pcxi() - get the contents of the PCXI register
 *
 *	This routine returns the value of the ICR register.
 *
 *	uint32_t get_icr(void);
*/
	.globl	get_icr
	.type	get_icr,@function
	.globl	__callee.get_icr.da.i.v
	.type	__callee.get_icr.da.i.v,@function

get_icr:
__callee.get_icr.da.i.v:
	_MFCR	%d2,ICR
	ret

/*
 *	get_icr() - get the contents of the ICR register
 *
 *	This routine returns the value of the PCXI register as seen in
 *	the calling function. To do this, it discards the first CSA in the
 *	list by jumping to a return instruction with a JL instruction, having
 *	saved the return address first. The return intruction "returns" to the
 *	instruction after the JL, having popped a CSA off the list. The PCXI
 *	register is then read into the d2 register for return. Finally, an
 *	indirect jump is made to the real return address. Care must be taken
 *	to preserve the upper context registers after the JL-RET sequence.
 *
 *	uint32_t get_pcxi(void);
*/
	.globl	get_pcxi
	.type	get_pcxi,@function
	.globl	__callee.get_pcxi.da.i.v
	.type	__callee.get_pcxi.da.i.v,@function

get_pcxi:
__callee.get_pcxi.da.i.v:
	mov.aa	%a4,%a11
	jl		discard_csa
	_MFCR	%d2,PCXI
	ji		%a4
discard_csa:
	ret

/*
 *	alloc_csa() - allocates CSAs from the free list
 *
 *	This routine allocates one or more CSAs from the free list and
 *	returns the CSA-index of the head of the list. No check is made that
 *	the number of CSAs requested is valid. In particular, at least 1
 *	CSA will be allocate even if the request is for 0.
 *
 *	uint32_t alloc_csa(int ncsa);
*/
	.globl	alloc_csa
	.type	alloc_csa,@function
	.globl	__callee.alloc_csa.da.i.i
	.type	__callee.alloc_csa.da.i.i,@function

alloc_csa:
__callee.alloc_csa.da.i.i:
	_MFCR	%d15,PCXI				/* Save current PCXI */
	mov		%d14,0					/* Set PCXI to 0 */
	_MTCR	PCXI,%d14
alloc_csa_1:
	svlcx							/* Push a CSA */
	add		%d4,%d4,-1				/* Decrement count */
	jge		%d4,1,alloc_csa_1		/* Repeat till enough allocated */
	dsync							/* Ensure SVLCX completes */
	_MFCR	%d2,PCXI				/* Get new value of PCXI */
	_MTCR	PCXI,%d15
	ret

/*
 *	free_csa() - releases CSAs back to the free list
 *
 *	This routine frees a list of CSAs back to the free list. The
 *	first parameter (d4) is the PCXI index of the head of the list.
 *	The second parameter (d5) is the PCXI index of the first CSA
 *	NOT to free, or 0 if the entire list is to be freed. The
 *	first CSA not freed is returned.
 *
 *	CSAs are freed using the rslcx intstruction. This trashes all the
 *	lower context registers plus a11, so all working registers must be
 *	in the upper context. To avoid context type exceptions, the U/L
 *	bit of PCXI is cleared. We also clear IE to ensure interrupts
 *	remain disabled, although the rslcx instruction probably
 *	doesn't restore the IE bit from PCXI.
 *
 *	uint32_t free_csa(uint32_t head, uint32_t limit);
*/
	.globl	free_csa
	.type	free_csa,@function
	.globl	__callee.free_csa.da.i.ii
	.type	__callee.free_csa.da.i.ii,@function

free_csa:
__callee.free_csa.da.i.ii:
	mov.aa	%a15,%a11			/* return address saved in a15 */
	mov		%d15,%d4			/* head of list */
	mov		%d14,%d5			/* tail of list */
	_MFCR	%d13,PCXI			/* save current PCXI */
	extr.U	%d12,%d14,0,20		/* extract segment & index tail */

free_csa_loop:
	extr.u	%d15,%d15,0,20		/* extract segment & index of next CSA */
	jeq		%d15,%d12,free_csa_end
	jeq		%d15,0,free_csa_end
	_MTCR	PCXI,%d15			/* free the CSA */
	rslcx
	dsync
	nop
	nop
	_MFCR	%d15,PCXI
	j		free_csa_loop

free_csa_end:
	mov.aa	%a11,%a15			/* restore return address */
	_MTCR	PCXI,%d13			/* restore original PCXI */
	mov		%d2,%d15			/* return 1st CSA not freed, or 0 */
	ret

/*
 *	set_biv() - sets the BIV register
 *
 *	This routine sets the BIV (base interrupt vector) register to
 *	the value specified by the biv parameter (d4)
 *
 *	void set_biv(uint32_t biv);
*/
	.globl	set_biv
	.type	set_biv,@function
	.globl	__callee.set_biv.da.v.i
	.type	__callee.set_biv.da.v.i,@function

set_biv:
__callee.set_biv.da.v.i:
	mov		%d14,%d4
	_MFCR	%d15,ICR
	disable
	mov		%d4,0
	call	endinit
	dsync
	nop
	nop
	_MTCR	BIV,%d14
	mov		%d4,1
	call	endinit
	_MTCR	ICR,%d15
	ret

/*
 *	get_biv() - gets the BIV register
 *
 *	uint32_t get_biv(void);
*/
	.globl	get_biv
	.type	get_biv,@function
	.globl	__callee.get_biv.da.i.v
	.type	__callee.get_biv.da.i.v,@function

get_biv:
__callee.get_biv.da.i.v:
	dsync
	nop
	nop
	_MFCR	%d2,BIV
	ret

/*
 *	set_btv() - sets the BTV register
 *
 *	This routine sets the BTV (base trap vector) register to
 *	the value specified by the btv parameter (d4)
 *
 *	void set_btv(uint32_t btv);
*/
	.globl	set_btv
	.type	set_btv,@function
	.globl	__callee.set_btv.da.v.i
	.type	__callee.set_btv.da.v.i,@function

set_btv:
__callee.set_btv.da.v.i:
	mov		%d14,%d4
	_MFCR	%d15,ICR
	disable
	mov		%d4,0
	call	endinit
	dsync
	nop
	nop
	_MTCR	BTV,%d14
	mov		%d4,1
	call	endinit
	_MTCR	ICR,%d15
	ret

/*
 *	get_btv() - gets the BTV register
 *
 *	uint32_t get_btv(void);
*/
	.globl	get_btv
	.type	get_btv,@function
	.globl	__callee.get_btv.da.i.v
	.type	__callee.get_btv.da.i.v,@function

get_btv:
__callee.get_btv.da.i.v:
	dsync
	nop
	nop
	_MFCR	%d2,BTV
	ret
