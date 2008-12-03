/*	arm-icp-disableint.c - __dv_disable_interrupt
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
#include <davros/constants.h>
#include <davros/interrupt.h>
#include <arm-icp-pic.h>

#ifdef __DV_IDENT
__DV_IDENT("$Id$")
#endif

/*==================================================================================================
 *	__dv_disable_interrupt - disable an interrupt
 *==================================================================================================
*/
__dv_status_t __dv_disable_interrupt
(	__dv_unsigned_t intno
)
{
	__dv_status_t result = __DV_ERR;

	if ( intno < __DV_NUMINT_PRI )
	{
		__dv_arm_pic_pri_irq.enable_clear = 1 << intno;
		result = __DV_OK;
	}
	else
	if ( intno < (__DV_NUMINT_PRI + __DV_NUMINT_SEC) )
	{
		__dv_arm_pic_sec.enable_clear = 1 << (intno - __DV_NUMINT_PRI);
		result = __DV_OK;
	}

	return result;
}
