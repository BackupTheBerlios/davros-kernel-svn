/*	cpu-process.h - process table (CPU-dependent structures)
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

#ifndef __dv_cpu_process_h
#define __dv_cpu_process_h

#ifdef __DV_IDENT
__DV_IDENT("$Id$")
#endif

#include <davros/processors.h>
#include <davros/basic-types.h>

/* Get the process description specifics of the processor family
 *
 * This file must define the following macros:
 *
 *   __DV_PROCESSREGISTERS_T			type for holding processor registers
 *
 * In addition, it will define the following as macros or functions:
*/
#define __DV_BASEFILE	process
#include <davros/family-select.h>

#ifndef __DV_ASM

/* Data type for holding the saved process context
*/
#ifndef __DV_PROCESSREGISTERS_T
#error "Family-specific file does not define __DV_PROCESSREGISTERS_T"
#else

typedef __DV_PROCESSREGISTERS_T __dv_processregisters_t;

#endif
#endif

#endif
