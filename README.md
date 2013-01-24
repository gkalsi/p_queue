p_queue
=======
### DanglOS Priority Queue ###

Building Running and Testing
----------------------------
To build the test harness, run
```
make
```
To run the tests in the compiled test harness, run
```
./p_queue
```
To make the test harness and run the accompanying tests, run
```
make test
```

Library Usage
-------------
### Configurable Defines ###
The following defines can be used to configure the library prior to use
```
#define N_ELEMS    	6		 /* Global Max number of elements in a priority queue */
#define QUEUE_TYPE 	<Type T> /* Data type of Queue elements */
#define QUEUE_GUARD -1		 /* Item of Type T, returned when pq_front is called on an empty queue */
```
### API ###
By default priorities are stored in a priority enum
```
typedef enum {
	HIGH 	= 0,
	MED		= 1,
	LOW 	= 2,
	LOWEST	= 3,
	N_PRIORITIES = 4
} priority;
```
The following four methods are defined to interact with a priority queue
```
void pq_init( p_queue* pq );	/* Call before using the PQ */

/* enqueue and dequeue return PQ_SUCCESS and PQ_FAILURE on success and failure respectively */
int pq_enqueue( p_queue* pq, QUEUE_TYPE val, priority p );	/* add an element with the given priority */
int pq_dequeue( p_queue* pq );								/* Remove the highest priority elem from the pq */

QUEUE_TYPE pq_front( p_queue* pq );	/* Return the higest priority elem from the pq */ 
```
### Example ###
#### Simple Example ####
```c
#include <stdio.h>
#include "p_queue.h"

int main( int argc, char** argv )
{
	p_queue pq;
	pq_init(&pq);

	pq_enqueue(&pq, 1, LOW);
	pq_enqueue(&pq, 2, MED);
	pq_enqueue(&pq, 3, HIGH);
	
	int front = pq_front(&pq);
	printf("%d\n", front);		/* Prints 3 */

	pq_dequeue(&pq);

	return 0;
}
```
#### More Complex Examples ####
More complex examples (error checking, etc) can be found in main.c
