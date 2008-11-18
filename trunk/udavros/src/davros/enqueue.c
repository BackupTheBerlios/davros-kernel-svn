/*	enqueue.c - __dv_enqueue
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

#ifdef __DV_IDENT
__DV_IDENT("$Id$")
#endif

/*==============================================================================
 *	__dv_enqueue - insert an item at the tail of a list
 *==============================================================================
*/
__dv_qent_t *__dv_enqueue
(	__dv_qent_t *item,		/* item to enqueue */
	__dv_queue_t *q			/* queue to put it on */
)
{
	item->next = &q->tail;
	item->prev = q->tail.prev;
	q->tail.prev->next = item;
	q->tail.prev = item;

	return item;
}
