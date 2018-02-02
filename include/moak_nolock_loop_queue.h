
/*
 * 当前版本不支持并发，最多只能由一个读者和一个写者
 * */
#ifndef __MOAK_NOLOCK_LOOP_QUEUE_INCLUDE__
#define __MOAK_NOLOCK_LOOP_QUEUE_INCLUDE__
#include "sys/err.h"
#include "sys/params.h"
typedef struct{
	u8 ReadPoint;
	u8 WritePoint;
	u8 ElementsNum;
	u16 ElementSize;
	void **Elements;//一个不定数量的指针数组
} nolock_loop_queue_t;

#define INCREASE_READ(p) ((p)->ReadPoint = ((p)->ReadPoint+1)%(p)->ElementsNum)
#define INCREASE_WRITE(p) ((p)->WritePoint = ((p)->WritePoint+1)%(p)->ElementsNum)
#define CHECK_FULL(p) (((p)->WritePoint+1)%(p)->ElementsNum == (p)->ReadPoint)
#define CHECK_FREE(p) ((p)->WritePoint == (p)->ReadPoint)
#define GET_READ_DATA(p) ((p)->Elements[(p)->ReadPoint])
#define SET_WRITE_DATA(p,Element) ((p)->Elements[(p)->WritePoint] = (Element))

//创建一个无锁循环队列
nolock_loop_queue_t* nolock_loop_queue_create(u8 ElementsNum,u16 ElementSize);
//出队该操作有可能失败,即r=w
void* nolock_loop_queue_read(nolock_loop_queue_t* nolock_loop_queueP);
void* nolock_loop_queue_get_write(nolock_loop_queue_t* nolock_loop_queueP);
//入队，有可能失败，即r==w+1
err_t nolock_loop_queue_done_write(nolock_loop_queue_t* nolock_loop_queueP);
//释放队列，但是内部的元素不释放
err_t nolock_loop_queue_destroy(nolock_loop_queue_t* nolock_loop_queueP);

#endif
