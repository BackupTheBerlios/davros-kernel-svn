/*	tricore-ebu.h - Tricore EBU module description
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
 *	This file contains a description of Tricore's external bus unit (EBU)
 *
*/

#if !defined(__tricore_ebu_h)
#define __tricore_ebu_h

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(__ASSEMBLER__)

typedef struct tricore_ebu
{
	tricore_mod_t		ebu_hdr;
    volatile uint32_t	reserved1[1];
    volatile uint32_t	ebu_ebucon;		/* EBU Configuration Register */
    volatile uint32_t	ebu_drmcon0;	/* DRAM Configuration Register */
    volatile uint32_t	ebu_drmcon1;	/* DRAM Configuration Register */
    volatile uint32_t	ebu_drmstat;	/* DRAM Status Register */
    volatile uint32_t	ebu_addsel0;	/* Address Select Register for CS0 */
    volatile uint32_t	ebu_addsel1;	/* Address Select Register for CS1 */
    volatile uint32_t	ebu_addsel2;	/* Address Select Register for CS2 */
    volatile uint32_t	ebu_addsel3;	/* Address Select Register for CS3 */
    volatile uint32_t	ebu_addsel4;	/* Address Select Register for CS4 */
    volatile uint32_t	ebu_addsel5;	/* Address Select Register for CS5 */
    volatile uint32_t	ebu_addsel6;	/* Address Select Register for CS6 */
    volatile uint32_t	ebu_addsel7;	/* Address Select Register for CS7 */
    volatile uint32_t	reserved2[8];
    volatile uint32_t	ebu_buscon0;	/* Bus Configuration Register for CS0 */
    volatile uint32_t	ebu_buscon1;	/* Bus Configuration Register for CS1 */
    volatile uint32_t	ebu_buscon2;	/* Bus Configuration Register for CS2 */
    volatile uint32_t	ebu_buscon3;	/* Bus Configuration Register for CS3 */
    volatile uint32_t	ebu_buscon4;	/* Bus Configuration Register for CS4 */
    volatile uint32_t	ebu_buscon5;	/* Bus Configuration Register for CS5 */
    volatile uint32_t	ebu_buscon6;	/* Bus Configuration Register for CS6 */
    volatile uint32_t	ebu_buscon7;	/* Bus Configuration Register for CS7 */
    volatile uint32_t	ebu_emuas;		/* Emulator memory address select register */
    volatile uint32_t	ebu_emubc;		/* Emulator memory bus configuration register */
    volatile uint32_t	ebu_emucon;		/* Emulator memory control register */
} tricore_ebu_t;

#endif

/*	Absolute addresses of EBU registers. Used mainly in assembler modules. */
#define EBUREG(x)	(EBU_BASE+(x))
#define EBUCLC		EBUREG(0x00)
#define EBUID		EBUREG(0x08)
#define EBUCON		EBUREG(0x10)
#define DRMCON0		EBUREG(0x14)
#define DRMCON1		EBUREG(0x18)
#define DRMSTAT		EBUREG(0x1c)
#define ADDSEL0		EBUREG(0x20)
#define ADDSEL1		EBUREG(0x24)
#define ADDSEL2		EBUREG(0x28)
#define ADDSEL3		EBUREG(0x2c)
#define ADDSEL4		EBUREG(0x30)
#define ADDSEL5		EBUREG(0x34)
#define ADDSEL6		EBUREG(0x38)
#define ADDSEL7		EBUREG(0x3c)
#define BUSCON0		EBUREG(0x60)
#define BUSCON1		EBUREG(0x64)
#define BUSCON2		EBUREG(0x68)
#define BUSCON3		EBUREG(0x6c)
#define BUSCON4		EBUREG(0x70)
#define BUSCON5		EBUREG(0x74)
#define BUSCON6		EBUREG(0x78)
#define BUSCON7		EBUREG(0x7c)
#define EMUAS		EBUREG(0x80)
#define EMUBC		EBUREG(0x84)
#define EMUCON		EBUREG(0x88)

#define EBU_MODULE_ID		0x04

/*	Bit definitions for ADDSELx */
#define ADDSEL_REGEN		0x00000001      /* Memory Region Enable */
#define ADDSEL_MIRRORE		0x00000002      /* Memory Region mirrored in segment 0xe */
#define ADDSEL_MASK			0x000000f0      /* Memory Region Address Mask */
#define ADDSEL_BASE			0xfffff000      /* Memory Region Base Address */

/*	Bit definitions for BUSCONx */
#define BUSCON_CMULT		0x00000003      /* Cycle Multiplier Control */
#define BUSCON_CMULT_CM1	0x00000000      /* Cycle Multiplier 1 */
#define BUSCON_CMULT_CM4	0x00000001      /* Cycle Multiplier 4 */
#define BUSCON_CMULT_CM8	0x00000002      /* Cycle Multiplier 8 */
#define BUSCON_CMULT_CM16	0x00000003      /* Cycle Multiplier 16 */
#define BUSCON_RECOVC		0x0000000c      /* Recovery Cycles Control */
#define BUSCON_HOLDC		0x00000030      /* Hold / Pause Cycle Control */
#define BUSCON_WAITRDC		0x000000c0      /* Read Access Waitstate Control */
#define BUSCON_WAITWRC		0x00000700      /* Write Access Waitstate Control */
#define BUSCON_BCGEN		0x00003000      /* Byte Control Signal Timing Mode */
#define BUSCON_BCGEN_CSM	0x00000000      /* Chipselect Mode */
#define BUSCON_BCGEN_CM		0x00001000      /* Control Mode */
#define BUSCON_BCGEN_WEM	0x00002000      /* Write Enable Mode */
#define BUSCON_BCGEN_CASM	0x00003000      /* CAS Mode */
#define BUSCON_ALEC			0x0000c000		/* ALE duration */
#define BUSCON_PORTW		0x00030000      /* External Device Data Width Control */
#define BUSCON_PORTW_8		0x00000000      /* 8 Bit */
#define BUSCON_PORTW_16		0x00010000      /* 16 Bit */
#define BUSCON_PORTW_32		0x00020000      /* 32 Bit */
#define BUSCON_PORTW_DQM	0x00030000      /* SDRAM mode */
#define BUSCON_WAITINV		0x00080000      /* Active Wait Level Control */
#define BUSCON_WAIT			0x00300000      /* Variable Waitstate Insertion Control */
#define BUSCON_WAIT_DIS		0x00000000      /* Variable Waitstate Insertion Disabled */
#define BUSCON_WAIT_ASYN	0x00100000      /* Asynchronous Waitstate Insertion */
#define BUSCON_WAIT_SYN		0x00200000      /* Synchronous Waitstate Insertion */
#define BUSCON_SETUP		0x00400000      /* Extended Address Setup Control */
#define BUSCON_AGEN			0x07000000      /* Address Generation Control */
#define BUSCON_AGEN_DEMUX	0x00000000      /* Demuxed Address */
#define BUSCON_AGEN_DRAM	0x01000000      /* DRAM Address Mode */
#define BUSCON_AGEN_MUX		0x02000000      /* Multiplexed address/data */
#define BUSCON_WRITE		0x80000000      /* Write Protection */

#define BUSCON_WAITWRCval(n)	(((n) << 8) & BUSCON_WAITWRC)
#define BUSCON_WAITRDCval(n)	(((n) << 6) & BUSCON_WAITRDC)
#define BUSCON_HOLDCval(n)		(((n) << 4) & BUSCON_RECOVC)
#define BUSCON_RECOVCval(n)		(((n) << 2) & BUSCON_RECOVC)

/* Bit definitions for EBUCON */
#define EBUCON_EXTRECON		0x00000002      /* Reconfiguration Control */
#define EBUCON_EXTSVM		0x00000004      /* External Supervisor Mode Access Control */
#define EBUCON_EXTACC		0x00000008      /* External Access to FPI Control */
#define EBUCON_EXTLOCK		0x00000010      /* External Bus Lock Control */
#define EBUCON_ARBSYNC		0x00000020      /* Arbitration Inputs Evaluation Control */
#define EBUCON_ARBMODE		0x000000c0      /* Arbitration Strategy */
#define EBUCON_ARBMODE_DIS	0x00000000      /* EBU is Disabled */
#define EBUCON_ARBMODE_EXTM	0x00000040      /* EBU is External Master */
#define EBUCON_ARBMODE_EXTS	0x00000080      /* EBU is External Slave */
#define EBUCON_ARBMODE_NONE	0x000000c0      /* EBU Arbitration is Disabled */
#define EBUCON_TIMOUTC		0x0000ff00      /* Time Out Control */
#define EBUCON_DTARW		0x00070000      /* Driver turn-around time rd-to-wr on same CS */
#define EBUCON_DTACS		0x00700000      /* Driver turn-around CS-to-CS */

/*	Bit definitions for DRMCON0 */
#define DRMCON0_REFRESHR	0x70000000		/* No. of refresh commands */
#define DRMCON0_REFRESHC	0x0f000000		/* Refresh interval */
#define DRMCON0_AWIDTH		0x000c0000		/* Start index of address lines in row address */
#define DRMCON0_AWIDTH_10	0x00000000		/* 10 address lines multiplexed */
#define DRMCON0_AWIDTH_11	0x00010000		/* 11 address lines multiplexed */
#define DRMCON0_AWIDTH_12	0x00020000		/* 12 address lines multiplexed */
#define DRMCON0_CRCD		0x00030000		/* Row-to-column delay */
#define DRMCON0_CRC			0x00007000		/* Row cycle time */
#define DRMCON0_CRP			0x00000c00		/* Row precharge time */
#define DRMCON0_CRSC		0x00000300		/* Mode register setup time */
#define DRMCON0_CRFSH		0x000000f0		/* No. of refresh commands in power-up sequence */
#define DRMCON0_CRAS		0x0000000f		/* Row activate to precharge time */

/*	Bit definitions for DRMCON1 */
#define DRMCON1_MODE		0x00003fff		/* Mode field, values depend on SDRAM. */
#define DRMCON1_MODE_CASL	0x00000070		/* CAS Latency */
#define DRMCON1_MODE_CASL2	0x00000020		/* CAS latency 2 */
#define DRMCON1_MODE_CASL3	0x00000030		/* CAS latency 3 */
#define DRMCON1_MODE_CASL4	0x00000040		/* CAS latency 4 */

/*	Bit definitions for DRMSTAT */
#define DRMSTAT_REFERR		0x00000001      /* Refresh Error Flag */
#define DRMSTAT_BUSY		0x00000002      /* Power-on initialisation running */

#ifdef __cplusplus
}
#endif

#endif
