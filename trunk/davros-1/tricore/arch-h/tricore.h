/*	tricore.h - Tricore CPU and board variants
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
 *	This file contains definitions for the core, microcontroller and
 *	board variants of tricore.
 *
*/

#if !defined(__tricore_h)
#define __tricore_h

/* Tricore cores. TRICORE_CORE should be one of these.
 * Different cores usually need different compiler switches and
 * therefore different builds.
*/
#define CORE_A		1	/* Rider A */
#define CORE_TC10	2	/* Rider B (TC10, TC101) */
#define CORE_TC113A	3	/* TC113 (Rider D) A-step */
#define CORE_TC113B	4	/* TC113 B-step */

/* Tricore microcontroller parts. TRICORE_CPU should be one of these.
*/
#define TC_A		1	/* Rider A prototype */
#define TC10GP_FIB	2	/* "Fibbed" TC10GP (cache not working) */
#define TC10GP		3	/* Full-spec TC10GP */
#define PXD4260		4	/* Harrier */
#define TC_D		5	/* Rider D prototype */
#define TC1920A		6	/* Lory+ A-step */

/* Tricore boards. TRICORE_BOARD should be one of these.
*/
#define BOARD_RA	1	/* Rider A development board */
#define TRIBOARD	2	/* Triboard */
#define EASY4260	3	/* Harrier */
#define METEOR		4	/* Meteor TSBC */

/* Combinations encountered in the wild:
 *	BOARD_RA		TC_A		CORE_A
 *	TRIBOARD		TC10GP_FIB	CORE_TC10
 *	TRIBOARD		TC10GP		CORE_TC10
 *	METEOR			TC10GP		CORE_TC10
 *	EASY4260		PXD4260		CORE_TC10
 *	METEOR			TC_D		CORE_TC113A
 *	TRIBOARD		TC_D		CORE_TC113A
 *	TRIBOARD		TC1920		CORE_TC113A
*/

#if (TRICORE_BOARD == BOARD_RA)
	#include "boards/rider-a.h"
#elif (TRICORE_BOARD == TRIBOARD)
	#if (TRICORE_CPU == TC10GP_FIB)
		#include "boards/triboard-tc10gp-fib.h"
	#elif (TRICORE_CPU == TC10GP)
		#include "boards/triboard-tc10gp.h"
	#elif (TRICORE_CPU == TC_D)
		#include "boards/triboard-rider-d.h"
	#elif (TRICORE_CPU == TC1920A)
		#include "boards/triboard-tc1920a.h"
	#else
		#error "Unknown/unsupported CPU for Triboard"
	#endif
#elif (TRICORE_BOARD == EASY4260)
	#include "boards/triboard-easy4260.h"
#elif (TRICORE_BOARD == METEOR)
	#if (TRICORE_CPU == TC10GP)
		#include "boards/meteor-tc10gp.h"
	#elif (TRICORE_CPU == TC_D)
		#include "boards/meteor-rider-d.h"
	#else
		#error "Unknown/unsupported CPU for Meteor TSBC"
	#endif
#else
	#error "TRICORE_BOARD undefined or unknown"
#endif

#endif
