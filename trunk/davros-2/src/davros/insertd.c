/*	insertd.c - __dv_insertd
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
#include <davros/queue.h>
#include <davros/constants.h>

#ifdef __DV_IDENT
__DV_IDENT("$Id$")
#endif

/*==============================================================================
 *	__dv_insertd - insert an entry into a delta queue
 *==============================================================================
*/
__dv_status_t __dv_insertd
(	__dv_qent_t *item,		/* item to insert */
	__dv_queue_t *q,		/* list to insert into */
	__dv_qkey_t key			/* key to use for insertion */
)
{
	__dv_qent_t *next;			/* runs through list */

	for ( next = q->head.next;
		  key > next->key;		/* tail has MAXINT as key */
		  next = next->next  )
		key -= next->key;

	item->next = next;
	item->prev = next->prev;
	item->prev->next = item;
	next->prev = item;
	item->key  = key;

	if ( next->next != __DV_NULL )	/* If not inserting at end of list ... */
		next->key -= key;			/* ... Reduce next item's key */

	return __DV_OK;
}
