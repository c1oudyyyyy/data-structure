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
	printf("请输入元素个数：");
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
	for(i=1; i<=L.length-1; i++)//length-1次冒泡 
	{
		for(j=0; j<L.length-i; j++)//前length-i个元素两两比较 
		{
			if(L.pData[j] > L.pData[j+1]) //若比后面的元素大则交换 
			{
				t = L.pData[j];
				L.pData[j] = L.pData[j+1];
				L.pData[j+1] = t;//t为中间变量，进行交换
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
	printf("冒泡排序后：\n"); 
	ListTraverse(L);
	return 0;
}
