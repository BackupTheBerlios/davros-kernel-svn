/*	processors.h - list of (potentially) supported processors
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

#ifndef __dv_processors_h
#define __dv_processors_h

#ifdef __DV_IDENT
__DV_IDENT("$Id$")
#endif

/* CPU families and CPUs
 *
 * The upper 16 bits of a 32-bit word represent the processor family (e.g. X86, MIPS, Tricore)
 * The lower 16 bits represent the individual processor (e.g. i486, TC1920)
 * "Small" processors use a 16-bit representation, so their upper 16 bits are zero and their
 * lower 16 bits are 8 for family and 8 for individual processor.
 *
 * __DV_FAMILY must be set to one of the __DV_CPUFAMILY_XXX values from this file.
 * __DV_CPU must be set to one of the __DV_CPU_* values from the appropriate family file.
 *
 * The CPU id is never zero.
 *
 * This file defines the CPU family IDs and then includes the family-specific files to define the
 * IDs of the individual members of that family.
*/

/* Some mask values for the fields
*/
#define __DV_CPUFAMILY			0xffff0000
#define __DV_CPUMEMBER			0x0000ffff
#define __DV_CPUFAMILY16		0xff00
#define __DV_CPUMEMBER16		0x00ff

/* The families are defined here so that it is easy to see what is used.
*/
#define	__DV_CPUFAMILY_DUMMY	0x00010000		/* Dummy family for template, documentation etc. */
#define	__DV_CPUFAMILY_X86		0x00020000		/* Intel x86 (32-bit) and compatibles */
#define __DV_CPUFAMILY_MIPS		0x00030000		/* MIPS */
#define __DV_CPUFAMILY_TRICORE	0x00040000		/* Infineon Tricore family */
#define	__DV_CPUFAMILY_ARM		0x00050000		/* ARM */
#define	__DV_CPUFAMILY_PPC		0x00060000		/* PowerPC */
#define	__DV_CPUFAMILY_MSP430	0x0100			/* Texas MSP430 */

#define __DV_BASEFILE	processors
#include <davros/family-select.h>

#endif
