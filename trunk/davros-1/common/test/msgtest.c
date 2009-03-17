/*	msgtest.c - test_message, testmsg
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

int testmsg(int argc, int *argv);

void test_message(void)
{
	__davros_process_t *p;
	__davros_status_t r1, r2;

	printf("Message tests ...\n");
	printf("Free memory:\n");
	__davros_lsmem(NULL);

	p = __davros_create
		(	testmsg,
			1000,
			__davros_getpid()->priority+1,
			"MsgTest",
			__davros_getstdin(),
			__davros_getstdin(),
			__davros_getstdin(),
			0,
			NULL
		);
	__davros_resume(p, 1);
	__davros_sleep(5 * __DAVROS_HZ);

/* testmsg should now be receiving (1st call),
 * It should have attempted to receive with recvclr() first.
*/
	printf("Process table:\n");
	__davros_lsproc(NULL);
	printf("Free memory:\n");
	__davros_lsmem(NULL);

	__davros_send(p, 666, 1);
/* testmsg should have received 666, and should now be sleeping */
	__davros_sleep(1 * __DAVROS_HZ);
	printf("Process table:\n");
	__davros_lsproc(NULL);

	r1 = __davros_send(p, 123, 1);
	r2 = __davros_send(p, 456, 1);
	printf("send(123) returned %d, send(456) returned %d\n", r1, r2);

	__davros_sleep(6 * __DAVROS_HZ);
/* testmsg should have received 123 and be sleeping */
	printf("Process table:\n");
	__davros_lsproc(NULL);

	__davros_send(p, 789, 1);
	__davros_sleep(10 * __DAVROS_HZ);
/* testmsg should have received 789 and terminated */

	printf("Process table:\n");
	__davros_lsproc(NULL);
	printf("Free memory:\n");
	__davros_lsmem(NULL);

	return;
}

int testmsg(int argc, int *argv)
{
	int msg;
	printf("testsmg() calling recvclr()\n");
	msg = __davros_recvclr();
	printf("recvclr() returned %d\n", msg);
	printf("calling receive()\n");
	msg = __davros_receive();
	printf("receive() returned %d\n", msg);
	__davros_sleep(5 * __DAVROS_HZ);
	printf("calling recvclr()\n");
	msg = __davros_recvclr();
	printf("recvclr() returned %d\n", msg);
	__davros_sleep(5 * __DAVROS_HZ);
	printf("calling receive()\n");
	msg = __davros_receive();
	printf("receive() returned %d\n", msg);
	return 0;
}
