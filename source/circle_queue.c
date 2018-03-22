#include "circle_queue.h"
#define adjust_pos(pos) ((pos)%QUEUE_SIZE)
#define USED_VOLUME(p)	(QUEUE_SIZE-(p)->remain)
#define TO_8BIT(data)	((u8)(data))
#define TO_8BIT_P(p)	((u8*)(p))
static inline void _circle_queue_put_8bit(struct circle_queue_t *circleQueueP,u8 dataPut)
{
	circleQueueP->data[circleQueueP->top] = dataPut;
	circleQueueP->top++;
	circleQueueP->top = adjust_pos(circleQueueP->top);
	circleQueueP->remain--;
}
//向循环队列里面放入一个8bit的数据
i8 circle_queue_put_8bit(struct circle_queue_t *circleQueueP,u8 dataPut)
{
	if(0==circleQueueP->remain){
		return -1;
	}
	_circle_queue_put_8bit(circleQueueP,dataPut);
	return 0;
}

//向循环队列里面放入一个16bit的数据,低位先入，高位后入,LSB
i8 circle_queue_put_16bit(struct circle_queue_t *circleQueueP,u16 dataPut)
{
	if(circleQueueP->remain<2){
		return -1;
	}
	_circle_queue_put_8bit(circleQueueP,TO_8BIT(dataPut));
	_circle_queue_put_8bit(circleQueueP,TO_8BIT(dataPut>>8));
	return 0;
}

static inline void _circle_queue_get_8bit(struct circle_queue_t *circleQueueP,u8 *dataGet)
{
	*dataGet = circleQueueP->data[circleQueueP->bottom];
	circleQueueP->bottom++;
	circleQueueP->bottom = adjust_pos(circleQueueP->bottom);
	circleQueueP->remain++;
}
//从循环队列里面得到一个8bit的数据
i8 circle_queue_get_8bit(struct circle_queue_t *circleQueueP,u8 *dataGet)
{
	//printf("USED_VOLUME(circleQueueP)=%d\n",USED_VOLUME(circleQueueP));
	if(USED_VOLUME(circleQueueP)==0){
		return -1;
	}
	_circle_queue_get_8bit(circleQueueP,dataGet);
	return 0;
}

//从循环队列里面得到一个16bit的数据
i8 circle_queue_get_16bit(struct circle_queue_t *circleQueueP,u16 *dataGet)
{
//	printf("USED_VOLUME(circleQueueP)=%d\n",USED_VOLUME(circleQueueP));
	if(USED_VOLUME(circleQueueP)<2){
		return -1;
	}
	_circle_queue_get_8bit(circleQueueP,TO_8BIT_P(dataGet)+0);
	_circle_queue_get_8bit(circleQueueP,TO_8BIT_P(dataGet)+1);
	return 0;
}

static inline void _circle_queue_watch_8bit(struct circle_queue_t *circleQueueP,u16 shift,u8 *dataWatch)
{
//	printf("adjust data %d\n",adjust_pos(circleQueueP->bottom+shift));
	*dataWatch = circleQueueP->data[adjust_pos(circleQueueP->bottom+shift)];
}
//观察循环队列中偏移shift个8bit的数据
i8 circle_queue_watch_8bit(struct circle_queue_t *circleQueueP,u16 shift,u8 *dataWatch)
{
	if(shift >= USED_VOLUME(circleQueueP)){
		return -1;
	}
	_circle_queue_watch_8bit(circleQueueP,shift,dataWatch);
	return 0;
}

//观察循环队列中偏移shift个16bit的数据
i8 circle_queue_watch_16bit(struct circle_queue_t *circleQueueP,u16 shift,u16 *dataWatch)
{
	if(shift >= USED_VOLUME(circleQueueP)/2){
		return -1;
	}
	_circle_queue_watch_8bit(circleQueueP,shift*2,TO_8BIT_P(dataWatch)+0);
	_circle_queue_watch_8bit(circleQueueP,shift*2+1,TO_8BIT_P(dataWatch)+1);
	return 0;
}
