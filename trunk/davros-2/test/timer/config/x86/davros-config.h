/* davros-config.h - configuration for synchronous tests (x86)
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

#ifndef __davros_config_h
#define __davros_config_h

#ifdef __DV_IDENT
__DV_IDENT("$Id$")
#endif

/* Specific configuration. See config.h for descriptions
*/
#define DV_CFG_CPUFAMILY		__DV_CPUFAMILY_X86
#define DV_CFG_CPU				__DV_X86_X86
#define DV_CFG_EXTRASTACK		16
#define DV_CFG_STACK_SPARE		4
#define DV_CFG_BASEIRQ			32

#define DV_CFG_HEAPBASE			test_heap
#define DV_CFG_HEAPSIZE			8192

#define DV_CFG_USERPROCESS		"test", test_func, 0, __DV_NULL, 512, 0

/* Declarations for the startup function
 * No need for assembler protection - it's implicit in the file!
*/
#ifdef DV_FILE_STARTUP
extern unsigned char DV_CFG_HEAPBASE[DV_CFG_HEAPSIZE];
int test_func(int, int*);
#endif

#endif
