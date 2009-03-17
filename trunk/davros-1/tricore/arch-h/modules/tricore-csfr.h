/*	tricore-csfr.h - Tricore Core Special Function Registers
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
 *	This file contains the CSFR offsets for Tricore Rider B and D and
 *	the field definitions for the CFSRs.
*/

#if !defined(__tricore_csfr_h)
#define __tricore_csfr_h

/*	CSFR offsets for Tricore Rider B and D. These offsets can be used
 *	with the mtcr/mfcr instructions, or can be added to a base address
 *	to get the absolute address for accesses via the bus.
 *
 *	For Rider B, the registers DCX and DMS are not documented.
 *	For Rider D, the registers DBITEN and GPRWB are not documented.
 *	
*/

#define	LCX		0xfe3c	/* Free CSA list limit pointer */
#define	FCX		0xfe38	/* Free CSA list head pointer */
#define	ICR		0xfe2c	/* Interrupt unit control register */
#define	ISP		0xfe28	/* Interrupt stack pointer */
#define	BTV		0xfe24	/* Base address of trap vector table */
#define	BIV		0xfe20	/* Base address of interrupt vector table */
#define	SYSCON	0xfe14	/* System configuration register */
#define	DBITEN	0xfe0c	/* Register bank dual bit enable register */
#define	PC		0xfe08	/* Program counter */
#define	PSW		0xfe04	/* Program status word */
#define	PCXI	0xfe00	/* Previous context information register */
#define DCX		0xfd44	/* Debug context save area pointer */
#define DMS		0xfd40	/* Debug monitor start address register */
#define	TR1EVT	0xfd24	/* Trigger event 1 specifier */
#define	TR0EVT	0xfd20	/* Trigger event 0 specifier */
#define	SWEVT	0xfd10	/* Software break event specifier */
#define	CREVT	0xfd0c	/* Emulator resource protection event specifier */
#define	EXEVT	0xfd08	/* External break input event specifier */
#define	GPRWB	0xfd04	/* GPR write back trigger */
#define	DBGSR	0xfd00	/* Debug status register */
#define	CPM1_0	0xe280	/* - CPM1_1 Code prot. mode regs, set 1 (2 bytes) */
#define	CPM0_0	0xe200	/* - CPM0_1 Code prot. mode regs, set 0 (2 bytes) */
#define	DPM1_0	0xe080	/* - DPM1_3 Data prot. mode regs, set 1 (4 bytes) */
#define	DPM0_0	0xe000	/* - DPM0_3 Data prot. mode regs, set 0 (4 bytes) */
#define	CPR1_1U	0xd40c	/* Code segment protection register 1, set 1, upper */
#define	CPR1_1L	0xd408	/* Code segment protection register 1, set 1, lower */
#define	CPR1_0U	0xd404	/* Code segment protection register 0, set 1, upper */
#define	CPR1_0L	0xd400	/* Code segment protection register 0, set 1, lower */
#define	CPR0_1U	0xd00c	/* Code segment protection register 1, set 0, upper */
#define	CPR0_1L	0xd008	/* Code segment protection register 1, set 0, lower */
#define	CPR0_0U	0xd004	/* Code segment protection register 0, set 0, upper */
#define	CPR0_0L	0xd000	/* Code segment protection register 0, set 0, lower */
#define	DPR1_3U	0xc41c	/* Data segment protection register 3, set 1, upper */
#define	DPR1_3L	0xc418	/* Data segment protection register 3, set 1, lower */
#define	DPR1_2U	0xc414	/* Data segment protection register 2, set 1, upper */
#define	DPR1_2L	0xc410	/* Data segment protection register 2, set 1, lower */
#define	DPR1_1U	0xc40c	/* Data segment protection register 1, set 1, upper */
#define	DPR1_1L	0xc408	/* Data segment protection register 1, set 1, lower */
#define	DPR1_0U	0xc404	/* Data segment protection register 0, set 1, upper */
#define	DPR1_0L	0xc400	/* Data segment protection register 0, set 1, lower */
#define	DPR0_3U	0xc01c	/* Data segment protection register 3, set 0, upper */
#define	DPR0_3L	0xc018	/* Data segment protection register 3, set 0, lower */
#define	DPR0_2U	0xc014	/* Data segment protection register 2, set 0, upper */
#define	DPR0_2L	0xc010	/* Data segment protection register 2, set 0, lower */
#define	DPR0_1U	0xc00c	/* Data segment protection register 1, set 0, upper */
#define	DPR0_1L	0xc008	/* Data segment protection register 1, set 0, lower */
#define	DPR0_0U	0xc004	/* Data segment protection register 0, set 0, upper */
#define	DPR0_0L	0xc000	/* Data segment protection register 0, set 0, lower */

/* Bit definitions for PSW */
#define	PSW_C			0x80000000		/* Carry flag */
#define	PSW_V			0x40000000		/* Overflow flag. */
#define PSW_SV			0x20000000		/* Sticky overflow flag. */
#define PSW_AV			0x10000000		/* Advanced overflow flag. */
#define PSW_SAV			0x08000000		/* Sticky advanced overflow flag. */
#define PSW_RES			0x07ffc000		/* Reserved. */
#define PSW_PRS			0x00003000		/* Protection Register Set. */
#define PSW_PRS_0		0x00000000		/* Protection Register Set 1. */
#define PSW_PRS_1		0x00001000		/* Protection Register Set 2. */
#define PSW_PRS_2		0x00002000		/* Protection Register Set 3. */
#define PSW_PRS_3		0x00003000		/* Protection Register Set 4. */
#define PSW_IO			0x00000c00		/* I/O privelege mode. */
#define PSW_IO_U0		0x00000000		/* User 0 I/O privelege mode. */
#define PSW_IO_U1		0x00000400		/* User 1 I/O privelege mode. */
#define PSW_IO_SU		0x00000800		/* Supervisor I/O privelege mode. */
#define PSW_IO_RES		0x00000c00		/* Reserved I/O privelege mode. */
#define PSW_IS			0x00000200		/* Interrupt stack in use. */
#define PSW_GW			0x00000100		/* Global register write permission. */
#define PSW_CDE			0x00000080		/* Call depth count enable. */
#define PSW_CDC			0x0000007f		/* Call depth counter. */
#define PSW_CDC_DIS		0x0000007f		/* Disable call depth counting. */
#define PSW_CDC_6		0x00000000		/* 6-bit call depth counter. */
#define PSW_CDC_5		0x00000040		/* 5-bit call depth counter. */
#define PSW_CDC_4		0x00000060		/* 4-bit call depth counter. */
#define PSW_CDC_3		0x00000070		/* 3-bit call depth counter. */
#define PSW_CDC_2		0x00000078		/* 2-bit call depth counter. */
#define PSW_CDC_1		0x0000007c		/* 1-bit call depth counter. */
#define PSW_CDC_TRA		0x0000007e		/* Call trace (trap every call). */

/*	Common bit definitions for all context pointer registers (PCXI,FCX,LCX)
 *	CSAs mist be aligned on a 16-word boundary. The offset is stored
 *	right-shifted by 6 bits.
*/
#define CX_SEG			0x000f0000		/* Segment number of CSA. */
#define CX_OFF			0x0000ffff		/* Offset (shr 6) of CSA. */
#define CX_CX			(CX_SEG|CX_OFF)	/* Entire context specifier. */

/*	Bit definitions 	for PCXI. See also common CX bit fields. */
#define PCXI_PCPN		0xff000000		/* Previous CPU priority. */
#define PCXI_PIE		0x00800000		/* Previous interrupt enable. */
#define PCXI_UL			0x00400000		/* Upper/lower context flag. */
#define PCXI_RES		0x00300000		/* Reserved. */

/* Bit definitions for ICR. */
#define ICR_RES			0xfc00fe00		/* Reserved. */
#define ICR_ARBCYC		0x03000000		/* Arbitration cycle control. */
#define ICR_PIPN		0x00ff0000		/* Pending interrupt priority number. */
#define ICR_IE			0x00000100		/* Interrupt enable. */
#define ICR_CCPN		0x000000ff		/* Current CPU priority number. */

/* Bit definitions for SYSCON. */
#define SYSCON_RES		0xfffffffc	/* Reserved. */
#define SYSCON_PROTEN	0x00000002	/* Enable memory protection. */
#define SYSCON_ENDINIT	0x00000001	/* End of initialisation. */

#ifdef __cplusplus
}
#endif

#endif
