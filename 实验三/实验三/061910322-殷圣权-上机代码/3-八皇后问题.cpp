#include <stdio.h>
#include <stdlib.h>

#define OK 1
#define ERROR 0
#define CONFLICT 0

#define SIZE 256
#define INCREMENT 128

#define N 8//皇后数量

typedef int Status;

typedef struct point
{
	int row;
	int col;
}point;

typedef struct SeqStack
{
	point *pBase;
	point *pTop;
	int size;
}SeqStack;

//初始化顺序栈-储存皇后位置 
Status InitStack(SeqStack &S)
{
	S.pBase = (point *) malloc(SIZE * sizeof(point));
	if(S.pBase == NULL) exit(ERROR);
	S.pTop = S.pBase;
	S.size = SIZE;
	return OK;
}

//压栈-放入一个皇后
Status Push(SeqStack &S, point newqueen)
{
	if(S.pBase != NULL)//栈存在
	{
		if(S.pTop - S.pBase == S.size)//栈满
		{
			S.pBase = (point *) realloc(S.pBase, (S.size + INCREMENT) * sizeof(point));
			if(S.pBase == NULL) exit(ERROR);
			S.pTop = S.pBase + SIZE;
			S.size += INCREMENT;
		}
		S.pTop->col = newqueen.col;
		S.pTop->row = newqueen.row;
		S.pTop++;
		return OK;
	}
	printf("栈不存在,无法压栈\n");
	return ERROR;
}

//弹栈-弹出一个皇后
Status Pop(SeqStack &S, point &curqueen)
{
	if(S.pBase != NULL && S.pTop != S.pBase)//栈存在且非空
	{
		curqueen.col = S.pTop->col;
		curqueen.row = S.pTop->row;
		S.pTop--;
		return OK;
	}
	printf("栈不存在或为空栈，无法弹栈\n");
	return ERROR;
}

//判断是否冲突
Status JudgeConfliction(SeqStack S, point newqueen)
{
	point *pCurqueen;
	int x1, y1, x2, y2;
	x1 = newqueen.col;
	y1 = newqueen.row;
	pCurqueen = S.pBase;
	Status tag = OK;
	while(pCurqueen < S.pTop-1)//与除栈顶之外的元素对比，判断是否冲突 
	{
		x2 = pCurqueen->col;
		y2 = pCurqueen->row;
		if(x1 == x2)
		{
			tag = CONFLICT;
			break;
		}
		if(abs(x1 - x2) == abs(y1 - y2))
		{
			tag = CONFLICT;
			break;
		}
		pCurqueen++;
	}
	return tag;
}

//输出结果
Status OutputResult(SeqStack S, int n)
{
	printf("--------------------------------\n");
	point *cur = S.pBase;
	int i; 
	for(cur; cur < S.pTop; cur++)
	{
		for(i = 1; i <= n; i++)
		{
			if(i == cur->col)
				printf("Q ");
			else
				printf("X ");
		}
		printf("\n");
	}
	return OK;
} 

//皇后放置-递归
Status PlaceQueen(int row, int &resultCount, SeqStack &StkQueen)
{
	int col;
	point curqueen;
	for(col = 1; col <= N; col++)
	{
		curqueen.col = col;
		curqueen.row = row;
		Push(StkQueen, curqueen);//压栈 
		Status ret = JudgeConfliction(StkQueen, curqueen);//与除自己外的元素对比，判断是否冲突，若冲突则弹栈  
		if(ret == OK)//未冲突，轮到下一行 
		{
			if(row < N)//未到达最后一行，继续递归下一行 
				PlaceQueen(row + 1, resultCount, StkQueen);
			else
			{
				OutputResult(StkQueen, N);//最后一行的合适位置放置皇后之后输出结果 
				resultCount++;//结果数+1 
			}
		}
		Pop(StkQueen, curqueen);//冲突，弹栈 
	}
	return OK;
}

int main()
{
	int resultCount = 0;
	SeqStack StkQueen;
	InitStack(StkQueen);
	PlaceQueen(1, resultCount, StkQueen);
	printf("--------------------------------\n");
	printf("%d皇后问题共有%d种结果\n", N, resultCount);
	return 0;
}
