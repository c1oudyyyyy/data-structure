#include <stdio.h>
#include <stdlib.h>

#define OK 1
#define ERROR 0

#define MAXSIZE 256

typedef int Status;

typedef struct Triple//��Ԫ�� 
{
	int i, j;
	int data;
}Triple; 

typedef struct SqSMatrix//ϡ����� 
{
	Triple arr[MAXSIZE];
	int Rows, Cols, Nums;
}SqSMatrix;

Status CreateSMatrix(SqSMatrix &M)//����ϡ����� 
{
	int k;
	printf("�������������������ͷ���Ԫ�ظ�����");
	scanf("%d %d %d", &M.Rows, &M.Cols, &M.Nums);
	printf("���������Ԫ�ص�λ�ú�ֵ��\n");
	for(k = 0; k < M.Nums; k++)
		scanf("%d %d %d", &M.arr[k].i, &M.arr[k].j, &M.arr[k].data);	
	return OK;
}

Status PrintSMatrix(SqSMatrix M)//���ϡ����� 
{
	int a, b, k = 0;
	for(a = 0; a < M.Rows; a++)
	{
		for(b = 0; b < M.Cols; b++)
		{
			if(M.arr[k].i == a && M.arr[k].j == b)
			{
				printf("%d ", M.arr[k].data);
				k++;
			}
			else
				printf("0 ");
		}
		printf("\n");
	}
	printf("---------------------------\n"); 
	return OK;
}

/*˼·��
����ϡ�����A��n�У�����Ҫ����n��ɨ�裬
��k������A.arr��j�в����к�Ϊk����Ԫ�飬�����ڣ���Ѵ���Ԫ������B.arr�ĵ�k�С�
*/ 
Status TransposeSMatrix(SqSMatrix A, SqSMatrix &B)//���������ת�� 
{
	//��ϡ�����Aת�ã��������ϡ�����B��
	B.Rows = A.Cols;
	B.Cols =  A.Rows;
	B.Nums = A.Nums;
	if(A.Nums > 0)//����Ԫ�ظ�����Ϊ�� 
	{
		int q = 0;//B.arr�ĵ�ǰλ�� 
		int k, p;
		for(k = 0; k < A.Cols; k++)//��A����Cols��ɨ��
		{
			for(p = 0; p < A.Nums; p++)//ÿ�˶�A��������Ԫ�����ɨ�� 
			{
				if(A.arr[p].j == k)//���к�ΪK���������ҵ���B.arr�ĵ�k��Ԫ�� 
				{
					B.arr[q].i = A.arr[p].j;
					B.arr[q].j = A.arr[p].i;
					B.arr[q].data = A.arr[p].data;
					q++;
				}
			}
		} 
	}
	return OK;
}
int main()
{
	SqSMatrix A, B;
	CreateSMatrix(A);
	printf("ת��ǰ��\n"); 
	PrintSMatrix(A);
	TransposeSMatrix(A, B);
	printf("ת�ú�\n"); 
	PrintSMatrix(B);
	return 0;
}

/*�������� 

*/ 
