/*	syscall.h - davros system calls
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

#ifndef __dv_syscall_h
#define __dv_syscall_h

#ifdef __DV_IDENT
__DV_IDENT("$Id$")
#endif

#include <davros/basic-types.h>

#define __DV_N_SYSCALLS		16

/* System-call indexes
*/
#define __DV_SC_UNKNOWN		0
#define __DV_SC_EXIT		1
#define __DV_SC_KILL		2
#define __DV_SC_CREATE		3
#define __DV_SC_SPAWN		4
#define __DV_SC_RESUME		5
#define __DV_SC_SUSPEND		6
#define __DV_SC_CHPRIO		7
#define __DV_SC_GETPID		8
#define __DV_SC_SLEEP		9

/* System-call table.
 * This macro provides the system-call table in syscall.c
 * The index of a function must match the system call index above.
 * The table must be __DV_N_SYSCALLS entries long.
 * Unused entries are __dv_unknowncall.
*/
#define __DV_SYSCALL_TABLE \
	(void *)__dv_unknowncall,		\
	(void *)__dv_exit,				\
	(void *)__dv_kill,				\
	(void *)__dv_create,			\
	(void *)__dv_unknowncall,		\
	(void *)__dv_resume,			\
	(void *)__dv_suspend,			\
	(void *)__dv_chprio,			\
	(void *)__dv_getpid,			\
	(void *)__dv_sleep,				\
	(void *)__dv_unknowncall,		\
	(void *)__dv_unknowncall,		\
	(void *)__dv_unknowncall,		\
	(void *)__dv_unknowncall,		\
	(void *)__dv_unknowncall,		\
	(void *)__dv_unknowncall

#ifndef __DV_ASM
extern const void *__dv_syscall_table[__DV_N_SYSCALLS];

__dv_status_t __dv_unknowncall(void);
__dv_status_t __dv_usr_unknown(void);
#endif

#endif
