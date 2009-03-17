/*	asc-drv.c - Driver for Tricore ASC module
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
 *	This file contains the common part of a driver for Tricore's
 *	asynchronous serial communications module (ASC)
 *
*/

#include "drv/asc-drv.h"
#include "drv/mod-drv.h"
#include "drv/pwr-drv.h"
#include "tricore-core.h"


const uint32_t	default_baud		= 9600;
const char		default_params[]	= "8N1";

/*
 *	asc_init() - initialise the module
 *
 *	This function initialises the ASC module and puts some default values
 *	into the settings registers.
*/

void asc_init(tricore_asc_t *asc, int pisel)
{
	tricore_module_init(&asc->asc_hdr, 0, 1);
	asc->asc_tsrc = ISR_CLRR;
	asc->asc_rsrc = ISR_CLRR;
	asc->asc_esrc = ISR_CLRR;
	asc->asc_tbsrc = ISR_CLRR;
	asc->asc_con = 0;
	asc_params(asc, default_params);
	asc_baud(asc, default_baud);
	asc->asc_pisel = pisel;
	asc->asc_con |= ASC_CON_REN;
}

/*
 *	asc_params() - set and/or get the parameters
 *
 *	This function sets the comms parameters (data bits, stop bits, parity) if the
 *	supplied parameter string is a legal string. The new or current
 *	parameters are returned in a static string.
 *	Legal parameter strings are (for the moment):
 *		8N1, 8N2, 8E1, 8E2, 8O1, 8O2, 7E1, 7E2, 7O1, 7O2
 *	In theory we can also do 8M1, 8M2, 8S1, 8S2, but that requires software intervention.
*/

char * asc_params(tricore_asc_t *asc, const char *params)
{
	static char retbuf[4];
	uint32_t con = asc->asc_con & ~(ASC_CON_M | ASC_CON_STP | ASC_CON_PEN | ASC_CON_ODD);
	int error = 0;

	if ( params != NULL && ( params[2] == '1' ||  params[2] == '2' ) )
	{
		if ( params[2] == '2' )
			con |= ASC_CON_STP_2;
		
		if ( params[0] == '7' )
		{
			con |= ASC_CON_M_7P | ASC_CON_PEN;
			if ( params[1] == 'E' )
			{
			}
			else
            if ( params[1] == 'O' )
            {
				con |= ASC_CON_ODD;
            }
            else
				error = 1;
		}
		else
        if ( params[0] == '8' )
        {
			if ( params[1] == 'N' )
			{
				con |= ASC_CON_M_8ASYNC;
			}
			else
			if ( params[1] == 'E' )
			{
				con |= (ASC_CON_M_8P | ASC_CON_PEN);
			}
			else
            if ( params[1] == 'O' )
            {
				con |= (ASC_CON_M_8P | ASC_CON_PEN | ASC_CON_ODD);
            }
            else
				error = 1;
        }
        else
			error = 1;

		if ( !error )
			asc->asc_con = con;
	}

	con = asc->asc_con;
	retbuf[0] = '?';
	retbuf[1] = '?';
	retbuf[2] = '?';
	retbuf[3] = '\0';

	if ( (con & ASC_CON_M) == ASC_CON_M_8ASYNC )
	{
		retbuf[0] = '8';
		retbuf[1] = 'N';
	}
	else
	if ( (con & ASC_CON_M) == ASC_CON_M_8P )
	{
		retbuf[0] = '8';
	}
	else
	if ( (con & ASC_CON_M) == ASC_CON_M_7P )
	{
		retbuf[0] = '7';
	}

	if ( retbuf[0] != '?' && retbuf[1] == '?' )
		retbuf[1] = ( con & ASC_CON_ODD ) ? 'O' : 'E';

	if ( retbuf[1] != '?' )
		retbuf[2] = ( ( con & ASC_CON_STP ) == ASC_CON_STP_2 ) ? '2' : '1';

	return(retbuf);
}

/*
 *	asc_baud() - set and/or get the baud rate
 *
 *	This function sets the baud rate if the supplied rate is non-zero.
 *	The new or current rate is returned.
 *
 *	Input to the baud rate generator is SYSCLK, as returned by cpu_clock_rate(0).
 *	This frequency can be divided by 2 or by 3, or multiplied by FDV/512. The
 *	intermediate frequency thus obtained is further divided by 16*(BG+1) to obtain
 *	the desired bit rate.
*/

uint32_t asc_baud(tricore_asc_t *asc, uint32_t baud)
{
	int ps;
	int asc_freq;	/* Frequency the ASC module is clocked at */
	int bg_val;
	uint32_t baud_frac, fdv_val, freq;

	if ( baud == 0 )
	{
		/* FIXME: should calculate current baud rate */
	}
	else
	{
		asc_freq = module_clock_rate();

		/* The nominal BG value is reduced by 1 to be on the safe side
		 * for the FDV factor calculation.
		*/
		bg_val = asc_freq / ( baud*16 ) - 2;

		if (bg_val < 0 || bg_val > 8191)
			return (0);		/* can't possibly generate that baud rate */

		/* Calculate the Fractional devider Factor FDV
		*/
		baud_frac = baud/100;
		fdv_val = (bg_val+1)*512*16*baud_frac;
		freq = asc_freq/100;
		fdv_val /= freq;

		/* disable interrupts during chip access
		*/
		ps = disable_interrupts();

		/* Disable Fractional Divider (FDE)
		 * Divide clock by reload-value + constant (BRS)
		 * Disable Baud Rate Generator; BG should only be written when SR=0
		 *
		 * FDE = 0; BRS = 0; SR = 0
		*/
		asc->asc_con &= ~(ASC_CON_FDE | ASC_CON_BRS | ASC_CON_R);

		/* Enable fractional divider: FDE = 1; BRS = don't care
		*/
		asc->asc_con |= ASC_CON_FDE;

		/* Set reload value in BG
		*/
		asc->asc_bg = bg_val;

		/* Set the fractional divider value in FDV
		*/
		asc->asc_fdv = fdv_val;

		/* Enable Baud Rate Generator
		*/
		asc->asc_con |= ASC_CON_R;			/* SR = 1 */
 
		restore_interrupts(ps);
	}

	return(baud);
}
