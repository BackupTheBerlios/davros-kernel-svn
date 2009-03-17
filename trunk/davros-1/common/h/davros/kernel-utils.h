/*	kernel-utils.h - kernel utilities
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

#ifndef __davros_kernel_utils_h
#define __davros_kernel_utils_h

#include "davros/kernel.h"

__DAVROS_IDENT("$Id$")

/* Structure filled by __davros_getmeminfo */
typedef struct __davros_meminfo
{
	int	nfrag;
	size_t biggest;
	size_t smallest;
	size_t total;
} __davros_meminfo_t;

void __davros_getmeminfo(__davros_meminfo_t *info);
void __davros_lsmem(__davros_device_t *out);
void __davros_lsdev(__davros_device_t *out);
void __davros_lsproc(__davros_device_t *out);


#endif
