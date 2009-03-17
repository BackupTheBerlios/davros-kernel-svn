/*	i8250-drv.h - simple driver for 8250 UART + derivatives.
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
 *	This file contains definitions for a simple driver for the intel
 *	8250 UART and its derivatives and clones.
 *
*/

#ifndef __i8250_drv_h
#define __i8250_drv_h

#include "arch-cpudef.h"
#include "devices/i8250.h"

/*	These must be supplied by the board config */
extern uint32_t i8250_read(memaddr_t i8250, int reg);
extern void i8250_write(memaddr_t i8250, int reg, uint32_t val);

/*	Prototypes for the polled driver */
void i8250_polled_init(memaddr_t i8250);
uint32_t i8250_polled_getc(memaddr_t i8250);
void i8250_polled_putc(memaddr_t i8250, uint32_t c);

/*	Prototypes for the interrupt-driven driver	*/

/*	Prototypes common to both drivers */
void i8250_init(memaddr_t i8250);
char * i8250_params(memaddr_t i8250, const char *params);
uint32_t i8250_baud(memaddr_t i8250, uint32_t baud);

#endif
