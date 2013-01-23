CPP = gcc
EXEC = p_queue
OBJECTS = p_queue.o

${EXEC} : ${OBJECTS} main.c
	${CPP} p_queue.o main.c -o ${EXEC}

p_queue.o : p_queue.c
	${CPP} -c p_queue.c

test: ${EXEC}
	./${EXEC}

clean:
	rm -fr ${OBJECTS}
	rm -fr ${EXEC}

