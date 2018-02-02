CC = ${CROSS_COMPILE}gcc -Wformat=0
AR = ${CROSS_COMPILE}ar
CLEAN = rm -rf
CFLAG = -DTEST_NOLOCK_LOOP_QUEUE
INCLUDE = ${PRIVATELIB}/
test:bin/test
	ln -f bin/test -s test
	
fifo:lib/fifo.a

lib/fifo.a:object/fifo.o
	${AR} -cr lib/fifo.a object/fifo.o

nolock_loop_queue:lib/nolock_loop_queue.a

lib/nolock_loop_queue.a:object/moak_nolock_loop_queue.o
	${AR} -cr lib/nolock_loop_queue.a object/moak_nolock_loop_queue.o

bin/test:object/fifo.o object/moak_nolock_loop_queue.o object/main.o
	${CC} ${CFLAG} -o $@  $^ -lpthread

object/fifo.o:source/fifo.c
	${CC} ${CFLAG} -o $@ -c $^ -I${INCLUDE}

object/moak_nolock_loop_queue.o:source/moak_nolock_loop_queue.c
	${CC} ${CFLAG} -o $@ -c $^ -I${INCLUDE}

object/main.o:source/main.c
	${CC} ${CFLAG} -o $@ -c $^ -I${INCLUDE}

clean:
	${CLEAN} bin/* object/* lib/*