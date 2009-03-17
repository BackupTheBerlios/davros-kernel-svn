/*	lsmem.c - __davros_lsmem
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
#include <stdio.h>

__DAVROS_IDENT("$Id$")

/*==============================================================================
 *	lsmem - print memory stats
 *==============================================================================
*/
void __davros_lsmem
(	__davros_device_t *out
)
{
	__davros_meminfo_t info;

	if ( out == NULL )
		out = __davros_getstdout();

	if ( out == NULL )
		return;

	__davros_getmeminfo(&info);

	fprintf(out, "Total %u bytes in %u fragments. Biggest %u, smallest %u.\n",
		info.total, info.nfrag, info.biggest, info.smallest);
}
