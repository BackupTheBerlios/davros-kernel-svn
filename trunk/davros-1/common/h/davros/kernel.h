/* kernel.h - constants, macros, structures etc for Davros kernel
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
*/

#ifndef __davros_kernel_h
#define __davros_kernel_h

#include "davros/defines.h"

__DAVROS_IDENT("$Id$")

#define __DAVROS_OK      0
#define __DAVROS_SYSERR  (-1)

#include "arch-kernel.h"
#include "davros/types.h"

#ifndef __DAVROS_MAXINT
#define __DAVROS_MAXINT  0x7fffffff
#endif
#ifndef __DAVROS_MININT
#define __DAVROS_MININT  0x80000000
#endif
#ifndef __DAVROS_NULLSTACK
#define __DAVROS_NULLSTACK	1024
#endif
#ifndef __DAVROS_EXTRASTACK
#define __DAVROS_EXTRASTACK	0
#endif

/* process state constants */

#define __DAVROS_PRCURR		0x01	/* process is currently running			*/
#define __DAVROS_PRFREE		0x02	/* process slot is free					*/
#define __DAVROS_PRREADY	0x03	/* process is on ready queue			*/
#define __DAVROS_PRRECV		0x04	/* process is waiting for message		*/
#define __DAVROS_PRSLEEP	0x05	/* process is sleeping					*/
#define __DAVROS_PRSUSP		0x06	/* process is suspended					*/
#define __DAVROS_PRWAIT		0x07	/* process is on semaphore queue		*/
#define __DAVROS_BPSTOP		0x08	/* process hit a breakpoint				*/

/* miscellaneous process definitions */

#ifndef __DAVROS_PNMLEN
#define __DAVROS_PNMLEN	8		/* length of process name				*/
#endif

#ifndef __DAVROS_DVNMLEN
#define __DAVROS_DVNMLEN 8		/* length of device name				*/
#endif

/*	Function codes for device control function. */
#define __DAVROS_DVOPEN		1
#define __DAVROS_DVCLOSE	2
#define __DAVROS_DVNEXT		10	/*	First device-specific code */


#ifndef __ASSEMBLER__

/*	Kernel data structures. */

typedef struct __davros_qent		/* queue entry data structure			*/
{
	struct __davros_qent *next;		/* pointer to next entry or tail		*/
	struct __davros_qent *prev;		/* pointer to previous entry or head	*/
	union
	{
		__davros_qkey_t key;		/* key on which the queue is ordered	*/
		void *data;					/* pointer to data on queue				*/
	} kd;
} __davros_qent_t;

typedef struct __davros_queue		/* queue structure						*/
{
	__davros_qent_t head;			/* head of queue						*/
	__davros_qent_t tail;			/* tail of queue						*/
} __davros_queue_t;

typedef struct __davros_semaphore	/* semaphore data structure             */
{
	__davros_semcount_t count;		/* count for this semaphore             */
	__davros_queue_t queue;			/* queue of waiting processes			*/
} __davros_semaphore_t;

struct __davros_device;

typedef	int (*__davros_dvopen_t)(struct __davros_device *,char *,int);
typedef	int (*__davros_dvclose_t)(struct __davros_device *);
typedef	int (*__davros_dvread_t)(struct __davros_device *,uint8_t *,int);
typedef	int (*__davros_dvwrite_t)(struct __davros_device *,uint8_t *,int);
typedef	int (*__davros_dvgetc_t)(struct __davros_device *);
typedef	int (*__davros_dvputc_t)(struct __davros_device *,int);
typedef	int (*__davros_dvctrl_t)(struct __davros_device *,int,int);

typedef struct __davros_devsw		/* device switch table					*/
{
	__davros_dvopen_t dvopen;
	__davros_dvclose_t dvclose;
	__davros_dvread_t dvread;
	__davros_dvwrite_t dvwrite;
	__davros_dvgetc_t dvgetc;
	__davros_dvputc_t dvputc;
	__davros_dvctrl_t dvctrl;
} __davros_devsw_t;

typedef struct __davros_device	/* device data structure				*/
{
	__davros_qent_t devtab_entry;	/* device table entry					*/
	char name[__DAVROS_DVNMLEN];	/* device name							*/
    __davros_devsw_t *dvsw;			/* high level operations switch table	*/
} __davros_device_t;

typedef int (*__davros_procentry_t)(int, int *);

typedef struct __davros_process	/* process data structure				*/
{
	__davros_qent_t queue_entry;	/* queue entry, must be first!			*/
	__davros_qent_t proctab_entry;	/* process table entry					*/
	size_t alloc;					/* total number of bytes allocated		*/
    uint8_t state;					/* process state: PRCURR etc.			*/
    uint8_t priority;				/* process priority						*/
	size_t stacksize;				/* size of process' stack				*/
    __davros_semaphore_t *sem;		/* semaphore if process waiting			*/
    __davros_msg_t msg;				/* message sent to this process			*/
    boolean_t hasmsg;				/* non-zero iff pmsg is valid			*/
	__davros_procentry_t start;		/* entry point for process				*/
	int nargs;						/* no. of arguments						*/
	int *args;						/* array of arguments					*/
    __davros_device_t *dvstdin;		/* stdin for this process				*/
    __davros_device_t *dvstdout;	/* stdout for this process				*/
    __davros_device_t *dvstderr;	/* stderr for this process				*/
    char name[__DAVROS_PNMLEN];		/* process name							*/
	__arch_ctxtreg_t registers;		/* architecture-dependent registers		*/
} __davros_process_t;

typedef struct __davros_mblock	/* memory management structure			*/
{
	size_t len;						/* length of this block					*/
	struct __davros_mblock *next;	/* pointer to next block in free list	*/
} __davros_mblock_t;

#ifndef __DAVROS_MEMROUND
/*	Note: this only works if sizeof(__davros_mblock_t) is a power of 2 */
#define __DAVROS_MEMRND		(sizeof(__davros_mblock_t)-1)
#define __DAVROS_MEMROUND(l)	( ( l + __DAVROS_MEMRND ) & ~__DAVROS_MEMRND )
#endif

/* kernel data */

typedef struct __davros_data
{
	__davros_queue_t proctab;		/* list of all processes		*/
	__davros_queue_t readyqueue;	/* list of ready processes		*/
	__davros_queue_t sleepqueue;	/* list	of sleeping processes	*/
	__davros_process_t *currpid;	/* current process				*/
	int numproc;					/* no of processes				*/
	__davros_qkey_t *sleepcount;	/* addr. of	key	of 1st sleeper	*/
	boolean_t clkpres;				/* clock present flag			*/
	__davros_frc_t frc;				/* free-running counter			*/
	memaddr_t memtop;				/* address of top of memory		*/
	memaddr_t membot;				/* address of bottom of	memory	*/
	__davros_mblock_t memhead;		/* start of	free list			*/
	__davros_queue_t devtab;		/* list of all devices			*/
#ifdef __ARCH_KERNEL_DATA
	__ARCH_KERNEL_DATA;				/* architecture-specific data	*/
#endif
} __davros_data_t;

extern __davros_data_t __davros;

/* function prototypes (internal functions) */

__davros_status_t		__davros_initqueue(__davros_queue_t *);
__davros_qent_t *		__davros_enqueue(__davros_qent_t *,__davros_queue_t *);
__davros_qent_t *		__davros_dequeue(__davros_qent_t *);
__davros_qent_t *		__davros_dequeued(__davros_qent_t *);
__davros_status_t		__davros_insert(__davros_qent_t *,__davros_queue_t *,__davros_qkey_t);
__davros_status_t		__davros_insertd(__davros_qent_t *,__davros_queue_t *,__davros_qkey_t);

void *					__davros_getmem(size_t);
__davros_status_t		__davros_freemem(void *,size_t);

__davros_process_t *	__davros_getpid(void);
__davros_device_t *		__davros_getstdin(void);
__davros_device_t *		__davros_getstdout(void);
__davros_device_t *		__davros_getstderr(void);

__davros_process_t *	__davros_create(__davros_procentry_t,size_t,uint8_t,char *,
	                      __davros_device_t *,__davros_device_t *,__davros_device_t *,
	                      int,int *);
void					__davros_setstdio(__davros_process_t *,__davros_device_t *,__davros_device_t *,__davros_device_t *);
__davros_status_t		__davros_reschedule(void);
__davros_status_t		__davros_ready(__davros_process_t *,boolean_t);

__davros_status_t		__davros_sleep(int);
unsigned				__davros_isleep(int,unsigned);
__davros_status_t		__davros_unsleep(__davros_process_t *);
void					__davros_psleep(int);

__davros_status_t		__davros_suspend(__davros_process_t *);
__davros_status_t		__davros_resume(__davros_process_t *,boolean_t);
uint8_t					__davros_chprio(__davros_process_t *,uint8_t);
__davros_status_t		__davros_kill(__davros_process_t *);
void					__davros_exit(int exitcode);

__davros_status_t		__davros_send(__davros_process_t *,__davros_msg_t,boolean_t);
__davros_msg_t			__davros_receive(void);
__davros_msg_t			__davros_recvclr(void);

__davros_semaphore_t *	__davros_screate(int);
__davros_status_t		__davros_wait(__davros_semaphore_t *);
boolean_t				__davros_test(__davros_semaphore_t *);
__davros_status_t		__davros_signal(__davros_semaphore_t *,boolean_t);
__davros_semcount_t		__davros_scount(__davros_semaphore_t *);
__davros_semcount_t		__davros_sreset(__davros_semaphore_t *, __davros_semcount_t);
__davros_status_t		__davros_sdelete(__davros_semaphore_t *);

__davros_device_t *		__davros_dcreate(__davros_device_t *,char *, const __davros_devsw_t *);
__davros_device_t *		__davros_dfind(char *);
int						__davros_ioerr(void);
int						__davros_ionull(void);
__davros_device_t *		__davros_open(char *,int);
int						__davros_close(__davros_device_t *);
int						__davros_read(__davros_device_t *,uint8_t *,int);
int						__davros_write(__davros_device_t *,uint8_t *,int);
int						__davros_getc(__davros_device_t *);
int						__davros_putc(__davros_device_t *,int);
int						__davros_control(__davros_device_t *,int,int);
void *					__davros_getioblk(__davros_device_t *);

void					__davros_init(memaddr_t,memaddr_t);
void					__davros_initproc(__davros_process_t *);

void					__davros_tick(void);
void					__davros_wakeup(void);

/*	Supplied by architecture port, but declared here because they
 *	are required by davros, and because they use davros data types.
 *	Only declared if they aren't already defined as macros.
*/
#ifndef __arch_enterkernel
__arch_intstatus_t		__arch_enterkernel(void);
#endif
#ifndef __arch_leavekernel
__arch_intstatus_t		__arch_leavekernel(__arch_intstatus_t);
#endif
#ifndef __arch_enableinterrupts
__arch_intstatus_t		__arch_enableinterrupts(void);
#endif
#ifndef __arch_disableinterrupts
__arch_intstatus_t		__arch_disableinterrupts(void);
#endif
#ifndef __arch_restoreinterrupts
__arch_intstatus_t		__arch_restoreinterrupts(__arch_intstatus_t);
#endif
#ifndef __arch_kill
void					__arch_kill(__davros_process_t *);
#endif
void					__arch_ctxsw(__arch_ctxtreg_t *,__arch_ctxtreg_t *);
void					__arch_initproc(__davros_process_t *, memaddr_t);
void					__arch_setstack(memaddr_t);
void					__arch_initkernel(__davros_data_t *);
void					__arch_init(void);		/* Starts drivers */

/*	Supplied by user */
void					__user_init(void);		/* Starts application */
void					__user_nullproc(void);	/* Something for NULL to do. */

/*	Interrupt handling. This part might be implemented differently
 *	by the architecture port, but these are the "standard" functions
 *	and types:
*/
typedef void (*__davros_intfunc_t)(void *);
int __davros_attach_interrupt(int, __davros_intfunc_t, void *);
int __davros_detach_interrupt(int);
__davros_intfunc_t __davros_get_interrupt_handler(int inum);
void *__davros_get_interrupt_parameter(int inum);

/*	Kernel debugging */
#include "davros/kdebug.h"

#endif

#endif
