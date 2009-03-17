/*	dequeued.c - __davros_dequeued
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
#endif

__DAVROS_IDENT("$Id$")

/*==============================================================================
 *	__davros_dequeued - remove a process from a delta list (opposite of insertd)
 *==============================================================================
*/
__davros_qent_t *__davros_dequeued
(	__davros_qent_t *qent
)
{
	__davros_qent_t *next;

	next = qent->next;
	__davros_dequeue(qent);

	if ( next != &__davros.sleepqueue.tail )
	{
		next->kd.key += qent->kd.key;
	}

	if ( __davros.sleepqueue.head.next == &__davros.sleepqueue.tail )
	{
		__davros.sleepcount = NULL;
	}
	else
	{
		__davros.sleepcount = &(__davros.sleepqueue.head.next->kd.key);
	}

	return(qent);
}
