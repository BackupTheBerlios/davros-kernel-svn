/*	queue.h - header file for davros queues
 *
 *	Copyright 2008 David Haworth
 *
 *	This file is part of davros.
 *
 *	davros is free software: you can redistribute it and/or modify
 *	it under the terms of the GNU General Public License as published by
 *	the Free Software Foundation, either version 3 of the License, or
 *	(at your option) any later version.
 *
 *	davros is distributed in the hope that it will be useful,
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *	GNU General Public License for more details.
 *
 *	You should have received a copy of the GNU General Public License
 *	along with davros.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef __dv_queue_h
#define __dv_queue_h

#ifdef __DV_IDENT
__DV_IDENT("$Id$")
#endif

#include <davros/cpu-characteristics.h>
#include <davros/object.h>

/* __dv_qkey_t is nearly always unsigned 32-bit because it is used
 * for timing in delta-queues. However, we still permit family-specific override.
*/
#ifndef __DV_QKEY_T
#define __DV_QKEY_T			__dv_uint32_t
#define __DV_MAX_QKEY		0xffffffff
#define __DV_SIZEOF_QKEY	4
#endif

#ifndef __DV_ASM

/* Queue and queue-entry types.
*/
typedef __DV_QKEY_T __dv_qkey_t;
typedef	struct __dv_qent_s __dv_qent_t;
typedef	struct __dv_queue_s __dv_queue_t;

struct __dv_qent_s
{
	__dv_qent_t *next;		/* pointer to next element in queue, or tail */
	__dv_qent_t *prev;		/* pointer to previous element in queue, or head */
	__dv_obj_t *object;		/* pointer to the object associated with this entry */
	__dv_qkey_t	key;		/* key on which the queue is ordered */
};

struct __dv_queue_s
{
	__dv_qent_t head;		/* head of queue */
	__dv_qent_t tail;		/* tail of queue */
};

/* Prototypes for queue management functions
*/
__dv_qent_t *__dv_dequeue(__dv_qent_t *);
__dv_qent_t *__dv_dequeued(__dv_qent_t *);
__dv_qent_t *__dv_enqueue(__dv_qent_t *, __dv_queue_t *);
__dv_status_t __dv_insert(__dv_qent_t *, __dv_queue_t *, __dv_qkey_t);
__dv_status_t __dv_insertd(__dv_qent_t *, __dv_queue_t *, __dv_qkey_t);

#define __dv_initqueue(q) \
do {								\
	(q)->head.next = &(q)->tail;	\
	(q)->head.prev = __DV_NULL;		\
	(q)->head.object = __DV_NULL;	\
	(q)->head.key = 0;				\
	(q)->tail.next = __DV_NULL;		\
	(q)->tail.prev = &(q)->head;	\
	(q)->tail.object = __DV_NULL;	\
	(q)->tail.key = __DV_MAX_QKEY;	\
} while(0)

#define __dv_initqent(qe, obj) \
do {						\
	(qe)->next = __DV_NULL;	\
	(qe)->prev = __DV_NULL;	\
	(qe)->key = 0;			\
	(qe)->object = obj;		\
} while(0)
	

#endif

#define __DV_SIZEOF_QENT	(__DV_SIZEOF_PTR*3+__DV_SIZEOF_QKEY)

#endif
