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
	printf("����Ԫ�ظ�����");
	scanf("%d", &n);
	L.length = n;
	L.size = SIZE;
	printf("����Ԫ�أ�");
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

Status DeleteRepeat(SeqList &L)//ɾ���ظ�Ԫ�� 
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

//���ҳ�����b������c���Ԫ�ز�����d���飬��a����ɾ����c����ͬ��Ԫ�� 
Status DeleteBC_A(SeqList Lb, SeqList Lc, SeqList &La)
{
	//1��ɾ���ظ�Ԫ�� 
	DeleteRepeat(Lb);
	DeleteRepeat(Lc);
	//2���ҳ�bc��ͬԪ�ش�������d
	int d[SIZE];
	int i, j, k = 0;
	for(i=0; i<Lb.length; i++)//����b�� 
	{
		for(j=0; j<Lc.length; j++)//����c��
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
		printf("���ظ�Ԫ��\n");
		return ERROR;
	}
	
	printf("b��c���ظ�Ԫ��Ϊ��");//�����ɾԪ�� 
	for(i=0; i<k; i++)
		printf("%d ", d[i]);
	printf("\n");
	
	//3����a����ɾ������d�е�Ԫ��
	for(j=0; j<k; j++)//����d���� 
	{
		for(i=0; i<La.length; i++)//����a��Ԫ�� 
		{
			if(La.pData[i] == d[j])//�������ɾ��a��Ԫ�� 
			{
				for(int m=i; m<La.length-1; m++)
					La.pData[m] = La.pData[m+1];
				La.length -= 1;
				i--;//����Ԫ�ؾ���ǰ��һ��i-1��֤�´αȽ�����ɾԪ�ص���һ��Ԫ�� 
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
	printf("a��ɾ��Ԫ��֮��\n");
	ListTraverse(La);
}
