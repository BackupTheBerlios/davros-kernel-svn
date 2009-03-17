/*	x86-kernel-asm.s - kernel assembler functions for x86
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
 *	This file contains the x86 kernel functions that are written
 *	in assembly language.
*/

#include "x86.h"
#include "x86-core.h"

	.text
	.align	4

/*
 *	__arch_ctxsw() - the context switch
 *
 *	This routine performs the context switch by saving all the
 *	registers into the outgoing process' table and restoring the
 *	registers for the incoming process.
 *
 *	void __arch_ctxsw(__arch_ctxtreg_t *,__arch_ctxtreg_t *);
 *
 *	This version pushes all the registers onto the stack, then saves the
 *	stack pointer in the process table.
*/
	.globl	__arch_ctxsw
	.type	__arch_ctxsw,@function

__arch_ctxsw:
	pushfl
	pushl	%eax
	pushl	%ebx
	pushl	%ecx
	pushl	%edx
	pushl	%ebp
	pushl	%esi
	pushl	%edi

	mov		0x24(%esp),%ebp	/* old process */
	cmpl	$0,%ebp
	je		getnew
	mov		%esp,0(%ebp)

getnew:
	mov		0x28(%esp),%ebp	/* new process */
	mov		0(%ebp),%esp

	popl	%edi
	popl	%esi
	popl	%ebp
	popl	%edx
	popl	%ecx
	popl	%ebx
	popl	%eax
	popfl
	ret

/*
 *	__arch_setstack() - sets the stackpointer of the current thread
 *
 *	This function is a dummy. entry.s defines a stack, which
 *	eventually becomes the null process' stack.
 *	The original version of this caused problems, and it isn't
 *	really necessary on the x86.
 *
 *	void __arch_setstack(memaddr_t stk)
*/
	.globl	__arch_setstack
	.type	__arch_setstack,@function

__arch_setstack:
	ret

/*
 *	__arch_exit() - calls exit when a process returns
 *
 *	This function's address is pushed onto the stack for
 *	a newly created process, such that when the process
 *	returns it continues execution here. __davros_exit is
 *	called with the return value (eax) as parameter.
 *	This function must never be called directly.
*/
	.globl	__arch_exit
	.type	__arch_exit,@function

__arch_exit:
	pushl	%eax
	call	__davros_exit		/* Never returns! */
