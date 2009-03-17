/*	tty-drv.c - generic tty driver
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
 *	This file contains the generic tty driver for davros.
 *
*/

#include "davros/kernel.h"
#include "drv/tty.h"
#include "string.h"
#define __STDIO_PRIVATE
#include "stdio.h"

const __davros_devsw_t tty_dvsw =
{	__davros_tty_open,
	__davros_tty_close,
	__davros_tty_read,
	__davros_tty_write,
	__davros_tty_getc,
	__davros_tty_putc,
	__davros_tty_ctrl
};

/*
 *	__davros_tty_open() - open function for tty device
 *
 *	Nothing much to do really
*/
int __davros_tty_open(__davros_device_t *dev, char *name, int mode)
{
	return(__DAVROS_OK);
}

/*
 *	__davros_tty_close() - close function for tty device
 *
 *	Nothing much to do really
*/
int __davros_tty_close(__davros_device_t *dev)
{
	return(__DAVROS_OK);
}

/*
 *	__davros_tty_read() - read function for tty device
 *
 *	Read one or more characters from the device.
*/
int __davros_tty_read(__davros_device_t *dev, uint8_t *buf, int count)
{
	__davros_tty_t *tty = (__davros_tty_t *)dev;
	__arch_intstatus_t ps;
	int avail, nread;
	char *ilim;

	if ( count < 0 )
		return(__DAVROS_SYSERR);

	ps = __arch_enterkernel();

	avail = __davros_scount(tty->isem);
	if ( count == 0 )
		count = avail;
	nread = count;

	if ( count != 0 )
	{
		if ( avail > 0 )
		{
			ilim = tty->ibuff + __DAVROS_TTY_IBUFLEN;
			__davros_sreset(tty->isem, avail - count);
			if ( avail > count )
				avail = count;
			for ( ; avail > 0; avail-- )
			{
				*buf++ = *tty->itail++;
				if ( tty->itail >= ilim )
					tty->itail = tty->ibuff;
				count--;
			}
		}
		for ( ; count > 0; count-- )
			*buf++ = __davros_tty_getc(dev);
	}
	
	__arch_leavekernel(ps);
	return(nread);
}

/*
 *	__davros_tty_write() - write function for tty device
 *
 *	Write one or more characters to the device.
*/
int __davros_tty_write(__davros_device_t *dev, uint8_t *buf, int count)
{
	__davros_tty_t *tty = (__davros_tty_t *)dev;
	__arch_intstatus_t ps;
	int avail, nwrit;
	char c, *olim;

	if ( count < 0 )
		return(__DAVROS_SYSERR);
	if ( count == 0 )
		return(__DAVROS_OK);

	ps = __arch_enterkernel();

	avail = __davros_scount(tty->osem);

	nwrit = 0;
	if ( avail > 0 )
	{
		olim = tty->obuff + __DAVROS_TTY_OBUFLEN;
		for ( ; count > 0 && avail > 0; avail--, count-- )
		{
			c = *buf++;
#ifdef __DAVROS_TTY_COOKED
			if ( c == '\n' && (tty->mode & MODE_OMODE) == MODE_OMODE_COOKED
						   && (tty->mode & MODE_OCRLF) )
			{
				if ( avail >= 2 )
				{
					*tty->ohead++ = '\r';
					if ( tty->ohead >= olim )
						tty->ohead = tty->obuff;
				}
				avail--;
			}
			else
			{
				*tty->ohead++ = c;
				if ( tty->ohead >= olim )
					tty->ohead = tty->obuff;
				nwrit++;
			}
#else
			*tty->ohead++ = c;
			if ( tty->ohead >= olim )
				tty->ohead = tty->obuff;
			nwrit++;
#endif
		}
		__davros_sreset(tty->osem, avail);
		(*tty->hwctrl)(tty, __DAVROS_TTY_KICKOUT_CHAR, 0);
	}
	for ( ; count > 0; count-- )
	{
		__davros_tty_putc(dev, *buf++);
		nwrit++;
	}

	__arch_leavekernel(ps);
	return(nwrit);
}

/*
 *	__davros_tty_getc() - getc function for tty device
 *
 *	Read one character from the device.
*/
int __davros_tty_getc(__davros_device_t *dev)
{
	__davros_tty_t *tty = (__davros_tty_t *)dev;
	__arch_intstatus_t ps;
	int c;

	ps = __arch_enterkernel();

	__davros_wait(tty->isem);

	c = *tty->itail++;
	if ( tty->itail >= tty->ibuff + __DAVROS_TTY_IBUFLEN )
		tty->itail = tty->ibuff;

	__arch_leavekernel(ps);
	return(c);
}

/*
 *	__davros_tty_putc() - putc function for tty device
 *
 *	Write one character to the device.
*/
int __davros_tty_putc(__davros_device_t *dev, int c)
{
	__davros_tty_t *tty = (__davros_tty_t *)dev;
	__arch_intstatus_t ps;


#ifdef __DAVROS_TTY_COOKED
	if ( c == '\n' && (tty->mode & MODE_OMODE) == MODE_OMODE_COOKED
				   && (tty->mode & MODE_OCRLF) )
		__davros_tty_putc(dev, '\r');
#endif

	__davros_wait(tty->osem);
	ps = __arch_enterkernel();
	*tty->ohead++ = c;
	if ( tty->ohead >= tty->obuff + __DAVROS_TTY_OBUFLEN )
		tty->ohead = tty->obuff;
	(*tty->hwctrl)(tty, __DAVROS_TTY_KICKOUT_CHAR, c);
	__arch_leavekernel(ps);
	return(c);
}

/*
 *	__davros_tty_ctrl() - ctrl function for tty device
 *
 *	Perform one of several possible control actions.
 *	FIXME: much work is needed here!
*/
int __davros_tty_ctrl(__davros_device_t *dev, int func, int param)
{
	__davros_tty_t *tty = (__davros_tty_t *)dev;

	switch ( func )
	{
	case __DAVROS_TTYCTRL_SPEED:
		tty->ispeed = param;
		tty->hwctrl(tty, __DAVROS_TTY_SPEED_CHANGE, 0);
		break;

	case __DAVROS_TTYCTRL_PARAMS:
		strncpy(tty->params, (char *)param, 3);
		tty->params[3] = '\0';
		tty->hwctrl(tty, __DAVROS_TTY_PARAM_CHANGE, 0);
		break;

	default:
		return(__DAVROS_SYSERR);
		break;
	}

	return(__DAVROS_OK);
}

/*
 *	__davros_tty_create() - create function for tty device
 *
 *	This function initialises the given tty device structure. The
 *	structure will have been allocated by the hardware-specific
 *	driver.
*/
__davros_tty_t *__davros_tty_create(__davros_tty_t *tty, char *name)
{
	memset(tty, 0, sizeof(__davros_tty_t));
	tty->ihead = tty->ibuff;
	tty->itail = tty->ibuff;
	tty->isem = __davros_screate(0);
	tty->ohead = tty->obuff;
	tty->otail = tty->obuff;
	tty->osem = __davros_screate(__DAVROS_TTY_OBUFLEN);;
	strncpy(tty->params, __DAVROS_TTY_PARAMS, 3);
	tty->ispeed = __DAVROS_TTY_SPEED;
	tty->ospeed = __DAVROS_TTY_SPEED;
#ifdef __DAVROS_TTY_COOKED
	tty->ehead = tty->ebuff;
	tty->etail = tty->ebuff;
	tty->mode = 0;
	tty->ierasec = 0x03;	/* ctrl-C */
	tty->ikillc = 0x18;		/* ctrl-X */
	tty->xon = 0x11;		/* ctrl-Q */
	tty->xoff = 0x13;		/* ctrl-S */
#endif

	if ( tty->isem == NULL || tty->osem == NULL ||
		 __davros_dcreate(&tty->dev_head, name, &tty_dvsw) == NULL )
	{
		if ( tty->osem != NULL )
			__davros_sdelete(tty->osem);
		if ( tty->isem != NULL )
			__davros_sdelete(tty->isem);
		return(NULL);
	}
	return(tty);
}

/*
 *	__davros_tty_cin() - handle incoming character
 *
 *	This function handles an incoming character. It is normally
 *	called from the device-specific receive interrupt handler.
*/
void __davros_tty_cin(__davros_tty_t *tty, int c)
{
	if ( __davros_scount(tty->isem) >= __DAVROS_TTY_IBUFLEN )
	{
		/* Forget it! */
	}
	else
	{
		*tty->ihead++ = c;
		if ( tty->ihead >= (tty->ibuff + __DAVROS_TTY_IBUFLEN) )
			tty->ihead = tty->ibuff;
		__davros_signal(tty->isem, FALSE);
	}
}

/*
 *	__davros_tty_cout() - get outgoing character
 *
 *	This function gets the next outgoing character. It is normally
 *	called from the device-specific transmit interrupt handler.
*/
int __davros_tty_cout(__davros_tty_t *tty)
{
	int c;

	if ( __davros_scount(tty->osem) >= __DAVROS_TTY_OBUFLEN )
	{
		c = __DAVROS_TTY_EOF;
	}
	else
	{
		c = *tty->otail++;
		if ( tty->otail >= (tty->obuff + __DAVROS_TTY_OBUFLEN) )
			tty->otail = tty->obuff;
		__davros_signal(tty->osem, FALSE);
	}

	return(c);
}
