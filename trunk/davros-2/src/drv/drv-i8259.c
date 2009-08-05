/*	drv-i8259.c - __dv_enable_interrupt
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
#include <davros/interrupt.h>
#include <drv/i8259-pic.h>
#include <devices/i8259.h>

#ifdef __DV_IDENT
__DV_IDENT("$Id$")
#endif

/*==============================================================================
 *	__dv_i8259_enable - enable the interrupts specified by 1s in the mask
 *==============================================================================
*/
void __dv_i8259_enable(__dv_uint32_t base, __dv_uint8_t mask)
{
	__dv_uint8_t old;

	old = __dv_i8259_read(base, i8259_ocw1);
	__dv_i8259_write(base, i8259_ocw1, (old & ~mask));
}

/*==============================================================================
 *	__dv_i8259_disable - disable the interrupts specified by 1s in the mask
 *==============================================================================
*/
void __dv_i8259_disable(__dv_uint32_t base, __dv_uint8_t mask)
{
	__dv_uint8_t old;

	old = __dv_i8259_read(base, i8259_ocw1);
	__dv_i8259_write(base, i8259_ocw1, (old | mask));
}

/*==============================================================================
 *	__dv_i8259_init - initialise the 8259
 *==============================================================================
*/
void __dv_i8259_init
(	__dv_uint32_t base,		/* PIC base address */
	__dv_uint8_t icw1,		/* Value for ICW1 */
	__dv_uint8_t icw2,		/* Value for ICW2 */
	__dv_uint8_t icw3,		/* Value for ICW3 */
	__dv_uint8_t icw4		/* Value for ICW4 */
)
{
    __dv_i8259_write(base, i8259_icw1, icw1 | I8259_ICW1);
    __dv_i8259_write(base, i8259_icw2, icw2);

    if ( (icw1 & I8259_ICW1_SNGL) == 0 )
	{
        __dv_i8259_write(base, i8259_icw3, icw3);
	}

    if ( (icw1 & I8259_ICW1_IC4) != 0 )
	{
        __dv_i8259_write(base, i8259_icw4, icw4);
	}

	/* Disable all interrupts
	*/
    __dv_i8259_write(base, i8259_ocw1, 0xff);
}
