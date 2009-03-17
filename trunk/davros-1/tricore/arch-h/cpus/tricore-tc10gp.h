/*	tricore-tc10gp.h - Address map for Tricore TC10GP
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
 *	This file contains the addresses of the modules and internal memory
 *	in tricore TC10GP
 *
*/

#if !defined(__tricore_tc10gp_h)
#define __tricore_tc10gp_h

#ifdef __cplusplus
extern "C" {
#endif

#include "arch-cpudef.h"


/*	Internal memory.
 *
 *	The DSRAM (data scratchpad RAM) can be used for data and or contexts.
 *	It can also be used for the data cache, but on the fibbed chips this
 *	doesn't work.
 *
 *	The CSRAM (code scratchpad RAM) can be used for code execution.
 *	It can also be used for the instruction cache, but on the fibbed
 *	chips this doesn't work.
 *	Presumably it has the same byte write limitations as the CRAM (see
 *	below).
 *
 *	The CRAM (code RAM) can be used for program execution, but because
 *	byte writes are forbidden cannot be used for data. This limits the
 *	possibilities somewhat. This RAM is rumoured to be non-functional
 *	on some of the fibbed chips.
*/
#define DSRAM_START		0xD0000000	/* 32K internal data RAM */
#define DSRAM_SIZE		0x8000
#define CSRAM_START		0x88000000	/* 8K internal code RAM */
#define CSRAM_SIZE		0x2000
#define CRAM_START		0x80000000	/* 192K internal code RAM */
#define CRAM_SIZE		0x30000

/*	CPS module is located at 0xfffeff00.
*/
#define CPS_BASE	0xfffeff00
#define CPS			((tricore_cps_t *)CPS_BASE)

/*	PWR module is located at 0xf0000000.
*/
#define PWR_BASE	0xf0000000
#define PWR			((tricore_pwr_t *)PWR_BASE)

/*	BCU is located at 0xf0000200.
*/
#define BCU_BASE	0xf0000200
#define BCU			((tricore_bcu_t *)BCU_BASE)

/*	PMU is located at 0xc7ffff00.
*/
#define PMU_BASE	0xc7ffff00
#define PMU			((tricore_pmu_t *)PMU_BASE)

/*	DMU is located at 0xd7ffff00.
*/
#define DMU_BASE	0xd7ffff00
#define DMU			((tricore_dmu_t *)DMU_BASE)

/*	EBU is located at 0xf0000500.
*/
#define EBU_BASE	0xf0000500
#define EBU			((tricore_ebu_t *)EBU_BASE)

/*	TC10GP has 2 GPTU modules. These macros give pointers to them.
*/
#define GPTU_BASE	0xf0000600
#define GPTU(n)		((tricore_gptu_t *)(((char *)GPTU_BASE) + ((n)*0x100)))
#define GPTU0		GPTU(0)
#define GPTU1		GPTU(1)

/*	TC10GP has 2 serial ports. These macros give pointers to them.
*/
#define ASC_BASE	0xf0000800
#define ASC(n)		((tricore_asc_t *)(((char *)ASC_BASE) + ((n)*0x100)))
#define ASC0		ASC(0)
#define ASC1		ASC(1)

/*	TC10GP has 3 general-purpose I/O ports.
*/
#define TRICORE_NGPIO	3
#define TRICORE_GPIO_DESCR \
{   { (tricore_gpio_t *)0xf0002800, 8, GPIO_HAS_IO|GPIO_HAS_OD|GPIO_HAS_PUD|GPIO_HAS_AS2 },	\
    { (tricore_gpio_t *)0xf0002900, 8, GPIO_HAS_IO|GPIO_HAS_OD|GPIO_HAS_PUD|GPIO_HAS_AS2 },	\
    { (tricore_gpio_t *)0xf0002a00, 8, GPIO_HAS_IO|GPIO_HAS_OD|GPIO_HAS_PUD|GPIO_HAS_AS2 },	\
}

#ifdef __cplusplus
}
#endif

#endif
