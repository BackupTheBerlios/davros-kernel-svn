/*	i8253-drv.h - driver for 8253 counter/timer
 *
 *	Copyright 2002 David Haworth
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
 *	This file contains driver definitions for the intel 8253
 *	counter/timer
 *
*/

#ifndef __i8253_drv_h
#define __i8253_drv_h

#include "arch-cpudef.h"
#include "devices/i8253.h"

#ifdef __cplusplus
extern "C" {
#endif

/*	These must be supplied by the board config */
extern uint32_t i8253_read(memaddr_t i8253, int reg);
extern void i8253_write(memaddr_t i8253, int reg, uint32_t val);

void i8253_init(memaddr_t i8253, int counter, uint8_t mode, uint16_t count);

#ifdef __cplusplus
}
#endif

#endif
