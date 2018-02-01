#include <stdio.h>
#include <stdlib.h>
#include "moak_nolock_loop_queue.h"

//创建一个无锁循环队列
nolock_loop_queue_t* nolock_loop_queue_create(u8 ElementsNum,u16 ElementSize)
{
	int i;
	nolock_loop_queue_t* nolock_loop_queueP = NULL;
	if(ElementsNum < 3){
		printf("ElementsNum less 3\n");
		goto nolock_loop_queue_create_END0;
	}
	nolock_loop_queueP = malloc(sizeof(nolock_loop_queue_t));
	if(!nolock_loop_queueP){
		printf("%s:malloc failed!!\n",__func__);
		goto nolock_loop_queue_create_END0;
	}
	nolock_loop_queueP->Elements = malloc(ElementsNum * sizeof(void*));
	if(!nolock_loop_queueP){
		printf("%s:malloc failed!!\n",__func__);
		goto nolock_loop_queue_create_END1;
	}
	for(i=0;i<ElementsNum;i++){
		nolock_loop_queueP->Elements[i] = malloc(ElementSize);
		if(!nolock_loop_queueP->Elements[i]){
			int j;
			for(j=0;j<i;j++)
				free(nolock_loop_queueP->Elements[j]);
			goto nolock_loop_queue_create_END2;
		}
	}
	nolock_loop_queueP->ReadPoint = 0;
	nolock_loop_queueP->WritePoint = 0;
	nolock_loop_queueP->ElementSize = ElementSize;
	nolock_loop_queueP->ElementsNum = ElementsNum;
	goto nolock_loop_queue_create_END0;
nolock_loop_queue_create_END2:
	free(nolock_loop_queueP->Elements);
	nolock_loop_queueP->Elements = NULL;
nolock_loop_queue_create_END1:
	free(nolock_loop_queueP);
	nolock_loop_queueP = NULL;
nolock_loop_queue_create_END0:
	return nolock_loop_queueP;
}

//只是取出数据，没做处理，该操作有可能失败,即r=w
void* nolock_loop_queue_read(nolock_loop_queue_t* nolock_loop_queueP)
{
	void* data_to_read = NULL;
	if(CHECK_FREE(nolock_loop_queueP)){
		goto nolock_loop_queue_to_read_END;
	}
	data_to_read = GET_READ_DATA(nolock_loop_queueP);
	INCREASE_READ(nolock_loop_queueP);
nolock_loop_queue_to_read_END:
	return data_to_read;
}
//返回当前的写buffer，填写数据
void* nolock_loop_queue_get_write(nolock_loop_queue_t* nolock_loop_queueP)
{
	void* data_to_write = NULL;
	if(CHECK_FULL(nolock_loop_queueP)){
		goto nolock_loop_queue_get_write_END;
	}
	data_to_write = nolock_loop_queueP->Elements[nolock_loop_queueP->WritePoint];
	goto nolock_loop_queue_get_write_END;
nolock_loop_queue_get_write_END:
	return data_to_write;
}
//入队，有可能失败，即r==w+1
err_t nolock_loop_queue_done_write(nolock_loop_queue_t* nolock_loop_queueP)
{
	INCREASE_WRITE(nolock_loop_queueP);
	return SUCCESE;
}
//释放队列，但是内部的元素不释放
err_t nolock_loop_queue_destroy(nolock_loop_queue_t* nolock_loop_queueP)
{
	int i;
	for(i=0;i<nolock_loop_queueP->ElementsNum;i++)
		free(nolock_loop_queueP->Elements[i]);
	free(nolock_loop_queueP);
	return SUCCESE;
}
