#include <stdlib.h>
#include <malloc.h>
#define Status int
#define STACK_INIT_SIZE 100
#define STACKINCREMENT 10

//���������� 
#define OK 1 			//�ɹ� 
#define VISIT_FAILED -10	//Ԫ�ط���ʧ�� 
#define INPUT_VALID -20		//����Ƿ��ַ� 

//������� 
#define OVERFLOW -100		//�洢����ʧ�� 
#define STACK_IS_NULL -200	//���Ա�Ϊ��
#define BASE_IS_NULL -201	//����Ϊ�� 
#define STACK_IS_EMPTY -202	//�Կ�ջ�ķǷ����� 
#define ERROR -900			//�������� 

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
