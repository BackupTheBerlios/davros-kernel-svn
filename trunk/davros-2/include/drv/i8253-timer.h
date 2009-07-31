/*	i8253-timer.h - header file for i8253 timer
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

#ifndef __i8253_timer_h
#define __i8253_timer_h

#include <davros/basic-types.h>
#include <devices/i8253.h>

#ifdef __DV_IDENT
__DV_IDENT("$Id$")
#endif

#ifndef __DV_ASM

/* For davros' system timer we use timer 2 (configured as free-running) for the reference
 * time, and timer 0 (configured as 1 shot) for generating interrupts. Timer 0 is the
 * only timer that's connected to the interrupt controller.
 *
 * The timer is 16-bits, so we must enforce the wrap
 * The timer is a down-counter so we negate if for use in the kernel.
*/
#define __DV_TIMER_INTVEC	__DV_INTNUM_TIMER

#define __dv_readtimer()	(-__dv_i8253_read(__dv_i8253_base, i8253_c2))
#define __dv_subtimer(x, y)	(((x)-(y))&0xffff)

__dv_status_t __dv_inittimer(void);
__dv_status_t __dv_settimer(__dv_uint32_t, __dv_uint32_t);
__dv_status_t __dv_stoptimer(void);

/*  These must be supplied by the board config
*/
__dv_uint32_t __dv_i8253_read(__dv_address_t, __dv_int_t);
void __dv_i8253_write(__dv_address_t, __dv_int_t, __dv_uint32_t val);

/* The address of this "variable" is usually defined in the linker file
*/
extern __dv_uint16_t __dv_i8253_base;

#endif

#define __DV_MAXINTERVAL		0xc000
#define __DV_DEFINTERVAL		0x8000

#endif
