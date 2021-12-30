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

Status DeleteElem(SeqList &L, int i)//ɾ���߼�λ��Ϊi��Ԫ�� 
{
	for(int j=i; j<=L.length-1; j++)
	{
		L.pData[j-1] = L.pData[j];
	}
	L.length -= 1;
	return OK;
}

Status numberOff(SeqList L, int m)//���к��� 
{
	int n = 1, i = 0;
	while(L.length != 1)//��ֻʣһ��Ԫ��ʱֹͣѭ�� 
	{
		while(n != m)//��1����ֱ������mֵ 
		{
			i++;
			n++;
			if(i >= L.length)//�������������һ��Ԫ�����ͷ��ʼ 
			{
				i -= L.length;
			}
		}
		n = 1;
		printf("%d ", L.pData[i]);//���ǡ�ñ���mֵ��Ԫ��ֵ 
		DeleteElem(L, i+1);//ɾ��ǡ�ñ���mֵ��Ԫ�� 
	}
	printf("%d \n", L.pData[0]);//������һ��Ԫ��ֵ 
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
	printf("����˳��\n"); 
	numberOff(L, m);
	return 0;
}
