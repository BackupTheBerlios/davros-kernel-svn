/*	initmem.c - __dv_initmem
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
#include <davros/mem.h>

#ifdef __DV_IDENT
__DV_IDENT("$Id$")
#endif

/*==============================================================================
 *	Kernel variables
 *==============================================================================
*/
__dv_mblock_t			__dv_memhead;

/*==============================================================================
 *	__dv_initmem - initialise the davros memory pool
 *==============================================================================
*/
void __dv_initmem
(	__dv_uint8_t *membase,		/* Bottom of free memory */
	__dv_size_t memlen			/* Length of free memory in bytes */
)
{
	__dv_memhead.next = (__dv_mblock_t *)membase;
	__dv_memhead.len = 0;
	__dv_memhead.next->len = memlen;
	__dv_memhead.next->next = __DV_NULL;
}
