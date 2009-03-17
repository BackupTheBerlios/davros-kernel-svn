/*	insertd.c - __davros_insertd
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

#ifndef __DAVROS_ASM_INSERTD

#ifndef __DAVROS_COMPLETE
#include "davros/kernel.h"
#endif

__DAVROS_IDENT("$Id$")

/*==============================================================================
 *	__davros_insertd - insert an item into a delta queue
 *==============================================================================
*/
__davros_status_t __davros_insertd
(	__davros_qent_t *item,	/* item to insert */
	__davros_queue_t *q,		/* list to insert into */
	__davros_qkey_t key		/* key to use for insertion */
)
{
	__davros_qent_t *next;		/* runs through list */

	for ( next = q->head.next;
		  key > next->kd.key;	/* tail has MAXINT as key */
		  next = next->next  )
		key -= next->kd.key;

	item->next = next;
	item->prev = next->prev;
	item->prev->next = item;
	next->prev = item;
	item->kd.key  = key;

	if ( next->next != NULL )	/* If not inserting at end of list ... */
		next->kd.key -= key;	/* ... Reduce next item's key */

	return(__DAVROS_OK);
}

#endif
