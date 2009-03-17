/*	pwr-drv.c - Driver for Tricore PWR module
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
 *	This file contains a driver for the Tricore PWR module.
*/

#include "tricore.h"
#include "drv/pwr-drv.h"
#include "tricore-core.h"

/*
 *	endinit - set the endinit bit to the value specified by e.
 *
 *	To set the endinit bit requires a special sequence of incantations
 *	known only to true masters of the forbidden arts. The rest of you
 *	will have to read the code ;-)
*/

void endinit(int e)
{
	uint32_t w0,w1;

	w1 = PWR->pwr_wdtcon1 & (WDTIR | WDTDR);
	w0 = ( PWR->pwr_wdtcon0 | WDTHPW1_MSK ) & ~WDTHPW0_MSK;
	w0 = (w0 ^ WDTLCK) | w1;
	PWR->pwr_wdtcon0 = w0;
	w0 = (w0 & ~(WDTHPW0_MSK | ENDINIT)) ^ WDTLCK;
	if ( e )
		w0 |= ENDINIT;
	PWR->pwr_wdtcon0 = w0;
}

/*
 *	cpu_clock_rate() - gets and/or sets the CPU clock rate
 *
 *	This function gets and/or sets the CPU clock rate. Its parameter is the
 *	required clock rate. It returns the actual clock rate chosen, which is the
 *	highest possible rate not exceeding the required rate. If the required rate
 *	parameter is zero, the rate remains unchanged and the current rate is returned.
*/

uint32_t cpu_clock_rate(uint32_t req_rate)
{
	uint32_t pll = PWR->pwr_pllclc;
	uint32_t rate, current;
	uint32_t k_fac, n_fac, n_rates, nearest_kdiv;
	int i;

	if ( pll & PLL_BYPASS )			/*	PLL bypassed: Clock rate == crystal frequency */
		return(CRYSTAL);

	n_fac = PLL_NFAC((pll >> 12) & 7) * CRYSTAL;
	k_fac = PLL_KFAC((pll >> 16) & 7);

	if ( req_rate == 0 )
		current = n_fac / k_fac;
	else
	{
		current = 0;
		n_rates = (PLL_K_DIV >> 16) + 1;

		for ( i = 0; i < n_rates; i++ )
		{
			rate = n_fac / PLL_KFAC(i);
			if ( rate > current && rate <= req_rate )
			{
				current = rate;
				nearest_kdiv = i;
			}
		}

		if ( current == 0 )
			current = n_fac / k_fac;	/* Requested rate was too low! */
		else
		{
			nearest_kdiv = PLL_K_DIVval(nearest_kdiv);
			if ( (pll & PLL_K_DIV) != nearest_kdiv )
			{
				rate = disable_interrupts();
				endinit(0);
				PWR->pwr_pllclc = ( PWR->pwr_pllclc & ~ PLL_K_DIV ) | nearest_kdiv;
				endinit(1);
				restore_interrupts(rate);
			}
		}
	}

	return(current);
}

/*
 *	module_clock_rate() - gets the module clock rate
 *
 *	The clock distributed to the modules might be different from the
 *	CPU clock. We just return the clock rate here.
*/

uint32_t module_clock_rate(void)
{
	return(cpu_clock_rate(0));	/* FIXME: rider-D has divider! */
}
