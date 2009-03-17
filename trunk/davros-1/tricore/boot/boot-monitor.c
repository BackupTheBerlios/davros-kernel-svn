/*	boot-monitor.c - boot a system running the monitor
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
 *	This file contains the code that initialises the processor and the
 *	rest of the basic hardware before jumping to the main monitor
 *	function.
 *
*/

#include "tricore.h"
#include "boot-sys.h"
#include "monitor.h"
#include "modules/tricore-csfr.h"
#include "modules/tricore-mod.h"
#include "modules/tricore-pwr.h"
#include "modules/tricore-pmu.h"
#include "modules/tricore-dmu.h"
#include "modules/tricore-bcu.h"
#include "modules/tricore-ebu.h"
#include "drv/asc-drv.h"
#include "drv/gpio-drv.h"
#include "drv/pwr-drv.h"
#include "tricore-core.h"

/* FIXME: temp */
unsigned	bss_start[10];
unsigned	bss_end[1];
unsigned	data_start[20] = { 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20};
unsigned	data_end[1] = {42};
const unsigned	data_image[20] = { 21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40};
/* END of temp */

/*
 *	usrmain() - start the monitor
 *
 *  This function is called from from rom_entry. It initialises the
 *	serial port (ASC0) and then starts the monitor program.
 *
*/
void usrmain(void)
{
#if (ASC0_PORT==0)
	gpio_port_config(0, 4, GPIO_MODE_OUT|GPIO_MODE_ALT2);
	gpio_port_config(0, 5, GPIO_MODE_IN);
	asc_init(ASC0, 1);
#elif (ASC0_PORT==2)
	gpio_port_config(2, 4, GPIO_MODE_OUT|GPIO_MODE_ALT1);
	gpio_port_config(2, 5, GPIO_MODE_IN);
	asc_init(ASC0, 0);
#endif
	ASC0->asc_tbuf = '!';	/* FIXME - kick out a character */
	for (;;)
		monitor("mon> ");
}

/* writechar function for monitor */
void writechar(int c)
{
	if ( c == '\n' )
		asc_polled_putc(ASC0, '\r');
	asc_polled_putc(ASC0, c);
}

/*
 *	init_cpu() - intialise the CPU
 *
 *	This function initialises those parts of the CPU that have not already been
 *	initialised by the assembler code in rom-entry. This function is called before
 *	the bss and data sections are initialised, because the RAM may not be visible
 *	until the initialisation done here.
 *
 *	On Tricore we can intialise almost everything - except the SDRAM controller
 *	and the context management systems.
 *
 *	Assumptions: interrupts are disabled globally. ENDINIT is clear.
*/
void init_cpu(void)
{
	/*	Initialise the BCU and EBU
	*/
	BCU->bcu_bcucon = INIT_BCUCON;
	EBU->ebu_ebucon = INIT_EBUCON;

	/*	We only initialise the chip selects that have address ranges defined.
	*/
#if defined(INIT_ADDSEL0) && defined(INIT_BUSCON0)
	EBU->ebu_addsel0 = INIT_ADDSEL0;
	EBU->ebu_buscon0 = INIT_BUSCON0;
#endif
#if defined(INIT_ADDSEL1) && defined(INIT_BUSCON1)
	EBU->ebu_addsel1 = INIT_ADDSEL1;
	EBU->ebu_buscon1 = INIT_BUSCON1;
#endif
#if defined(INIT_ADDSEL2) && defined(INIT_BUSCON2)
	EBU->ebu_addsel2 = INIT_ADDSEL2;
	EBU->ebu_buscon2 = INIT_BUSCON2;
#endif
#if defined(INIT_ADDSEL3) && defined(INIT_BUSCON3)
	EBU->ebu_addsel3 = INIT_ADDSEL3;
	EBU->ebu_buscon3 = INIT_BUSCON3;
#endif

	/*	From here we can assume that all external memory and I/O is visible
	 *	on the bus.
	 *	Now we must set the ENDINIT flag. This must be done very shortly after
	 *	reset, otherwise the CPU resets itself.
	 *	Before doing this, we write the watchdog disable bit into WDTCON1,
	 *	since this only takes effect when WDTCON0 is unlocked and relocked,
	 *	and this happens while setting ENDINIT.
	*/
#if 0	/* Done in rom_entry */
	PWR->pwr_wdtcon1 |= WDTDR;
	set_endinit(1);
#endif

	/*	We set the CPU clock frequency here. This function should be called with
	 *	ENDINIT set, since it manipulates ENDINIT as required.
	*/
	cpu_clock_rate(CLOCK_RATE);

	/*	Now we're running at full speed, we can zero the bss section and
	 *	copy the ROM image of the data section out to RAM
	*/
	clear_bss();
	copy_data();
}

/*
 *	clear_bss() - sets the whole bss section to zero, as expected by C programs
 *
 *	This function is called from the assembler-code startup function. It cannot
 *	assume that any global variables contain the expected values. In addition,
 *	it cannot make use of any uninitialised (bss) global variables.
 *
 *	In practice, it only uses local (automatic) variables, and on Tricore, we can
 *	fairly safely assume that these will be in registers.
 *
 *	Assumptions: the bss section is word aligned and is a whole number of words long.
*/

void clear_bss(void)
{
	uint32_t *p = (uint32_t *)bss_start;

	while ( p < bss_end )
		*p++ = 0;
}

/*
 *	copy_data() - copies the ROM image of the data section to the proper place in RAM
 *
 *	This function is called from the assembler-code startup function. It can assume
 *	that bss is zeroed (if BOOT_CLEAR_BSS is defined). It cannot make use of any
 *	initialised (data) global variables.
 *	
 *	In practice, it only uses local (automatic) variables, and on Tricore, we can
 *	fairly safely assume that these will be in registers.
 *
 *	Assumptions: the data section is word aligned and is a whole number of words long.
*/

void copy_data(void)
{
	uint32_t *p, *q;

	p = (uint32_t *)data_start;
	q = (uint32_t *)data_image;

	while ( p < data_end )
		*p++ = *q++;
}
