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

//˳��ջ��ʼ�� 
Status InitStack(SeqStack &S)
{
	S.pBase = (int *) malloc(SIZE * sizeof(int));
	if(S.pBase == NULL) exit(ERROR);
	S.pTop = S.pBase;
	S.size = SIZE;
	return OK;
}

//����˳��ջ 
Status DestroyStack(SeqStack &S)
{
	if(S.pBase != NULL)//��˳��ջ�Ѵ��� 
	{
		free(S.pBase);
		S.pBase = NULL;
	}
	S.pTop = NULL;
	S.size = 0;
	printf("��ջ�ѱ�����\n");
	return OK;
}

//���˳��ջ
Status ClearStack(SeqStack &S)
{
	if(S.pBase != NULL && S.pTop != S.pBase)//��˳��ջ�Ѵ����ҷǿ�
	{
		S.pTop = S.pBase;
		printf("��ջ�ѱ����\n");
		return OK;
	}
	printf("��ջ�����ڻ��ѱ����\n");
	return ERROR; 
}

//�п�
bool StackEmpty(SeqStack S)
{
	if(S.pBase != NULL)//��˳��ջ�Ѵ���
	{
		if(S.pTop == S.pBase)
		{
			return true;
		}
		return false;
	}
	printf("��˳��ջ������\n");
	return true;
}

//��ȡ����
int StackLength(SeqStack S)
{
	if(S.pBase != NULL)//��˳��ջ�Ѵ���
	{
		return (S.pTop - S.pBase);//ָ���׵�ַ��� 
	}
	printf("��˳��ջ������\n");
	return ERROR;
}

//��ȡջ��Ԫ��
Status GetTop(SeqStack S, int &e)
{
	if(S.pBase != NULL && S.pTop != S.pBase)//˳��ջ�����ҷǿ� 
	{
		e = *(S.pTop - 1);
		return OK;
	}
	printf("��˳��ջ�����ڻ�Ϊ��ջ\n");
	return ERROR;
}

//�������
Status StackTraverse(SeqStack S)
{
	if(S.pBase != NULL && S.pTop != S.pBase)//˳��ջ�����ҷǿ�
	{
		int i;
		for(i = 0; i < S.pTop - S.pBase; i++)
		{
			printf("%d ", S.pBase[i]);
		}
		printf("\n");
		return OK;
	}
	printf("��˳��ջ�����ڻ�Ϊ��ջ\n");
	return ERROR;
}

//ѹջ
Status Push(SeqStack &S, int e)
{
	if(S.pBase != NULL)//˳��ջ����
	{
		if(S.pTop - S.pBase == S.size)//ջ��
		{
			S.pBase = (int *) realloc(S.pBase, (S.size+INCREMENT) * sizeof(int));
			if(S.pBase == NULL) exit(ERROR);
			S.pTop = S.pBase + S.size;//���¶���ջ��ָ�� 
			S.size += INCREMENT;
		} 
		*S.pTop++ = e;
		return OK;
	}
	printf("��˳��ջ������\n");
	return ERROR; 
}

//��ջ
Status Pop(SeqStack &S, int &e)
{
	if(S.pBase != NULL && S.pTop != S.pBase)//˳��ջ�����ҷǿ�
	{
		e = *--S.pTop;
		return OK;
	}
	printf("��˳��ջ�����ڻ�Ϊ��ջ\n");
	return ERROR;
}

//����Ԫ��
Status InputElem(SeqStack &S)
{
	if(S.pBase != NULL)
	{
		int i, n;
		printf("����Ԫ�ظ�����");
		scanf("%d", &n);
		S.pTop = S.pBase + n;
		printf("����Ԫ�أ�");
		for(i = 0; i < n; i++)
		{
			scanf("%d", &S.pBase[i]);
		}
		return OK;
	}
	printf("��˳��ջ������\n");
	return ERROR;
} 

//���Ժ��� 
int main()
{
	SeqStack S;
	InitStack(S);
	InputElem(S);
	StackTraverse(S);
	printf("ѹջ��");
	Push(S, 6);
	StackTraverse(S);
	int e;
	Pop(S, e);
	printf("��ջ��");
	StackTraverse(S);
	printf("����Ԫ�أ�%d\n", e);
	GetTop(S, e);
	printf("��ʱ��ջ��Ԫ�أ�%d\n", e);
	printf("��ʱ��Ԫ�ظ�����%d\n", StackLength(S));
	if(!StackEmpty(S))
		printf("��ջ��Ϊ��\n");
	ClearStack(S);
	if(StackEmpty(S))
		printf("��ջΪ��\n");
	DestroyStack(S);
	StackEmpty(S);
	return 0;
}
