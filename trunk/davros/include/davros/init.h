/*	init.h - header file for davros initialisation
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

#ifndef __dv_init_h
#define __dv_init_h

#ifdef __DV_IDENT
__DV_IDENT("$Id$")
#endif

#include <davros/cpu-characteristics.h>
#include <davros/basic-types.h>

extern __dv_stackelement_t	__dv_kernstack[];
extern __dv_stackelement_t	__dv_nullstack[];

extern __dv_uint8_t __dv_in_kernel;

void __dv_init(__dv_uint8_t*, __dv_size_t);

#endif
