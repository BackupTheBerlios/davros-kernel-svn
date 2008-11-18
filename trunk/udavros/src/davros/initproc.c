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
#include <davros/queue.h>
#include <davros/process.h>

#ifdef __DV_IDENT
__DV_IDENT("$Id$")
#endif

/*==============================================================================
 *	Kernel variables
 *==============================================================================
*/
__dv_queue_t			__dv_readyqueue;
__dv_processstate_t		*__dv_currproc;


/*==============================================================================
 *	__dv_initproc - initialise the process management variables
 *==============================================================================
*/
void __dv_initproc(void)
{
	/* Set up the ready queue
	*/
	__dv_initqueue(&__dv_readyqueue);

	/* Set the current process to NULL. init() will overwrite this, but there you go...
	*/
	__dv_currproc = __DV_NULL;
}
