/*	drv/tty.h - generic tty driver
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
 *	This file contains definitions for the generic tty driver
 *
*/

#ifndef __tty_h
#define __tty_h

#include "kernel-config.h"
#include "davros/kernel.h"

/* Default configuration parameters */
#ifndef __DAVROS_TTY_IBUFLEN
#define __DAVROS_TTY_IBUFLEN	256
#endif

#ifndef __DAVROS_TTY_OBUFLEN
#define __DAVROS_TTY_OBUFLEN	256
#endif

#ifndef __DAVROS_TTY_EBUFLEN
#define __DAVROS_TTY_EBUFLEN	16
#endif

#ifndef __DAVROS_TTY_SPEED
#define __DAVROS_TTY_SPEED		9600
#endif

#ifndef __DAVROS_TTY_PARAMS
#define __DAVROS_TTY_PARAMS		"8N1"
#endif


/* Other defines */
#define __DAVROS_TTY_EOF	(-1)	/* returned by __davros_tty_cout if buffer empty */

/* Control functions for hwctrl */
#define __DAVROS_TTY_SPEED_CHANGE	1
#define __DAVROS_TTY_PARAM_CHANGE	2
#define __DAVROS_TTY_KICKOUT_CHAR	3

/* Control functions for __davros_tty_ctrl */
#define __DAVROS_TTYCTRL_SPEED		1
#define __DAVROS_TTYCTRL_PARAMS		2

typedef struct __davros_tty
{
	__davros_device_t dev_head;
	int (*hwctrl)(struct __davros_tty *tty, int func, int param);
	char ibuff[__DAVROS_TTY_IBUFLEN];
	char *ihead;
	char *itail;
	__davros_semaphore_t *isem;
	char obuff[__DAVROS_TTY_OBUFLEN];
	char *ohead;
	char *otail;
	__davros_semaphore_t *osem;
	uint32_t ispeed;
	uint32_t ospeed;		/* If 0, same as ispeed (cannot be different) */
	char params[4];			/* 8N1, etc. */
#if defined(__DAVROS_TTY_COOKED)
	char ebuff[__DAVROS_TTY_EBUFLEN];
	char *ehead;
	char *etail;
	uint32_t mode;
	char ierasec;			/* Backspace character */
	char ikillc;			/* Kill line character */
	char xon;				/* XON character */
	char xoff;				/* XOFF character */
#endif
} __davros_tty_t;

#define MODE_IMODE		0x00000003		/* Input mode: raw, cooked, cbreak */
#define MODE_IMODE_RAW		0x00000000
#define MODE_IMODE_COOKED	0x00000001
#define MODE_IMODE_CBREAK	0x00000002
#define MODE_IMODE_SPARE	0x00000003
#define MODE_ECHO		0x00000004		/* Echo incoming characters */
#define MODE_EBACK		0x00000008		/* Echo BS as BS-SPACE-BS */
#define MODE_EVIS		0x00000010		/* Echo control characters as ^x */
#define MODE_ECRLF		0x00000020		/* Echo LF as CR-LF */
#define MODE_ICRLF		0x00000040		/* CR input changes to LF */
#define MODE_IERASE		0x00000080		/* Honour erase character */
#define MODE_IKILL		0x00000100		/* Honour kill character */
#define MODE_OMODE		0x00010000		/* Output mode: raw, cooked */
#define MODE_OMODE_RAW		0x00000000
#define MODE_OMODE_COOKED	0x00010000
#define MODE_OFLOW		0x00020000		/* Honour flow control */
#define MODE_OCRLF		0x00040000		/* Output CR-LF for LF */
#define MODE_OHELD		0x80000000		/* Output currently XOFFed */

void __davros_tty_cin(__davros_tty_t *tty, int c);
int __davros_tty_cout(__davros_tty_t *tty);

int __davros_tty_open(__davros_device_t *,char *,int);
int __davros_tty_close(__davros_device_t *);
int __davros_tty_read(__davros_device_t *,uint8_t *,int);
int __davros_tty_write(__davros_device_t *,uint8_t *,int);
int __davros_tty_getc(__davros_device_t *);
int __davros_tty_putc(__davros_device_t *,int);
int __davros_tty_ctrl(__davros_device_t *,int,int);

__davros_tty_t *__davros_tty_create(__davros_tty_t *tty, char *name);

#endif
