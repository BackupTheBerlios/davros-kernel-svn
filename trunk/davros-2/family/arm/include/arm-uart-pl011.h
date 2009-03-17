/*	arm-uart-pl011.h - header file for Prime Cell UART PL011
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

#ifndef __dv_arm_uart_pl011_h
#define __dv_arm_uart_pl011_h

#ifdef __DV_IDENT
__DV_IDENT("$Id$")
#endif

/* Data structure for the UART's memory-mapped registers
*/
typedef struct arm_uart_s arm_uart_t;

struct arm_uart_s
{
	__dv_reg32_t data;
	__dv_reg32_t status;
	__dv_uint32_t reserved1[4];
	__dv_reg32_t flags;
	__dv_uint32_t reserved2;
	__dv_reg32_t irda_lpcount;
	__dv_reg32_t i_brd;
	__dv_reg32_t f_brd;
	__dv_reg32_t lcr_h;
	__dv_reg32_t control;
	__dv_reg32_t ifls;
	__dv_reg32_t imsc;
	__dv_reg32_t ris;
	__dv_reg32_t mis;
	__dv_reg32_t icr;
	__dv_reg32_t dmacr;
	__dv_uint32_t reserved3[13];
	__dv_uint32_t reserved4[4];
	__dv_uint32_t reserved5[976];
	__dv_uint32_t reserved6[4];
	__dv_unit32_t periph_id[4];
	__dv_unit32_t cell_id[4];
};

/* Data register
*/
#define __DV_PL011_OE	0x800
#define __DV_PL011_BE	0x400
#define __DV_PL011_PE	0x200
#define __DV_PL011_FE	0x100


#endif
