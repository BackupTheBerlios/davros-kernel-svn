/*	time.h - davros time services
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

#ifndef __dv_time_h
#define __dv_time_h

#ifdef __DV_IDENT
__DV_IDENT("$Id$")
#endif

#include <davros/basic-types.h>
#include <davros/queue.h>

/* Get the timer definitions from the processor family.
 * Required macros:
 * __DV_ABSOLUTEMAXTIME - maximum time that an interrupt can be set for. Allow room for delays.
 * __DV_DEFAULTTIME - time to set interrupt for if 'diff' is more than __DV_ABSOLUTEMAXTIME
*/
#define __DV_BASEFILE	timer
#include <davros/family-select.h>

#ifndef __DV_ASM

extern __dv_uint64_t __dv_time;
extern __dv_uint32_t __dv_last_timer_value;
extern __dv_queue_t __dv_sleepqueue;

void __dv_inittime(void);
void __dv_marktime(void);
__dv_uint32_t __dv_tick(__dv_uint32_t);

__dv_uint64_t __dv_gettime(void);
__dv_status_t __dv_sleep(__dv_uint32_t);
__dv_status_t __dv_sleepuntil(__dv_uint64_t);

/* These are provided by the processor family ...
 *
 * They may be macros so we'll hide these protoypes behind ifndef walls.
*/
#ifndef __dv_inittimer
__dv_status_t __dv_inittimer(void);
#endif

#ifndef __dv_readtimer
__dv_uint32_t __dv_readtimer(void);
#endif

#ifndef __dv_wraptimer
__dv_uint32_t __dv_wraptimer(__dv_uint32_t);
#endif

#ifndef __dv_settimer
__dv_status_t __dv_settimer(__dv_uint32_t, __dv_uint32_t);
#endif

#ifndef __dv_stoptimer
__dv_status_t __dv_stoptimer(void);
#endif

#endif

#endif
