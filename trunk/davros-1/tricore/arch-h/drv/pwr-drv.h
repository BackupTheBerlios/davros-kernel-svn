/*	pwr-drv.h - Driver for Tricore PWR module
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
 *	This file contains definitions for a driver for Tricore's
 *	PWR module.
 *
*/

#if !defined(__pwr_drv_h)
#define __pwr_drv_h
#include "arch-cpudef.h"
#include "modules/tricore-pwr.h"

/*	Prototypes for the driver */
void endinit(int e);
uint32_t cpu_clock_rate(uint32_t req_rate);
uint32_t module_clock_rate(void);

#endif
