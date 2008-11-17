/*	arm-dispatch-irq.c - __dv_arm-dispatch-irq
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
#include <davros/interrupt.h>
#include <arm-icp-pic.h>

#ifdef __DV_IDENT
__DV_IDENT("$Id$")
#endif

/*==============================================================================
 *	__dv_dispatch_irq - dispatch one or more interrupt handlers
 *==============================================================================
*/
void __dv_dispatch_irq(void)
{
	__dv_uint32_t pending;
	__dv_uint32_t bit = 1;
	__dv_interruptentry_t *isr;
	int i;

	/* Read pending interrupts and clear them */
	pending = __dv_arm_pic_pri_irq.status;
	__dv_arm_pic_pri_irq.soft_clear = pending;

	isr = &__dv_interrupt_table[0];
	for ( i = 0; i < __DV_NUMINT_PRI; i++ )
	{
		if ( pending & bit )
		{
			(*isr->func)(isr->param);
		}

		bit = bit << 1;
		isr++;
	}
}
