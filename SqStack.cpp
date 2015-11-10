#include "SqStack.h"

template <class SElemType>
SqStack<SElemType>::SqStack()
{
	base = (SElemType *)malloc(STACK_INIT_SIZE * sizeof(SElemType));
	if (!base) exit(OVERFLOW);
	top = base;
	stacksize = STACK_INIT_SIZE;
}

template <class SElemType>
SqStack<SElemType>::~SqStack()
{
	free(base);
}

template <class SElemType>
Status SqStack<SElemType>::Clear()
{
	if (!base) exit(BASE_IS_NULL); 
	free(base);
	base = (SElemType *)malloc(STACK_INIT_SIZE * sizeof(SElemType));
	if (!base) exit(OVERFLOW);
	top = base;
	stacksize = STACK_INIT_SIZE;
	return OK;
}//ClearStack

template <class SElemType>
bool SqStack<SElemType>::IsEmpty()
{
	if (!base) exit(BASE_IS_NULL); 
	return base==top ? true : false;
}//StackEmpty

template <class SElemType>
int SqStack<SElemType>::GetLength()
{
	if (!base) exit(BASE_IS_NULL); 
	return top-base;
}//StackLength

template <class SElemType>
SElemType SqStack<SElemType>::GetTop()
{
	if (top == base) exit(STACK_IS_EMPTY);
	return *(top - 1);
}//GetTop

template <class SElemType>
Status SqStack<SElemType>::Push(SElemType e)
{
	if (top - base >= stacksize)
	{
		base = (SElemType *) realloc(base, (stacksize + STACKINCREMENT) * sizeof(SElemType));
		if (!base) exit(OVERFLOW);
		
		top = base + stacksize;
		stacksize += STACKINCREMENT;
	}
	
	*top++ = e;
	return OK;
}//Push

template <class SElemType>
Status SqStack<SElemType>::Pop(SElemType *e)
{
	if (top == base) return STACK_IS_NULL;
	*e = *--top;
	return OK;
}//Pop

template <class SElemType>
Status SqStack<SElemType>::StackTraverse(Status visit(SElemType))
{
	if (!base) exit(BASE_IS_NULL);
	SElemType *p = base;
	
	for (;p<top; p++)
	{
		if (visit(*p) != OK) return VISIT_FAILED;
	}
}//StackTraverse
