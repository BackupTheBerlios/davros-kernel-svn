/*	drv-i8253.c - __dv_inittimer, __dv_readtimer, __dv_settimer, __dv_stoptimer
 *
 *	Copyright 2009 David Haworth
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
#include <davros/config.h>
#include <davros/basic-types.h>

#ifdef __DV_IDENT
__DV_IDENT("$Id$")
#endif

/*==============================================================================
 *	__dv_inittimer - initialise the 8253 timer for use
 *==============================================================================
*/
__dv_status_t __dv_inittimer(void)
{
	return 0;
}

/*==============================================================================
 *	__dv_settimer - set an interval timer to interrupt after a given time
 *==============================================================================
*/
__dv_status_t __dv_settimer(__dv_uint32_t last, __dv_uint32_t delta)
{
	return 0;
}

/*==============================================================================
 *	__dv_stoptimer - stop an interval timer
 *==============================================================================
*/
__dv_status_t __dv_stoptimer(void)
{
	return 0;
}

/*==============================================================================
 *	__dv_readtimer - read the free-running counter
 *==============================================================================
*/
__dv_uint32_t __dv_readtimer(void)
{
	return 0;
}
