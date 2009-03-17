/*	triboard-tc10gpfib-config.h - configuration file for triboard (fibbed rider b)
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
 *	This file contains memory and I/O address and related constants for
 *	a Triboard fitted with a fibbed (prototype) rider B CPU. The fibbed
 *	parts were hand-modified. The cache doesn't work; neither does the
 *	SDRAM controller.
 *
 *	This file is included by tricore.h
 *
*/

#if !defined(__triboard_tc10gpfib_config_h)
#define __triboard_tc10gpfib_config_h

#define TRICORE_BOARD	TRIBOARD
#define TRICORE_CPU		TC10GP_FIB
#define TRICORE_CORE	CORE_TC10

#define	CRYSTAL			16000000	/* 16 MHz */
#define CLOCK_RATE		72000000	/* 72 MHz */

/*	This board has a "fibbed" (laser-modified) Tricore rider B fitted.
 *	The part isn't fully functional, but the standard descriptions will suffice.
*/
#include "cpus/tricore-tc10gp.h"

/*	The Triboard with fibbed rider B (no cache) fitted is an oddball.
 *	In common with other Triboards, the flash fitted could vary.
 *	The RAM fitted on the board is 1MB static RAM, since the dynamic RAM
 *	controller doesn't work. There's an optional 4MB add-on board.
 *	There's also an add-on ethernet card available.
*/
/*
 *  BCU and EBU settings.
 *	WARNING: Incorrect values in these registers can make the system
 *	unusable in subtle ways.
 *	The EBUCON register controls the whole external bus unit.
 *	Get this wrong, and nothing works properly.
 *	Each pair of ADDSELx/BUSCONx registers corresponds to the matching
 *	chip select pin (CSx) on the Tricore chip. These pins are in turn
 *	used to select external circuitry (memory, I/O, etc) for reading
 *	and writing. The timing parameters must be set up for the worst
 *	case device that is enabled via the chip select.
 *	rom-entry.s only sets up the ROM chip select amd a single RAM chip
 *	select. It's up to the application code to initialise the chip selects
 *	for the rest of the RAM and the I/O.
*/
#define	INIT_BCUCON		0x4000ffff
#define	INIT_EBUCON		0x0000ff68	/* EXTACC=1, ARBMODE=ext.master.
									   OK for JTAG debuggers - can
									   use 0xc0 for standalone use */
#define	INIT_DRMCON0	0x00000000
#define	INIT_DRMCON1	0x00000000

/*	FLASH ROM settings:
 *	Size	ADDSEL0		BUSCON0		FLASH_SIZE
 *	256K	0xa0000091	0x004207c4	0x40000
 *	512K	0xa0000081	0x004207c4	0x80000
 *	1MB		0xa0000071	0x004207c4	0x100000
 *	2MB		0xa0000061	0x004207c4	0x200000
 *	4MB		0xa0000051	0x004207c4	0x400000
*/
#define	FLASH_START		0xa0000000
#define	FLASH_SIZE		0x200000
#define INIT_ADDSEL0	0xa0000061	/* = BOOT_ADDSELROM */
#define	INIT_BUSCON0	0x004207c4	/* = BOOT_BUSCONROM */

/*	Static RAM settings:
 *	Size	ADDSEL1		BUSCON1		ADDSEL3		BUSCON3		RAM_SIZE
 *	1MB		0xa8000071	0x00420000	---			---			0x100000
 *	4MB		---			---			0Xa8000051	0X00420280	0x400000
 *	5MB		0xa8400071	0x00420280	0xa8000051	0x00420280	0x500000
 *
 *	The 5MB setting is a combination of the 1MB and 4MB, except that
 *	the wait-states must be increased to take account of the extra
 *	bus loading. When using the 5MB setting, the 4MB block must be
 *	located below the 1MB block, or the blocks will not be contiguous.
 *	If you switch to the 1MB setting, you need to switch over the
 *	BOOT_xxxxxxRAM settings below.
*/
#define	RAM_START		0xa8000000
#define RAM_SIZE		0x500000
#define	INIT_ADDSEL3	0xa8000051	/* = BOOT_ADDSELRAM */
#define	INIT_BUSCON3	0x00420280	/* = BOOT_BUSCONRAM */
#define	INIT_ADDSEL1	0xa8400071
#define	INIT_BUSCON1	0x00420280

/*	Ethernet controller
 *
 *	The controller is a Cirrus 8900 connected to CS2.
 *	The interrupt line is connected to NMI :-(
 *	Fortunately, NMI is edge-triggered, and on Tricore there is the 
 *	"software-triggered interrupts" feature, which go through the same
 *	arbitration as hardware interrupts, and are therefore maskable.
 *	So we redirect NMI to a maskable interrupt via the CPS module.
 *
*/
#define	INIT_ADDSEL2	0xe00000e1
#define	INIT_BUSCON2	0x004103c5
#define	CIRRUS_BASE		0xe0000000
#define REDIRECT_NMI	INT_ETHER	/* Redirected priority/vector */
#define	REDIRECT_NODE	CPUSRC3

/*	ASC modules (serial ports)
 *
*/
#define ASC0_PORT		2		/* asc0 connects through port2 */
#define ASC1_PORT		2		/* asc1 connects through port2 */

/* Interrupt priorities for hardware interrupts
*/
#define INT_TIMER0		2
#define INT_TIMER1		3
#define INT_ASC0_RIR	4	/* received interrupt */
#define INT_ASC0_TBIR	5	/* transmit buffer empty interrupt */
#define INT_ASC0_EIR	6	/* error */
#define INT_ASC1_RIR	7	/* received interrupt */
#define INT_ASC1_TBIR	8	/* transmit buffer empty interrupt */
#define INT_ASC1_EIR	9	/* error */
#define INT_ETHER		10

/*	Configuration macros for rom-entry.s
*/

#undef	COPYRIGHT_YEAR			/* Use default */
#undef	COPYRIGHT_AUTHOR		/* Use default */
#define	BOOTWORD				0x000080cc
#define	BOOT_STACK				(RAM_START + 0x400000 - 0x100)
#define	BOOT_INTSTACK			(RAM_START + 0x400000)
#define	BOOT_CSA				DSRAM_START
#define	BOOT_NCSA				(DSRAM_SIZE / 64)
#define	BOOT_NCSAEXC			10
#define	ADDSELROM				ADDSEL0
#define	BUSCONROM				BUSCON0
#define	ADDSELRAM				ADDSEL3
#define	BUSCONRAM				BUSCON3
#define	BOOT_ADDSELROM			INIT_ADDSEL0
#define	BOOT_BUSCONROM			INIT_BUSCON0
#define	BOOT_ADDSELRAM			INIT_ADDSEL3
#define	BOOT_BUSCONRAM			INIT_BUSCON3
#define	BOOT_EBUCON				INIT_EBUCON
#define	BOOT_DRMCON0			INIT_DRMCON0
#define	BOOT_DRMCON1			INIT_DRMCON1
#define	BOOT_BCUCON				INIT_BCUCON
#define BOOT_INIT_CPU			init_cpu
#define BOOT_CLEAR_BSS			clear_bss
#define	BOOT_COPY_DATA			copy_data
#define	BOOT_MAIN				usrmain

#endif
