/*	dequeued.c - __dv_dequeued
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
 *	__dv_dequeued - remove an entry from a delta list (opposite of insertd)
 *==============================================================================
*/
__dv_qent_t *__dv_dequeued
(	__dv_qent_t *qent
)
{
	__dv_qent_t *next;

	next = qent->next;
	__dv_dequeue(qent);

	if ( next->next != __DV_NULL )	/* If not removing from end of list ... */
		next->key += qent->key;		/* ... increase  next entry's key */

	return qent;
}
