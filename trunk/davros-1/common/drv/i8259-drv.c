/*	i8259-drv.c - simple driver for 8259 UART + derivatives.
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
 *	This file contains a simple driver for the intel
 *	8259 UART and its derivatives and clones.
 *
*/

#include "drv/i8259-drv.h"

/*
 *	i8259_init() - initialise the device
 *
 *	This function initialises the i8259 chip and disables all interrupts
*/
void i8259_init(memaddr_t i8259,
			uint8_t icw1, uint8_t icw2, uint8_t icw3, uint8_t icw4)
{
	i8259_write(i8259, i8259_icw1, icw1 | I8259_ICW1);
	i8259_write(i8259, i8259_icw2, icw2);
	if ( (icw1 & I8259_ICW1_SNGL) == 0 )
		i8259_write(i8259, i8259_icw3, icw3);
	if ( (icw1 & I8259_ICW1_IC4) != 0 )
		i8259_write(i8259, i8259_icw4, icw4);
	i8259_set_mask(i8259, 0xff);
}

/*
 *	i8259_set_mask() - set the mask register
 *
 * 	Sets the interrupt mask register to the specified value,
 *	returns the old value.
*/
uint8_t i8259_set_mask(memaddr_t i8259, uint8_t mask)
{
	uint8_t old = i8259_read(i8259, i8259_ocw1);
	i8259_write(i8259, i8259_ocw1, mask);
	return old;
}

/*
 *	i8259_get_mask() - read the mask register
*/
uint8_t i8259_get_mask(memaddr_t i8259)
{
	return i8259_read(i8259, i8259_ocw1);
}

/*
 *	i8259_enable() - enable the specified interrupts
 *
 *	This routine enables the interrupts specified by the bits in the
 *	mask parameter: 1 = enable, 0 = do not change.
 *
 *	The old value is returned.
*/
uint8_t i8259_enable(memaddr_t i8259, uint8_t mask)
{
	uint8_t old = i8259_read(i8259, i8259_ocw1);
	i8259_write(i8259, i8259_ocw1, old & ~mask);
	return old;
}

/*
 *	i8259_disable() - disable the specified interrupts
 *
 *	This routine disables the interrupts specified by the bits in the
 *	mask parameter: 1 = disable, 0 = do not change.
 *
 *	The old value is returned.
*/
uint8_t i8259_disable(memaddr_t i8259, uint8_t mask)
{
	uint8_t old = i8259_read(i8259, i8259_ocw1);
	i8259_write(i8259, i8259_ocw1, old | mask);
	return old;
}
