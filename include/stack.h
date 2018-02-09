#ifndef __STACK_INCLUDE__
#define __STACK_INCLUDE__
#include "err.h"
#include "params.h"
#include "sys.h"

typedef struct
{
  u16 top;
  u16 numOfElements;
  void** elements;
}__attribute__ ((aligned(2))) stack_t;

#define stack_top(p) \
  ((p)->top)
#define stack_numOfElements(p) \
  ((p)->numOfElements)
#define stack_full(p) \
  (stack_numOfElements(p)==stack_top(p)?TRUE:FALSE)
#define stack_free(p) \
  (stack_top(p)==0?TRUE:FALSE)

stack_t*
stack_create (u16 sizeOfStack);
err_t
stack_destroy (stack_t* stackP);
void*
stack_get (stack_t* stackP);
err_t
stack_put (stack_t* stackP, void* elementP);

#endif
