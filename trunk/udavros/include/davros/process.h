/*	process.h - process data structures, types and constants
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

#ifndef __dv_process_h
#define __dv_process_h

#ifdef __DV_IDENT
__DV_IDENT("$Id$")
#endif

#include <davros/basic-types.h>
#include <davros/queue.h>
#include <davros/cpu-process.h>
#include <davros/process-config.h>

#ifndef __DV_ASM

typedef struct __dv_processstate_s __dv_processstate_t;
typedef struct __dv_processconfig_s __dv_processconfig_t;
typedef __dv_uint8_t __dv_pstate_t;
typedef __dv_uint8_t __dv_pprio_t;

struct __dv_processstate_s
{
	__dv_obj_t obj;							/* Object identification - must be first */
	__dv_qent_t	qent;						/* Queue entry */
	const __dv_processconfig_t *config;		/* Process config info */
	__dv_processregisters_t registers;		/* Registers (processor-dependent) */
	__dv_stackelement_t *stack;				/* Base of stack */
	__dv_size_t nalloc;						/* Total number of byes allocated */
	__dv_pstate_t state;					/* Current state of process (suspended, ready, running etc.) */
	__dv_pprio_t prio;						/* Current priority of process */
};

/* Process-management variables
*/
extern __dv_queue_t __dv_readyqueue;
extern __dv_processstate_t *__dv_currproc;
extern __dv_processstate_t *__dv_proctbl[];

/* Prototypes for internal process management functions
*/
void __dv_initproc(void);
__dv_status_t __dv_ready(__dv_processstate_t *);
__dv_processstate_t * __dv_schedule(void);
void __dv_dispatch(__dv_int_t);
void __dv_ctxtsw(__dv_processregisters_t *);
void __dv_initialregisters(__dv_processstate_t *);

/* Prototypes for system-call functions
*/
void __dv_exit(__dv_int_t);
__dv_processstate_t *__dv_create(const __dv_processconfig_t *, __dv_pprio_t prio);
__dv_processstate_t *__dv_spawn(const __dv_processconfig_t *, __dv_pprio_t prio);
__dv_status_t __dv_resume(__dv_processstate_t *);
__dv_status_t __dv_suspend(__dv_processstate_t *);
__dv_status_t __dv_kill(__dv_processstate_t *);
__dv_int_t __dv_chprio(__dv_processstate_t *, __dv_pprio_t);
__dv_processstate_t *__dv_getpid(void);

/* Prototypes for userland stubs
*/
__dv_processstate_t *__dv_usr_create(const __dv_processconfig_t *, __dv_pprio_t prio);
__dv_processstate_t *__dv_usr_spawn(const __dv_processconfig_t *, __dv_pprio_t prio);
__dv_status_t __dv_usr_resume(__dv_processstate_t *);
__dv_status_t __dv_usr_suspend(__dv_processstate_t *);
void __dv_usr_exit(__dv_int_t);
void __dv_usr_kill(__dv_processstate_t *);
#endif

/* Basic values for process state (__dv_pstate_t)
 * Implementation can add to these for other states.
 * Note: 0 and 255 are never used.
*/
#define __DV_PRCURR			1
#define __DV_PRREADY		2
#define __DV_PRSUSP			3
#define __DV_PRFREE			254

/* Offset of registers member in __dv_processstate_t, for assembler files
*/
#define __DV_REGS			(__DV_SIZEOF_OBJ+__DV_SIZEOF_QENT+__DV_SIZEOF_PTR)

/* Check validity of a process pointer
*/
#define __DV_IS_VALID_PROCESS(proc)	__DV_IS_VALID_OBJECT(&proc->obj, __DV_OBJTYPE_PROCESS)

#endif
