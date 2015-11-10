#include "SqStack.cpp"
#include <stdio.h>


char OP[] = "+-*/()#";
char DIGIT[] = "0123456789";

int cmp[7][7]=  
{
	 1, 1,-1,-1,-1, 1, 1,
	 1, 1,-1,-1,-1, 1, 1,  
	 1, 1, 1, 1,-1, 1, 1,  
  	 1, 1, 1, 1,-1, 1, 1,  
  	-1,-1,-1,-1,-1, 0, ERROR,  
  	 1, 1, 1, 1, 0, 1, 1,  
  	-1,-1,-1,-1,-1, ERROR, 0,  
};  

int Index(char c)
{
	switch(c)
	{
		case '+':
			return 0;
		case '-':
			return 1;
		case '*':
			return 2;
		case '/':
			return 3;
		case '(':
			return 4;
		case ')':
			return 5;
		case '#':
			return 6;
		case '.':
			return 10;
		default:
			exit(ERROR);
	}
}

bool In(char c, char* set)
{
	char *p = set;
	while (*p)
	{
		if (c == *p) return true;
		p++;
	}
	return false;
}

double Operate(double x, int op, double y)
{
	switch(op)
	{
		case 0:
			return x+y;
		case 1:
			return x-y;
		case 2:
			return x*y;
		case 3:
			return x/y;
		default:
			exit(ERROR);
	}
}

int mGetchar()
{
	char tmp[1024];
	char buffer = getchar();
	while (!In(buffer, OP) && !In(buffer, DIGIT) && buffer!='.') 
	{
		printf("您的输入有误，请确保输入只包含数字和运算符号并以#结尾！\n"); 
		if (buffer != '\n') gets(tmp);
		return INPUT_VALID;
	}
	return buffer;
}

double E(double base, int exp)
{
	double res = base;
	for (int i=0; i<exp; i++)
	{
		res *= 10;
	}
	for (int i=0; i>exp; i--)
	{
		res /= 10;
	}
	return res;
}

double EvaExpression()
{
	SqStack<int> OPTR;
	SqStack<double> OPND;
	
	int buffer;
	bool preIsDigit = false;
	bool hasDot = false; 
	int exp;
	
	double ans = 0;
	
	OPTR.Push(Index('#'));
	
	buffer = mGetchar();
	if (buffer == INPUT_VALID) return EvaExpression();

	while (buffer!='#' || OPTR.GetTop()!=Index('#'))
	{
		if (buffer == '.')
		{
			if (hasDot)
			{
				char tmp_s[1024];
				printf("您的输入有误，请确保输入的算术表达式合法！\n");
				if (buffer != '\n') gets(tmp_s);
				return EvaExpression();
			}
			hasDot = true;
			exp = 0;
			
			buffer = mGetchar();
			if (buffer == INPUT_VALID) return EvaExpression();
		}
		else if (In(buffer, DIGIT)) 
		{
			if (preIsDigit)
			{
				double number; 
				OPND.Pop(&number);
				
				if (hasDot)
				{
					exp--;
					number += E(buffer-'0', exp);
				}
				else
				{
					number *= 10;
					number += buffer-'0';
				}
				OPND.Push(number);
			}
			else
			{
				OPND.Push(buffer-'0');
				preIsDigit = true; 
			}
			
			buffer = mGetchar();
			if (buffer == INPUT_VALID) return EvaExpression();
		}
		else 
		{
			int toOperate, top;
			preIsDigit = false;
			hasDot = false;
			toOperate = Index(buffer);
			top = OPTR.GetTop();
			switch(cmp[top][toOperate])
			{
				case -1:
					OPTR.Push(toOperate);
					buffer = mGetchar();
					if (buffer == INPUT_VALID) return EvaExpression();
					break;
				case 0:
					int tmp;
					OPTR.Pop(&tmp);
					buffer = mGetchar();
					if (buffer == INPUT_VALID) return EvaExpression();
					break;
				case 1:
					int op;
					double a, b;
					if (OPTR.Pop(&op) != OK || OPND.Pop(&b) != OK || OPND.Pop(&a) != OK)
					{
						char tmp_s[1024];
						printf("您的输入有误，请确保输入的算术表达式合法！\n");
						if (buffer != '\n') gets(tmp_s);
						return EvaExpression();
					}
					ans = Operate(a, op, b);  
					OPND.Push(ans);
					break;
				case ERROR:
					char tmp_s[1024];
					printf("您的输入有误，请确保输入的算术表达式合法！\n");
					if (buffer != '\n') gets(tmp_s);
					return EvaExpression();
				default:
					exit(ERROR);
			}
		}
		
	}
	OPND.Pop(&ans);
	if (OPTR.IsEmpty() || OPND.IsEmpty() ) return ans;
	
	char tmp_s[1024];
	printf("您的输入有误，请确保输入的算术表达式合法！\n");
	if (buffer != '\n') gets(tmp_s);
	return EvaExpression();
}                

int main()
{
	printf("输入运算式(以#号结束)：\n");
	double ans = EvaExpression();
    printf("答案是：%lf", ans);
    return 0;

}
