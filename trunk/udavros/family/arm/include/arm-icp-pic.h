/*	arm-icp-pic.h - header file for arm integrator/cp PIC
 *
 *	Copyright 2008 David Haworth
 *
 *	This file is part of davros.
 *
 *	davros is free software: you can redistribute it and/or modify
 *	it under the terms of the GNU General Public License as published by
 *	the Free Software Foundation, either version 3 of the License, or
 *	(at your option) any later version.
 *
 *	davros is distributed in the hope that it will be useful,
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *	GNU General Public License for more details.
 *
 *	You should have received a copy of the GNU General Public License
 *	along with davros.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef __dv_arm_icp_pic_h
#define __dv_arm_icp_pic_h

#ifdef __DV_IDENT
__DV_IDENT("$Id$")
#endif

#include <davros/basic-types.h>

/* This data structure represents a PIC register block. All fields
 * either automatically aupdate without software intervention or
 * have side effects when accessed, so they are all declared as
 * __dv_reg32_t.
 * Note: according to the doc, the fiq pic might not have the
 * soft_set and soft_clear registers.
*/
typedef struct __dv_arm_pic_s __dv_arm_pic_t;

struct __dv_arm_pic_s
{
	__dv_reg32_t status;			/* Pending and enabled */
	__dv_reg32_t raw_status;		/* Pending, whether enabled or not */
	__dv_reg32_t enable_set;		/* Write 1s to set the enable flags */
	__dv_reg32_t enable_clear;		/* Write 1s to clear the enable flags */
	__dv_reg32_t soft_set;			/* Write 1s to trigger the interrupts */
	__dv_reg32_t soft_clear;		/* Write 1s to clear the interrups */
};

#if 1
extern __dv_arm_pic_t __dv_arm_pic_pri_irq;
extern __dv_arm_pic_t __dv_arm_pic_pri_fiq;
extern __dv_arm_pic_t __dv_arm_pic_sec;
#else
#define __dv_arm_pic_pri_irq	(*(__dv_arm_pic_t *)0x14000000)
#define __dv_arm_pic_pri_fiq	(*(__dv_arm_pic_t *)0x14000020)	/* Might not have soft set/clr */
#define __dv_arm_pic_sec		(*(__dv_arm_pic_t *)0xca000000)
#endif

/* Interrupt assignments on primary controllers
*/
#define __DV_INTMASK_TSPEN		0x10000000
#define __DV_INTMASK_ETH		0x08000000
#define __DV_INTMASK_CPPLD		0x04000000		/* Secondary controller */
#define __DV_INTMASK_AACI		0x02000000
#define __DV_INTMASK_MMCI1		0x01000000
#define __DV_INTMASK_MMCI0		0x00800000
#define __DV_INTMASK_CLCDC		0x00400000
#define __DV_INTMASK_LMLL1		0x00000400
#define __DV_INTMASK_LMLL0		0x00000200
#define __DV_INTMASK_RTC		0x00000100
#define __DV_INTMASK_TIMER2		0x00000080
#define __DV_INTMASK_TIMER1		0x00000040
#define __DV_INTMASK_TIMER0		0x00000020
#define __DV_INTMASK_MOUSE		0x00000010
#define __DV_INTMASK_KBD		0x00000008
#define __DV_INTMASK_UART1		0x00000004
#define __DV_INTMASK_UART0		0x00000002
#define __DV_INTMASK_SOFT		0x00000001

/* Interrupt assignments on secondary controller
*/
#define __DV_INTMASK_LM7		0x00000800
#define __DV_INTMASK_LM6		0x00000400
#define __DV_INTMASK_LM5		0x00000200
#define __DV_INTMASK_LM4		0x00000100
#define __DV_INTMASK_LM3		0x00000080
#define __DV_INTMASK_LM2		0x00000040
#define __DV_INTMASK_LM1		0x00000020
#define __DV_INTMASK_LM0		0x00000010
#define __DV_INTMASK_CARDIN		0x00000008
#define __DV_INTMASK_RI1		0x00000004
#define __DV_INTMASK_RI0		0x00000002
#define __DV_INTMASK_SEC_SOFT	0x00000001

/* Interrupt indexes
 *
 * These are the indexes in the interrupt table.
*/
#define __DV_INTNUM_SOFT		0
#define __DV_INTNUM_UART0		1
#define __DV_INTNUM_UART1		2
#define __DV_INTNUM_KBD			3
#define __DV_INTNUM_MOUSE		4
#define __DV_INTNUM_TIMER0		5
#define __DV_INTNUM_TIMER1		6
#define __DV_INTNUM_TIMER2		7
#define __DV_INTNUM_RTC			8
#define __DV_INTNUM_LMLL0		9
#define __DV_INTNUM_LMLL1		10
/* 11 .. 21 reserved */
#define __DV_INTNUM_CLCDC		22
#define __DV_INTNUM_MMCI0		23
#define __DV_INTNUM_MMCI1		24
#define __DV_INTNUM_AACI		25
#define __DV_INTNUM_CPPLD		26		/* Secondary controller */
#define __DV_INTNUM_ETH			27
#define __DV_INTNUM_TSPEN		28
/* 29 .. 31 reserved */
#define __DV_NUMINT_PRI			32

#define __DV_NUMINT_PRI_SOFT	(__DV_NUMINT_PRI + 0)
#define __DV_INTNUM_RI0			(__DV_NUMINT_PRI + 1)
#define __DV_INTNUM_RI1			(__DV_NUMINT_PRI + 2)
#define __DV_INTNUM_CARDIN		(__DV_NUMINT_PRI + 3)
#define __DV_INTNUM_LM0			(__DV_NUMINT_PRI + 4)
#define __DV_INTNUM_LM1			(__DV_NUMINT_PRI + 5)
#define __DV_INTNUM_LM2			(__DV_NUMINT_PRI + 6)
#define __DV_INTNUM_LM3			(__DV_NUMINT_PRI + 7)
#define __DV_INTNUM_LM4			(__DV_NUMINT_PRI + 8)
#define __DV_INTNUM_LM5			(__DV_NUMINT_PRI + 9)
#define __DV_INTNUM_LM6			(__DV_NUMINT_PRI + 10)
#define __DV_INTNUM_LM7			(__DV_NUMINT_PRI + 11)
#define __DV_NUMINT_SEC			12

#define __DV_NUMINT				(__DV_NUMINT_PRI + __DV_NUMINT_SEC)

#endif
