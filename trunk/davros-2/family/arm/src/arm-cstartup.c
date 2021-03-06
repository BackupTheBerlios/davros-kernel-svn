/*	arm-cstartup.c - __dv_C_startup (for arm family)
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
#include <davros/constants.h>
#include <davros/basic-types.h>
#include <davros/init.h>
#include <arm-icp-pic.h>

#ifdef __DV_IDENT
__DV_IDENT("$Id$")
#endif

const __dv_stackelement_t *__dv_irq_sp = &__dv_nullstack[DV_CFG_NULLSTACK_LEN];

/*==============================================================================
 *	__dv__C_startup - the C part of the system startup code
 *==============================================================================
*/
void __dv_C_startup(void)
{
	/* Disable all interrupt sources.
	*/
	__dv_arm_pic_pri_irq.enable_clear = 0xffffffff;
	__dv_arm_pic_pri_fiq.enable_clear = 0xffffffff;
	__dv_arm_pic_sec.enable_clear = 0xffffffff;

	/* Clear all pending interrupts.
	*/
	__dv_arm_pic_pri_irq.soft_clear = 0xffffffff;
	__dv_arm_pic_sec.soft_clear = 0xffffffff;
}
