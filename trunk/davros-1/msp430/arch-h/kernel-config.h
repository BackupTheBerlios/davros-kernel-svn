/*	kernel-config.h - Kernel configuration file
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
 *	Kernel configuration should be edited locally to define
 *	exactly what goes in to the kernel.
 *
 *	$Log: kernel-config.h,v $
 *	Revision 1.1  2004/05/11 20:45:56  dave
 *	Files for new msp430 port.
 *	
*/

#if !defined(__kernel_config_h)
#define __kernel_config_h

/*
 *	Interrupt configuration.
 *
 *	__DAVROS_HZ
 *		defines the frequency of the regular timer interrupt
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
*/

#define __DAVROS_HZ			100
#define __DAVROS_FILLSTACK	1		/* Fill new process' stack with 0xee */

#define __DAVROS_NULLSTACK	100


#define __DAVROS_ACLK_HZ	32768

#define __DAVROS_HAVE_ISR_12	1		/* The x149 timerA0 interrupt */

/* tty configuration */
#undef __DAVROS_TTY_COOKED			/* Raw mode only. Cooked mode not working */
#undef __DAVROS_TTY_IBUFLEN			/* Use default */
#undef __DAVROS_TTY_OBUFLEN			/* Use default */
#undef __DAVROS_TTY_EBUFLEN			/* Use default */
#undef __DAVROS_TTY_SPEED			/* Use default */
#undef __DAVROS_TTY_PARAMS			/* Use default */

#endif
