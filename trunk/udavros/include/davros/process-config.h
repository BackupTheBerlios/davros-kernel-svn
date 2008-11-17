/*	process-config.h - process config data structure
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

#ifndef __dv_process_config_h
#define __dv_process_config_h

#ifdef __DV_IDENT
__DV_IDENT("$Id$")
#endif

#ifndef __DV_ASM

/* The __dv_processconfig_s structure and the __dv_processentry_t type
 * are separated in this file because they are the only data types that it is
 * necessary to expose to a "pure" userland program, and only then if that program
 * wishes to create processes.
*/
typedef int (*__dv_processentry_t)(int, int *);

struct __dv_processconfig_s
{
	char *name;					/* Name of process */
	__dv_processentry_t entry;	/* Entry function */
	int nargs;					/* No. of arguments */
	int *args;					/* Array of nargs arguments */
	int stacksize;				/* Stack size in bytes */
	unsigned options;			/* A set of options for the process */
};

#endif

#endif
