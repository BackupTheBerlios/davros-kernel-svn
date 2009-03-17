/*	i8253-drv.c - driver for 8253 counter/timer
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
 *	This file contains the driver for the intel 8253 counter/timer
 *
*/

#include "drv/i8253-drv.h"

/*
 *	i8253_init() - initialise a counter of the 8253
 *
*/
void i8253_init(memaddr_t i8253, int counter, uint8_t mode, uint16_t count)
{
	i8253_write(i8253, i8253_ctrl, mode | (counter << 6));
	if ( mode & I8253_CTRL_RWL_L )
		i8253_write(i8253, counter, count & 0xff);
	if ( mode & I8253_CTRL_RWL_M )
		i8253_write(i8253, counter, (count >> 8) & 0xff);
}
