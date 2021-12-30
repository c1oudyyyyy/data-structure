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
	printf("n = ");
	scanf("%d", &n);
	L.length = n;
	for(i=0; i<n; i++)
	{
		L.pData[i] = i+1;
	}
	return OK;
}

Status DeleteElem(SeqList &L, int i)//删除逻辑位置为i的元素 
{
	for(int j=i; j<=L.length-1; j++)
	{
		L.pData[j-1] = L.pData[j];
	}
	L.length -= 1;
	return OK;
}

Status numberOff(SeqList L, int m)//出列函数 
{
	int n = 1, i = 0;
	while(L.length != 1)//当只剩一个元素时停止循环 
	{
		while(n != m)//从1报数直至报到m值 
		{
			i++;
			n++;
			if(i >= L.length)//若报数报到最后一个元素则从头开始 
			{
				i -= L.length;
			}
		}
		n = 1;
		printf("%d ", L.pData[i]);//输出恰好报到m值的元素值 
		DeleteElem(L, i+1);//删除恰好报到m值的元素 
	}
	printf("%d \n", L.pData[0]);//输出最后一个元素值 
	return OK;
} 

int main()
{
	SeqList L;
	InitList(L);
	InputElem(L);
	int m;
	printf("m = ");
	scanf("%d", &m);
	printf("出列顺序：\n"); 
	numberOff(L, m);
	return 0;
}
