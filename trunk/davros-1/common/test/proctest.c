/*	proctest.c - test_processes, testproc
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

int testproc(int argc, int *argv);

char *names[] =
{ "Pooh", "Piglet", "Eeyore", "Tigger", "Owl", "Rabbit" };

void test_processes(void)
{
	__davros_process_t *p[6];
	__davros_device_t *t1;
	int i, j, ps;

	printf("Process tests starting ...\n");

	ps = __arch_disableinterrupts();
	__arch_restoreinterrupts(ps);
	printf("Interrupt status (CPU specific) = 0x%08x\n", ps); 

	t1 = __davros_open("/dev/tty/1", 0);

	printf("Free memory:\n");
	__davros_lsmem(NULL);

	for ( i = 0; i < 6; i++ )
	{
		printf("Creating process %s\n", names[i]);
		p[i] = __davros_create
				(	testproc,
					1000,
					10,
					names[i],
					__davros_getstdin(),
					__davros_getstdin(),
					t1,
					1,
					&i
				);
		__davros_resume(p[i], 1);
	}

	printf("All processes started. Please wait.\n");
	__davros_sleep(__DAVROS_HZ);
	printf("Free memory:\n");
	__davros_lsmem(NULL);
	printf("Process table:\n");
	__davros_lsproc(NULL);

	printf("Killing all processes:\n");
	for ( i=0; i<6; i++ )
	{
		printf("%s\n", p[i]->name);
		__davros_kill(p[i]);
		__davros_sleep(__DAVROS_HZ);
		printf("Free memory:\n");
		__davros_lsmem(NULL);
	}
	__davros_sleep(__DAVROS_HZ);

	printf("Creating and killing 600 processes\n");
	j = 1;
	for ( i=0; i<600; i++ )
	{
		p[0] = __davros_create
				(	testproc,
					1000,
					__davros_getpid()->priority+1,
					names[0],
					__davros_getstdin(),
					__davros_getstdin(),
					t1,
					1,
					&j
				);
		__davros_resume(p[0], 1);
		__davros_kill(p[0]);
	}

	printf("Creating 600 processes that die naturally\n");
	j = 10;
	for ( i=0; i<600; i++ )
	{
		p[0] = __davros_create
				(	testproc,
					1000,
					__davros_getpid()->priority+1,
					names[0],
					__davros_getstdin(),
					__davros_getstdin(),
					t1,
					1,
					&j
				);
		__davros_resume(p[0], 1);
	}
	
	return;
}

int testproc(int argc, int *argv)
{
	if ( argc != 1 )
	{	printf("testproc: no argument, exiting\n");
		return 0;
	}

	switch ( *argv )
	{
	case 0:
		__davros_suspend(__davros_getpid());
		break;
	case 1:
		__davros_receive();
		break;
	case 2:
		for (;;)
			__davros_getc(stderr);
		break;
	case 3:
		for (;;)
			__davros_sleep(__DAVROS_HZ);
		break;
	case 4:
		for (;;)
			__davros_sleep(1);
		break;
	case 5:
		__davros_suspend(__davros_getpid());
		break;
	case 10:
		/* Die naturally */
		break;
	default:
		printf("testproc: unknown argument, exiting\n");
		break;
	}
	return 0;
}
