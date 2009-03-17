/*	tricore-pmu.h - Tricore PMU module description
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
 *	This file contains a description of Tricore's program memory unit (PMU)
 *
*/

#if !defined(__tricore_pmu_h)
#define __tricore_pmu_h

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(__ASSEMBLER__)

typedef struct tricore_pmu
{
	tricore_mod_t		pmu_hdr;			/* CLC register not implemented */
	uint32_t			reserved1[1];		/* Reserved */
	volatile uint32_t	pmu_con0;			/* PMU Control Register 0 */
	volatile uint32_t	pmu_con1;			/* PMU Control Register 1 */
} tricore_pmu_t;

#endif

/*	Absolute addresses of PMU registers. Used mainly in assembler modules. */
#define PMUREG(x)	(PMU_BASE+(x))
#define PMUID		PMUREG(0x08)
#define PMUCON0		PMUREG(0x10)
#define PMUCON1		PMUREG(0x14)

#define PMU_MODULE_ID	0x71

/* Bit definitions for pmucon0 */
#define PMUCON0_CMEMEN		0x00000004		/*	Enabled code SRAM (CSRAM) */
#define PMUCON0_CCBYP		0x00000002		/*	Code cache bypass (0=instr. cache enable) */
#define PMUCON0_CCSIZ		0x00000001		/*	Code cache size */
#define PMUCON0_CCSIZ_8		0x00000000		/*	8Kbyte cache size */
#define PMUCON0_CCSIZ_16	0x00000001		/*	16Kbyte cache size */

/* Bit definitions for pmucon1 */
#define PMUCON1_CCINV	0x00000001			/* Code cache invalidate */

#ifdef __cplusplus
}
#endif

#endif
