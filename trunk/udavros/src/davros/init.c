/*	init.c - __dv_init
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
#include <davros/constants.h>
#include <davros/mem.h>
#include <davros/queue.h>
#include <davros/process.h>
#include <davros/interrupt.h>
#include <davros/time.h>
#include <davros/error.h>
#include <davros/cpu-intlock.h>

#ifdef __DV_IDENT
__DV_IDENT("$Id$")
#endif

/*==============================================================================
 *	Kernel variables
 *==============================================================================
*/
__dv_stackelement_t		__dv_nullstack[DV_CFG_NULLSTACK_LEN];
__dv_stackelement_t		__dv_kernstack[DV_CFG_KERNSTACK_LEN];
__dv_uint8_t			__dv_in_kernel;


#define NSTACK	(DV_CFG_NULLSTACK_LEN * sizeof(__dv_stackelement_t))

const __dv_processconfig_t __dv_nullproc_cfg =
{	"null",				/* name */
	__DV_NULL,			/* entry */
	0,					/* nargs */
	__DV_NULL,			/* args */
	NSTACK				/* stacksize (macro defined above) */
};

__dv_processstate_t __dv_nullproc;

__dv_stackelement_t		*const __dv_kernel_sp = &__dv_kernstack[DV_CFG_KERNSTACK_LEN-DV_CFG_STACK_SPARE];

/*==============================================================================
 *	__dv_init - initialise all DAVROS data structures
 *==============================================================================
*/
void __dv_init
(	__dv_uint8_t *membase,		/* Bottom of free memory */
	__dv_size_t memlen			/* Length of free memory in bytes */
)
{
	/* Initialise the low-level memory allocator
	*/
	__dv_initmem(membase, memlen);

	/* Initialise the object table
	*/
	__dv_initobj();

	/* Set up the process management system
	*/
	__dv_initproc();

	/* Set up the interrupt management system
	*/
	__dv_initint();

	/* Set up the time subsystem
	*/
	__dv_inittime();

	/* The process table entry for the null process is statically
	 * declared. The stack is the startup stack. We just need to initialise
	 * the process state structure and note it in the process table.
	*/
	__dv_nullproc.obj.type = __DV_OBJTYPE_PROCESS;
	if ( __dv_registerobj(&__dv_nullproc.obj) < 0 )
	{
		__dv_die();
	}

	__dv_initqent(&__dv_nullproc.qent, &__dv_nullproc.obj);

	__dv_nullproc.config = &__dv_nullproc_cfg;
	__dv_nullproc.stack = __dv_nullstack;
	__dv_nullproc.nalloc = 0;
	__dv_nullproc.state = __DV_PRCURR;

	/* Set the null process as the current process
	*/
	__dv_currproc = &__dv_nullproc;

	/* Finally, enable interrupts
	*/
	__dv_enable();
}
