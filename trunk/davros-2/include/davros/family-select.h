/*	family-select.h - includes a selected header file for the CPU family
 *
 * To use:
 *  #define the macro __DV_BASEFILE, then include this file.
 *  This file then includes davros/family/FAMILY/FAMILY-__DV_BASEFILE.h
 *  This file undefines the __DV_BASEFILE macro
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

#ifndef __dv_family_select_h
#define __dv_family_select_h

#ifdef __DV_IDENT
__DV_IDENT("$Id$")
#endif

#include <davros/processors.h>

#define __DV_INCLUDIFY(x)	<x>
#define __DV_FAMILYFILE(__fam__,__fn__)	__DV_INCLUDIFY(__fam__-__fn__.h)

#endif

/* This part must be outside the anti-recursion block because the file selector can be used
 * several times during a single compilation, including a different file every time
*/

#if __DV_FAMILY == __DV_CPUFAMILY_DUMMY
#define __FILE_TO_INCLUDE	__DV_FAMILYFILE(dummy,__DV_BASEFILE)
#elif __DV_FAMILY == __DV_CPUFAMILY_X86
#define __FILE_TO_INCLUDE	__DV_FAMILYFILE(x86,__DV_BASEFILE)
#elif __DV_FAMILY == __DV_CPUFAMILY_MIPS
#define __FILE_TO_INCLUDE	__DV_FAMILYFILE(mips,__DV_BASEFILE)
#elif __DV_FAMILY == __DV_CPUFAMILY_TRICORE
#define __FILE_TO_INCLUDE	__DV_FAMILYFILE(tricore,__DV_BASEFILE)
#elif __DV_FAMILY == __DV_CPUFAMILY_ARM
#define __FILE_TO_INCLUDE	__DV_FAMILYFILE(arm,__DV_BASEFILE)
#elif __DV_FAMILY == __DV_CPUFAMILY_MSP430
#define __FILE_TO_INCLUDE	__DV_FAMILYFILE(msp430,__DV_BASEFILE)
#elif __DV_FAMILY == __DV_CPUFAMILY_PPC
#define __FILE_TO_INCLUDE	__DV_FAMILYFILE(ppc,__DV_BASEFILE)
#else
#error "__DV_FAMILY is not set correctly. Check your makefiles!"
#endif

#include __FILE_TO_INCLUDE

#undef __FILE_TO_INCLUDE
#undef __DV_BASEFILE
