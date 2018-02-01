#include "fifo.h"
#include <stdlib.h>


/******************************************************
 * function:fifo_create
 * params:
 * 			size:fifo的深度
 * return:
 *			成功返回创建的fifo的指针，失败返回NULL
 * note:
 ********************************************************/
fifo_t* fifo_create(u8 size)
{
	fifo_t* fifoP;
	if(0 == size)
		return NULL;
	fifoP = (fifo_t*)malloc(sizeof(fifo_t));
	if(!fifoP){
		err_info;
		return NULL;
	}
	fifoP->numOfElements = size;
	fifoP->currentSize = 0;
	fifoP->startPoint = 0;
	fifoP->endPoint = 0;
	fifoP->elements = (void**)malloc(sizeof(void*)*size);
	if(!fifoP->elements){
		err_info;
		goto fifo_create_error0;
	}
	return fifoP;
fifo_create_error0:
	free(fifoP);
	return NULL;

}
/******************************************************
 * function:fifo_destroy
 * params:
 *			fifoP:将要操作的fifo的指针
 * return:
 *			失败返回错误码，成功返回SUCCESE
 * note:
 ********************************************************/
err_t fifo_destroy(fifo_t* fifoP)
{
	if(!fifoP)
		return -EIO;
	free(fifoP->elements);
	free(fifoP);
	return SUCCESE;
}
/******************************************************
 * function:fifo_get
 * params:
 *			fifoP:将要操作的fifo的指针
 * return:
 *			失败返回NULL，成功返回取出的element
 * note:
 ********************************************************/
void* fifo_get(fifo_t* fifoP)
{
	void* tmp;
	if(fifo_free(fifoP))
		return NULL;
	tmp = fifoP->elements[fifoP->startPoint++];
	fifoP->startPoint %= fifoP->numOfElements;
	fifoP->currentSize--;
	return tmp;
}
/******************************************************
 * function:fifo_put
 * params:
 *			fifoP:将要操作的fifo的指针
 *			element:将要放入fifo的元素
 * return:
 *			失败返回错误码，成功返回SUCCESE
 * note:
 ********************************************************/
err_t fifo_put(fifo_t* fifoP,void* element)
{
	if(fifo_full(fifoP))
		return -ENOMAL;
	fifoP->elements[fifoP->endPoint++] = element;
	fifoP->endPoint %= fifoP->numOfElements;
	fifoP->currentSize++;
	return SUCCESE;
}
