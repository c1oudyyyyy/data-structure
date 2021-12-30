#include <stdio.h>
#include <stdlib.h>

#define OK 1
#define ERROR 0
#define CONFLICT 0

#define SIZE 256
#define INCREMENT 128

#define N 8//�ʺ�����

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

//��ʼ��˳��ջ-����ʺ�λ�� 
Status InitStack(SeqStack &S)
{
	S.pBase = (point *) malloc(SIZE * sizeof(point));
	if(S.pBase == NULL) exit(ERROR);
	S.pTop = S.pBase;
	S.size = SIZE;
	return OK;
}

//ѹջ-����һ���ʺ�
Status Push(SeqStack &S, point newqueen)
{
	if(S.pBase != NULL)//ջ����
	{
		if(S.pTop - S.pBase == S.size)//ջ��
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
	printf("ջ������,�޷�ѹջ\n");
	return ERROR;
}

//��ջ-����һ���ʺ�
Status Pop(SeqStack &S, point &curqueen)
{
	if(S.pBase != NULL && S.pTop != S.pBase)//ջ�����ҷǿ�
	{
		curqueen.col = S.pTop->col;
		curqueen.row = S.pTop->row;
		S.pTop--;
		return OK;
	}
	printf("ջ�����ڻ�Ϊ��ջ���޷���ջ\n");
	return ERROR;
}

//�ж��Ƿ��ͻ
Status JudgeConfliction(SeqStack S, point newqueen)
{
	point *pCurqueen;
	int x1, y1, x2, y2;
	x1 = newqueen.col;
	y1 = newqueen.row;
	pCurqueen = S.pBase;
	Status tag = OK;
	while(pCurqueen < S.pTop-1)//���ջ��֮���Ԫ�ضԱȣ��ж��Ƿ��ͻ 
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

//������
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

//�ʺ����-�ݹ�
Status PlaceQueen(int row, int &resultCount, SeqStack &StkQueen)
{
	int col;
	point curqueen;
	for(col = 1; col <= N; col++)
	{
		curqueen.col = col;
		curqueen.row = row;
		Push(StkQueen, curqueen);//ѹջ 
		Status ret = JudgeConfliction(StkQueen, curqueen);//����Լ����Ԫ�ضԱȣ��ж��Ƿ��ͻ������ͻ��ջ  
		if(ret == OK)//δ��ͻ���ֵ���һ�� 
		{
			if(row < N)//δ�������һ�У������ݹ���һ�� 
				PlaceQueen(row + 1, resultCount, StkQueen);
			else
			{
				OutputResult(StkQueen, N);//���һ�еĺ���λ�÷��ûʺ�֮�������� 
				resultCount++;//�����+1 
			}
		}
		Pop(StkQueen, curqueen);//��ͻ����ջ 
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
	printf("%d�ʺ����⹲��%d�ֽ��\n", N, resultCount);
	return 0;
}
