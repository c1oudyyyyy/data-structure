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

int InverseList(SeqList L)
{
	int i, t;
	for(i=0; i<L.length/2; i++)
	{
		t = L.pData[i];
		L.pData[i] = L.pData[L.length-1-i];
		L.pData[L.length-1-i] = t;
	}
	return OK;
}

int main()
{
	SeqList L;
	InitList(L);
	InputList(L);
	InverseList(L);
	printf("ÄæÖÃÖ®ºó£º\n");
	ListTraverse(L);
	return 0;
}
