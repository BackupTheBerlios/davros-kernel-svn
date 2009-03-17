/*	tricore-gpio.h - Tricore general-purpose I/O port description
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
 *	This file contains a description of Tricore's General Purpose I/O
 *  Port module. 
*/

#if !defined(__tricore_gpio_h)
#define __tricore_gpio_h

#ifdef __cplusplus
extern "C" {
#endif

#include "modules/tricore-mod.h"

#if !defined(__ASSEMBLER__)

typedef struct tricore_gpio
{
    tricore_mod_t gpio_hdr;				/* No clc, just id */
	volatile uint32_t reserved1;
    volatile unsigned gpio_out;			/* Data output register */
    volatile unsigned gpio_in;			/* Data input register */
    volatile unsigned gpio_dir;			/* Direction register */
    volatile unsigned gpio_od;			/* Open drain register */
    volatile unsigned reserved2[2];
    volatile unsigned gpio_pudsel;		/* Pull up/down select register */
    volatile unsigned gpio_puden;		/* Pull up/down enable register */
    volatile unsigned reserved3[5];
    volatile unsigned gpio_altsel0;		/* Alternate select register 0 */
    volatile unsigned gpio_altsel1;		/* Alternate select register 1 */
} tricore_gpio_t;

#endif

#ifdef __cplusplus
}
#endif

#endif
