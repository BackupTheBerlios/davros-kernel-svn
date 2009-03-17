/*	msp430-kernel.c - architecture-specific kernel routines
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
 *	This file contains architecture-specific routines that are required
 *	by the kernel.
 *
 *	$Log: msp430-kernel.c,v $
 *	Revision 1.1  2004/05/11 20:50:06  dave
 *	New file for msp430 port.
 *	
*/

#include "msp430.h"
#include "davros/kernel.h"
#include "msp430-core.h"
#include "string.h"

/*
 *	__arch_setstack() - sets the stackpointer of the current thread
 *
 *	This function modifies the stack pointer of the current
 *	thread. It must be done in assembler code - this is just
 *	documentation!
 *	The calling function must never return!
*/
#if 0
void __arch_setstack(memaddr_t stk)
{
}
#endif

/*
 *	__arch_initproc() - initialise arch-dependent parts of process
 *
 *	This function is called at process creation time to initialise
 *	the architecture-dependent parts of the process entry.
 *	When the context switch resumes a process, it pops the registers
 *  off the stack, then returns. This means that we must store the
 *	expected register values onto the stack here in the correct order.
 *	When the task's main function returns, it too will pop the PC
 *	off the stack, so first we push the address of an exit function.
*/
void __arch_initproc
(	__davros_process_t *p,	/*	Process entry */
	memaddr_t sp			/*	Stack pointer */
)
{
	unsigned *ssp = (unsigned *)sp;

	*(--ssp) = (uint16_t)__davros_exit;
	*(--ssp) = (uint16_t)p->start;
	*(--ssp) = SR_GIE;
	*(--ssp) = 0;					/* r4 */
	*(--ssp) = 0;					/* r5 */
	*(--ssp) = 0;					/* r6 */
	*(--ssp) = 0;					/* r7 */
	*(--ssp) = 0;					/* r8 */
	*(--ssp) = 0;					/* r9 */
	*(--ssp) = 0;					/* r10 */
	*(--ssp) = 0;					/* r11 */
	*(--ssp) = 0;					/* r12 */
	*(--ssp) = 0;					/* r13 */
	*(--ssp) = (uint16_t)p->args;	/* r14 */
	*(--ssp) = p->nargs;			/* r15 */
	p->registers.sp = (uint16_t)ssp;
}

/*
 *	__arch_kill() - clean up when process dies.
 *
 *	This function is called from kill() to clean up architecture-
 *	dependent data when a process is killed. For MSP430, there's
 *	nothing to do.
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

#if 0
__arch_intstatus_t		__arch_enterkernel(void);
void					__arch_leavekernel(__arch_intstatus_t);
__arch_intstatus_t		__arch_enableinterrupts(void);
__arch_intstatus_t		__arch_disableinterrupts(void);
__arch_intstatus_t		__arch_restoreinterrupts(__arch_intstatus_t);
void					__arch_ctxsw(__arch_ctxtreg_t *,__arch_ctxtreg_t *);
void					__arch_initkernel(__davros_data_t *);
#endif
