/*	gpio-drv.c - Driver for Tricore GPIO module
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
 *	general-purpose I/O port module (GPIO)
 *
*/

#include "drv/mod-drv.h"
#include "drv/gpio-drv.h"
#include "tricore-core.h"

const gpio_port_descr_t gpio_table[TRICORE_NGPIO] = TRICORE_GPIO_DESCR;

/******************************************************************************
 *
 *	gpio_port_config - configure the mode of a gpio pin
 *
 *	This routine sets the pin <pin> of the port <port> to the given <mode>.
 *
 *	Mode can be one of the following:
 *		GPIO_MODE_IN		- input
 *		GPIO_MODE_OUT		- output
 *
 *	along with a combination of the following modifiers:
 *		GPIO_MODE_PULLUP	- enable the internal pull-up
 *		GPIO_MODE_PULLDOWN	- enable the internal pull-down
 *		GPIO_MODE_OPENDRAIN	- output is open drain
 *		GPIO_MODE_ALT1		- alternate function 1
 *		GPIO_MODE_ALT2		- alternate function 2
 *		GPIO_MODE_ALT3		- alternate function 3
*/

int gpio_port_config(int port, int pin, uint32_t mode)
{
	uint32_t pinmask;
	const gpio_port_descr_t *pd;

	if ( port < 0 || port >= TRICORE_NGPIO )
		return(-1);

	pd = &gpio_table[port];

	if ( pd->base == NULL || pin < 0 || pin >= pd->nPins )
		return(-1);

	if ( (mode & GPIO_MODE_PULL) & !(pd->options & GPIO_HAS_PUD) )
		return(-1);		/* Port cannot do pull-up/down */

	if ( (mode & GPIO_MODE_ALT1) && !(pd->options & GPIO_HAS_AS0) )
		return(-1);		/* Port doesn't have altsel0 register */

	if ( (mode & GPIO_MODE_ALT2) && !(pd->options & GPIO_HAS_AS1) )
		return(-1);		/* Port doesn't have altsel1 register */

	pinmask = (1 << pin);

	if ( mode & GPIO_MODE_OUT )
	{
		/* Output requested. */
		if ( (pd->options & GPIO_HAS_OUT) == 0 )
			return(-1);		/* Port cannot do output */

		if ( (mode & GPIO_MODE_OPENDRAIN) && !(pd->options & GPIO_HAS_OD) )
			return(-1);		/* Port doesn't have od register */

		/* Select open drain or push-pull if port has that feature */
		if ( pd->options & GPIO_HAS_OD )
		{
			if ( mode & GPIO_MODE_OPENDRAIN )	/* OD-reg is inverted (0==open drain) */
				pd->base->gpio_od &= ~pinmask;	
			else
				pd->base->gpio_od |= pinmask;
		}

		/* Finally, set direction to "output" (must be last!) */
		pd->base->gpio_dir |= pinmask;
	}
	else
	{
		if ( (pd->options & GPIO_HAS_IN) == 0 )
			return(-1);		/* Port cannot do input */

		pd->base->gpio_dir &= ~pinmask;	/* Set direction to "input" */
	}

	/* Select alternate function 1 if port has that feature */
	if ( pd->options & GPIO_HAS_AS0 )
	{
		if ( mode & GPIO_MODE_ALT1 )
			pd->base->gpio_altsel0 |= pinmask;
		else
			pd->base->gpio_altsel0 &= ~pinmask;
	}

	/* Select alternate function 2 if port has that feature */
	if ( pd->options & GPIO_HAS_AS1 )
	{
		if ( mode & GPIO_MODE_ALT2 )
			pd->base->gpio_altsel1 |= pinmask;
		else
			pd->base->gpio_altsel1 &= ~pinmask;
	}

	/* Note: alternate funtion 3 is alt.f.1 and alt.f.2 simultaneously */

	/* Select pull-up/pull-down options if port has that feature */
	if ( pd->options & GPIO_HAS_PUD )
	{
		if ( mode & GPIO_MODE_PULL )
		{
			if ( mode & GPIO_MODE_PULLDIR )
				pd->base->gpio_pudsel |= pinmask;	/* Pull-up */
			else
				pd->base->gpio_pudsel &= ~pinmask;	/* Pull-down */

			pd->base->gpio_puden |= pinmask;		/* Enable pu/pd */
		}
		else
			pd->base->gpio_puden &= ~pinmask;	/* Disable pu/pd */
	}

	return(0);
}
