/*	i8250-drv.c - simple driver for 8250 UART + derivatives.
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
 *	8250 UART and its derivatives and clones.
 *
*/

#include "drv/i8250-drv.h"

const uint32_t	default_baud		= 9600;
const char		default_params[]	= "8N1";
const uint32_t	default_clock		= 115200;

/*
 *	i8250_init() - initialise the device
 *
 *	This function initialises the i8250 chip and puts some default values
 *	into the settings registers.
*/
void i8250_init(memaddr_t i8250)
{
	i8250_write(i8250, i8250_lcr, 0);
	i8250_write(i8250, i8250_ier, 0);
	i8250_write(i8250, i8250_iid, 0);
	i8250_write(i8250, i8250_mcr, 0);
	i8250_params(i8250, default_params);
	i8250_baud(i8250, default_baud);
}

/*
 *	asc_params() - set and/or get the parameters
 *
 *	This function sets the comms parameters (data bits, stop bits, parity) if
 *	the supplied parameter string is a legal string. The new or current
 *	parameters are returned in a static string.
 *	Legal parameter strings are (for the moment):
 *		5/6/7/8 N/E/O/M/S 1/2
*/
char * i8250_params(memaddr_t i8250, const char *params)
{
	static char retbuf[4];
	uint8_t lcr = 0;
	int error = 0;

	if ( params != NULL )
	{
		switch ( params[0] )
		{
		case '5':
			lcr |= I8250_LCR_CS_5;
			break;

		case '6':
			lcr |= I8250_LCR_CS_6;
			break;

		case '7':
			lcr |= I8250_LCR_CS_7;
			break;

		case '8':
			lcr |= I8250_LCR_CS_8;
			break;

		default:
			error = 1;
			break;
		}

		switch ( params[1] )
		{
		case 'N':
			break;

		case 'E':
			lcr |= ( I8250_LCR_PEN | I8250_LCR_EPS );
			break;

		case 'O':
			lcr |= ( I8250_LCR_PEN );
			break;

		case 'S':
			lcr |= ( I8250_LCR_PEN | I8250_LCR_EPS | I8250_LCR_SP );
			break;

		case 'M':
			lcr |= ( I8250_LCR_PEN | I8250_LCR_SP );
			break;

		default:
			error = 1;
			break;
		}

		switch ( params[2] )
		{
		case '1':
			lcr |= I8250_LCR_STB_1;
			break;

		case '2':
			lcr |= I8250_LCR_STB_2;
			break;

		default:
			error = 1;
			break;
		}

		if ( !error )
			i8250_write(i8250, i8250_lcr, lcr);
	}

	lcr = i8250_read(i8250, i8250_lcr);

	retbuf[0] = '?';
	retbuf[1] = 'N';
	retbuf[2] = '1';
	retbuf[3] = '\0';

	switch ( lcr & I8250_LCR_CS )
	{
	case I8250_LCR_CS_5:
		retbuf[0] = '5';
		break;

	case I8250_LCR_CS_6:
		retbuf[0] = '6';
		break;

	case I8250_LCR_CS_7:
		retbuf[0] = '7';
		break;

	case I8250_LCR_CS_8:
		retbuf[0] = '8';
		break;
	}

	if ( lcr & I8250_LCR_PEN )
	{
		switch ( lcr & (I8250_LCR_EPS | I8250_LCR_SP) )
		{
		case 0:
			retbuf[1] = 'O';
			break;

		case I8250_LCR_EPS:
			retbuf[1] = 'E';
			break;

		case I8250_LCR_SP:
			retbuf[1] = 'M';
			break;

		case (I8250_LCR_EPS | I8250_LCR_SP):
			retbuf[1] = 'S';
			break;
		}
	}

	if ( (lcr & I8250_LCR_STB) == I8250_LCR_STB_2 )
		retbuf[2] = '2';

	return(retbuf);
}

/*
 *	i8250_baud() - set and/or get the baud rate
 *
 *	This function sets the baud rate if the supplied rate is non-zero.
 *	The new or current rate is returned.
 *
 *	Input to the baud rate generator is default_clock.
 *	This frequency is divided by the BRD to gice the required rate.
*/
uint32_t i8250_baud(memaddr_t i8250, uint32_t baud)
{
	uint32_t brd;
	uint8_t lcr;

	lcr = i8250_read(i8250, i8250_lcr);
	i8250_write(i8250, i8250_lcr, (lcr | I8250_LCR_DLAB));

	if ( baud != 0 )
	{
		brd = (default_clock + (baud/2))/baud;
		if ( brd > 0 && brd < 32767 )
		{
			i8250_write(i8250, i8250_brdh, (brd >> 8) & 0xff);
			i8250_write(i8250, i8250_brdl, brd & 0xff);
		}
	}

	brd = ((i8250_read(i8250, i8250_brdh) & 0xff) << 8 ) |
		   (i8250_read(i8250, i8250_brdl) & 0xff);
	baud = default_clock / brd;

	i8250_write(i8250, i8250_lcr, lcr);

	return(baud);
}
