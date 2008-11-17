/*	arm-characteristics.h - characteristics of the arm CPU family
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

#ifndef __dv_arm_characteristics_h
#define __dv_arm_characteristics_h

#ifdef __DV_IDENT
__DV_IDENT("$Id$")
#endif

#define __DV_ENDIAN					__DV_LITTLEENDIAN
#define __DV_STACKGROWS				__DV_STACKGROWSDOWN
#define __DV_SIZEOF_STACKELEMENT	4
#define __DV_SIZEOF_INT				4
#define __DV_SIZEOF_PTR				4

#endif
