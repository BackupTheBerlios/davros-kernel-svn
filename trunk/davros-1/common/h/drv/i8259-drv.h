/*	i8259-drv.h - driver for 8259 interrupt controller
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
 *	This file contains driver definitions for the intel 8259 interrupt
 *	controller
 *
*/

#ifndef __i8259_drv_h
#define __i8259_drv_h

#include "arch-cpudef.h"
#include "devices/i8259.h"

#ifdef __cplusplus
extern "C" {
#endif

/*	These must be supplied by the board config */
extern uint32_t i8259_read(memaddr_t i8259, int reg);
extern void i8259_write(memaddr_t i8259, int reg, uint32_t val);


void i8259_init(memaddr_t i8259,
			uint8_t icw1, uint8_t icw2, uint8_t icw3, uint8_t icw4);
uint8_t i8259_set_mask(memaddr_t i8259, uint8_t mask);
uint8_t i8259_get_mask(memaddr_t i8259);
uint8_t i8259_enable(memaddr_t i8259, uint8_t mask);
uint8_t i8259_disable(memaddr_t i8259, uint8_t mask);

#ifdef __cplusplus
}
#endif

#endif
