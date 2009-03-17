/*	cpu-characteristics.h - defines the CPU characteristics
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

#ifndef __dv_cpu_characteristics_h
#define __dv_cpu_characteristics_h

#ifdef __DV_IDENT
__DV_IDENT("$Id$")
#endif

#include <davros/processors.h>

/* Here are the permitted values for the characteristics
*/
#define __DV_BIGENDIAN		1
#define	__DV_LITTLEENDIAN	2

#define __DV_STACKGROWSUP	1
#define	__DV_STACKGROWSDOWN	2


/* Get the characteristics of the processor family from the family-specific file.
 *
 * This file must define the following macros:
 *
 *   __DV_ENDIAN				either __DV_BIGENDIAN or __DV_LITTLEENDIAN
 *	 __DV_STACKGROWS			either __DV_STACKGROWSUP or __DV_STACKGROWSDOWN
 *   __DV_SIZEOF_STACKELEMENT	1, 2, 4, 8, ...
 *	 __DV_SIZEOF_INT			2, 4, ...
*/
#define __DV_BASEFILE	characteristics
#include <davros/family-select.h>

/* __DV_STACKROUND rounds a requested stack size UP to the next
 * __DV_SIZEOF_STACKELEMENT. Note: this only works if __DV_SIZEOF_STACKELEMENT
 * is an integral power of 2.
*/
#define	__DV_STACKROUND_MASK	(__DV_SIZEOF_STACKELEMENT - 1)
#define __DV_STACKROUND(l)	(((l) + __DV_STACKROUND_MASK) & ~__DV_STACKROUND_MASK)

#endif
