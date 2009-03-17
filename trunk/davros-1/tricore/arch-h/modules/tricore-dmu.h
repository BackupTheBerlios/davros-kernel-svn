/*	tricore-dmu.h - Tricore DMU module description
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
 *	This file contains a description of Tricore's data memory unit (DMU)
 *
*/

#if !defined(__tricore_dmu_h)
#define __tricore_dmu_h

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(__ASSEMBLER__)

typedef struct tricore_dmu
{
	tricore_mod_t		dmu_hdr;			/* CLC register not implemented */
	uint32_t			reserved1[1];		/* Reserved */
	volatile uint32_t	dmu_con;			/* DMU Control Register */
	volatile uint32_t	dmu_str;			/* DMU synchronous trap register */
	volatile uint32_t	dmu_atr;			/* DMU asynchronous trap register */
} tricore_dmu_t;

#endif

/*	Absolute addresses of PMU registers. Used mainly in assembler modules. */
#define DMUREG(x)	(DMU_BASE+(x))
#define DMUID		PMUREG(0x08)
#define DMUCON		PMUREG(0x10)
#define DMUSTR		PMUREG(0x18)
#define DMUATR		PMUREG(0x20)

#define DMU_MODULE_ID	0x70

/* Bit definitions for DMUCON */
#define DMUCON_DCAON	0x00000001			/* Data cache enable */

/* Bit definitions for DMUSTR and DMUATR */
#define DMU_TR_CME		0x00000800		/*	Cache management error */
#define DMU_TR_SCE		0x00000020		/*	DMU register store error */
#define DMU_TR_LCE		0x00000010		/*	DMU register load error */
#define DMU_TR_SFE		0x00000008		/*	FPI store error */
#define DMU_TR_LFE		0x00000004		/*	FPI load error */
#define DMU_TR_SRE		0x00000002		/*	Store range error */
#define DMU_TR_LRE		0x00000001		/*	Load range error */

#ifdef __cplusplus
}
#endif

#endif
