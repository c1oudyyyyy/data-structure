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


//���ν�b���е�Ԫ����a���еıȽϣ���bԪ�ز���a���к��ʵ�λ�� 
Status ListUnion(SeqList &La, SeqList Lb)
{
	int i, j, k;
	for(j = 0; j < Lb.length; j++)//����b�� 
	{
		for(i = 0; i < La.length; i++)//����a�� 
		{
			//ɾ��a�����ظ�Ԫ��
			if(La.pData[i] == La.pData[i+1])
			{
				for(k=i; k<La.length-1; k++)
				{
					La.pData[k] = La.pData[k+1];
				}
				La.length -= 1;
			}
			//�ҵ�����a��Ԫ�ص�λ�� 
			if(Lb.pData[j] > La.pData[i])
			{
				if(La.length == La.size)//��a������ 
				{
					int *newbase = (int *) realloc(La.pData, (SIZE+INCREMENT) * sizeof(int));
					if(newbase == NULL) exit(ERROR);
					La.pData = newbase;
					La.size += INCREMENT;
				}
				//���뵱ǰԪ��֮ǰ
				for(k=La.length; k>i; k--)
					La.pData[k] = La.pData[k-1];
				La.pData[i] = Lb.pData[j];
				La.length += 1;
				break;	//����ѭ�����ֵ���һ��b��Ԫ�� 
			}
			else if(Lb.pData[j] == La.pData[i])//����ȣ������� 
			{
				j++;
				break;
			}	
		}
		//��Ԫ�ر�a��Ԫ�ض�С�������a���β
		if(Lb.pData[j] < La.pData[La.length-1])
		{
			if(La.length == La.size)//��a������ 
			{
				int *newbase = (int *) realloc(La.pData, (SIZE+INCREMENT) * sizeof(int));
				if(newbase == NULL) exit(ERROR);
				La.pData = newbase;
				La.size += INCREMENT;
			}
			La.pData[La.length] = Lb.pData[j];//�����Ԫ�� 
			La.length += 1;
		}	
	}	
	return OK;
}

int main()
{
	SeqList La, Lb;
	InitList(La);
	InitList(Lb);
	InputElem(La);
	InputElem(Lb);
	ListUnion(La, Lb);
	printf("�ϲ�֮��\n");
	ListTraverse(La);
	return 0;
} 
