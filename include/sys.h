#ifndef __SYS_INCLUDE__
#define __SYS_INCLUDE__

#include <stdio.h>

#define err_info \
	printf("EROR:file %s,function %s,LINE %d\n",__FILE__,__func__,__LINE__);

#endif
