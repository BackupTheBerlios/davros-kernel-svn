/*	tricore-mmu.h - Tricore MMU description
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
 *	This file contains a description of the MMU used on Tricore.
 *
*/

#if !defined(__tricore_mmu_h)
#define (__tricore_mmu_h)

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(__ASSEMBLER__)

typedef struct tricore_mmu
{
	volatile uint32_t mmu_con;		/* Configuration register */
	volatile uint32_t mmu_asi;		/* Address space identifier register */
	volatile uint32_t mmu_id;		/* Identification register */
	volatile uint32_t mmu_tva;		/* Translation virtual address register */
	volatile uint32_t mmu_tpa;		/* Translation physical address register */
	volatile uint32_t mmu_tpx;		/* Translation page index register */
	volatile uint32_t mmu_tfa;		/* Translation fault address register */
} tricore_mmu_t;

#endif

/*	CSFR offsets for Tricore Rider D MMU. These offsets can be used
 *	with the mtcr/mfcr instructions, or can be added to the CSFR base
 *	address to get the absolute address for accesses via the bus.
*/

#define MMU_CON		0x8000		/* Configuration register */
#define MMU_ASI		0x8004		/* Address space identifier register */
#define MMU_ID		0x8008		/* Identification register */
#define MMU_TVA		0x800c		/* Translation virtual address register */
#define MMU_TPA		0x8010		/* Translation physical address register */
#define MMU_TPX		0x8014		/* Translation page index register */
#define MMU_TFA		0x8018		/* Translation fault address register */

#ifdef __cplusplus
}
#endif

#endif
