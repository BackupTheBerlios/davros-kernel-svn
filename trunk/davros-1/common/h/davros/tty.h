/*	tty.h - Generic Davros tty driver
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
*/

#ifndef __davros_tty_h
#define __davros_tty_h

#include "davros/defines.h"

__DAVROS_IDENT("$Id$")

#include "arch-cpudef.h"

/* Flags */
#define __TTY_IMODE			0x0003
#define		__TTY_IM_RAW	0x0001
#define		__TTY_IM_COOKED	0x0002
#define		__TTY_IM_CBREAK	0x0003
#define	 __TTY_OMODE		0x0004
#define		__TTY_OM_RAW	0x0000
#define		__TTY_OM_COOKED	0x0004
#define __TTY_IECHO			0x0008
#define __TTY_IEBACK		0x0010
#define __TTY_EVIS			0x0020
#define __TTY_ECRLF			0x0040
#define __TTY_ICRLF			0x0080
#define __TTY_IERASE		0x0100
#define __TTY_IKILL			0x0200
#define __TTY_OFLOW			0x0400
#define __TTY_OCRLF			0x0800

#define __TTY_ERASEC		0
#define __TTY_KILLC			1
#define __TTY_XONC			2
#define __TTY_XOFFC			3
#define __TTY_FULLC			4
#define __TTY_NCC			5

#define __TTY_IBUFLEN		32
#define __TTY_OBUFLEN		32
#define __TTY_EBUFLEN		8

#define __TTY_RXSPEED		0x0F
#define __TTY_TXSPEED		0xF0

#define __TTY_300			0x1
#define __TTY_600			0x2
#define __TTY_1200			0x3
#define __TTY_2400			0x4
#define __TTY_4800			0x5
#define __TTY_9600			0x6
#define __TTY_19200			0x7
#define __TTY_38400			0x8
#define __TTY_57600			0x9
#define __TTY_76800			0xA
#define __TTY_115200		0xB
#define __TTY_EXTERN		0xF

/*	Special function codes for control function */
#define __TTY_TXSTART		(__DAVROS_DVNEXT+1)

#ifndef __ASSEMBLER__

typedef struct __tty_dvctrl
{
	void (*__tty_rxchar)(__davros_device_t *, int);
	int (*__tty_txchar)(__davros_device_t *);
	__davros_status_t (*__tty_ctrl)(__davros_device_t *, int);
} __tty_dvctrl_t;

typedef struct __davros_tty
{
	uint16_t flags;
	uint8_t speed;
	char ibuf[__TTY_IBUFLEN];
	char *ihead;
	char *itail;
	__davros_semaphore_t *isem;
	char obuf[__TTY_OBUFLEN];
	char *ohead;
	char *otail;
	__davros_semaphore_t *osem;
#ifdef __TTY_LINE_EDITING
	char ebuf[__TTY_EBUFLEN];
	char *ehead;
	char *etail;
	char cc[__TTY_NCC];
#endif
} __davros_tty_t;

/* tty device switch functions - not all will be implemented */
int __davros_ttyopen(__davros_device_t *,char *,int);
int __davros_ttyclose(__davros_device_t *);
int __davros_ttyread(__davros_device_t *,char *,int);
int __davros_ttywrite(__davros_device_t *,char *,int);
int __davros_ttygetc(__davros_device_t *);
int __davros_ttyputc(__davros_device_t *,int);
int __davros_ttyctrl(__davros_device_t *,int,char *,char *);

extern const __davros_devsw_t __davros_ttydevsw;

/* tty back-end functions */
void __davros_ttyrxchar(__davros_device_t *, int);		/* Handles incoming char & error */
int __davros_ttytxchar(__davros_device_t *);			/* Gets next char to send */

#else

#define __tty_dvctrl_RXCHAR		0
#define __tty_dvctrl_TXCHAR		2
#define __tty_dvctrl_DVCTRL		4

#endif

#endif
