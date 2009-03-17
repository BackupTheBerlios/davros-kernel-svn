/*	initproc.c - __davros_initproc
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
*/

#ifndef __DAVROS_COMPLETE
#include "davros/kernel.h"
#include "string.h"
#endif

__DAVROS_IDENT("$Id$")

/*==============================================================================
 *	__davros_initproc - initialise a __davros_process_t structure
 *==============================================================================
*/
void __davros_initproc
(	__davros_process_t *p
)
{
	p->queue_entry.next = NULL;		/* the queue entry uses the key field. */
	p->queue_entry.prev = NULL;
	p->queue_entry.kd.key = 0;

	p->proctab_entry.next = NULL;	/* the proctab entry uses the data field */
	p->proctab_entry.prev = NULL;
	p->proctab_entry.kd.data = p;

	p->state = 0;
	p->priority = 0;
	p->stacksize = 0;
	p->sem = NULL;
	p->msg = 0;
	p->hasmsg = FALSE;

	p->dvstdin = NULL;
	p->dvstdout = NULL;
	p->dvstderr = NULL;

	memset(p->name, '\0', sizeof(p->name));
}
