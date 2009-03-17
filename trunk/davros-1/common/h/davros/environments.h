/*	environments.h - list of (potentially) supported environments
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
*/

#ifndef __davros_environments_h
#define __davros_environments_h

#ifdef __DAVROS_IDENT
__DAVROS_IDENT("$Id$")
#endif

/* Masks */
#define HOST_MASK_OS		0x00FF
#define HOST_MASK_SYSTEM	0xFF00

/* Hosts */
#define	HOST_LINUX		0x0001
#define HOST_SOLARIS	0x0002

#define HOST_I86		0x0100
#define HOST_SPARC		0x0200

#define HOST_I486_LINUX	(HOST_I86|HOST_LINUX)

/* Tools */
#define TOOL_GNU		0x0001	/* gcc	*/
#define TOOL_INTROL		0x0002	/* pure Introl-CODE */
#define TOOL_INTROL_X	0x0003	/* Introl + xasm */

#endif
