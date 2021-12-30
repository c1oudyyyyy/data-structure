#include <stdio.h>
#include <stdlib.h>

#define OK 1
#define ERROR 0

#define SIZE 256
#define INCREMENT 128

typedef int Status;

typedef struct SeqStack
{
	int *pBase;
	int *pTop;
	int size;
}SeqStack;

//顺序栈初始化 
Status InitStack(SeqStack &S)
{
	S.pBase = (int *) malloc(SIZE * sizeof(int));
	if(S.pBase == NULL) exit(ERROR);
	S.pTop = S.pBase;
	S.size = SIZE;
	return OK;
}

//销毁顺序栈 
Status DestroyStack(SeqStack &S)
{
	if(S.pBase != NULL)//若顺序栈已存在 
	{
		free(S.pBase);
		S.pBase = NULL;
	}
	S.pTop = NULL;
	S.size = 0;
	printf("该栈已被销毁\n");
	return OK;
}

//清空顺序栈
Status ClearStack(SeqStack &S)
{
	if(S.pBase != NULL && S.pTop != S.pBase)//若顺序栈已存在且非空
	{
		S.pTop = S.pBase;
		printf("该栈已被清空\n");
		return OK;
	}
	printf("该栈不存在或已被清空\n");
	return ERROR; 
}

//判空
bool StackEmpty(SeqStack S)
{
	if(S.pBase != NULL)//若顺序栈已存在
	{
		if(S.pTop == S.pBase)
		{
			return true;
		}
		return false;
	}
	printf("该顺序栈不存在\n");
	return true;
}

//获取长度
int StackLength(SeqStack S)
{
	if(S.pBase != NULL)//若顺序栈已存在
	{
		return (S.pTop - S.pBase);//指针首地址相减 
	}
	printf("该顺序栈不存在\n");
	return ERROR;
}

//获取栈顶元素
Status GetTop(SeqStack S, int &e)
{
	if(S.pBase != NULL && S.pTop != S.pBase)//顺序栈存在且非空 
	{
		e = *(S.pTop - 1);
		return OK;
	}
	printf("该顺序栈不存在或为空栈\n");
	return ERROR;
}

//遍历输出
Status StackTraverse(SeqStack S)
{
	if(S.pBase != NULL && S.pTop != S.pBase)//顺序栈存在且非空
	{
		int i;
		for(i = 0; i < S.pTop - S.pBase; i++)
		{
			printf("%d ", S.pBase[i]);
		}
		printf("\n");
		return OK;
	}
	printf("该顺序栈不存在或为空栈\n");
	return ERROR;
}

//压栈
Status Push(SeqStack &S, int e)
{
	if(S.pBase != NULL)//顺序栈存在
	{
		if(S.pTop - S.pBase == S.size)//栈满
		{
			S.pBase = (int *) realloc(S.pBase, (S.size+INCREMENT) * sizeof(int));
			if(S.pBase == NULL) exit(ERROR);
			S.pTop = S.pBase + S.size;//重新定义栈顶指针 
			S.size += INCREMENT;
		} 
		*S.pTop++ = e;
		return OK;
	}
	printf("该顺序栈不存在\n");
	return ERROR; 
}

//弹栈
Status Pop(SeqStack &S, int &e)
{
	if(S.pBase != NULL && S.pTop != S.pBase)//顺序栈存在且非空
	{
		e = *--S.pTop;
		return OK;
	}
	printf("该顺序栈不存在或为空栈\n");
	return ERROR;
}

//输入元素
Status InputElem(SeqStack &S)
{
	if(S.pBase != NULL)
	{
		int i, n;
		printf("输入元素个数：");
		scanf("%d", &n);
		S.pTop = S.pBase + n;
		printf("输入元素：");
		for(i = 0; i < n; i++)
		{
			scanf("%d", &S.pBase[i]);
		}
		return OK;
	}
	printf("该顺序栈不存在\n");
	return ERROR;
} 

//测试函数 
int main()
{
	SeqStack S;
	InitStack(S);
	InputElem(S);
	StackTraverse(S);
	printf("压栈后：");
	Push(S, 6);
	StackTraverse(S);
	int e;
	Pop(S, e);
	printf("弹栈后：");
	StackTraverse(S);
	printf("弹出元素：%d\n", e);
	GetTop(S, e);
	printf("此时的栈顶元素：%d\n", e);
	printf("此时的元素个数：%d\n", StackLength(S));
	if(!StackEmpty(S))
		printf("该栈不为空\n");
	ClearStack(S);
	if(StackEmpty(S))
		printf("该栈为空\n");
	DestroyStack(S);
	StackEmpty(S);
	return 0;
}
