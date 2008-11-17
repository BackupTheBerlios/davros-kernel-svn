/*	arm-timer.h - timer header for arm family
 *
 *	Copyright 2008 David Haworth
 *
 *	This file is part of davros.
 *
 *	davros is free software: you can redistribute it and/or modify
 *	it under the terms of the GNU General Public License as published by
 *	the Free Software Foundation, either version 3 of the License, or
 *	(at your option) any later version.
 *
 *	davros is distributed in the hope that it will be useful,
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *	GNU General Public License for more details.
 *
 *	You should have received a copy of the GNU General Public License
 *	along with davros.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef __dv_arm_timer_h
#define __dv_arm_timer_h

#ifdef __DV_IDENT
__DV_IDENT("$Id$")
#endif

/* FIXME: eventually this file will have to select the timer depending on processor, board etc.
 * For now, we'll assume an arm926EJ on an Integrator/CP board.
*/
#include <arm-icp-timer.h>

#endif
