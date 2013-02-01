#ifndef __DANGLOS_PQUEUE__
#define __DANGLOS_PQUEUE__

#define N_ELEMS    	6	/* Total number of elements available in the PQ */

#define QUEUE_TYPE 	int /* We don't have templates, this is the type of element in the PQ */
#define PQ_NOT_FOUND -1	/* Return this if pq_front() is called on an empty queue */

/* Returned by enqueue and dequeue on successful and unsuccessful operations */
#define PQ_SUCCESS 0
#define PQ_FAILURE -1

typedef enum {
	HIGH 	= 0,
	MED		= 1,
	LOW 	= 2,
	LOWEST	= 3,
	N_PRIORITIES = 4	/* Not a real priority, used as a constant to represent the number of priorities */
} priority;

typedef struct {
	QUEUE_TYPE elems[N_ELEMS * N_PRIORITIES];	/* Queue memory */
	int start[N_PRIORITIES];	/* Index of the first element on the given priority */
	int length[N_PRIORITIES];	/* Index of the number of priorities of the given priority */
	int size;					/* Overall number of elements in the queue */
} p_queue;

void pq_init( p_queue* pq );	/* Call before using the PQ */

/* enqueue, dequeue and move return PQ_SUCCESS and PQ_FAILURE on success and failure respectively */
int pq_enqueue ( p_queue* pq, QUEUE_TYPE val, priority p );	/* add an element with the given priority */
int pq_dequeue ( p_queue* pq );								/* Remove the highest priority elem from the pq */
int pq_move    ( p_queue* pq, QUEUE_TYPE target, priority source, priority dest ); /* Move target item from source priority to dest priority */


QUEUE_TYPE pq_front( p_queue* pq );	/* Return the higest priority elem from the pq */ 

#endif /* __DANGLOS_PQUEUE__ */
