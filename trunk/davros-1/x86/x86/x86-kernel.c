/*	x86-kernel.c - architecture-specific kernel routines
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
 *	This file contains architecture-specific routines that are required
 *	by the kernel.
 *
*/

#include "x86.h"
#include "davros/kernel.h"
#include "x86-core.h"
#include "string.h"

/*
 *	__arch_initproc() - initialise arch-dependent parts of process
 *
 *	This function is called at process creation time to initialise
 *	the architecture-dependent parts of the process entry.
 *	When the context switch resumes a process, it pops the lower
 *	context off the PCXI list, then returns (thus also popping
 *	the upper context off the list). A new process must therefore
 *	be intialised with a list of 2 contexts. The register values
 *	in these contexts must be initialised with the top of stack
 *	in the stack pointer register (a10), the entry point in the
 *	return address register (a11) and nargs and args in d4 and a4
 *	respectively.
 *	When the process' main function returns, it will generate a
 *	context list underflow exception. The handler for this exception
 *	must therefore clear the saved contexts, transfer d2 to d4 and
 *	jump to exit.
*/
void __arch_initproc
(	__davros_process_t *p,	/*	Process entry */
	memaddr_t sp			/*	Stack pointer */
)
{
	unsigned *_sp = (unsigned *)sp;

	*(--_sp) = (unsigned)p->args;		/*	2nd parameter for process */
	*(--_sp) = (unsigned)p->nargs;		/*	1st parameter for process */
	*(--_sp) = (unsigned)__arch_exit;	/*	Return address for process */
	*(--_sp) = (unsigned)p->start;		/*	Entry point for process */
	*(--_sp) = FLAG_IF | FLAG_1;		/*	Flags: interrupts enabled */
	*(--_sp) = 0;						/*	%eax */
	*(--_sp) = 0;						/*	%ebx */
	*(--_sp) = 0;						/*	%ecx */
	*(--_sp) = 0;						/*	%edx */
	*(--_sp) = 0;						/*	%ebp */
	*(--_sp) = 0;						/*	%esi */
	*(--_sp) = 0;						/*	%edi */

	p->registers.esp = (unsigned)_sp;
}

/*
 *	__arch_kill() - clean up when process dies.
 *
 *	This function is called from kill() to clean up architecture-
 *	dependent data when a process is killed. For x86 there's
 *	nothing to do.
 *	FIXME: optimise this by making it into a macro.
*/
void __arch_kill(__davros_process_t *p)
{
}

/*
 *	__arch_leavekernel() - leave the kernel
 *
 *	This function is called at the end of almost every kernel
 *	routine. The parameter that it is passed is the value that
 *	__arch_enterkernel() returns when called at the start of the
 *	routine.
 *	In this version, __arch_enterkernel() is merely disable_interrupts
 *	(see arch-kernel.h), so this routine must restore interrupts. It
 *	calls reschedule() first to run any higher priority tasks.
*/
__arch_intstatus_t __arch_leavekernel(__arch_intstatus_t ps)
{
	/* __davros_reschedule(); */
	return(restore_interrupts(ps));
}
