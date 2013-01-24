#include "p_queue.h"

/* 
 * computes the index of the nth element of the queue with priority p
 * use to access elements in the elem array
 */
int _pq_compute_offset( p_queue* pq, int n, priority p ) 
{
	int offset = pq->start[p] - ( p * N_ELEMS );
	offset += n;
	offset = offset % N_ELEMS;
	return offset + ( p * N_ELEMS );
}


/*
 * prepare a p_queue structure for use
 */
void pq_init(p_queue* pq) 
{
	
	int i = 0;
	pq->size = 0;


	for ( i = 0; i < N_PRIORITIES; i++ ) {
		pq->start[i]  = i * N_ELEMS; /* Each priority region in the array is N_ELEMS long */
		pq->length[i] = 0; 
	}

}


/*
 * add an element to the priority queue
 * returns PQ_FAILURE if the action was not successful (the queue was full)
 * returns PQ_SUCCESS otherwise
 */
int pq_enqueue(p_queue* pq, QUEUE_TYPE val, priority p) 
{
	
	if ( pq->size == N_ELEMS ) return PQ_FAILURE;

	/* Do some math here since the queue is circular */
	pq->elems[ _pq_compute_offset( pq, pq->length[p], p ) ] = val;
	
	/* Increment the size of this priority and the overall size */
	pq->length[p]++;
	pq->size++;

	return PQ_SUCCESS;
}


/*
 * removed the top element from the priority queue
 * returns PQ_FAILURE if the action was not successful (the queue was empty)
 * returns PQ_SUCCESS otherwise
 */
int pq_dequeue( p_queue* pq ) 
{
	int i;

	if ( pq->size == 0 ) return PQ_FAILURE;

	for ( i = 0; i < N_PRIORITIES; i++ ) {
		if (pq->length[i] != 0) {

			/* The valid region becomes smaller but the start location is incremented to 
			   drop the first element from the queue */
			pq->length[i]--;
			pq->start[i]++;
			
			/* calling _pq_compute_offset with an offset of 0 normalizes pq->start in case
			   it has increased beyond the valid region for this priority */
			pq->start[i] = _pq_compute_offset( pq, 0, i );
			pq->size--;
			return PQ_SUCCESS;
		}
	}
	return PQ_FAILURE;
}


/*
 * Returns the highest priority element from the priority queue
 * returns QUEUE_GUARD if the action was not successful (the queue was empty)
 */
QUEUE_TYPE pq_front(p_queue* pq) 
{
	int i;

	for ( i = 0 ; i < N_PRIORITIES; i++ ) {
		if (pq->length[i] != 0) {
			return pq->elems[ pq->start[i] ];
		}
	}

	return QUEUE_GUARD;
}

/*
void pq_print(p_queue* pq) {
	int i, j;
	printf("PQ Print:\n");
	for (i = 0; i < N_PRIORITIES; i++) {
		printf("P%d[%d-%d]: { ",i + 1, pq->start[i], pq->length[i]);
		for (j = 0; j < pq->length[i]; j++) {
			printf("%d ", pq->elems[_pq_compute_offset(pq, j, i)]);
		}
		printf("}\n");
	}
	printf("\n");
}
*/