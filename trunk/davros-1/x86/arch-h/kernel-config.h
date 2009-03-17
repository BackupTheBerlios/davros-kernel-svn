/*	kernel-config.h - Kernel configuration file
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
*/

#if !defined(__kernel_config_h)
#define __kernel_config_h

/*
 *	Interrupt configuration.
 *
 *	__DAVROS_NVECTORS
 *		defines how many interrupt vectors to reserve. Leave this at
 *		the default 224 unless you're really short of RAM.
 *		This number is in addition to the 32 reserved vectors.
 *	__DAVROS_NHANDLERS
 *		defines how many interrupt stubs you want. This might be
 *		fewer than NVECTORS if not all vectors are used.
 *	__DAVROS_INTPRIO
 *		defines what CPU priority the interrupt handlers should run
 *		at. Leave this at the default of 255 unless you want to run
 *		some special interrupts outside the kernel.
 *	__DAVROS_HZ
 *		defines the frequency of the regular timer interrupt
 *	__DAVROS_INUM_ASC0
 *	__DAVROS_INUM_ASC1
 *		define the base interrupt number for ASC0 and ASC1. Each ASC
 *		occupies 3 consecutive interrupt vectors starting at the
 *		defined number.
 *	__DAVROS_INUM_TIMER
 *		defines the interrupt number for the timer interrupt.
 *	__DAVROS_TTY_COOKED
 *		defines whether the tty driver supports "cooked" mode.
 *		Leave undefined - cooked mode isn't fully implemented yet.
 *	__DAVROS_TTY_IBUFLEN
 *		defines the tty input buffer length. Leave undefined to
 *		use the default value (see tty.h).
 *	__DAVROS_TTY_OBUFLEN
 *		defines the tty output buffer length. Leave undefined to
 *		use the default value (see tty.h).
 *	__DAVROS_TTY_EBUFLEN
 *		defines the tty echo buffer length. Leave undefined to
 *		use the default value (see tty.h). Only meaningful if
 *		"cooked" mode is enabled.
 *	__DAVROS_TTY_SPEED
 *		defines the default baud rate for tty devices. Leave undefined
 *		to use the default (see tty.h).
 *	__DAVROS_TTY_PARAMS
 *		defines the default line parameters for tty devices. A string,
 *		one of 8N1, 8N2, 7E1, 7E2, 7O1, 7O2, etc. Leave undefined 
 *		to use the default (see tty.h). Permitted values can 
 *		be found in ... where?
 *	__DAVROS_BASE_IRQ
 *		Base interrupt vector. PC uses 16 vectors starting here
*/

#define __DAVROS_NVECTORS	224
#define __DAVROS_NHANDLERS	32
#define __DAVROS_BASE_IRQ	32
#define __DAVROS_HZ			100

/*	Interrupt numbers */
/*	These are fixed by ISA architecture, so they're in x86.h */

/* tty configuration */
#undef __DAVROS_TTY_COOKED			/* Raw mode only. Cooked mode not working */
#undef __DAVROS_TTY_IBUFLEN			/* Use default */
#undef __DAVROS_TTY_OBUFLEN			/* Use default */
#undef __DAVROS_TTY_EBUFLEN			/* Use default */
#undef __DAVROS_TTY_SPEED			/* Use default */
#undef __DAVROS_TTY_PARAMS			/* Use default */

#endif
