/*	x86-core-asm.s - core assembler functions for x86
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
 *	This file contains some common x86 assembler functions
*/

#include "x86.h"
#include "x86-core.h"

	.text
	.align	2

/*
 *	disable_interrupts() - clears the IE bit of ICR, returns old ICR value
 *
 *	uint32_t disable_interrupts(void);
*/
	.globl	disable_interrupts
	.type	disable_interrupts,@function

disable_interrupts:
	pushfl
	cli
	popl	%eax
	ret

/*
 *	enable_interrupts() - sets the IE bit of ICR, returns old ICR value
 *
 *	uint32_t enable_interrupts(void);
*/
	.globl	enable_interrupts
	.type	enable_interrupts,@function

enable_interrupts:
	pushfl
	sti
	popl	%eax
	ret

/*
 *	restore_interrupts() - restores an old ICR value as returned by interrupt functions
 *
 *	uint32_t restore_interrupts(uint32_t old);
*/
	.globl	restore_interrupts
	.type	restore_interrupts,@function

restore_interrupts:
	pushfl
	mov		8(%esp),%eax
	pushl	%eax
	popfl
	popl	%eax
	ret

/*
 *	out8()/out16()/out32() - output a value using appropriate 'out' instruction
 *
 *	void out8(memaddr_t port, uint32_t val);
 *	void out16(memaddr_t port, uint16_t val);
 *	void out32(memaddr_t port, uint32_t val);
*/
	.globl	out8
	.type	out8,@function

out8:
	movl	4(%esp),%edx
	movl	8(%esp),%eax
	outb	%al,%dx
	ret

	.globl	out16
	.type	out16,@function

out16:
	movl	4(%esp),%edx
	movl	8(%esp),%eax
	outw	%ax,%dx
	ret

	.globl	out32
	.type	out32,@function

out32:
	movl	4(%esp),%edx
	movl	8(%esp),%eax
	outl	%eax,%dx
	ret

/*
 *	in8()/in16()/in32() - input a value using appropriate 'in' instruction
 *
 *	uint32_t in8(memaddr_t port);
 *	uint32_t in16(memaddr_t port);
 *	uint32_t in32(memaddr_t port);
*/
	.globl	in8
	.type	in8,@function

in8:
	movl	4(%esp),%edx
	movl	$0,%eax
	inb		%dx,%al
	ret

	.globl	in16
	.type	in16,@function

in16:
	movl	4(%esp),%edx
	movl	$0,%eax
	inw		%dx,%ax
	ret

	.globl	in32
	.type	in32,@function

in32:
	movl	4(%esp),%edx
	inl		%dx,%eax
	ret

/*
 *	load_idt() - load interrupt descriptor table register
 *
 *	void load_idt(void *idt)
*/
	.globl	load_idt
	.type	load_idt,@function

load_idt:
	movl	4(%esp),%eax
	lidt	(%eax)
	ret
