/*	arm-dispatch-sec.c - __dv_arm-dispatch-sec
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
#include <davros/config.h>
#include <davros/basic-types.h>
#include <arm-icp-pic.h>

#ifdef __DV_IDENT
__DV_IDENT("$Id$")
#endif

/*==============================================================================
 *	__dv_dispatch_sec - dispatch one or more interrupt handlers from secondary PIC
 *==============================================================================
*/
void __dv_dispatch_sec(void)
{
	__dv_uint32_t pending;
	__dv_uint32_t bit = 1;
	int i;

	/* Read pending interrupts and clear them */
	pending = __dv_arm_pic_sec.status;
	__dv_arm_pic_sec.soft_clear = pending;

	for ( i = 0; i < 32; i++ )
	{
		if ( pending & bit )
		{
		}

		bit = bit << 1;
	}
}
