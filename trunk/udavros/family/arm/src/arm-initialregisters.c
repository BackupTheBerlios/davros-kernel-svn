/*	arm-initialregisters.c - __dv_initialregisters
 *
 *	Copyright 2008 David Haworth
 *
 *	This file is part of davros.
 *
 *	davros is free software: you can redistribute it and/or modify
 *	it under the terms of the GNU General Public License as published by
 *	the Free Software Foundation, either version 3 of the License, or
 *	(at your option) any later version.
 *
 *	davros is distributed in the hope that it will be useful,
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *	GNU General Public License for more details.
 *
 *	You should have received a copy of the GNU General Public License
 *	along with davros.  If not, see <http://www.gnu.org/licenses/>.
*/
#include <davros/config.h>
#include <davros/process.h>		/* FIXME: temporary; needed for __dv_usr_create etc. */
#include <arm-core.h>		/* FIXME: temporary; needed for __dv_usr_create etc. */

#ifdef __DV_IDENT
__DV_IDENT("$Id$")
#endif

/*
 *	__dv_initialregisters - initialise a new process' registers
 *
 *	The "registers" are in the process' registers structure
 *
 *	For the time being (assuming a void parameter list) we needc to set the
 *	following registers:
 *
 *	r2  - small data pointer
 *  r13 - small data pointer
 *  pc  - process entry point
 *  msr - initial MSR (interrupts enabled, supervisor, etc.)
 *  lr  - where to go when the process returns
*/
#if 0
#define INITIAL_PSR	()
#else
#define INITIAL_PSR	(__DV_PSR_MODE_SYS | __DV_PSR_IRQ | __DV_PSR_FIQ)
#endif

void __dv_initialregisters(__dv_processstate_t *proc)
{
	__dv_int_t len = __DV_STACKROUND(proc->config->stacksize + __DV_EXTRASTACK);
	__dv_stackelement_t *sp = &proc->stack[len/sizeof(__dv_stackelement_t)];

	proc->registers.regs[__DV_REG_r0] = proc->config->nargs;
	proc->registers.regs[__DV_REG_r1] = (__dv_uint32_t)proc->config->args;
	proc->registers.regs[__DV_REG_r13] = (__dv_uint32_t)sp;
	proc->registers.regs[__DV_REG_r14] = (__dv_uint32_t)__dv_usr_exit;
	proc->registers.regs[__DV_REG_r15] = (__dv_uint32_t)proc->config->entry;
	proc->registers.regs[__DV_REG_psr] = INITIAL_PSR;
}
