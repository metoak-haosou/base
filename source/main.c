/*
 ============================================================================
 Name        : fifo.c
 Author      : wj
 Version     :
 Copyright   : 
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include "moak_nolock_loop_queue.h"
#include "fifo.h"
#include "stack.h"

#define TEST
#ifdef TEST_FIFO
#define TEST_FIFO_CREATE
#define TEST_FIFO_PUT
#define TEST_FIFO_GET
#endif

static void
main_nolock_loop_queue (void);
static void
main_fifo (void);
static void
main_stack (void);

int
main (int argc, char **argv)
{
#ifdef TEST_STACK
  main_stack();
#endif
#ifdef TEST_FIFO
  main_fifo();
#endif
#ifdef TEST_NOLOCK_LOOP_QUEUE
  main_nolock_loop_queue();
#endif
  printf ("\tEND TEST\n*****************\n");
  return 0;
}

#ifdef TEST_STACK
static void
main_stack (void)
{
  stack_t* stackP;
  int i;
  printf ("\tTEST STACK\n");
  printf ("\tTEST STACK CREATE 0\n");
  stackP = stack_create (0);
  printf ("size 0:stackP = 0x%x\n", stackP);
  free (stackP);
  printf ("\tTEST STACK CREATE 1\n");
  stackP = stack_create (1);
  printf ("size 0:stackP = 0x%x\n", stackP);
  free (stackP);
  printf ("\tTEST STACK PUT\n");
  stackP = stack_create (10);
  for (i = 0; i < 10 * 2; i++)
    {
      if (SUCCESE != stack_put (stackP, (void*)i))
	{
	  printf ("\n");
	}
      printf ("%d\t", i);
    }
  printf ("\n");
  for (i = 0; i < 10 * 2; i++)
    {
      printf ("%d\t", (int)stack_get (stackP));
    }
  printf ("\n");
}
#endif

#ifdef TEST_FIFO
static void
main_fifo (void)
  {
    err_t ret;
    void* testP;
    fifo_t* fifoP;
#ifdef TEST_FIFO_CREATE
    printf ("\tTEST FIFO CREATE\n");
    fifoP = fifo_create (0);
    printf ("1、size=0,fifoP=0x%x\n", fifoP);
    fifo_destroy (fifoP);
    fifoP = fifo_create (1);
    printf ("2、size=1,fifoP = 0x%x\n", fifoP);
    fifo_destroy (fifoP);
    fifoP = fifo_create (2);
    printf ("3、size=2,fifoP = 0x%x\n", fifoP);
    fifo_destroy (fifoP);
#endif

#ifdef TEST_FIFO_PUT
    printf ("\tTEST FIFO PUT\n");
    fifoP = fifo_create (1);
    printf ("size = 1\n");
    ret = fifo_put (fifoP, fifoP);
    printf ("1.1、ret = %s\n", !ret ? "TRUE" : "FALSE");
    ret = fifo_put (fifoP, fifoP);
    printf ("1.2、ret = %s\n", !ret ? "TRUE" : "FALSE");
    ret = fifo_put (fifoP, fifoP);
    printf ("1.3、ret = %s\n", !ret ? "TRUE" : "FALSE");
    ret = fifo_put (fifoP, fifoP);
    printf ("1.4、ret = %s\n", !ret ? "TRUE" : "FALSE");
    fifo_destroy (fifoP);

    fifoP = fifo_create (2);
    printf ("size = 2\n");
    ret = fifo_put (fifoP, fifoP);
    printf ("2.1、ret = %s\n", !ret ? "TRUE" : "FALSE");
    ret = fifo_put (fifoP, fifoP);
    printf ("2.2、ret = %s\n", !ret ? "TRUE" : "FALSE");
    ret = fifo_put (fifoP, fifoP);
    printf ("2.3、ret = %s\n", !ret ? "TRUE" : "FALSE");
    ret = fifo_put (fifoP, fifoP);
    printf ("2.4、ret = %s\n", !ret ? "TRUE" : "FALSE");
    fifo_destroy (fifoP);

    fifoP = fifo_create (3);
    printf ("size = 3\n");
    ret = fifo_put (fifoP, fifoP);
    printf ("3.1、ret = %s\n", !ret ? "TRUE" : "FALSE");
    ret = fifo_put (fifoP, fifoP);
    printf ("3.2、ret = %s\n", !ret ? "TRUE" : "FALSE");
    ret = fifo_put (fifoP, fifoP);
    printf ("3.3、ret = %s\n", !ret ? "TRUE" : "FALSE");
    ret = fifo_put (fifoP, fifoP);
    printf ("3.4、ret = %s\n", !ret ? "TRUE" : "FALSE");
    fifo_destroy (fifoP);

    fifoP = fifo_create (4);
    printf ("size = 4\n");
    ret = fifo_put (fifoP, fifoP);
    printf ("4.1、ret = %s\n", !ret ? "TRUE" : "FALSE");
    ret = fifo_put (fifoP, fifoP);
    printf ("4.2、ret = %s\n", !ret ? "TRUE" : "FALSE");
    ret = fifo_put (fifoP, fifoP);
    printf ("4.3、ret = %s\n", !ret ? "TRUE" : "FALSE");
    ret = fifo_put (fifoP, fifoP);
    printf ("4.4、ret = %s\n", !ret ? "TRUE" : "FALSE");
    fifo_destroy (fifoP);

    fifoP = fifo_create (5);
    printf ("size = 5\n");
    ret = fifo_put (fifoP, fifoP);
    printf ("5.1、ret = %s\n", !ret ? "TRUE" : "FALSE");
    ret = fifo_put (fifoP, fifoP);
    printf ("5.2、ret = %s\n", !ret ? "TRUE" : "FALSE");
    ret = fifo_put (fifoP, fifoP);
    printf ("5.3、ret = %s\n", !ret ? "TRUE" : "FALSE");
    ret = fifo_put (fifoP, fifoP);
    printf ("5.4、ret = %s\n", !ret ? "TRUE" : "FALSE");
    fifo_destroy (fifoP);

#endif

#ifdef TEST_FIFO_GET
    printf ("\tTEST FIFO GET\n");
    fifoP = fifo_create (10);
    printf ("fifoP = 0x%x\n", fifoP);
    printf ("put 0\n");
    testP = fifo_get (fifoP);
    printf ("currentSize = %d,testP = 0x%x\n", fifo_current_size(fifoP), testP);
    testP = fifo_get (fifoP);
    printf ("currentSize = %d,testP = 0x%x\n", fifo_current_size(fifoP), testP);
    testP = fifo_get (fifoP);
    printf ("currentSize = %d,testP = 0x%x\n", fifo_current_size(fifoP), testP);

    printf ("put 1\n");
    fifo_put (fifoP, fifoP);
    testP = fifo_get (fifoP);
    printf ("currentSize = %d,testP = 0x%x\n", fifo_current_size(fifoP), testP);
    testP = fifo_get (fifoP);
    printf ("currentSize = %d,testP = 0x%x\n", fifo_current_size(fifoP), testP);
    testP = fifo_get (fifoP);
    printf ("currentSize = %d,testP = 0x%x\n", fifo_current_size(fifoP), testP);

    printf ("put 2\n");
    fifo_put (fifoP, fifoP);
    fifo_put (fifoP, fifoP);
    testP = fifo_get (fifoP);
    printf ("currentSize = %d,testP = 0x%x\n", fifo_current_size(fifoP), testP);
    testP = fifo_get (fifoP);
    printf ("currentSize = %d,testP = 0x%x\n", fifo_current_size(fifoP), testP);
    testP = fifo_get (fifoP);
    printf ("currentSize = %d,testP = 0x%x\n", fifo_current_size(fifoP), testP);

    printf ("put 3\n");
    fifo_put (fifoP, fifoP);
    fifo_put (fifoP, fifoP);
    fifo_put (fifoP, fifoP);
    testP = fifo_get (fifoP);
    printf ("currentSize = %d,testP = 0x%x\n", fifo_current_size(fifoP), testP);
    testP = fifo_get (fifoP);
    printf ("currentSize = %d,testP = 0x%x\n", fifo_current_size(fifoP), testP);
    testP = fifo_get (fifoP);
    printf ("currentSize = %d,testP = 0x%x\n", fifo_current_size(fifoP), testP);

    printf ("put 4\n");
    fifo_put (fifoP, fifoP);
    fifo_put (fifoP, fifoP);
    fifo_put (fifoP, fifoP);
    fifo_put (fifoP, fifoP);
    testP = fifo_get (fifoP);
    printf ("currentSize = %d,testP = 0x%x\n", fifo_current_size(fifoP), testP);
    testP = fifo_get (fifoP);
    printf ("currentSize = %d,testP = 0x%x\n", fifo_current_size(fifoP), testP);
    testP = fifo_get (fifoP);
    printf ("currentSize = %d,testP = 0x%x\n", fifo_current_size(fifoP), testP);

    fifo_destroy (fifoP);
#endif
  }
#endif

#ifdef TEST_NOLOCK_LOOP_QUEUE
static void* reader_handler(void* arg)
  {
    nolock_loop_queue_t* nolockLoopQueueP = (nolock_loop_queue_t*)arg;
    void* data = NULL;
    while(1)
      {
	data = nolock_loop_queue_read(nolockLoopQueueP);
	if(NULL == data)
	  {
	    printf("reader wait...\n");
	    continue;
	  }
	printf("\tread data:\t%d\n",*(int *)data);
	usleep(30000);
      }
    return NULL;
  }
static void* writer_handler(void* arg)
  {
    int i = 0;
    nolock_loop_queue_t* nolockLoopQueueP = (nolock_loop_queue_t*)arg;
    void *data=NULL;
    while(1)
      {
	data = nolock_loop_queue_get_write(nolockLoopQueueP);
	if(!data)
	  {
	    printf("writer wait\n");
	    continue;
	  }
	memcpy(data,&i,4);
	i++;
	if(i%10==0)
	usleep(80000);
	nolock_loop_queue_done_write(nolockLoopQueueP);
	printf("write data:\t%d\n",*(int *)data);
	usleep(20000);
      }
    return NULL;
  }

static void main_nolock_loop_queue(void)
  {
    pthread_t writerFd,readerFd;
    //创建无锁循环队列
    nolock_loop_queue_t* nolockLoopQueueP = nolock_loop_queue_create(0xff,100);
    if(!nolockLoopQueueP)
      {
	printf("malloc failed\n");
      }
    printf("nolockLoopQueueP->ElementsNum = %d\n",nolockLoopQueueP->ElementsNum);
    //创建写线程
    pthread_create(&writerFd,NULL,writer_handler,nolockLoopQueueP);
    //创建读线程
    pthread_create(&readerFd,NULL,reader_handler,nolockLoopQueueP);
    while(1);
    //删除无锁循环队列
    nolock_loop_queue_destroy(nolockLoopQueueP);
  }
#endif
