COMPILE ?= ${CROSS_COMPILE}gcc -Wformat=0
CLEAN ?= rm -rf
CFLAG ?= -DTEST_NOLOCK_LOOP_QUEUE
INCLUDE = ${PRIVATELIB}/
test:bin/test
	ln -f bin/test -s test
fifo:lib/fifo.a
bin/test:object/fifo.o object/moak_nolock_loop_queue.o object/main.o
	${COMPILE} ${CFLAG} -o $@  $^ -lpthread
object/fifo.o:source/fifo.c
	${COMPILE} ${CFLAG} -o $@ -c $^ -I${INCLUDE}
object/moak_nolock_loop_queue.o:source/moak_nolock_loop_queue.c
	${COMPILE} ${CFLAG} -o $@ -c $^ -I${INCLUDE}
object/main.o:source/main.c
	${COMPILE} ${CFLAG} -o $@ -c $^ -I${INCLUDE}
clean:
	${CLEAN} bin/* object/*