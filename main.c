// Standard Library Includes
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Custom includes
#include "p_queue.h"

#define TEST_SUCCESS 0
#define TEST_FAILURE -1

#define N_TESTS 10

typedef struct {
	char name[100];
	int (*test)(void);
} test_case;

test_case test[N_TESTS];

int test_basic(void);
int test_enqueue_full(void);
int test_dequeue_empty(void);
int test_cycle(void);
int test_reverse(void);
int test_full_flush_all(void);
int test_move_priority_basic(void);
int test_move_priority_full(void);
int test_move_all_bad(void);
int test_move_interleave(void);

void init_tests();

int main(int argc, char** argv) {
	int i;
	int num_passed = 0;

	init_tests();

	printf("\nRunning DanglOS p_queue Test Suite\n\n");

	for (i = 0; i < N_TESTS; i++) {
		
		char* pass = "PASS\0";
		char* fail = "FAIL\0";
		char* result = NULL;

		if (test[i].test() == TEST_SUCCESS) {
			result = pass;
			num_passed++;
		} else {
			result = fail;
		}
		
		printf("\t[%s] - %s\n", result, (test[i].name));
	
	}
	printf("\nPassed %d of %d tests.\n\n", num_passed, N_TESTS);
	return 0;
}

void init_tests() {
	strcpy(test[0].name, "test_basic - enqueue/dequeue\0");
	test[0].test = test_basic;

	strcpy(test[1].name, "test_enqueue_full - enqueue into a full queue\0");
	test[1].test = test_enqueue_full;

	strcpy(test[2].name, "test_dequeue_empty - dequeue from an empty queue\0");
	test[2].test = test_dequeue_empty;

	strcpy(test[3].name, "test_cycle - fill, dequeue half of the total elements and refill\0");
	test[3].test = test_cycle;

	strcpy(test[4].name, "test_reverse - insert elements in reverse order of priority\0");
	test[4].test = test_reverse;

	strcpy(test[5].name, "test_full_flush_all - fill and empty every priority level, twice\0");
	test[5].test = test_full_flush_all;	

	strcpy(test[6].name, "test_move_priority_basic - create an item and move it to each priority\0");
	test[6].test = test_move_priority_basic;

	strcpy(test[7].name, "test_move_priority_full - fill a priority level and move all of its elements to another priority\0");
	test[7].test = test_move_priority_full;

	strcpy(test[8].name, "test_move_all_bad - try to move elements that don't exist\0");
	test[8].test = test_move_all_bad;

	strcpy(test[9].name, "test_move_interleave - interleave elements by alternating moves and enqueues\0");
	test[9].test = test_move_interleave;

}

int test_basic(void) {
	int i;
	p_queue pq;
	pq_init(&pq);

	pq_enqueue(&pq, 0, HIGH);
	pq_enqueue(&pq, 1, MED);
	pq_enqueue(&pq, 2, LOW);
	pq_enqueue(&pq, 3, LOWEST);

	for (i = 0; i < 4; i++) {
		if (pq_front(&pq) != i) {
			return TEST_FAILURE;
		}
		if (pq_dequeue(&pq) != PQ_SUCCESS) {
			return TEST_FAILURE;
		}
	}
	return TEST_SUCCESS;
}

int test_enqueue_full(void) {
	int i;
	p_queue pq;
	pq_init(&pq);

	for (i = 0; i < N_ELEMS; i++) {
		if (pq_enqueue(&pq, i, LOWEST) == PQ_FAILURE) {
			return TEST_FAILURE;
		}
	}

	if (pq_enqueue(&pq, 10, HIGH) == PQ_SUCCESS) {
		return TEST_FAILURE;
	}

	for (i = 0; i < N_ELEMS; i++) {
		
		if (pq_front(&pq) != i) {
			return TEST_FAILURE;
		}
		if (pq_dequeue(&pq) != PQ_SUCCESS) {
			return TEST_FAILURE;
		}
	}
	
	return TEST_SUCCESS;
}

int test_dequeue_empty(void) {
	p_queue pq;
	pq_init(&pq);
	if (pq_dequeue(&pq) == PQ_SUCCESS) return TEST_FAILURE;
	return TEST_SUCCESS; 
}

int test_cycle(void) {
	int i;
	int limit = N_ELEMS / 2;
	p_queue pq;
	pq_init(&pq);

	for (i = 0; i < N_ELEMS; i++) {
		if (pq_enqueue(&pq, i, HIGH) == PQ_FAILURE) {
			return TEST_FAILURE;
		}
	} 

	for (i = 0; i < limit; i++) {
		
		if (pq_front(&pq) != i) {
			return TEST_FAILURE;
		}
		if (pq_dequeue(&pq) != PQ_SUCCESS) {
			return TEST_FAILURE;
		}
	}

	for (i = N_ELEMS; i < N_ELEMS + limit; i++) {
		if (pq_enqueue(&pq, i, HIGH) == PQ_FAILURE) {
			return TEST_FAILURE;
		}
	}

	for (i = 0; i < N_ELEMS; i++) {
		
		if (pq_front(&pq) != i + limit) {
			return TEST_FAILURE;
		}
		if (pq_dequeue(&pq) != PQ_SUCCESS) {
			return TEST_FAILURE;
		}
	}
	
	return TEST_SUCCESS;
}

int test_reverse(void) {
	int i;
	p_queue pq;
	pq_init(&pq);

	pq_enqueue(&pq, 0, LOWEST);
	pq_enqueue(&pq, 1, LOW);
	pq_enqueue(&pq, 2, MED);
	pq_enqueue(&pq, 3, HIGH);

	for (i = 3; i >= 0; i--) {
		if (pq_front(&pq) != i) {
			return TEST_FAILURE;
		}
		if (pq_dequeue(&pq) != PQ_SUCCESS) {
			return TEST_FAILURE;
		}
	}
	return TEST_SUCCESS;
}

int test_full_flush_all(void) {
	int i;
	priority p;
	p_queue pq;
	pq_init(&pq);

	for (p = HIGH; p < N_PRIORITIES; p++) {
		for (i = 0; i < N_ELEMS; i++) {
			if (pq_enqueue(&pq, i, p) == PQ_FAILURE) {
				return TEST_FAILURE;
			}
		}

		for (i = 0; i < N_ELEMS; i++) {
			
			if (pq_front(&pq) != i) {
				return TEST_FAILURE;
			}
			if (pq_dequeue(&pq) != PQ_SUCCESS) {
				return TEST_FAILURE;
			}
		}
	}

	for (p = LOWEST; p != HIGH - 1; p--) {
		for (i = 0; i < N_ELEMS; i++) {
			if (pq_enqueue(&pq, i, p) == PQ_FAILURE) {
				return TEST_FAILURE;
			}
		}
		for (i = 0; i < N_ELEMS; i++) {
			if (pq_front(&pq) != i) {
				return TEST_FAILURE;
			}
			if (pq_dequeue(&pq) != PQ_SUCCESS) {
				return TEST_FAILURE;
			}
		}
	}

	return TEST_SUCCESS;
}

int test_move_priority_basic(void) {
	int i;
	p_queue pq;
	pq_init(&pq);

	pq_enqueue(&pq, 0, HIGH);
	if (pq_front(&pq) != 0) {
		return TEST_FAILURE;
	}
	if (pq_move( &pq, 0, HIGH, MED ) != PQ_SUCCESS) return TEST_FAILURE;
	if (pq_front(&pq) != 0) {
		return TEST_FAILURE;
	}
	if (pq_move( &pq, 0, MED, LOW ) != PQ_SUCCESS) return TEST_FAILURE;
	if (pq_front(&pq) != 0) {
		return TEST_FAILURE;
	}
	if (pq_move( &pq, 0, LOW, LOWEST ) != PQ_SUCCESS) return TEST_FAILURE;
	if (pq_front(&pq) != 0) {
		return TEST_FAILURE;
	}
	return TEST_SUCCESS;
}

int test_move_priority_full(void) {
	int i;
	p_queue pq;
	pq_init(&pq);

	for (i = 0; i < N_ELEMS; i++) {
		if (pq_enqueue(&pq, i, HIGH) == PQ_FAILURE) {
			return TEST_FAILURE;
		}
	}
	for (i = 0; i < N_ELEMS; i++) {
		if (pq_front(&pq) != i) {
			return TEST_FAILURE;
		}
		if (pq_move( &pq, i, HIGH, LOWEST ) != PQ_SUCCESS) {
			return TEST_FAILURE;
		}
	}
	for (i = 0; i < N_ELEMS; i++) {
		
		if (pq_front(&pq) != i) {
			return TEST_FAILURE;
		}
		if (pq_dequeue(&pq) != PQ_SUCCESS) {
			return TEST_FAILURE;
		}
	}
	return TEST_SUCCESS;
	
}

int test_move_all_bad(void) {
	p_queue pq;
	pq_init(&pq);
	if (pq_move( &pq, 10, HIGH, LOWEST ) == PQ_SUCCESS) {
		return TEST_FAILURE;
	}
	pq_enqueue(&pq, 10, HIGH);
	if (pq_move( &pq, 10, MED, LOWEST ) == PQ_SUCCESS) {
		return TEST_FAILURE;
	}
	if (pq_move( &pq, 4, HIGH, LOWEST ) == PQ_SUCCESS) {
		return TEST_FAILURE;
	}
	return TEST_SUCCESS;
}


int test_move_interleave(void) {
	int i;
	p_queue pq;
	pq_init(&pq);

	for (i = 0; i < N_ELEMS; i += 2) {
		if (pq_enqueue(&pq, i, LOWEST) == PQ_FAILURE) {
			return TEST_FAILURE;
		}
	}

	for (i = 0; i < N_ELEMS; i += 2) {
		pq_move(&pq, i, LOWEST, HIGH);
		pq_enqueue(&pq, i + 1, HIGH);
	}

	for (i = 0; i < N_ELEMS; i++) {
		
		if (pq_front(&pq) != i) {
			return TEST_FAILURE;
		}
		if (pq_dequeue(&pq) != PQ_SUCCESS) {
			return TEST_FAILURE;
		}
	}
	
	return TEST_SUCCESS;
}

