/*	x86-pc-int.c - x86 (pc) interrupt controller
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
#include <davros/constants.h>
#include <davros/interrupt.h>

#ifdef __DV_IDENT
__DV_IDENT("$Id$")
#endif

/*==============================================================================
 *	__dv_enable_interrupt - enable an interrupt source on the PIC
 *==============================================================================
*/
__dv_status_t __dv_enable_interrupt(__dv_unsigned_t inum)
{
	__dv_uint32_t base = __dv_i8259_master;
	__dv_uint32_t mask = 1 << inum;

	if ( inum >= 8 )
	{
		base = __dv_i8259_slave;
		mask = mask >> 8;
	}

	__dv_i8259_enable(base, mask);

	return __DV_OK;
}

/*==============================================================================
 *	__dv_disable_interrupt - disable an interrupt source on the PIC
 *==============================================================================
*/
__dv_status_t __dv_disable_interrupt(__dv_unsigned_t inum)
{
	__dv_uint32_t base = __dv_i8259_master;
	__dv_uint32_t mask = 1 << inum;

	if ( inum >= 8 )
	{
		base = __dv_i8259_slave;
		mask = mask >> 8;
	}

	__dv_i8259_disable(base, mask);

	return __DV_OK;
}

/*==============================================================================
 *	__dv_init_pic - initialise the 2 cascaded PICs
 *==============================================================================
*/
__dv_status_t __dv_init_pic(void)
{
	/*  PC has 2 8259s. Slave connected to input 2 on master.
	 *  We choose auto-eoi mode for now, because nested interrupts 
	 *  are not supported.
	*/
	__dv_i8259_init(__dv_i8259_master, I8259_ICW1_IC4, DV_CFG_BASEIRQ, I8259_ICW3_M_S2,
													I8259_ICW4_BUF | I8259_ICW4_MS | I8259_ICW4_AEOI | I8259_ICW4_UPM);
	__dv_i8259_init(__dv_i8259_slave, I8259_ICW1_IC4, DV_CFG_BASEIRQ+8, 2,
													I8259_ICW4_BUF | I8259_ICW4_AEOI | I8259_ICW4_UPM);

	return __DV_OK;
}
