/*	getmem.c - __davros_getmem
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
 *	__davros_getmem - get block of memory from free list
 *==============================================================================
*/
void *__davros_getmem
(	size_t nbytes
)
{
	__arch_intstatus_t ps;
	__davros_mblock_t *p,*q,*r;
	boolean_t looking;

	if ( nbytes == 0 )
	{
		p = NULL;
	}
	else
	{
		nbytes = __DAVROS_MEMROUND(nbytes);
		looking = TRUE;
		ps = __arch_enterkernel();

		q = &__davros.memhead;
		p = __davros.memhead.next;
		while (	p != NULL && looking )
		{
			if ( p->len == nbytes )
			{
				q->next = p->next;
				looking = FALSE;
			}
			else
			if ( p->len > nbytes )
			{
				r = (__davros_mblock_t *)((unsigned)p + nbytes);
				q->next = r;
				r->next = p->next;
				r->len = p->len - nbytes;
				looking = FALSE;
			}
			else
			{
				q = p;
				p = p->next;
			}
		}
		__arch_leavekernel(ps);
	}

	return(p);
}
