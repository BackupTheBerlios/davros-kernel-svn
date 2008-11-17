/*	cpu-intlock.h - interrupt locking mechanisms
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

#ifndef __dv_cpu_intlock_h
#define __dv_cpu_intlock_h

#ifdef __DV_IDENT
__DV_IDENT("$Id$")
#endif

#include <davros/processors.h>
#include <davros/basic-types.h>

/* Get the interrupt locking mechanisms of the processor family
 *
 * This file must define the following macros:
 *
 *   __DV_INTSTATUS_T			type for holding interrupt status
 *
 * In addition, it will define the following as macros or functions:
*/
#define __DV_BASEFILE	intlock
#include <davros/family-select.h>

#ifndef __DV_ASM

/* Data type for holding the saved interrupt status.
*/
#ifndef __DV_INTSTATUS_T
#error "Family-specific file does not define __DV_INTSTATUS_T"
#else

typedef __DV_INTSTATUS_T __dv_intstatus_t;

#endif
#endif

#endif
