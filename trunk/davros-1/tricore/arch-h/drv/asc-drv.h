/*	asc-drv.h - Driver for Tricore ASC module
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
 *	This file contains definitions for a driver for Tricore's asynchronous
 *	serial communications module (ASC)
 *
*/

#if !defined(__asc_drv_h)
#define __asc_drv_h

#include "modules/tricore-asc.h"

/*	Prototypes for the polled driver */
void asc_polled_init(tricore_asc_t *asc);
uint32_t asc_polled_getc(tricore_asc_t *asc);
void asc_polled_putc(tricore_asc_t *asc, uint32_t c);

/*	Prototypes for the interrupt-driven driver	*/

/*	Prototypes common to both drivers */
void asc_init(tricore_asc_t *asc, int pisel);
char * asc_params(tricore_asc_t *asc, const char *params);
uint32_t asc_baud(tricore_asc_t *asc, uint32_t baud);

#endif
