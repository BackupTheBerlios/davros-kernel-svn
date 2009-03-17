/*	tricore-stm.h - Tricore system timer module description
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
 *	This file contains a description of Tricore's 56-bit system timer
 *	module (STM).
*/

#if !defined(__tricore_cps_h)
#define (__tricore_cps_h)

#ifdef __cplusplus
extern "C" {
#endif

#include "modules/tricore-mod.h"

#if !defined(__ASSEMBLER__)

/* Tricore 56-bit system timer, running at the system frequency.
   Reading tim0 latches bits 55..32 into the cap register, so that
   the whole 56-bit register can be read in two operations without
   rollover effects.
*/
typedef struct tricore_stm
    {
    tricore_mod_t stm_hdr;
    uint32_t reserved;
    volatile uint32_t stm_tim0;		/* bits 31..0 */
    volatile uint32_t stm_tim1;		/* bits 35..4 */
    volatile uint32_t stm_tim2;		/* bits 39..8 */
    volatile uint32_t stm_tim3;		/* bits 43..12 */
    volatile uint32_t stm_tim4;		/* bits 47..16 */
    volatile uint32_t stm_tim5;		/* bits 51..20 */
    volatile uint32_t stm_tim6;		/* bits 55..32 (!!!) */
    volatile uint32_t stm_cap;		/* capture register for bits 55..32 */
} tricore_stm_t;

#endif

#define STM_MODULE_IDENT	0

#ifdef __cplusplus
}
#endif

#endif
