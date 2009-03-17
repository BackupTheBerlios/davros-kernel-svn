/*	tricore-gptu.h - Tricore GPTU description
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
 *	This file contains a description of Tricore's General Purpose
 *	Timer Unit (GPTU).
*/

#if !defined(__tricore_gptu_h)
#define __tricore_gptu_h

#ifdef __cplusplus
extern "C" {
#endif

#include "modules/tricore-mod.h"

#if !defined(__ASSEMBLER__)

typedef struct tricore_gptu
{
	tricore_mod_t		gptu_hdr;
    volatile uint32_t	gptu_reserved1;
    volatile uint32_t	gptu_t01irs;
    volatile uint32_t	gptu_t01ots;
    volatile uint32_t	gptu_t2con;
    volatile uint32_t	gptu_t2rccon;
    volatile uint32_t	gptu_t2ais;
    volatile uint32_t	gptu_t2bis;
    volatile uint32_t	gptu_t2es;
    volatile uint32_t	gptu_gtosel;
    volatile uint32_t	gptu_gtout;
    volatile uint32_t	gptu_t0dcba;
    volatile uint32_t	gptu_t0cba;
    volatile uint32_t	gptu_t0rdcba;
    volatile uint32_t	gptu_t0rcba;
    volatile uint32_t	gptu_t1dcba;
    volatile uint32_t	gptu_t1cba;
    volatile uint32_t	gptu_t1rdcba;
    volatile uint32_t	gptu_t1rcba;
    volatile uint32_t	gptu_t2;
    volatile uint32_t	gptu_t2rc0;
    volatile uint32_t	gptu_t2rc1;
    volatile uint32_t	gptu_t012run;
    volatile uint32_t	gptu_reserved2[30];
    volatile uint32_t	gptu_gtsrsel;
    tricore_isr_t		gptu_gtsrc7;
    tricore_isr_t		gptu_gtsrc6;
    tricore_isr_t		gptu_gtsrc5;
    tricore_isr_t		gptu_gtsrc4;
    tricore_isr_t		gptu_gtsrc3;
    tricore_isr_t		gptu_gtsrc2;
    tricore_isr_t		gptu_gtsrc1;
    tricore_isr_t		gptu_gtsrc0;
} tricore_gptu_t;

#endif

#define GPTU_MODULE_ID	0x1c

/* Bit definitions for T01IRS */
#define GPTU_T01IN1			0xC0000000
#define GPTU_T01IN0			0x30000000
#define GPTU_T1INC			0x02000000
#define GPTU_T0INC			0x01000000
#define GPTU_T1DREL			0x00800000
#define GPTU_T1CREL			0x00400000
#define GPTU_T1BREL			0x00200000
#define GPTU_T1AREL			0x00100000
#define GPTU_T0DREL			0x00080000
#define GPTU_T0CREL			0x00040000
#define GPTU_T0BREL			0x00020000
#define GPTU_T0AREL			0x00010000
#define GPTU_T1DINS			0x0000C000
#define GPTU_T1CINS			0x00003000
#define GPTU_T1BINS			0x00000C00
#define GPTU_T1AINS			0x00000300
#define GPTU_T0DINS			0x000000C0
#define GPTU_T0CINS			0x00000030
#define GPTU_T0BINS			0x0000000C
#define GPTU_T0AINS			0x00000003

/*	Combinations of fields, to avoid typing */
#define GPTU_T0INS			(GPTU_T0AINS|GPTU_T0BINS|GPTU_T0CINS|GPTU_T0DINS)
#define GPTU_T0REL			(GPTU_T0AREL|GPTU_T0BREL|GPTU_T0CREL|GPTU_T0DREL)
#define GPTU_T1INS			(GPTU_T1AINS|GPTU_T1BINS|GPTU_T1CINS|GPTU_T1DINS)
#define GPTU_T1REL			(GPTU_T1AREL|GPTU_T1BREL|GPTU_T1CREL|GPTU_T1DREL)

/*	Values for the TxyINS fields. Each macro contains the value for
 *	all fields, so AND it with the field appropriate field mask
 *	to get the value in the field you need.
*/
#define GPTU_TxyINS_CLK		0x00000000
#define GPTU_TxyINS_CNT0	0x55555555
#define GPTU_TxyINS_CNT1	0xAAAAAAAA
#define GPTU_TxyINS_CARRY	0xFFFFFFFF

/*	Values for the T01INx fields. Each macro contains the value for
 *  all fields, so AND it with the field appropriate field mask
 *  to get the value in the field you need.
*/
#define GPTU_T01INx_T2		0x00000000
#define GPTU_T01INx_POS		0x55555555
#define GPTU_T01INx_NEG		0xAAAAAAAA
#define GPTU_T01INx_BOTH	0xFFFFFFFF

/* Bit definitions for T01OTS */
#define GPTU_SSR11			0x0C000000
#define GPTU_SSR10			0x03000000
#define GPTU_STRG11			0x00C00000
#define GPTU_STRG10			0x00300000
#define GPTU_SOUT11			0x000C0000
#define GPTU_SOUT10			0x00030000
#define GPTU_SSR01			0x00000C00
#define GPTU_SSR00			0x00000300
#define GPTU_STRG01			0x000000C0
#define GPTU_STRG00			0x00000030
#define GPTU_SOUT01			0x0000000C
#define GPTU_SOUT00			0x00000003

/*	Combinations of fields, to avoid typing */
#define GPTU_SOUT0			(GPTU_SOUT00 | GPTU_SOUT01)
#define GPTU_SOUT1			(GPTU_SOUT10 | GPTU_SOUT11)
#define GPTU_STRG0			(GPTU_STRG00 | GPTU_STRG01)
#define GPTU_STRG1			(GPTU_STRG10 | GPTU_STRG11)
#define GPTU_SSR0			(GPTU_SSR00 | GPTU_SSR01)
#define GPTU_SSR1			(GPTU_SSR10 | GPTU_SSR11)
#define GPTU_SALL0			(GPTU_SOUT0 | GPTU_STRG0 | GPTU_SSR0)
#define GPTU_SALL1			(GPTU_SOUT1 | GPTU_STRG1 | GPTU_SSR1)

/*	Values for the TxAOFLO fields. Each macro contains the value for
 *  all fields, so AND it with the field appropriate field mask
 *  to get the value in the field you need.
*/
#define GPTU_SS_TxAOFLO		0x00000000
#define GPTU_SS_TxBOFLO		0x55555555
#define GPTU_SS_TxCOFLO		0xAAAAAAAA
#define GPTU_SS_TxDOFLO		0xFFFFFFFF

/* Bit definitions for T012RUN */
#define GPTU_T2BCLRR		0x00004000
#define GPTU_T2BSETR		0x00002000
#define GPTU_T2BRUN			0x00001000
#define GPTU_T2ACLRR		0x00000400
#define GPTU_T2ASETR		0x00000200
#define GPTU_T2ARUN			0x00000100
#define GPTU_T1DRUN			0x00000080
#define GPTU_T1CRUN			0x00000040
#define GPTU_T1BRUN			0x00000020
#define GPTU_T1ARUN			0x00000010
#define GPTU_T0DRUN			0x00000008
#define GPTU_T0CRUN			0x00000004
#define GPTU_T0BRUN			0x00000002
#define GPTU_T0ARUN			0x00000001

/* Combinations to avoid typing */
#define GPTU_T0RUN			(GPTU_T0ARUN|GPTU_T0BRUN|GPTU_T0CRUN|GPTU_T0DRUN)
#define GPTU_T1RUN			(GPTU_T1ARUN|GPTU_T1BRUN|GPTU_T1CRUN|GPTU_T1DRUN)

/* Bit definitions for T2AIS */
#define GPTU_T2AIRC1		0x07000000
#define GPTU_T2AIRC0		0x00700000
#define GPTU_T2AICLR		0x00070000
#define GPTU_T2AIUD			0x00007000
#define GPTU_T2AISTP		0x00000700
#define GPTU_T2AISTR		0x00000070
#define GPTU_T2AICNT		0x00000007

/*	Values for the fields in T2AIS. Each macro contains the value for
 *  all fields, so AND it with the field appropriate field mask
 *  to get the value in the field you need.
*/
#define GPTU_T2IN_GPTUx_IN0	0x00000000
#define GPTU_T2IN_GPTUx_IN1	0x01111111
#define GPTU_T2IN_GPTUx_IN2	0x02222222
#define GPTU_T2IN_GPTUx_IN3	0x03333333
#define GPTU_T2IN_GPTUx_IN4	0x04444444
#define GPTU_T2IN_GPTUx_IN5	0x05555555
#define GPTU_T2IN_GPTUx_IN6	0x06666666
#define GPTU_T2IN_GPTUx_IN7	0x07777777

/* Bit definitions for T2ES */
#define GPTU_T2AERC1		0x00003000
#define GPTU_T2AERC0		0x00000c00
#define GPTU_T2AECLR		0x00000300
#define GPTU_T2AEUD			0x000000c0
#define GPTU_T2AESTP		0x00000030
#define GPTU_T2AESTR		0x0000000c
#define GPTU_T2AECNT		0x00000003

/*	Values for the fields in T2ES. Each macro contains the value for
 *  all fields, so AND it with the field appropriate field mask
 *  to get the value in the field you need.
*/
#define GPTU_T2EDGE_NONE	0x00000000	/* input disabled */
#define GPTU_T2EDGE_POS		0x15551555
#define GPTU_T2EDGE_NEG		0x2aaa2aaa
#define GPTU_T2EDGE_BOTH	0x3fff3fff

/* Bit definitions for GTSRSEL */
#define GPTU_GTSSR0			0xF0000000
#define GPTU_GTSSR1			0x0F000000
#define GPTU_GTSSR2			0x00F00000
#define GPTU_GTSSR3			0x000F0000
#define GPTU_GTSSR4			0x0000F000
#define GPTU_GTSSR5			0x00000F00
#define GPTU_GTSSR6			0x000000F0
#define GPTU_GTSSR7			0x0000000F

/*	Values for the fields in GTSRSEL. Each macro contains the value for
 *  all fields, so AND it with the field appropriate field mask
 *  to get the value in the field you need.
*/
#define GPTU_GTSSRx_StartA	0x00000000
#define GPTU_GTSSRx_StopA	0x11111111
#define GPTU_GTSSRx_UpDownA	0x22222222
#define GPTU_GTSSRx_ClearA	0x33333333
#define GPTU_GTSSRx_RLCP0A	0x44444444
#define GPTU_GTSSRx_RLCP1A	0x55555555
#define GPTU_GTSSRx_OUVT2A	0x66666666
#define GPTU_GTSSRx_OUVT2B	0x77777777
#define GPTU_GTSSRx_StartB	0x88888888
#define GPTU_GTSSRx_StopB	0x99999999
#define GPTU_GTSSRx_RLCP0B	0xAAAAAAAA
#define GPTU_GTSSRx_RLCP1B	0xBBBBBBBB
#define GPTU_GTSSRx_SR00	0xCCCCCCCC
#define GPTU_GTSSRx_SR01	0xDDDDDDDD
#define GPTU_GTSSRx_SR10	0xEEEEEEEE
#define GPTU_GTSSRx_SR11	0xFFFFFFFF

#ifdef __cplusplus
}
#endif

#endif
