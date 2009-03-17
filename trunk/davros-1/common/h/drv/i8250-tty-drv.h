/*	i8250-tty-drv.h - i8250 tty driver for davros.
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
 *	This file contains definitions for the i8250 tty driver
 *
*/

#ifndef __i8250_tty_drv_h
#define __i8250_tty_drv_h

#include "drv/tty.h"
#include "drv/i8250-drv.h"

/*	This function must be supplied by the board-specific libraries. */
extern void pic_enable_interrupts(uint16_t mask);

typedef struct __i8250_tty_drv
{	__davros_tty_t tty;	/* tty driver */
	memaddr_t i8250;	/* Hardware base address */
	int inum;			/* Interrupt number */
	int	imask;			/* Interrupt mask */
	int txrun;			/* Transmit interrupts running */
} __i8250_tty_drv_t;

/* Create and destroy */
__i8250_tty_drv_t *i8250_tty_create(char *name, memaddr_t _i8250,
									int _inum, int _imask);
void i8250_tty_delete(__i8250_tty_drv_t *dev);

/* Interrupt service routine */
void i8250_tty_interrupt(void *_dev);

/* Control routine */
int i8250_tty_control(__davros_tty_t *dev, int func, int param);

#endif
