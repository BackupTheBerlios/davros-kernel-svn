/*	davros.h - the Davros API
 *
 *  This file is the only file that needs to be included by "userland" code to get access
 *	to the davros API. None of the kernel's internals are exposed here; everything
 *	defined is in the form of a "magic cookie". To get access to internals you
 *	need to include specific davros/XXX.h files for the internals that you want to access.
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
#ifndef __davros_h
#define __davros_h

#ifdef __DV_IDENT
__DV_IDENT("$Id$")
#endif

#include <davros/process-config.h>

typedef struct __dv_processstate_s *dv_proc_t;
typedef struct __dv_processconfig_s dv_process_t;

dv_proc_t DvCreate(const dv_process_t *, int);
dv_proc_t DvSpawn(const dv_process_t *, int);
int DvResume(dv_proc_t);
int DvSuspend(dv_proc_t);
int DvChprio(dv_proc_t, int);
dv_proc_t DvGetpid(void);
void DvExit(int);
void DvKill(dv_proc_t);

#endif
