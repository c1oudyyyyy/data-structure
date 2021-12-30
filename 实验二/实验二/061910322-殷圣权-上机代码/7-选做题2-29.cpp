#include <stdio.h>
#include <stdlib.h>

#define OK 1
#define ERROR 0

#define SIZE 256
#define INCREMENT 128

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
	int n, i;
	printf("输入元素个数：");
	scanf("%d", &n);
	L.length = n;
	L.size = SIZE;
	printf("输入元素：");
	for(i=0; i<L.length; i++)
		scanf("%d", &L.pData[i]);
	return OK;
}

Status ListTraverse(SeqList L)
{
	int i;
	for(i=0; i<L.length; i++)
		printf("%d ", L.pData[i]);
	printf("\n");
	return OK;
}

Status DeleteRepeat(SeqList &L)//删除重复元素 
{
	int i, j;
	for(i=0; i<L.length; i++)
	{
		if(L.pData[i] == L.pData[i+1])
		{
			for(j=i; j<L.length-1; j++)
				L.pData[j] = L.pData[j+1];
			L.length -= 1;
		}
	}
	return OK;
} 

//先找出既在b表又在c表的元素并存在d数组，在a表中删除和c表相同的元素 
Status DeleteBC_A(SeqList Lb, SeqList Lc, SeqList &La)
{
	//1、删除重复元素 
	DeleteRepeat(Lb);
	DeleteRepeat(Lc);
	//2、找出bc相同元素存在数组d
	int d[SIZE];
	int i, j, k = 0;
	for(i=0; i<Lb.length; i++)//遍历b表 
	{
		for(j=0; j<Lc.length; j++)//遍历c表
		{
			if(Lb.pData[i] == Lc.pData[j])
			{
				d[k++] = Lb.pData[i];
				break; 
			}
		} 
	}
	
	if(k == 0)
	{
		printf("无重复元素\n");
		return ERROR;
	}
	
	printf("b和c表重复元素为：");//输出待删元素 
	for(i=0; i<k; i++)
		printf("%d ", d[i]);
	printf("\n");
	
	//3、在a表中删除数组d中的元素
	for(j=0; j<k; j++)//遍历d数组 
	{
		for(i=0; i<La.length; i++)//遍历a表元素 
		{
			if(La.pData[i] == d[j])//若相等则删除a表元素 
			{
				for(int m=i; m<La.length-1; m++)
					La.pData[m] = La.pData[m+1];
				La.length -= 1;
				i--;//由于元素均向前移一格，i-1保证下次比较是已删元素的下一个元素 
			}
		} 
	} 
	return OK;
}

int main()
{
	SeqList La, Lb, Lc;
	InitList(La);
	InitList(Lb);
	InitList(Lc);
	DeleteBC_A(Lb, Lc, La);
	printf("a表删除元素之后：\n");
	ListTraverse(La);
}
