/*	x86.h - X86 CPU and board variants
 *
 *	Copyright 2002 David Haworth
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
 *	This file contains definitions for the core, microcontroller and
 *	board variants of x86.
 *
*/

#if !defined(__x86_h)
#define __x86_h

/*	These are the definitions for a standard PC.
 *	We might have to consider splitting this file up like
 *	the Tricore version if the architecture gets complicated.
 *	For now, I've only got an old 486 ISA PC anyway.
 *	FIXME: some of these values are rubbish!
 *	There's a hole in the RAM between 640K and 1024K where
 *	the ROM BIOS, vidoe RAM, etc lives.
 *	Our kernel actually starts at 0x00100000 (1MB).
 *	Whether or not we use the low memory is up to the
 *	application. It's easy to add memory to the system
 *	pool - simply "freemem()" it! Don't forget that the interrupt
 *	vectors occupy the first 2K.
*/
#define RAM_START		0x00000000
#define RAM_SIZE		0x00800000
#define BOOT_MAIN		usrmain
#define BOOT_INIT_CPU	init_cpu

#define TIMER_FREQ		1193180	/*	Hz	*/

#define	I8250_0		0x3f8		/*	"COM1" */
#define I8250_1		0x2f8		/*	"COM2" */

#define I8253		0x40		/*	Counter/timer */

#define I8259_M		0x20		/*	Master interrupt controller */
#define I8259_S		0xa0		/*	Slave interrupt controller on master.2 */

/* Primary interrupt controller:
 *	0 = Timer
 *	1 = Keyboard
 *	2 = Secondary (cascade)
 *	3 = Serial 1 ("COM2")
 *	4 = Serial 0 ("COM1")
 *	5 =
 *	6 =	Floppy
 *	7 = Parallel
 *
 * Secondary interrupt controller:
 *	0 (8) =	RTC
 *	1 (9) =
 *	2 (10) =
 *	3 (11) =
 *	4 (12) =
 *	5 (13) =
 *	6 (14) = IDE0
 *	7 (15) =
 *
 *	The __DAVROS_IMASK_* macros have the primary mask in the
 *	LSB and the secondary in the MSB. All interrupts on the
 *	secondary controller have their primary mask set to IRQ2 (cascade).
*/

#define IRQ(n)	(__DAVROS_BASE_IRQ+n)
#define IMASK(n)	((1<<n)|((n>7)?0x04:0x00))

#define __DAVROS_IMASK_MASTER	0x00ff
#define __DAVROS_IMASK_SLAVE	0xff00

#define	INUM_TIMER	0
#define INUM_KBD	1
#define INUM_TTY0	4
#define INUM_TTY1	3
#define INUM_FD		6
#define INUM_PAR	7
#define INUM_RTC	8
#define INUM_IDE0	14

#define	__DAVROS_INUM_TIMER	IRQ(INUM_TIMER)
#define __DAVROS_INUM_KBD	IRQ(INUM_KBD)
#define __DAVROS_INUM_TTY0	IRQ(INUM_TTY0)
#define __DAVROS_INUM_TTY1	IRQ(INUM_TTY1)
#define __DAVROS_INUM_FD	IRQ(INUM_FD)
#define __DAVROS_INUM_PAR	IRQ(INUM_PAR)
#define __DAVROS_INUM_RTC	IRQ(INUM_RTC)
#define __DAVROS_INUM_IDE0	IRQ(INUM_IDE0)

#define __DAVROS_IMASK_TIMER	IMASK(INUM_TIMER)
#define __DAVROS_IMASK_KBD		IMASK(INUM_KBD)
#define __DAVROS_IMASK_TTY0		IMASK(INUM_TTY0)
#define __DAVROS_IMASK_TTY1		IMASK(INUM_TTY1)
#define __DAVROS_IMASK_FD		IMASK(INUM_FD)
#define __DAVROS_IMASK_PAR		IMASK(INUM_PAR)
#define __DAVROS_IMASK_RTC		IMASK(INUM_RTC)
#define __DAVROS_IMASK_IDE0		IMASK(INUM_IDE0)

/* Other interrupts on plug-in cards are in kernel-config.h */

#endif
