#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#define LISTINITSIZE 256
#define LISTINCREMENT 128
#define OVERFLOW 0
#define PARA_ERROR -1
#define OK 1

typedef struct SeqList
{
	int *pData;
	int length;
	int size;
}SeqList;
 
int InitList(SeqList &L)
{
	L.pData = (int *)malloc(LISTINITSIZE * sizeof(int));
	if(L.pData == NULL)
		exit(OVERFLOW);
	L.size = LISTINITSIZE;
	L.length = 0;
}

void ListTraverse(SeqList L)
{
	int i;
	for(i=0; i<L.length; i++)
	{
		printf("%d  " , L.pData[i]);
	}
}

void InputList(SeqList &L)
{
	int i=0;
	scanf("%d" , &L.pData[i]);
	while(L.pData[i] != -1)
	{
		i++;
		scanf("%d" , &L.pData[i]);
	}
	L.length = i;
}

int DeleteElem(SeqList &L, int i)
{
	if(i<1 || i>L.length)
		return PARA_ERROR;
	int j;
	for(j=i; j<L.length-1; j++)
		L.pData[j] = L.pData[j+1];
	L.length -= 1;
	return OK;
}

void DeleteRepeat(SeqList &L)
{
	int i, j;
	for(i=0; i<L.length-1; i++)
	{
		for(j=i+1; j<L.length; j++)
		{
			if(L.pData[i] == L.pData[j])
			{
				DeleteElem(L, j);
			}
		}
	}
}

int main()
{
	SeqList L;
	InitList(L);
	InputList(L);
	DeleteRepeat(L);
	printf("删除重复元素之后：\n");
	ListTraverse(L);
	return 0;
}
