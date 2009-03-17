/*	i8250-tty-drv.c - i8250 tty driver for davros.
 *
 *	Copyright 2002 David Haworth
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
 *	This file contains definitions for the i8250 tty driver
 *
*/

#include "davros/kernel.h"
#include "drv/i8250-tty-drv.h"
#include "drv/i8250-drv.h"
#define __STDIO_PRIVATE
#include "stdio.h"

/*
 *	i8250_tty_create() - create a tty device for an i8250 UART
 *
 *	This function allocates the data structure for the device,
 *	then intialises it, calling the generic tty driver's initialisation
 *	function to intitialise the generic parts.
 *	Finally the interrupts service routines are connected, the i8250
 *	is initialised and the interrupts are enabled.
*/
__i8250_tty_drv_t *i8250_tty_create
(	char *name,
	memaddr_t _i8250,
	int _inum,
	int _imask
)
{
	__i8250_tty_drv_t *dev = __davros_getmem(sizeof(__i8250_tty_drv_t));
	if ( dev == NULL )
	{
		return NULL;
	}

	dev->i8250 = _i8250;
	dev->inum = _inum;
	dev->imask = _imask;
	dev->txrun = 0;

	if ( __davros_tty_create(&dev->tty, name) == NULL )
	{
		__davros_freemem(dev, sizeof(__i8250_tty_drv_t));
		return(NULL);
	}

	dev->tty.ospeed = 0;	/* ispeed & ospeed must be the same */
	dev->tty.hwctrl = i8250_tty_control;	/* my control function */

	i8250_init(dev->i8250);
	i8250_params(dev->i8250, dev->tty.params);
	i8250_baud(dev->i8250, dev->tty.ispeed);

	__davros_attach_interrupt(dev->inum, i8250_tty_interrupt, dev);

	/* FIXME: must be a better place for this */
	i8250_write(dev->i8250, i8250_mcr,
				I8250_MCR_DTR | I8250_MCR_RTS | I8250_MCR_OUT2);
	pic_enable_interrupts(dev->imask);

	return(dev);
}

/*
 *	i8250_tty_delete() - delete an i8250-tty device
 *
 *	This function shuts down the hardware and frees the data memory.
*/
void i8250_tty_delete(__i8250_tty_drv_t *dev)
{
	/* FIXME: to do */
}

/*
 *	i8250_tty_interrupt() - interrupt handler
 *
 *	Handles all interrupts 
*/
void i8250_tty_interrupt(void *_dev)
{
	__i8250_tty_drv_t *dev = (__i8250_tty_drv_t *)_dev;
	int iid;
	int c;


	iid = i8250_read(dev->i8250, i8250_iid);
	do
	{
		switch ( iid & I8250_IID_ID )
		{
		case I8250_IID_ID_MSTAT:		/* Clear and ignore */
			i8250_read(dev->i8250, i8250_msr);
			break;
			
		case I8250_IID_ID_SEOB:		/* Clear and ignore */
			i8250_read(dev->i8250, i8250_lsr);
			break;
			
		case I8250_IID_ID_THRE:
			c = __davros_tty_cout(&dev->tty);
			if ( c == __DAVROS_TTY_EOF )
			{
				dev->txrun = 0;
				i8250_write(dev->i8250, i8250_ier, I8250_IER_RDR);
			}
			else
			{
				dev->txrun = 1;
				i8250_write(dev->i8250, i8250_data, c);
			}
			break;

		case I8250_IID_ID_RBRF:
			c = i8250_read(dev->i8250, i8250_data);
			__davros_tty_cin(&dev->tty, c);
			break;
		}
		iid = i8250_read(dev->i8250, i8250_iid);
	} while ( (iid & I8250_IID_IP) == 0 );
}

/*
 *	i8250_tty_control() - hwctrl function for tty
 *
 *	This function updates the hardware with changes to the device
 *	settings.
*/
int i8250_tty_control(__davros_tty_t *_dev, int func, int param)
{
	__i8250_tty_drv_t *dev = (__i8250_tty_drv_t *)_dev;
	uint32_t ps;

	switch ( func )
	{
	case __DAVROS_TTY_SPEED_CHANGE:
		i8250_baud(dev->i8250, dev->tty.ispeed);
		break;

	case __DAVROS_TTY_PARAM_CHANGE:
		i8250_params(dev->i8250, dev->tty.params);
		break;

	case __DAVROS_TTY_KICKOUT_CHAR:
		ps = disable_interrupts();
		if ( dev->txrun == 0 )
		{
			int c = __davros_tty_cout(&dev->tty);
			if ( c != __DAVROS_TTY_EOF )
			{
				dev->txrun = 1;
				i8250_write(dev->i8250, i8250_ier, I8250_IER_RDR|I8250_IER_TBE);
				i8250_write(dev->i8250, i8250_data, c);
			}
		}
		restore_interrupts(ps);
		break;

	default:
		return(__DAVROS_SYSERR);
		break;
	}
	return(__DAVROS_OK);
}
