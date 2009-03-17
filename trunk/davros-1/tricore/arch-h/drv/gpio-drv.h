/*	gpio-drv.h - Driver for Tricore GPIO module
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
 *	This file contains definitions for a driver for Tricore's general-
 *	purpose I/O port module (GPIO)
 *
*/

#if !defined(__gpio_drv_h)
#define __gpio_drv_h

#include "tricore.h"
#include "modules/tricore-gpio.h"

typedef struct gpio_port_descr
{
    tricore_gpio_t *base;
    int	nPins;
    unsigned options;	/* GPIO_HAS_***	*/
} gpio_port_descr_t;

/* Bit fields for mode parameter for gpio_port_config.
 * Base value is either MODE_IN or MODE OUT.
 * Optional modifiers are:
 * 	- MODE_PULL_UP or MODE_PULL_DOWN.
 * 	- MODE_ALT_n  (one of 3 alternative output functions)
 *	- MODE_OD (open drain - output only)
*/
#define GPIO_MODE_IN		0x00
#define GPIO_MODE_OUT		0x01
#define GPIO_MODE_PULL		0x04	/* Private */
#define GPIO_MODE_PULLDIR	0x08	/* Private */
#define GPIO_MODE_PULLUP	(GPIO_MODE_PULL)
#define GPIO_MODE_PULLDOWN	(GPIO_MODE_PULL|GPIO_MODE_PULLDIR)
#define GPIO_MODE_ALT		0x30	/* Private */
#define GPIO_MODE_ALT1		0x10
#define GPIO_MODE_ALT2		0x20
#define GPIO_MODE_ALT3		(GPIO_MODE_ALT1|GPIO_MODE_ALT2)
#define GPIO_MODE_OPENDRAIN	0x80

/* Bits in descriptor options */
#define GPIO_HAS_IN			0x00000001	/* Can do input */
#define GPIO_HAS_OUT		0x00000002	/* Can do output */
#define GPIO_HAS_IO			(GPIO_HAS_IN|GPIO_HAS_OUT)	/* Can do both */
#define GPIO_HAS_PUD		0x00000004	/* Has pull-up/down */
#define GPIO_HAS_OD			0x00000010	/* od register is present */
#define GPIO_HAS_AS0		0x00000020	/* altsel0 register is present */
#define GPIO_HAS_AS1		0x00000040	/* altsel1 register is present */
#define GPIO_HAS_AS2		(GPIO_HAS_AS0|GPIO_HAS_AS1)	/* Both are present */

int gpio_port_config(int port, int pin, uint32_t mode);

#endif
