#ifndef __CIRCLE_QUEUE_INCLUDE__
#define __CIRCLE_QUEUE_INCLUDE__

#include "params.h"

#define QUEUE_SIZE (0x400)

struct circle_queue_t{
	u16 bottom;
	u16 top;
	u16 remain;
	u8 data[QUEUE_SIZE];
};

#define init_circle_queue(circleQueueName) \
	struct circle_queue_t circleQueueName = {\
			0,0,QUEUE_SIZE,{0}\
	}
i8 circle_queue_put_8bit(struct circle_queue_t *circleQueueP,u8 dataPut);
i8 circle_queue_put_16bit(struct circle_queue_t *circleQueueP,u16 dataPut);
i8 circle_queue_get_8bit(struct circle_queue_t *circleQueueP,u8 *dataGet);
i8 circle_queue_get_16bit(struct circle_queue_t *circleQueueP,u16 *dataGet);
i8 circle_queue_watch_8bit(struct circle_queue_t *circleQueueP,u16 shift,u8 *dataWatch);
i8 circle_queue_watch_16bit(struct circle_queue_t *circleQueueP,u16 shift,u16 *dataWatch);

#endif
