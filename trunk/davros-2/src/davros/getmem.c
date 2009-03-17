/*	getmem.c - __dv_getmem
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
 *	__dv_getmem - get block of memory from free list
 *==============================================================================
*/
void *__dv_getmem
(	__dv_size_t nbytes
)
{
	__dv_intstatus_t ps;
	__dv_mblock_t *p,*q,*r;
	__dv_fint8_t looking;

	if ( nbytes == 0 )
	{
		p = __DV_NULL;
	}
	else
	{
		nbytes = __DV_MEMROUND(nbytes);
		looking = __DV_TRUE;
		ps = __dv_lock();

		q = &__dv_memhead;
		p = __dv_memhead.next;
		while (	p != __DV_NULL && looking )
		{
			if ( p->len == nbytes )
			{
				q->next = p->next;
				looking = __DV_FALSE;
			}
			else
			if ( p->len > nbytes )
			{
				r = (__dv_mblock_t *)((unsigned)p + nbytes);
				q->next = r;
				r->next = p->next;
				r->len = p->len - nbytes;
				looking = __DV_FALSE;
			}
			else
			{
				q = p;
				p = p->next;
			}
		}
		__dv_restore(ps);
	}

	return p;
}
