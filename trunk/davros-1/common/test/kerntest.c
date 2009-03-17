/*	kerntest.c - __unser_init, test_master
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
 *	This file contains the task startup code for the davros test
 *	suite.
*/

#include "davros/kernel-utils.h"
#include "stdio.h"

int test_master(int argc, int *argv);
void test_processes(void);
void test_semaphore(void);
void test_message(void);

/* This runs in context of null process, so cannot block.
 * We therefore spawn a master task
*/
void __user_init(void)
{
	__davros_process_t *p;
	__davros_device_t *t0;

	t0 = __davros_open("/dev/tty/0", 0);

	p = __davros_create
	(	test_master,
		1000,
		10,
		"testmstr",
		t0,
		t0,
		t0,
		0,
		NULL
	);
	__davros_resume(p, 1);
}

/* This is the master test process
*/
int test_master(int argc, int *argv)
{
	printf("\n\n\nTestMaster starting ...\n");
	__davros_sleep(__DAVROS_HZ);

	test_processes();		/* Process creation and deletion */
	test_semaphore();		/* Wait/signal/etc */
	test_message();			/* Send/receive/recvclr */

	__davros_sleep(__DAVROS_HZ);
	printf("The tests have completed. Now please check the results\n");
	__davros_sleep(__DAVROS_HZ);
	return 0;
}
