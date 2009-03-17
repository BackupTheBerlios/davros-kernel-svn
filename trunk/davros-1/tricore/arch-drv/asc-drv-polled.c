/*	asc-drv-polled.c - Polled driver for Tricore ASC module
 *
 *	Copyright 2001 David Haworth
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
 *	This file contains a polled driver for Tricore's asynchronous serial
 *	communications module (ASC)
 *
*/

#include "modules/tricore-asc.h"
#include "drv/asc-drv.h"

/*
 *  asc_polled_init() - initialise for polled operation
 *
 *  This function initialises the ASC for polled operation. The involves
 *	disabling all the interrupt request nodes. The generic initialisation
 *	is assumed to be done before or after this routine is called.
*/

void asc_polled_init(tricore_asc_t *asc)
{
	asc->asc_tsrc = ( asc->asc_tsrc & ~ISR_SRE ) | ISR_CLRR;
	asc->asc_rsrc = ( asc->asc_rsrc & ~ISR_SRE ) | ISR_CLRR;
	asc->asc_esrc = ( asc->asc_esrc & ~ISR_SRE ) | ISR_CLRR;
	asc->asc_tbsrc = ( asc->asc_tbsrc & ~ISR_SRE ) | ISR_CLRR;
}


/*
 *	asc_polled_getc() - get a character from the input. Wait if necessary.
 *
 *	This function returns the first character to be received by the receiver.
 *	The routine blocks until a character is present (busy-wait).
*/

uint32_t asc_polled_getc(tricore_asc_t *asc)
{
	while ( (asc->asc_rsrc & ISR_SRR) == 0 )
		;	/*	Nothing	*/
	asc->asc_rsrc |= ISR_CLRR;

	return(asc->asc_rbuf);
}

/*
 *	asc_polled_putc() - put a character in the transmit buffer. Wait if necessary.
 *
 *	This function puts the given character into the transmit buffer. The routine
 *	blocks until the buffer is free (busy-wait).
*/

void asc_polled_putc(tricore_asc_t *asc, uint32_t c)
{
	while ( (asc->asc_tsrc & ISR_SRR) == 0 )
		;	/*	Nothing	*/
	asc->asc_tsrc |= ISR_CLRR;
	asc->asc_tbuf = c;
}
