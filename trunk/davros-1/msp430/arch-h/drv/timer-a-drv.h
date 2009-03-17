/*	timer-a-drv.h - Driver for MSP430 Timer A module
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
 *	This file contains declarations for the timer A driver.
 *
 *	$Log: timer-a-drv.h,v $
 *	Revision 1.1  2004/05/11 20:46:48  dave
 *	File for the new msp430 port.
 *	
*/

#ifndef __TIMER_A_DRV_H
#define __TIMER_A_DRV_H

typedef struct timera_s
{
	volatile unsigned ctl;
	volatile unsigned cctl0;
	volatile unsigned cctl1;
	volatile unsigned cctl2;
	volatile unsigned gap[4];   /* Pad to the next group of registers */
	volatile unsigned tar;
	volatile unsigned taccr0;
	volatile unsigned taccr1;
	volatile unsigned taccr2;
} timera_t;

#define TIMER_A		0x160
#define TIMER_A_IV	0x12e

#define timer_a	(*(timera_t *)(TIMER_A))
#define taiv	(*(uint16_t *)(TIMER_A_IV))

#define TCTL_TASSEL	0x0300		/* Source select: */
#define TCTL_TASSEL_TACLK	0x0000
#define TCTL_TASSEL_ACLK	0x0100
#define TCTL_TASSEL_MCLK	0x0200
#define TCTL_TASSEL_INCLK	0x0300
#define TCTL_ID		0x00c0
#define	TCTL_ID_1			0x0000
#define	TCTL_ID_2			0x0040
#define	TCTL_ID_4			0x0080
#define	TCTL_ID_8			0x00c0
#define TCTL_MC		0x0030
#define TCTL_MC_STOP		0x0000
#define TCTL_MC_UP			0x0010
#define TCTL_MC_CONT		0x0020
#define TCTL_MC_UPDONW		0x0030
#define TCTL_TACLR	0x0004
#define TCTL_TAIE	0x0002
#define TCTL_TAIFG	0x0001

#define TCCTL_CM	0xc000
#define TCCTL_CM_NONE	0x0000
#define TCCTL_CM_RISE	0x4000
#define TCCTL_CM_FALL	0x8000
#define TCCTL_CM_BOTH	0xc000
#define TCCTL_CCIS	0x3000
#define TCCTL_CCIS_XA	0x0000
#define TCCTL_CCIS_XB	0x1000
#define TCCTL_CCIS_GND	0x2000
#define TCCTL_CCIS_VCC	0x3000
#define TCCTL_SCS	0x0800
#define TCCTL_SCCI	0x0400
#define TCCTL_CAP	0x0100
#define TCCTL_OM	0x00e0
#define TCCTL_OM_OBV	0x0000
#define TCCTL_OM_S		0x0020
#define TCCTL_OM_TR		0x0040
#define TCCTL_OM_SR		0x0060
#define TCCTL_OM_T		0x0080
#define TCCTL_OM_R		0x00a0
#define TCCTL_OM_TS		0x00c0
#define TCCTL_OM_RS		0x00e0
#define TCCTL_CCIE	0x0010
#define TCCTL_CCI	0x0008
#define TCCTL_OUT	0x0004
#define TCCTL_COV	0x0002
#define TCCTL_CCIFG	0x0001

extern unsigned timer_a_count;

int timer_a_start(void);
int timer_a_stop(void);

#endif
