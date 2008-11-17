/*	basic-constants.h - davros constants (general-purpose)
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

#ifndef __dv_basic_constants_h
#define __dv_basic_constants_h

#ifdef __DV_IDENT
__DV_IDENT("$Id$")
#endif

#include <davros/cpu-characteristics.h>

/* A NULL pointer
*/
#define __DV_NULL		0

/* Boolean values
*/
#define __DV_TRUE		1
#define __DV_FALSE		0

/* Return values from some functions
*/
#define __DV_OK			0
#define __DV_ERR		(-1)

/* MAXINT, MININT and MAXUINT depend on the size of the integer type
*/
#ifndef __DV_SIZEOF_INT

#error "Processor characteristics file fails to define __DV_SIZEOF_INT"

#elif	__DV_SIZEOF_INT == 2

#define __DV_MAXINT		32767
#define __DV_MININT		(-32768)
#define __DV_MAXUINT	0xffff

#elif	__DV_SIZEOF_INT == 4

#define __DV_MAXINT		2147483647
#define __DV_MININT		(-2147483648)
#define __DV_MAXUINT	0xffffffff

#else
#error "Unsupported integer size"
#endif

#endif
