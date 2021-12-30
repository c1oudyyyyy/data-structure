#include <stdio.h>
#include <stdlib.h>

#define OK 1
#define ERROR 0

#define SIZE 256

typedef int Status;

typedef struct SeqList
{
	int *pData;
	int length;
	int size;
}SeqList;

Status InitList(SeqList &L)
{
	L.pData = (int *) malloc(SIZE * sizeof(int));
	if(L.pData == NULL) exit(ERROR);
	L.length = 0;
	L.size = SIZE;
	return OK;
}

Status InputElem(SeqList &L)
{
	int n, i;
	printf("������Ԫ�ظ�����");
	scanf("%d", &n);
	L.length = n;
	for(i=0; i<n; i++)
	{
		scanf("%d", &L.pData[i]);
	}
	return OK;
}

Status ListTraverse(SeqList L)
{
	for(int i=0; i<L.length; i++)
	{
		printf("%d ", L.pData[i]);
	}
	printf("\n");
	return OK;
}

Status BubbleSort(SeqList &L)
{
	int i, j, t;
	for(i=1; i<=L.length-1; i++)//length-1��ð�� 
	{
		for(j=0; j<L.length-i; j++)//ǰlength-i��Ԫ�������Ƚ� 
		{
			if(L.pData[j] > L.pData[j+1]) //���Ⱥ����Ԫ�ش��򽻻� 
			{
				t = L.pData[j];
				L.pData[j] = L.pData[j+1];
				L.pData[j+1] = t;//tΪ�м���������н���
			}
		}
	}
	return OK;
}

int main()
{
	SeqList L;
	InitList(L);
	InputElem(L);
	BubbleSort(L);
	printf("ð�������\n"); 
	ListTraverse(L);
	return 0;
}
