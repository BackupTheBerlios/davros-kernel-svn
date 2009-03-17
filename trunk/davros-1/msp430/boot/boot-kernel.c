/*	boot-kernel.c - boot a system running the Davros kernel
 *
 *	$Id$
 *	Copyright 2004 David Haworth
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
 *	This file contains the code that initialises the processor and the
 *	rest of the basic hardware before jumping to the main davros
 *	function.
 *
 *	$Log: boot-kernel.c,v $
 *	Revision 1.1  2004/05/11 20:48:21  dave
 *	New file for msp430 port.
 *	
*/

#include "kernel-config.h"
#include "msp430.h"
#include "boot-sys.h"
#include "davros/kernel.h"
#include "msp430-core.h"
#include "drv/timer-a-drv.h"
#include <ctype.h>
#define __STDIO_PRIVATE
#include <stdio.h>

/*
 *	main() - start the kernel
 *
 *  This function is called from the startup code. It initialises the
 *	serial port for kernel debug messages and then starts the
 *	kernel program.
 *
*/
int main(void)
{
#if 0
	/* Initialise serial port */

	kprintf("davros version 0.1, copyright 2001 David Haworth\n");
	kprintf("davros comes with ABSOLUTELY NO WARRANTY. It is free software,\n");
	kprintf("and you are welcome to redistribute it under certain conditions.\n");
	kprintf("Please read the file COPYING for details.\n");
#endif

	__davros_init((memaddr_t)&__bss_end, (RAM_START+RAM_SIZE));
	/* Never returns */
	return 0;
}

/*
 *	__arch_init() - start the drivers, etc.
 *
*/
void __arch_init(void)
{
	/* Clear any pending clock failure interrupt & disable watchdog
	 * FIXME: how does the interrupt get enabled?
	*/
	*(unsigned char *)2 &= ~2;
/*
	*(unsigned short *)0x120 = 0x5a86;
*/

	/* Stop all devices */
	timer_a_stop();

	enable_interrupts();
	timer_a_start();
}

/* kputc function for kprintf */
int kputc(int c, void *stream)
{
#if 0
	if ( c == '\n' )
		asc_polled_putc(ASC0, '\r');
	asc_polled_putc(ASC0, c);
#endif
	return(c);
}

/* kmode function for kprintf
*/
int kmode(int m)
{
	if ( m == KPOLLED )
		return(disable_interrupts());
	else
		return(restore_interrupts(m));
}

/* FIXME: temp */
int fputc(int c, void *stream)
{
	if ( c == '\n' )
		__davros_putc((__davros_device_t *)stream, '\r');
	__davros_putc((__davros_device_t *)stream, c);
	return(c);
}
