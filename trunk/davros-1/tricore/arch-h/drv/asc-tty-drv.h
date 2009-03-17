/*	asc-tty-drv.h - ASC tty driver for davros.
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
 *	This file contains definitions for the ASC tty driver
 *
*/

#ifndef __asc_tty_drv_h
#define __asc_tty_drv_h

#include "drv/tty.h"
#include "drv/asc-drv.h"

typedef struct __asc_tty_drv
{	__davros_tty_t tty;	/* tty driver */
	tricore_asc_t *asc;	/* Hardware base address */
	int inum_base;		/* Base interrupt number (3 levels used) */
	int txrun;			/* Transmit interrupts running */
} __asc_tty_drv_t;

#define ASCTTY_INUM_OFFSET_TXD		2
#define ASCTTY_INUM_OFFSET_RXD		1
#define ASCTTY_INUM_OFFSET_ERR		0

/* Create and destroy */
__asc_tty_drv_t *asc_tty_create(char *name, tricore_asc_t *_asc,
									int _inum_base, int pisel);
void asc_tty_delete(__asc_tty_drv_t *dev);

/* Interrupt service routines */
void asc_tty_rx_interrupt(void *_dev);
void asc_tty_tx_interrupt(void *_dev);
void asc_tty_err_interrupt(void *_dev);

/* Control routine */
int asc_tty_control(__davros_tty_t *dev, int func, int param);

#endif
