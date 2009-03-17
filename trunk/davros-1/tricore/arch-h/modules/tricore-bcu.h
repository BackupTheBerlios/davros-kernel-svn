/*	tricore-bcu.h - Tricore BCU module description
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
 *	This file contains a description of Tricore's bus control unit (BCU)
 *
*/

#if !defined(__tricore_bcu_h)
#define __tricore_bcu_h

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(__ASSEMBLER__)

typedef struct tricore_bcu
{
	uint32_t			reserved1[4];
	volatile uint32_t	bcu_bcucon;			/* BCU control */
	volatile uint32_t	bcu_id;				/* Module identification register */
	uint32_t			reserved2[2];
	volatile uint32_t	bcu_econ;			/* Error control capture register */
	volatile uint32_t	bcu_eadd;			/* Error address capture register */
	uint32_t			reserved3[23];
	volatile uint32_t	bcu_edat;			/* Error data capture register */
	uint32_t			reserved4[29];
	tricore_isr_t		bcu_src;			/* Service request node */
} tricore_bcu_t;

#endif

/*	Absolute addresses of BCU registers. Used mainly in assembler modules. */
#define BCUREG(x)	(BCU_BASE+(x))
#define BCUCON		BCUREG(0x10)
#define BCUID		BCUREG(0x14)
#define BCUECON		BCUREG(0x20)
#define BCUEADD		BCUREG(0x24)
#define BCUEDAT		BCUREG(0x84)
#define BCUSRC		BCUREG(0xfc)

#ifdef __cplusplus
}
#endif

#endif
