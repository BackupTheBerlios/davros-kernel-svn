/*	kernel.c - __davros
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
 *	Contains all the kernel data structures. Can also be compiled with the
 *	complete kernel included to ensure all functions available.
*/

#include "davros/kernel.h"

__DAVROS_IDENT("$Id$")

/*==============================================================================
 *	declaration of all system data structures
 *==============================================================================
*/

__davros_data_t __davros;	/*	Easy, isn't it?		*/

/*==============================================================================
 *	include all kernel source files if required.
 *==============================================================================
*/

#ifdef __DAVROS_COMPLETE
#endif
