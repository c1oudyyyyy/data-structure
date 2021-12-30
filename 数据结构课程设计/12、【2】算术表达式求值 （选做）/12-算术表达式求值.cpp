/*
先把表达式转化为后缀表达式，即遇到数字，则直接放入后缀表达式字符串，
遇到符号如果没有数字在栈中，则先入栈，然后遇到右括号或者#结束标志一并输入到后缀表达式字符串中。
后缀表达式求解即先数字进栈，如果碰到符号则两数字出栈运算后在进栈。
另外注意空格的存放。 
*/

#include<iostream>
#include<stack>
#include<stdlib.h>
#include<stdio.h>
#include<string.h> 
#define stacksize 100
#define add 10
using namespace std;
typedef struct SNode
{
	char* base;
	char* top;
	int Stacksize;
	int length;
}SNode, * SqStack;
stack<double> nu;//储存计算结果 
char input[1000000], output[1000000];//储存初始表达式和后缀表达式 
int InitStack(SqStack& S)
{
	S = (SNode*)malloc(sizeof(SNode));
	S->Stacksize = stacksize;
	S->base = (char*)malloc(sizeof(char) * stacksize);
	S->top = S->base;
	S->length = 0;
	return 1;
}

int Push(SqStack& S, char e)
{
	if (S->top - S->base >= stacksize)
	{
		S->base = (char*)realloc(S->base, sizeof(char) * (stacksize + add));
		S->Stacksize += add;
	}
	*(S->top) = e;
	S->top++;
	S->length++;
	return 1;
}

int Pop(SqStack& S, char& e)
{
	if (S->top == S->base)
		return 0;
	e = *(S->top - 1);
	S->top--;
	S->length--;
	return 1;
}

int shift(SqStack& op)//转化为后缀表达式存在output中 
{
	int flag = 0;
	int i = 0, j = 0, black_white = 1;
	char c;
	while (input[i] != '\0')
	{
		if (input[i] >= '0' && input[i] <= '9' || input[i] == '.')//若是数字 
		{
			if (input[i] == '.')
				flag = 1;
			output[j] = input[i];
			i++;
			j++;
			if (input[i] == '.' && flag == 1)
			{
				cout << "小数点重复出现！格式错误！" << endl;
				return -1;
			}
			if ((input[i]<'0' || input[i]>'9') && input[i] != '.')
			{
				flag = 0;
				output[j] = ' ';
				j++;
			}
		}
		else if (input[i] == '+')
		{
			if (op->length == 0)//没有数字在栈中 
			{
				Push(op, input[i]);
			}
			else//否则 
			{
				do
				{
					Pop(op, c);
					if (c == '(')
					{
						Push(op, c);
						continue;
					}
					output[j++] = c;
					output[j++] = ' ';
				} while (op->length != 0 && c != '(');
				Push(op, input[i]);
			}
			i++;
		}
		else if (input[i] == '-' && ((input[i - 1] >= '0' && input[i - 1] <= '9') || input[i - 1] == ')'))
		{
			if (op->length == 0)
			{
				Push(op, input[i]);
			}
			else
			{
				do
				{
					Pop(op, c);
					if (c == '(')
					{
						Push(op, c);
						continue;
					}
					output[j++] = c;
					output[j++] = ' ';
				} while (op->length != 0 && c != '(');
				Push(op, input[i]);
			}
			i++;
		}
		else if ((input[i] == '-' && i == 0) || (input[i] == '-' && (input[i - 1] == '(' || input[i - 1] == '+' || input[i - 1] == '-' || input[i - 1] == '*' || input[i - 1] == '/')))
		{
			output[j] = input[i];
			j++;
			i++;
		}
		else if (input[i] == '*' || input[i] == '/')
		{
			if (op->length == 0)
			{
				Push(op, input[i]);
			}
			else
			{
				do
				{
					Pop(op, c);
					if (c == '(')
					{
						Push(op, c);
						continue;
					}
					if (c == '+' || c == '-')
					{
						Push(op, c);
						break;
					}
					else if (c == '*' || c == '/')
					{
						Push(op, c);
						break;
					}
				} while (op->length != 0 && c != '(');
				Push(op, input[i]);
			}
			i++;
		}
		else if (input[i] == '(')
		{
			Push(op, input[i]);
			i++;
		}
		else if (input[i] == ')')
		{
			Pop(op, c);
			while (c != '(')
			{
				output[j] = c;
				j++;
				output[j] = ' ';
				j++;
				Pop(op, c);
			}
			i++;
		}
		else if (input[i] == '#')
		{
			if (op->length == 0)
				break;
			else
			{
				Pop(op, c);
				output[j++] = c;
				output[j++] = ' ';
			}
		}
	}
}

double calculate()//根据后缀表达式进行按顺序计算 
{
	int i = 0, j = 0;
	double t = 1;
	if (output[0] == '-')
	{
		t = -1;
		i++;
	}
	char num[100];
	double cal = 0;
	while (output[i + 1] != '\0')
	{
		if (output[i] >= '0' && output[i] <= '9' || output[i] == '.')
		{
			num[j++] = output[i];
			i++;
			if (output[i] == ' ')
			{
				if (i >= 100)
				{
					cout << "数字过大无法计算！" << endl;
					return -1;
				}
				double a = atof(num);
				nu.push(a * t);
				memset(num, '\0', 100);
				j = 0;
			}
		}
		else if (output[i] == ' ' && output[i + 1] >= '0' && output[i + 1] <= '9')
		{
			i++;
			t = 1;
			continue;
		}
		else if (output[i] == ' ' && output[i + 1] == '-' && output[i + 2] != ' ')
		{
			i++;
			i++;
			t = -1;
			continue;
		}
		else if (output[i] == ' ' && ((output[i + 1] == '-' && output[i + 2] == ' ') || output[i + 1] == '+' || output[i + 1] == '*' || output[i + 1] == '/' || (output[i + 1] >= '0' && output[i + 1] <= '9')))
		{
			i++;
			continue;
		}
		else if (output[i] == '+')
		{
			double a, b;
			if (nu.empty())
			{
				cout << "输入格式错误！数字缺失！" << endl;
				return -1;
			}
			a = nu.top();
			nu.pop();
			if (nu.empty())
			{
				cout << "输入格式错误！数字缺失！" << endl;
				return -1;
			}
			b = nu.top();
			nu.pop();
			nu.push(a + b);
			i++;
			cout << a << "+" << b << "=" << a + b << endl;
		}
		else if (output[i] == '/')
		{
			double a, b;
			if (nu.empty())
			{
				cout << "输入格式错误！数字缺失！" << endl;
				return -1;
			}
			a = nu.top();
			nu.pop();
			if (nu.empty())
			{
				cout << "输入格式错误！数字缺失！" << endl;
				return -1;
			}
			b = nu.top();
			nu.pop();
			if (a == 0)
			{
				cout << "除数不能为0" << endl;
				return -1;
			}
			nu.push(b / a);
			i++;
			cout << b << "/" << a << "=" << b / a << endl;
		}
		else if (output[i] == '-')
		{
			double a, b;
			if (nu.empty())
			{
				cout << "输入格式错误！数字缺失！" << endl;
				return -1;
			}
			a = nu.top();
			nu.pop();
			if (nu.empty())
			{
				cout << "输入格式错误！数字缺失！" << endl;
				return -1;
			}
			b = nu.top();
			nu.pop();
			nu.push(b - a);
			i++;
			cout << b << "-" << a << "=" << b - a << endl;
		}
		else if (output[i] == '*')
		{
			double a, b;
			if (nu.empty())
			{
				cout << "输入格式错误！数字缺失！" << endl;
				return -1;
			}
			a = nu.top();
			nu.pop();
			if (nu.empty())
			{
				cout << "输入格式错误！数字缺失！" << endl;
				return -1;
			}
			b = nu.top();
			nu.pop();
			nu.push(a * b);
			i++;
			cout << b << "*" << a << "=" << a * b << endl;
		}
	}
	return nu.top(); 
}

int main()
{
	SqStack op;
	InitStack(op);
	cin >> input;
	shift(op);
	cout << output << endl;
	double cal = calculate();
	cout << cal;
	delete op;
	return 0;
}
//6+15.1*(21-8/4)# 
