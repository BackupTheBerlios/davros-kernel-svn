/*	semtest.c - test_semaphore
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
 *	Process creation and deletion tests. Part of the Davros test suite.
 *	6 processes are created, all running the testproc function, but
 *	with different parameters so that the function goes to a different
 *	state. lsproc() is called to check the process states. Then the
 *	processes are killed. The memory status is printed before and after
 *	to see if there are any leaks.
 *	After that, the process is created and killed 600 times, and then
 *	created 600 times with a parameter that forces the process to exit.
 *	If process creation or deletion is leaking CSAs (Tricore) this
 *	should reveal the problem.
*/

#include "davros/kernel-utils.h"
#include "stdio.h"

int testsem(int argc, int *argv);


void test_semaphore(void)
{
	__davros_process_t *p;
	__davros_semaphore_t *s;
	volatile int count = 0;
	int params[3];

	printf("Semaphore tests ...\n");
	printf("Free memory:\n");
	__davros_lsmem(NULL);

	s = __davros_screate(42);
	printf("Semaphore created with count = %d\n", __davros_scount(s));
	__davros_sreset(s, 0);
	printf("Semaphore count reset to %d\n", __davros_scount(s));
	__davros_sleep(__DAVROS_HZ);
	printf("Free memory:\n");
	__davros_lsmem(NULL);


	params[0] = (int)s;
	params[1] = (int)&count;

	p = __davros_create
		(	testsem,
			1000,
			__davros_getpid()->priority+1,
			"SemTest",
			__davros_getstdin(),
			__davros_getstdin(),
			__davros_getstdin(),
			2,
			params
		);
	__davros_resume(p, 1);

/* testsem should now be waiting (1st call), count should be 1,
 * sem.count should be -1
*/
	printf("Count = %d, scount(s) = %d\n", count, __davros_scount(s));
	printf("Process table:\n");
	__davros_lsproc(NULL);
	printf("Free memory:\n");
	__davros_lsmem(NULL);


	printf("Signalling semaphore ...\n");
	__davros_signal(s, 1);

/* testsem should now be in 2nd wait(), count should be 2 */
	printf("Count = %d, scount(s) = %d\n", count, __davros_scount(s));
	printf("Process table:\n");
	__davros_lsproc(NULL);
	printf("Free memory:\n");
	__davros_lsmem(NULL);


	printf("Deleting semaphore ...\n");
	__davros_sdelete(s);

/* testsem should have exited, count should be 3 */
	printf("Count = %d, scount(s) = %d\n", count, __davros_scount(s));
	printf("Process table:\n");
	__davros_lsproc(NULL);

	printf("Free memory:\n");
	__davros_lsmem(NULL);

	return;
}

int testsem(int argc, int *argv)
{
	volatile int *count;
	__davros_semaphore_t *s;

	if ( argc != 2 )
	{	printf("testsem: arguments wrong, exiting\n");
		return 0;
	}

	s = (__davros_semaphore_t *)argv[0];
	count = (int *)argv[1];

	(*count)++;

	__davros_wait(s);

	(*count)++;

	__davros_wait(s);

	(*count)++;

	return 0;
}
