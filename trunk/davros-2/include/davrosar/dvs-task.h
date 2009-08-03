/*	dvs-task.h - Davrosar TASK description
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

#ifndef __dvs_task_h
#define __dvs_task_h

#ifdef __DV_IDENT
__DV_IDENT("$Id$")
#endif

#include <davros/object.h>
#include <davros/process.h>

typedef struct __dvs_taskstate_s __dvs_taskstate_t;
typedef struct __dvs_taskdescr_s __dvs_taskdescr_t;

struct __dvs_taskstate_s
{
	const __dvs_taskdescr_t *descr;			/*	(Constant) descriptor */
	__dv_processstate_t *runner;
	__dvs_taskstate_t state;
	__dvs_taskact_t n_activations;
};

struct __dvs_taskdescr_s
{
	__dvs_taskentry_t function;
	__dvs_stacklen_t stack_len;
	__dvs_taskprio_t queue_prio;
	__dvs_taskprio_t run_prio;
	__dvs_taskact_t max_activations
};

#endif
