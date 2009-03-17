/*	tricore-asc.h - Tricore ASC module description
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
 *	This file contains a description of Tricore's asynchronous serial
 *	communications module (ASC)
 *
*/

#if !defined(__tricore_asc_h)
#define __tricore_asc_h

#ifdef __cplusplus
extern "C" {
#endif

#include "arch-cpudef.h"
#include "modules/tricore-mod.h"

#if !defined(__ASSEMBLER__)

typedef struct tricore_asc
{
	tricore_mod_t		asc_hdr;
	volatile uint32_t	reserved1;
	volatile uint32_t	asc_con;		/* Control register */
	volatile uint32_t	asc_bg;			/* Baud rate generator */
	volatile uint32_t	asc_fdv;		/* Fractional divide register */
	volatile uint32_t	asc_pmw;		/* IrDA pulse mode & width register */
	volatile uint32_t	asc_tbuf;		/* Transmit buffer register */
	volatile uint32_t	asc_rbuf;		/* Receive buffer register */
	volatile uint32_t	reserved2[50];
	tricore_isr_t		asc_tsrc;		/* Transmit SR node */
	tricore_isr_t		asc_rsrc;		/* Receive SR node */
	tricore_isr_t		asc_esrc;		/* Error SR node */
	tricore_isr_t		asc_tbsrc;		/* Transmit buffer SR node */
} tricore_asc_t;

/*	The ASC has a register in the reserved location between the clc and the
 *	id registers in the module header. We can get to this through a
 *	macro definition.
*/
#define asc_pisel	asc_hdr.reserved

#endif

#define ASC_MODULE_ID		0x44		/* Use module_id macro */

/* Bit definitions for PISEL */
#define ASC_PISEL_RIS		0x00000001	/* Receiver Input Select */

/* Bit definitions for CON */
#define ASC_CON_M			0x00000007	/* Mode control */
#define ASC_CON_M_8SYNC		0x00000000	/* Synchronous, 8 bit */
#define ASC_CON_M_8ASYNC	0x00000001	/* Asynchronous, 8 bit */
#define ASC_CON_M_8IRDA		0x00000002	/* IrDA, 8 bit */
#define ASC_CON_M_7P		0x00000003	/* Asynchronous, 7 bit + parity */
#define ASC_CON_M_9			0x00000004	/* Asynchronous, 9 bit */
#define ASC_CON_M_8W		0x00000005	/* Asynchronous, 8 bit + wake up */
#define ASC_CON_M_8P		0x00000007	/* Asynchronous, 8 bit + parity */
#define ASC_CON_STP			0x00000008	/* Stop bits */
#define ASC_CON_STP_1		0x00000000	/* 1 stop bit */
#define ASC_CON_STP_2		0x00000001	/* 2 stop bits */
#define ASC_CON_REN			0x00000010	/* Receiver enable */
#define ASC_CON_PEN			0x00000020	/* Parity check enable, or
										   RxD invert in IrDA Mode */
#define ASC_CON_FEN			0x00000040	/* Framing check enable */
#define ASC_CON_OEN			0x00000080	/* Overrun check enable */
#define ASC_CON_PE			0x00000100	/* Parity error */
#define ASC_CON_FE			0x00000200	/* Framing error */
#define ASC_CON_OE			0x00000400	/* Overrun error */
#define ASC_CON_FDE			0x00000800	/* Fractional divider enable */
#define ASC_CON_ODD			0x00001000	/* Parity selection */
#define ASC_CON_BRS			0x00002000	/* Baudrate selection */
#define ASC_CON_LB			0x00004000	/* Loopback mode enable */
#define ASC_CON_R			0x00008000	/* Baudrate generator run */

/* Bit definitions for BG */
#define ASC_BG_RL			0x00001fff	/* Baudrate timer reload value */

/* Bit definitions for FDV */
#define ASC_FDV_DIV			0x000001ff	/* Fractional divider value */

/* Bit definitions for PMW */
#define ASC_PMW_PW			0x000000ff	/* IrDA pulse width */
#define ASC_PMW_IRPW		0x00000100	/* IrDA pulse width select */

/* Bit definitions for TBUF */
#define ASC_TBUF_TD			0x000001ff	/* Transmit data */

/* Bit definitions for RBUF */
#define ASC_RBUF_RD			0x000001ff	/* Receive data */

#ifdef __cplusplus
}
#endif

#endif
