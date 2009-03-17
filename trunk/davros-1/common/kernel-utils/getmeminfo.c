/*	getmeminfo.c - __davros_getmeminfo
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

#include "davros/kernel-utils.h"

__DAVROS_IDENT("$Id$")

/*==============================================================================
 *	getmeminfo - get free memory stats
 *==============================================================================
*/
void __davros_getmeminfo
(	__davros_meminfo_t *info
)
{
	__arch_intstatus_t ps;
	__davros_mblock_t *p;

	info->nfrag = 0;
	info->biggest = 0;
	info->smallest = ULONG_MAX;
	info->total = 0;

	ps = __arch_disableinterrupts();

	p = __davros.memhead.next;
	while (	p != NULL )
	{
		info->nfrag++;
		info->total += p->len;
		if ( p->len > info->biggest )
			info->biggest = p->len;
		if ( p->len < info->smallest )
			info->smallest = p->len;
		p = p->next;
	}

	__arch_restoreinterrupts(ps);
}
