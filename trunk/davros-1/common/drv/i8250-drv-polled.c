/*	i8250-drv-polled.c - simple polled driver for 8250 UART + derivatives.
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
 *	This file contains a simple polled driver for the intel
 *	8250 UART and its derivatives and clones.
 *
*/

#include "drv/i8250-drv.h"

/*
 *  i8250_polled_init() - initialise for polled operation
 *
 *  This function initialises the i8250 for polled operation. The involves
 *	disabling all the interrupts. We also set the OUT2 pin low, which
 *	diconnects the interrupt line on standard ISA PC cards.
*/
void i8250_polled_init(memaddr_t i8250)
{
	i8250_write(i8250, i8250_mcr,
					i8250_read(i8250, i8250_mcr) & ~I8250_MCR_OUT2);
	i8250_write(i8250, i8250_ier, 0);
}

/*
 *	i8250_polled_getc() - get a character from the input. Wait if necessary.
 *
 *	This function returns the first character to be received by the receiver.
 *	The routine blocks until a character is present (busy-wait).
*/
uint32_t i8250_polled_getc(memaddr_t i8250)
{
	while ( (i8250_read(i8250, i8250_lsr) & I8250_LSR_RXRDY) == 0 )
		;	/* Spin till character available */

	return(i8250_read(i8250, i8250_data) & 0xff);
}

/*
 *	i8250_polled_putc() - put a character in the transmit buffer. Wait if necessary.
 *
 *	This function puts the given character into the transmit buffer. The routine
 *	blocks until the buffer is free (busy-wait).
*/
void i8250_polled_putc(memaddr_t i8250, uint32_t c)
{
	while ( (i8250_read(i8250, i8250_lsr) & I8250_LSR_THRE) == 0 )
		;	/* Spin till buffer empty */

	i8250_write(i8250, i8250_data, c);
}
