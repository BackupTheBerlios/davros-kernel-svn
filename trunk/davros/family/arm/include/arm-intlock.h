/*	arm-intlock.h - interrupt locking on the arm family
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

#ifndef __dv_arm_intlock_h
#define __dv_arm_intlock_h

#ifdef __DV_IDENT
__DV_IDENT("$Id$")
#endif

#include <arm-core.h>

#define __DV_INTSTATUS_T	__dv_uint32_t

#define __dv_lock() 	0

#define __dv_unlock()	0

#define __dv_restore(x) \
	do {						\
	} while (0)

#define __dv_enable()	__dv_set_cpsr((__dv_get_cpsr() & ~__DV_PSR_IRQ))

#endif
