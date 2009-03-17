/*	rom-entry.s - entry point for cold boot for Tricore CPU
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
 *	This file contains the entry code for Tricore programs that start
 *	running from ROM.
 *
 *  At boot time, Tricore fetches a halfword from offset 4 of the ROM
 *  and uses this to configure the ROM chip select registers (BUSCONx
 *	and ADDSELx) to a reasonable (although not optimal) setting for
 *	running code.
 *
 *	Before we can execute any C functions, we must perform the following
 *	initialisations:
 *		- initialise the ROM and RAM chip selects and the dynamic RAM
 *		  controller, so that the ROM program runs as fast as possible,
 * 		  we have data memory to store things in.
 *		- initialise a mimimal set of CSAs, so that functions can be
 *		  called.
 *		- initialise the bss and data sections.
 *
 *	The boot routine expects some configuration to be supplied via
 *	the board-config.h file. The following macros are expected:
 *
 *	Macro					Notes
 *	COPYRIGHT_YEAR			String for the copyright notice.
 *	COPYRIGHT_AUTHOR		String for the copyright notice.
 *	BOOTWORD				The boot word to put at offset 4 of the ROM.
 *	BOOT_STACK				Where to put the stack (high end!).
 *	BOOT_INTSTACK			Where to put the interrupt stack (high end!).
 *	BOOT_CSA				Base of block of memory for initial free CSA list.
 *	BOOT_NCSA				No. of CSAs in the above block.
 *	BOOT_NCSAEXC			No. of CSAs to reserve for exception handling.
 *	ADDSELROM				ADDSEL register for ROM access.
 *	BUSCONROM				BUSCON register for ROM access.
 *	ADDSELRAM				ADDSEL register for RAM access.
 *	BUSCONRAM				BUSCON register for RAM access.
 *	BOOT_ADDSELROM			Value for ADDSELROM.
 *	BOOT_BUSCONROM			Value for BUSCONROM.
 *	BOOT_ADDSELRAM			Value for ADDSELRAM.
 *	BOOT_BUSCONRAM			Value for BUSCONRAM.
 *	BOOT_EBUCON				Value for EBUCON.
 *	BOOT_DRMCON0			Value for DRMCON0.
 *	BOOT_DRMCON1			Value for DRMCON1.
 *	BOOT_BCUCON				Value for BCUCON.
 *	BOOT_CLEAR_BSS			Function to clear bss section.
 *	BOOT_INIT_DATA			Function to initialise data section.
 *	BOOT_INIT_CPU			Function to intialise the CPU
 *	BOOT_MAIN				C entry point for program.
*/

#include "tricore.h"
#include "modules/tricore-csfr.h"
#include "modules/tricore-pwr.h"
#include "modules/tricore-pmu.h"
#include "modules/tricore-dmu.h"
#include "modules/tricore-bcu.h"
#include "modules/tricore-ebu.h"
#include "tricore-core.h"

/*
 *	Default values for unsupplied configuration macros
*/
#if !defined(COPYRIGHT_YEAR)
#define COPYRIGHT_YEAR		"2001"
#endif
#if !defined(COPYRIGHT_AUTHOR)
#define COPYRIGHT_AUTHOR	"David Haworth"
#endif
#if !defined(BOOT_MAIN)
#define BOOT_MAIN			main
#endif


/*
 * rom-entry - entry point for Tricore cold-boot
*/

	.text

	.globl	rom_entry
	.type	rom_entry,@function
	.globl	tricore_bootword
	.type	tricore_bootword,@object

	.extern	BOOT_MAIN

	.align	8
rom_entry:
	j	cold_boot		/* all we can do here. the boot word must be next */

/*	Tricore requires a 32-bit word here containing a specially-cooked
 *	version of the ROM BUSCONx register.
*/
	.align	2
tricore_bootword:
	.word	BOOTWORD

	.align	2

/*	Copyright notice.
	Inserted as early as possible in the ROM.
*/
rom_copyright:
	.ascii	"Copyright "
	.ascii	COPYRIGHT_YEAR
	.ascii	" "
	.ascii	COPYRIGHT_AUTHOR
	.ascii	". "
rom_gpl:
	.asciz	"Released under the Gnu General Public License."

	.align	2
cold_boot:
	disable

/*	We must clear ENDINIT here, in case it's a warm boot.
 *	We can't call a subroutine here, so we have to do it in-line.
 *	We use the setENDINIT macro.
*/
	mov		%d4,0
	setENDINIT
	   
/* Set the BTV (base trap vector) register to point to the rom-based
 * exception vector table. We set the BIV (base interrupt vector) register
 * to the same value, which isn't quite right, but never mind.
*/
	movh	%d2,hi:rom_exceptions
	addi	%d2,%d2,lo:rom_exceptions
	_MTCR	BTV,%d2
	_MTCR	BIV,%d2

/*	If it's a warm boot, the caches might be enabled. Disable them.
 *	No need to flush - we're assuming all RAM is poo anyway.
*/
	movh.a	%a2,hi:PMUCON0			/* instruction cache */
	ld.w	%d2,[%a2]lo:PMUCON0
	or		%d2,%d2,PMUCON0_CCBYP
	dsync
	nop
	st.w	[%a2]lo:PMUCON0,%d2
	isync

	movh.a	%a2,hi:DMUCON			/* data cache */
	ld.w	%d2,[%a2]lo:DMUCON
	andn	%d2,%d2,DMUCON_DCAON
	dsync
	nop
	st.w	[%a2]lo:DMUCON,%d2
	isync

/*	Initialise PSW.
 *	- Enable call depth counting
 *	- Enable write permission to global registers
 *	- Go to supervisor mode
 *	- Use protection register set 0
 *	- Use interrupt stack (temporarily)
 *
 *	We must do this here, otherwise we might not be
 *	able to initialise the global address registers.
*/
	mov.u	%d2,PSW_CDE | PSW_GW | PSW_IO_SU | PSW_PRS_0 | PSW_IS
	_MTCR	PSW,%d2

/*	Clear Previous Context Information Register (PCXI).
*/
	mov		%d0,0
	_MTCR	PCXI,%d0

/*	Initialize context areas. Link all contexts to a list of
 *	free contexts. BOOT_CSA is the beginning of a block of
 *	BOOT_NCSA CSAs. BOOT_NCSAEXC defines how many CSAs to reserve
 *	for handling "context-list depleted" exceptions.
*/
	movh	%d2,hi:BOOT_CSA
	addi	%d2,%d2,lo:BOOT_CSA
	extr.u	%d3,%d2,6,16
	sh		%d4,%d2,-12
	movh	%d5,0x000f
	and		%d4,%d5
	or		%d3,%d4
	add		%d4,%d3,1

	_MTCR	FCX,%d3

	mov.a	%a3,%d2
	mov		%d5,(BOOT_NCSA-BOOT_NCSAEXC)
	mov		%d1,1				/* Set for 1st pass through loop */

initCSA:
	st.w	[%a3+]64,%d4
	add		%d4,1
	add		%d5,-1
	jge		%d5,1,initCSA

	jeq		%d1,0,endCSA		/* Jump on 2nd pass */

	add		%d3,%d4,-1			/* At end of first pass, set LCX register */
	_MTCR	LCX,%d3

	mov		%d5,(BOOT_NCSAEXC-1)/* No. of spare blocks */
	mov		%d1,0				/* Clear for 2nd pass through loop */
	j		initCSA				/* Back again for 2nd pass */

endCSA:
	mov		%d4,0				/* Set the last CSA link word to NULL */
	st.w	[%a3],%d4

/*	Initialise the EBU. First we initialise all the
 *	ADDSELx/BUSCONx registers. We only initialise the registers
 *	necessary for accessing RAM and ROM here: the rest can be done
 *	in C code.
*/
	movh.a	%a2,hi:EBUCLC	/* All BUSCONS/ADDSELs are reachable from here */

	movh	%d2,hi:BOOT_ADDSELROM
	addi	%d2,%d2,lo:BOOT_ADDSELROM
	st.w	[%a2]lo:ADDSELROM,%d2
	movh	%d2,hi:BOOT_BUSCONROM
	addi	%d2,%d2,lo:BOOT_BUSCONROM
	st.w	[%a2]lo:BUSCONROM,%d2

	movh	%d2,hi:BOOT_ADDSELRAM
	addi	%d2,%d2,lo:BOOT_ADDSELRAM
	st.w	[%a2]lo:ADDSELRAM,%d2
	movh	%d2,hi:BOOT_BUSCONRAM
	addi	%d2,%d2,lo:BOOT_BUSCONRAM
	st.w	[%a2]lo:BUSCONRAM,%d2

	movh	%d2,hi:BOOT_EBUCON
	addi	%d2,%d2,lo:BOOT_EBUCON
	st.w	[%a2]lo:EBUCON,%d2

	movh	%d2,hi:BOOT_DRMCON1
	addi	%d2,%d2,lo:BOOT_DRMCON1
	st.w	[%a2]lo:DRMCON1,%d2
	movh	%d2,hi:BOOT_DRMCON0
	addi	%d2,%d2,lo:BOOT_DRMCON0
	st.w	[%a2]lo:DRMCON0,%d2

	movh	%d2,hi:BOOT_BCUCON
	addi	%d2,%d2,lo:BOOT_BCUCON
	movh.a	%a3,hi:BCUCON
	st.w	[%a3]lo:BCUCON,%d2

/*	We need a stack. We'll just stick it at some harmless location in RAM
 *	for now. We also set the ISP (interrupt stack pointer), although this
 *	won't be used until interrupts are enabled. It can be initialised
 *	properly in the C code.
*/
	movh.a	%sp,hi:BOOT_STACK
	lea		%sp,[%sp]lo:BOOT_STACK
	mov.d	%d2,%sp
	movh.a	%sp,hi:BOOT_INTSTACK
	lea	%sp,[%sp]lo:BOOT_INTSTACK
	_MTCR	ISP,%d2

/*	Write the Disable W/D bit to WDTCON1. This only takes
 *	effect when WDTCON0 is unlocked and relocked (eg
 *	when setting or clearing ENDINIT.
 *	Then set ENDINIT.
*/
	movh.a	%a2,hi:WDTCON1
	mov		%d2,8
	st.w	[%a2]lo:WDTCON1,%d2
	mov		%d4,1
	setENDINIT

/*	A function to initialise the rest of the CPU is called.
 *	We only call this routines if it is defined.
*/

#if defined(BOOT_INIT_CPU)
	.extern	BOOT_INIT_CPU
	call	BOOT_INIT_CPU
#endif

/*	Jump to C entry point. We use jl instead of call to save a CSA.
 *	That means that if the C main function ever returns, we get a
 *	context-list underflow exception.
*/
	jl		BOOT_MAIN
	j		rom_entry		/* Can't boot. Try again */


/*
 *	The ROM exception table.
*/
	.text
	.align	8
rom_exceptions:
	svlcx
	mov	%d4,0
	j	exc_common

	.align	5
	svlcx
	mov	%d4,1
	j	exc_common

	.align	5
	svlcx
	mov	%d4,2
	j	exc_common

	.align	5
	svlcx
	mov	%d4,3
	j	exc_common

	.align	5
	svlcx
	mov	%d4,4
	j	exc_common

	.align	5
	svlcx
	mov	%d4,5
	j	exc_common

	.align	5
	svlcx
	mov	%d4,6
	j	exc_common

	.align	5
	rfe		/* NMI - ignore! */

exc_common:
	mov		%d5,%d15
	mov		%d6,0
	call	tricore_exception
	j		cold_boot
