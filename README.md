p_queue
=======
### DanglOS Priority Queue ###

Building Running and Testing
----------------------------
To compile the test harness, run
```bash
make
```
To run the tests in the compiled test harness, run
```bash
./p_queue
```
To compile the test harness and run the accompanying tests, run
```bash
make test
```

Library Usage
-------------
### Configurable Defines ###
The following defines can be used to configure the library prior to use
```c
#define N_ELEMS    	6		 /* Global Max number of elements in a priority queue */
#define QUEUE_TYPE 	<Type T> /* Data type of Queue elements */
#define PQ_NOT_FOUND -1		 /* Item of Type T, returned when pq_front is called on an empty queue */
```
### API ###
Priorities are defined in a priority enum
```c
typedef enum {
	HIGH 	= 0,
	MED		= 1,
	LOW 	= 2,
	LOWEST	= 3,
	N_PRIORITIES = 4
} priority;
```
The following four methods are defined to interact with a priority queue
```c
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
