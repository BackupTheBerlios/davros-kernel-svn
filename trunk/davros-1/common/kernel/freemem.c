/*	freemem.c - __davros_freemem
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
 *	__davros_freemem - release block of memory back to free list
 *==============================================================================
*/
__davros_status_t __davros_freemem
(	void *mptr,
	size_t nbytes
)
{
	__arch_intstatus_t ps;
	__davros_mblock_t *p,*q;
	memaddr_t top;
	__davros_status_t	result;

	if ( nbytes == 0 )
	{
		result = __DAVROS_SYSERR;
	}
	else
	{
		nbytes = __DAVROS_MEMROUND(nbytes);

		ps = __arch_enterkernel();

		for	( q = &__davros.memhead, p = __davros.memhead.next;
			  p != NULL && (memaddr_t)p < (memaddr_t)mptr;
			  q = p, p = p->next )
		{
			/* do nothing */
		}

		if ( (	( top = q->len + (memaddr_t)q ) > (memaddr_t)mptr &&
				q != &__davros.memhead ) ||
			 (	p != NULL && ( nbytes + (memaddr_t)mptr > (memaddr_t)p ) )  )
		{
			result = __DAVROS_SYSERR;
		}
		else
		{
			result = __DAVROS_OK;

			if ( q != &__davros.memhead && top == (memaddr_t)mptr	)
			{
				q->len += nbytes;
			}
			else
			{
				((__davros_mblock_t *)mptr)->len = nbytes;
				((__davros_mblock_t *)mptr)->next = p;
				q->next = (__davros_mblock_t *)mptr;
				q = mptr;
			}

			if ( ( q->len + (memaddr_t)q ) == (memaddr_t)p )
			{
				q->len += p->len;
				q->next = p->next;
			}
		}

		__arch_leavekernel(ps);
	}
	return(result);
}
