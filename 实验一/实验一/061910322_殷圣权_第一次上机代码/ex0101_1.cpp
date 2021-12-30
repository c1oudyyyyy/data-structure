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

//1����ʼ�� 
int InitList(SeqList &L)
{
	L.pData = (int *)malloc(LISTINITSIZE * sizeof(int));
	if(L.pData == NULL)
		exit(OVERFLOW);
	L.size = LISTINITSIZE;
	L.length = 0;
}

//2������ 
void DestroyList(SeqList &L)
{
	if(L.pData != NULL)
	{
		free(L.pData);
		L.pData = NULL;
	}
	L.length = 0;
	L.size = 0;
}

//3����� 
void ClearList(SeqList &L)
{
	L.length = 0;
}

//4����ȡ 
int GetElem(SeqList L, int i)
{
	if(i<1 || i>L.length)
		return PARA_ERROR;
	return L.pData[i-1];
}

//5������ 
int LocateElem(SeqList L, int e)
{
	int i;
	for(i=0; i<L.length; i++)
	{
		if(L.pData[i] == e)
			return i+1;
	}
	return OVERFLOW;
}

//6������ 
int InsertElem(SeqList &L, int i, int e)
{
	if(i<1 || i>L.length+1)
		return PARA_ERROR;
	if(L.length = L.size)
	{
		int *newbase = (int*)realloc(L.pData, (L.size+LISTINCREMENT) * sizeof(int));
		if(newbase == NULL)
			exit(OVERFLOW);
		L.pData = newbase;
		L.size += LISTINCREMENT;
	}
	int j;
	for(j=L.length-1; j>=i-1; j--)
		L.pData[j+1] = L.pData[j];
	L.pData[i-1] = e;
	L.length += 1;
	return OK;
}

//7��ɾ�� 
int DeleteElem(SeqList &L, int i)
{
	if(i<1 || i>L.length)
		return PARA_ERROR;
	int j;
	for(j=i-1; j<L.length-1; j++)
		L.pData[j] = L.pData[j+1];
	L.length -= 1;
	return OK;
}

//8��������� 
void ListTraverse(SeqList L)
{
	int i;
	printf("\n");
	for(i=0; i<L.length; i++)
	{
		printf("%d  " , L.pData[i]);
	}
	printf("\n����Ϊ����˳���\n");
}

//9������ 
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

//10���п�
bool ListEmpty(SeqList L)
{
	if(L.length == 0)
		return true;
	return false;
} 
 
//11����ȡ����
int ListLength(SeqList L)
{
 	return L.length;
}

//12������ǰ�� 
int PriorElem(SeqList L, int cur_e)
{
	int i;
	for(i=0; i<L.length; i++)
  	{
  		if(L.pData[i] == cur_e && i>0)
  			return L.pData[i-1];
	}
	return OVERFLOW;
}

//13�����غ��
int NextElem(SeqList L, int cur_e)
{
	int i;
	for(i=0; i<L.length; i++)
	{
		if(L.pData[i] == cur_e && i<=L.length-2)
			return L.pData[i+1];
	}
	return OVERFLOW;
}

//14���滻Ԫ��
int SetElem(SeqList &L, int i, int e)
{
	if(i<1 || i>L.length)
		return PARA_ERROR;
	L.pData[i-1] = e;
	return OK;	 
}

//���Ժ��� 
int main()
{	
	return 0;
}
