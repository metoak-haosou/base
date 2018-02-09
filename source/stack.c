#include "stack.h"
#include <stdlib.h>

stack_t*
stack_create (u16 sizeOfStack)
{
  if (sizeOfStack < 1)
    {
      goto stack_create_END0;
    }
  stack_t* stackP = (stack_t*) malloc (sizeof(*stackP));
  if (!stackP)
    {
      goto stack_create_END0;
    }
  stackP->top = 0;
  stackP->numOfElements = sizeOfStack;
  stackP->elements = (void**) malloc (sizeOfStack * sizeof(void*));
  if (!stackP->elements)
    {
      goto stack_create_END0;
    }
  return stackP;
  stack_create_END0:
  err_info
  ;
  return NULL;
}

err_t
stack_destroy (stack_t* stackP)
{
  free (stackP->elements);
  free (stackP);
  return SUCCESE;
}

void*
stack_get (stack_t* stackP)
{
  void* dataP;
  if (stack_free(stackP))
    {
      return NULL;
    }

  dataP = stackP->elements[stackP->top-1];
  stackP->top--;
  return dataP;
}

err_t
stack_put (stack_t* stackP, void* elementP)
{
  if (stack_full(stackP))
    {
      return EIO;
    }
  stackP->elements[stackP->top++] = elementP;
  return SUCCESE;
}
