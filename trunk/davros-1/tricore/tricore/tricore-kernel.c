/*	tricore-kernel.c - architecture-specific kernel routines
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
 *	This file contains architecture-specific routines that are required
 *	by the kernel.
 *
*/

#include "tricore.h"
#include "davros/kernel.h"
#include "tricore-core.h"
#include "modules/tricore-csfr.h"
#include "string.h"

/*
 *	__arch_setstack() - sets the stackpointer of the current thread
 *
 *	This function modifies the stack pointer of the current
 *	thread. It does so by getting the PCXI register and modifying
 *	the a10/sp location in the top CSA before returning.
 *	The calling function must never return!
*/
void __arch_setstack(memaddr_t stk)
{
	csa_t *csa = context_to_address(get_pcxi());

	csa->context.upper.a10 = stk;
	DSYNC();
}

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
	csa_t *lower, *upper;

	p->registers.pcxi = (alloc_csa(2) & ~(PCXI_PCPN|PCXI_UL)) | PCXI_PIE;
	lower = context_to_address(p->registers.pcxi);
	upper = next_csa(lower);
	memset(&lower->context, 0, sizeof(lower->context));
	memset(&upper->context, 0, sizeof(upper->context));
	upper->context.upper.psw = PSW_PRS_0 | PSW_IO_SU | PSW_IS | PSW_GW | PSW_CDC_DIS;
	lower->pcxi = (lower->pcxi & ~PCXI_PCPN) | PCXI_PIE | PCXI_UL;
	upper->context.upper.a10 = sp;
	upper->context.upper.a11 = (uint32_t)__davros_exit;	/* Process's RA */
	lower->context.lower.a11 = (uint32_t)p->start;		/* Address returned to by ctxsw */
	lower->context.lower.d4 = p->nargs;
	lower->context.lower.a4 = (uint32_t)p->args;
}

/*
 *	__arch_kill() - clean up when process dies.
 *
 *	This function is called from kill() to clean up architecture-
 *	dependent data when a process is killed. For Tricore, we must
 *	free the CSA list to prevent context leakage. If the process
 *	is the current process, the release of CSAs is done in the
 *	context switch. Otherwise we do it here.
*/
void __arch_kill(__davros_process_t *p)
{
	if ( p->state !=  __DAVROS_PRCURR )
	{
		free_csa(p->registers.pcxi, 0);
	}
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
