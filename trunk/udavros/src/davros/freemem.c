/*	freemem.c - __dv_freemem
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
#include <davros/cpu-intlock.h>
#include <davros/mem.h>

#ifdef __DV_IDENT
__DV_IDENT("$Id$")
#endif

/*==============================================================================
 *	__dv_freemem - release block of memory back to free list
 *==============================================================================
*/
__dv_status_t __dv_freemem
(	void *mptr,
	__dv_size_t nbytes
)
{
	__dv_intstatus_t ps;
	__dv_mblock_t *p,*q;
	__dv_address_t top;
	__dv_status_t result;
	__dv_size_t nround;


	if ( nbytes == 0 )
	{
		result = __DV_ERR;
	}
	else
	{
		nround = __DV_MEMROUND(nbytes);

		ps = __dv_lock();

		for	( q = &__dv_memhead, p = __dv_memhead.next;
			  p != __DV_NULL && (__dv_address_t)p < (__dv_address_t)mptr;
			  q = p, p = p->next )
		{
			/* do nothing */
		}

		if ( (	( top = q->len + (__dv_address_t)q ) > (__dv_address_t)mptr &&
				q != &__dv_memhead ) ||
			 (	p != __DV_NULL && ( nround + (__dv_address_t)mptr > (__dv_address_t)p ) )  )
		{
			result = __DV_ERR;
		}
		else
		{
			result = __DV_OK;

			if ( q != &__dv_memhead && top == (__dv_address_t)mptr	)
			{
				q->len += nround;
			}
			else
			{
				((__dv_mblock_t *)mptr)->len = nround;
				((__dv_mblock_t *)mptr)->next = p;
				q->next = (__dv_mblock_t *)mptr;
				q = mptr;
			}

			if ( ( q->len + (__dv_address_t)q ) == (__dv_address_t)p )
			{
				q->len += p->len;
				q->next = p->next;
			}
		}

		__dv_restore(ps);
	}
	return result;
}
