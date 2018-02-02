#ifndef __FIFO_INCLUDE__
#define __FIFO_INCLUDE__
#include "sys/params.h"
#include "sys/sys.h"
#include "sys/err.h"

typedef struct{
	void** elements;
	u8 numOfElements;
	u8 currentSize;
	u8 startPoint;
	u8 endPoint;
}fifo_t;
#define fifo_current_size(p) \
	((p)->currentSize)

#define fifo_num_of_elements(p) \
	((p)->numOfElements)

#define fifo_full(p) \
	(fifo_current_size(p)==fifo_num_of_elements(p)?TRUE:FALSE)

#define fifo_free(p) \
	(!fifo_current_size(p)?TRUE:FALSE)

#define fifo_see_top(p) \
	(fifo_free(p)?NULL:(p)->elements[(p)->startPoint])

fifo_t* fifo_create(u8 size);
err_t fifo_destroy(fifo_t* fifoP);
void* fifo_get(fifo_t* fifoP);
err_t fifo_put(fifo_t* fifoP,void* element);
#endif
