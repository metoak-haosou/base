CC = ${CROSS_COMPILE}gcc -Wformat=0
AR = ${CROSS_COMPILE}ar
CLEAN = rm -rf
CFLAG = -DTEST_NOLOCK_LOOP_QUEUE
INCLUDE = include
test:bin/test
	ln -f bin/test -s test
	
fifo:lib/libfifo.a
lib/libfifo.a:object/fifo.o
	${AR} -cr lib/libfifo.a object/fifo.o

nolock_loop_queue:lib/libnolock_loop_queue.a
lib/libnolock_loop_queue.a:object/moak_nolock_loop_queue.o
	${AR} -cr lib/libnolock_loop_queue.a object/moak_nolock_loop_queue.o
	
stack:lib/libstack.a
lib/libstack.a:object/stack.o
	${AR} -cr lib/libstack.a object/stack.o

bin/test:object/fifo.o object/moak_nolock_loop_queue.o object/main.o object/stack.o
	${CC} ${CFLAG} -o $@  $^ -lpthread

object/fifo.o:source/fifo.c
	${CC} ${CFLAG} -o $@ -c $^ -I${INCLUDE}

object/moak_nolock_loop_queue.o:source/moak_nolock_loop_queue.c
	${CC} ${CFLAG} -o $@ -c $^ -I${INCLUDE}

object/stack.o:source/stack.c
	${CC} ${CFLAG} -o $@ -c $^ -I${INCLUDE}

object/main.o:source/main.c
	${CC} ${CFLAG} -o $@ -c $^ -I${INCLUDE}

clean:
	${CLEAN} bin/* object/* lib/*