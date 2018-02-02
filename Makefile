COMPILE ?= ${CROSS_COMPILE}gcc -Wformat=0
FUNCTION ?= test
RM ?= rm -rf
OBJECTS += object/fifo.o object/moak_nolock_loop_queue.o object/main.o
INCLUDE = include
${FUNCTION}:${OBJECTS}
	${COMPILE} ${CFLAG} -o $@  $^ -lpthread
${OBJECTS}:source/fifo.c source/moak_nolock_loop_queue.c source/main.c
	${COMPILE} ${CFLAG} -o object/main.o -c source/main.c -I${INCLUDE}
	${COMPILE} ${CFLAG} -o object/fifo.o -c source/fifo.c -I${INCLUDE}
	${COMPILE} ${CFLAG} -o object/moak_nolock_loop_queue.o -c source/moak_nolock_loop_queue.c -I${INCLUDE}
clean:
	${RM} ${OBJECTS} ${FUNCTION}