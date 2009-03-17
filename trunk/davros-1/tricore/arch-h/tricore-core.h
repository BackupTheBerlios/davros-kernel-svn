/*	tricore-core.h - Tricore CPU core description
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
 *	This file contains definitions for the Tricore CPU core, including
 *	offsets of CSFRs, structures of context save areas, etc.
 *
*/

#if !defined(__tricore_core_h)
#define __tricore_core_h

#ifdef __cplusplus
extern "C" {
#endif

/* Offsets (in CSA) for all registers */
#define CSA_PCXI	0

#define CSA_U_PSW	4
#define CSA_U_A10	8
#define CSA_U_A11	12
#if (TRICORE_CORE == CORE_A)
#define CSA_U_A12	16
#define CSA_U_A13	20
#define CSA_U_A14	24
#define CSA_U_A15	28
#define CSA_U_D8	32
#define CSA_U_D9	36
#define CSA_U_D10	40
#define CSA_U_D11	44
#else
#define CSA_U_D8	16
#define CSA_U_D9	20
#define CSA_U_D10	24
#define CSA_U_D11	28
#define CSA_U_A12	32
#define CSA_U_A13	36
#define CSA_U_A14	40
#define CSA_U_A15	44
#endif
#define CSA_U_D12	48
#define CSA_U_D13	52
#define CSA_U_D14	56
#define CSA_U_D15	60

#define CSA_L_A11	4
#define CSA_L_A2	8
#define CSA_L_A3	12
#if (TRICORE_CORE == CORE_A)
#define CSA_L_A4	16
#define CSA_L_A5	20
#define CSA_L_A6	24
#define CSA_L_A7	28
#define CSA_L_D0	32
#define CSA_L_D1	36
#define CSA_L_D2	40
#define CSA_L_D3	44
#else
#define CSA_L_D0	16
#define CSA_L_D1	20
#define CSA_L_D2	24
#define CSA_L_D3	28
#define CSA_L_A4	32
#define CSA_L_A5	36
#define CSA_L_A6	40
#define CSA_L_A7	44
#endif
#define CSA_L_D4	48
#define CSA_L_D5	52
#define CSA_L_D6	56
#define CSA_L_D7	60

#define CSA_SIZE	64

#ifdef __ASSEMBLER__
/*
 *	_MTCR and _MFCR macros - these macros perform the required
 *	incantations, sacrifices, etc. in order to read and write the
 *	CSFRs (core special function registers).
 *
 *	Please read the Tricore documentation and errata sheets before
 *	modifying. The bug fixes might be implementation-dependent!
*/
	.macro	_MTCR	csfr,reg
	dsync
	nop
	nop
	mtcr	\csfr,\reg
	isync
	.endm

	.macro	_MFCR	reg,csfr
	mfcr	\reg,\csfr
	.endm

/*
 * setENDINIT - sets ENDINIT to value contained in LSB of D4.
 * This macro destroys %d4,%d8,%d9,%d10 and %a12.
*/
	.macro	setENDINIT

	/* Writing to the WDTCON0 register isn't easy.
	 *      First we must unlock the WDTCON0 register.
	 *      We first draw the pentagram on the floor, light a candle
	 *      at each apex, and chant the appropriate incantation.
	*/
	and		%d4,%d4,1				/* Clear all but LSB of parameter. */
	movh.a  %a12,hi:WDTCON0			/* Same value for WDTCON0 & WDTCON1 */
	ld.w    %d9,[%a12]lo:WDTCON1
	and     %d10,%d9,0xc			/* Get bits 3..2 from WDTCON1 for later */

	ld.w    %d8,[%a12]lo:WDTCON0	/* Start with value WDTCON0 */
	or      %d8,%d8,0xf0			/* Set bits 7..4 */
	andn    %d8,%d8,0xc				/* Clear bits 3..2 */
	xor     %d8,%d8,0x2				/* Invert bit 1 */
	or      %d8,%d8,%d10			/* Insert bits 3..2 from WDTCON1 */
	st.w    [%a12]lo:WDTCON0,%d8	/* Write the incantation */

	/* Now the demon has been summoned from the dark pit and
	 * WDTCON0 is unlocked. We can write the requested value
	 * into WDTCON0, along with more incantations to banish the
	 * demon and relock the register.
	*/
								/* Starting with the word we just wrote ... */
	andn	%d8,%d8,0xd				/* Clear bits 3,2 & 0 */
	xor		%d8,%d8,0x2				/* Invert bit 1 */
	or		%d8,%d8,%d4				/* Put required ENDINIT value in bit 0 */
	st.w	[%a12]lo:WDTCON0,%d8	/* Write the incantation */

	.endm

#else

typedef struct upper_context
{
	uint32_t psw;
	uint32_t a10;
	uint32_t a11;
#if (TRICORE_CORE == CORE_A)
	uint32_t a12;
	uint32_t a13;
	uint32_t a14;
	uint32_t a15;
	uint32_t d8;
	uint32_t d9;
	uint32_t d10;
	uint32_t d11;
#else
	uint32_t d8;
	uint32_t d9;
	uint32_t d10;
	uint32_t d11;
	uint32_t a12;
	uint32_t a13;
	uint32_t a14;
	uint32_t a15;
#endif
	uint32_t d12;
	uint32_t d13;
	uint32_t d14;
	uint32_t d15;
} upper_context_t;

typedef struct lower_context
{
	uint32_t a11;
	uint32_t a2;
	uint32_t a3;
#if (TRICORE_CORE == CORE_A)
	uint32_t a4;
	uint32_t a5;
	uint32_t a6;
	uint32_t a7;
	uint32_t d0;
	uint32_t d1;
	uint32_t d2;
	uint32_t d3;
#else
	uint32_t d0;
	uint32_t d1;
	uint32_t d2;
	uint32_t d3;
	uint32_t a4;
	uint32_t a5;
	uint32_t a6;
	uint32_t a7;
#endif
	uint32_t d4;
	uint32_t d5;
	uint32_t d6;
	uint32_t d7;
} lower_context_t;

typedef struct csa
    {
	uint32_t pcxi;
    union ctxt
	{
		lower_context_t lower;
		upper_context_t upper;
	} context;
} csa_t;

/*  Masks for converting *CX registers to memory addresses, and vice versa */
#define	CX_ADDR_ALIGN	0x0000003f		/* Must be zero to align correctly.*/
#define CX_ADDR_OFFSET	0x003fffc0		/* Variable offset part. */
#define CX_ADDR_LIMIT	0x0fc00000		/* Must be zero to be reachable. */
#define CX_ADDR_SEG		0xf0000000		/* Segment part. */
#define CX_SEG_SHIFT	12				/* No of bits to shift segment part. */
#define CX_OFF_SHIFT	6				/* No of bits to shift offset part. */

/*
 *	Some macros to allow access to assmbler instructions from C code.
 *	Gnu doesn't like "asm" in ANSI mode.
 *	But "__asm__" is fine  :-O
*/
#define ISYNC()	__asm__("isync")
#define DSYNC() __asm__("dsync")

/* Interrupt and exception handling */
typedef struct interrupt_vector
{
	uint32_t	bisr;
	uint32_t	jl;
	uint32_t	type;
	uint32_t	handler;
	uint32_t	param;
	uint32_t	spare1;
	uint32_t	spare2;
	uint32_t	spare3;
} interrupt_vector_t;

typedef struct exception_vector
{
	uint32_t	vector[8];
} exception_vector_t;

extern interrupt_vector_t interrupt_table[];
extern exception_vector_t exception_table[];

/*
 *	Function prototypes. Some functions are in tricore-core.c,
 *	the others are in tricore-core-asm.s
*/

uint32_t disable_interrupts(void);
uint32_t enable_interrupts(void);
uint32_t restore_interrupts(uint32_t old);
uint32_t set_cpu_priority(uint32_t prio);
uint32_t address_to_context(csa_t *csa);
csa_t *context_to_address(uint32_t cx);
csa_t *next_csa(csa_t *csa);
uint32_t alloc_csa(int ncsa);
uint32_t get_pcxi(void);
uint32_t get_icr(void);
uint32_t free_csa(uint32_t head, uint32_t limit);

void set_biv(uint32_t biv);
void set_btv(uint32_t btv);
uint32_t get_biv(void);
uint32_t get_btv(void);

#endif

/*	Class 0: MMU traps (to be defined) */

/*	Class 1: Internal protection traps */
#define EXC_TIN_PRIV	1	/* Privileged instruction */
#define EXC_TIN_MPR		2	/* Memory protection: read access */
#define EXC_TIN_MPW		3	/* Memory protection: write access */
#define EXC_TIN_MPX		4	/* Memory protection: execute access */
#define EXC_TIN_MPP		5	/* Memory protection: peripheral access */
#define EXC_TIN_MPN		6	/* Memory protection: null address */
#define EXC_TIN_GRWP	7	/* Global register write protection */

/*	Class 2: Instruction errors */
#define EXC_TIN_IOPC	1	/* Illegal opcode */
#define EXC_TIN_ALN		4	/* Data address alignment error */
#define EXC_TIN_MEM		5	/* Invalid memory address */

/*	Class 3: Context management */
#define EXC_TIN_FCD		1	/* Free contexts depleted (FCX==LCX) */
#define EXC_TIN_CDO		2	/* Call depth overflow */
#define EXC_TIN_CDU		3	/* Call depth underflow */
#define EXC_TIN_FCU		4	/* Free context list underflow (FCX==0) */
#define EXC_TIN_CSU		5	/* Context list underflow (PCX==0) */
#define EXC_TIN_CTYP	6	/* Context type error: PCXI.UL is wrong  */
#define EXC_TIN_NEST	7	/* Nesting error: RFE with non-zero call depth */

/*	Class 4: System bus errors */
#define EXC_TIN_PSE		1	/* Bus error on program fetch */
#define EXC_TIN_DSE		2	/* Bus error on data load */
#define EXC_TIN_DAE		3	/* Bus error on data store (asynchronous) */

/*	Class 5: Assertion traps */
#define EXC_TIN_OVF		1	/* Arithmetic overflow */
#define EXC_TIN_SOVF	2	/* Sticky arithmetic overflow */

/*	Offsets of fields in interrupt_vector_t.
 *	In the interrupt handler code (vectors.s) the offsets are from
 *	the word after the jl, because the jl puts the address of that
 *	word into a11. That's what the IVEC_A11 macro is for.
*/
#define IVEC_BISR		0x00
#define IVEC_JL			0x04
#define IVEC_TYPE		0x08
#define IVEC_HANDLER	0x0c
#define IVEC_PARAM		0x10
#define IVEC_SPARE1		0x14
#define IVEC_SPARE2		0x18
#define IVEC_SPARE3		0x1c

#define IVEC_A11(x)		((x)-IVEC_TYPE)

#ifdef __cplusplus
}
#endif

#endif
