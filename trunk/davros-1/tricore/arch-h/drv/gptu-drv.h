/*	gptu-drv.h - Driver for Tricore GPTU module
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
 *	purpose timer module (GPTU)
 *
*/

#if !defined(__gptu_drv_h)
#define __gptu_drv_h

#include "tricore.h"
#include "modules/tricore-gptu.h"

int gptu_timer_start(tricore_gptu_t *gptu, int timer, int inum, int hz);
int gptu_timer_stop(tricore_gptu_t *gptu, int timer);
int gptu_timer_enable_int(tricore_gptu_t *gptu, int timer);
int gptu_timer_disable_int(tricore_gptu_t *gptu, int timer);

#endif
