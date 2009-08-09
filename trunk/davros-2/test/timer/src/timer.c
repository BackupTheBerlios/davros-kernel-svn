/*	synchonous.c - Davros test : synchronous
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
#include <davros/config.h>
#include <davros.h>

#ifdef __DV_IDENT
__DV_IDENT("$Id$")
#endif

unsigned char DV_CFG_HEAPBASE[DV_CFG_HEAPSIZE];

volatile unsigned test_counter;

/*==============================================================================
 *	test_func - entry function for test processes
 *==============================================================================
*/
int test_func(int nargs, int *args)
{
	for (;;)
	{
		test_counter++;

		DvSleep(5000000);
	}

	return 0;
}

#include <davros/syscall.h>
#include <davros/init.h>

typedef unsigned (*foo_t)(void);

unsigned scdisp(unsigned idx)
{
	foo_t func = (foo_t)__dv_unknowncall;
	unsigned retval;
	__dv_uint8_t old_in_kernel;

	old_in_kernel = __dv_in_kernel;
	__dv_in_kernel = 1;

	if ( idx < __DV_N_SYSCALLS )
	{
		func = (foo_t)__dv_syscall_table[idx];
	}

	retval = (*func)();

	__dv_in_kernel = old_in_kernel;
	return retval;
}
