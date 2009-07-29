/*	i8250.h - 8250 UART + derivatives.
 *
 *	Copyright 2002 David Haworth
 *
 *  This file is part of davros.
 *
 *  davros is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  davros is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with davros.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef __i8250_h
#define __i8250_h

#ifdef __DV_IDENT
__DV_IDENT("$Id$")
#endif

/*	This file contains definitions for the intel 8250 UART and
 *	its derivatives and clones.
 *
 *	We define the registers as offsets from a base address for two
 *	reasons:
 *		1 -	the device is often i/o mapped on x86 systems 
 *		2 -	the device registers are often decoded at 16- or 32-bit
 *			intervals instead of the normal 8.
*/

#define i8250_data	0		/* Read = rx, write = tx */
#define	i8250_ier	1		/* Interrupt enable */
#define	i8250_iid	2		/* Interrupt id */
#define i8250_lcr	3		/* Line control */
#define i8250_mcr	4		/* Modem control */
#define i8250_lsr	5		/* Line status */
#define i8250_msr	6		/* Modem status */

/*	The baud-rate divisor sits over the data and ier registers, and
 *	is accessible when the dlab bit in lcr is set.
 *	It is little-endian, but we define the two halves separately.
*/
#define i8250_brdl	i8250_data
#define i8250_brdh	i8250_ier

/* Bit fields in registers */

#define I8250_IER_MSI	0x08	/* modem status interrupts */
#define I8250_IER_LST	0x04	/* line status interrupts */
#define I8250_IER_TBE	0x02	/* transmit buffer empty */
#define I8250_IER_RDR	0x01	/* receiver data ready */

#define I8250_IID_ID	0x06	/* interrupt id bits mask */
#define I8250_IID_ID_MSTAT	0x00	/* modem status interrupt */
#define I8250_IID_ID_THRE	0x02	/* transmit holding register empty */
#define I8250_IID_ID_RBRF	0x04	/* receiver buffer register full */
#define I8250_IID_ID_SEOB	0x06	/* serialisation error or break */
#define I8250_IID_IP	0x01	/* interrupt pending bit */

#define I8250_LCR_DLAB	0x80	/* divisor latch access enable */
#define I8250_LCR_SBRK	0x40	/* break control bit */
/* FIXME: define better values for parity: odd, even, mark, space */
#define I8250_LCR_SP	0x20    /* stick parity select */
#define I8250_LCR_EPS	0x10	/* even parity slect */
#define I8250_LCR_PEN	0x08	/* parity enable */
#define I8250_LCR_STB	0x04	/* stop bits */
#define I8250_LCR_STB_1		0x00	/* 1 stop bit */
#define I8250_LCR_STB_2		0x04    /* 2 stop bits */
#define I8250_LCR_CS	0x03	/* Character size */
#define I8250_LCR_CS_5		0x00	/* 5 bits characters */
#define I8250_LCR_CS_6		0x01	/* 6 bits characters */
#define I8250_LCR_CS_7		0x02	/* 7 bits characters */
#define I8250_LCR_CS_8		0x03	/* 8 bits characters */

#define I8250_MCR_LOOP	0x10    /* loop back */
#define I8250_MCR_OUT2	0x08    /* output #2 */
#define I8250_MCR_OUT1	0x04    /* output #1 */
#define I8250_MCR_RTS	0x02    /* rts output */
#define I8250_MCR_DTR	0x01    /* dtr output */

#define I8250_LSR_TEMT	0x40	/* transmitter empty */
#define I8250_LSR_THRE	0x20	/* transmit holding register empty */
#define I8250_LSR_BI	0x10	/* break interrupt */
#define I8250_LSR_FE	0x08	/* framing error */
#define I8250_LSR_PE	0x04	/* parity error */
#define I8250_LSR_OE	0x02	/* overrun error */
#define I8250_LSR_RXRDY	0x01	/* receiver data available */

#define I8250_MSR_DCD	0x80	/* complement of dcd */
#define I8250_MSR_RI	0x40	/* complement of ring signal */
#define I8250_MSR_DSR	0x20	/* complement of dsr */
#define I8250_MSR_CTS	0x10	/* complement of cts */
#define I8250_MSR_DDCD	0x08	/* data carrier change */
#define I8250_MSR_DRI	0x04	/* ring change */
#define I8250_MSR_DDSR	0x02	/* dsr change */
#define I8250_MSR_DCTS	0x01	/* cts change */

#endif
