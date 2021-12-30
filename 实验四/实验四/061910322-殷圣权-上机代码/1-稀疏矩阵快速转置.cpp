#include <stdio.h>
#include <stdlib.h>

#define OK 1
#define ERROR 0

#define MAXSIZE 256

typedef int Status;

typedef struct Triple
{
	int i, j;
	int data;
}Triple; 

typedef struct SqSMatrix
{
	Triple arr[MAXSIZE];
	int Rows, Cols, Nums;
}SqSMatrix;

Status CreateSMatrix(SqSMatrix &M)//����ϡ����󡪡��������������� 
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
��������A����Ԫ�飬��һ��ͳ��A��ÿ����Ԫ��ĸ�������B��ÿ����Ԫ��ĸ�����
�Ա����Bÿ����Ԫ�����ʼλ�ã��ڶ��α���Aʱ����Ԫ�����B����Ӧλ�á�
*/ 
Status FastTransposeSMatrix(SqSMatrix A, SqSMatrix &B)
{
	//��ϡ�����Aת�ã��������ϡ�����B��
	B.Cols = A.Rows;
	B.Rows = A.Cols;
	B.Nums = A.Nums;
	if(A.Nums > 0)//����Ԫ�ظ�����Ϊ��
	{
		//1��ͳ��A��ÿ�еķ���Ԫ�ظ�������������rowNum�� 
		int rowNum[A.Cols];
		int k, p, q;
		for(k = 0; k < A.Cols; k++)//�������� 
			rowNum[k] = 0;
		for(p = 0; p < A.Nums; p++)//ͳ��Aÿ�У���Bÿ�У�����Ԫ�ظ���
			rowNum[A.arr[p].j]++;
		//2������B��ÿ����Ԫ�����ʼλ��,��������rowStart�� 
		int rowStart[A.Cols];
		rowStart[0] = 0;
		for(k = 1; k < A.Cols; k++)
			rowStart[k] = rowStart[k-1] + rowNum[k-1];//��k�е���ʼλ�� = ��һ�е���ʼλ�� + ��һ�еķ���Ԫ�ظ��� 
		//3������A����Ԫ�飬����ת��
		for(p = 0; p < A.Nums; p++)
		{
			q = rowStart[A.arr[p].j];//ȡ��B��ǰ�е���ʼλ��
			B.arr[q].i = A.arr[p].j;
			B.arr[q].j = A.arr[p].i;
			B.arr[q].data = A.arr[p].data;
			rowStart[A.arr[p].j]++;//B��ǰ����ʼλ��+1��Ϊ������һ����Ԫ��ķ�����׼�� 
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
	FastTransposeSMatrix(A, B);
	printf("ת�ú�\n"); 
	PrintSMatrix(B);
	return 0;
}

/*�������� 
5 6 5
0 2 4
1 1 6
3 0 5
3 4 3
4 2 7
*/ 
