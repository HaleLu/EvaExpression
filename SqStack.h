#include <stdlib.h>
#include <malloc.h>
#define Status int
#define STACK_INIT_SIZE 100
#define STACKINCREMENT 10

//函数返回码 
#define OK 1 			//成功 
#define VISIT_FAILED -10	//元素访问失败 
#define INPUT_VALID -20		//输入非法字符 

//错误代码 
#define OVERFLOW -100		//存储分配失败 
#define STACK_IS_NULL -200	//线性表为空
#define BASE_IS_NULL -201	//链表为空 
#define STACK_IS_EMPTY -202	//对空栈的非法操作 
#define ERROR -900			//其他错误 

template <class SElemType>
class SqStack {
	private:	
		SElemType *base;
		SElemType *top;
		int stacksize;
	public:
		SqStack();
		~SqStack();
				
		Status Clear();
		
		bool IsEmpty();
		
		int GetLength();
		
		SElemType GetTop();
		
		Status Push(SElemType e);
		
		Status Pop(SElemType *e);
		
		Status StackTraverse(Status visit(SElemType));
};
