#include <stdio.h>
#include <stdlib.h>

#define OK 1
#define ERROR 0

#define MAXSIZE 256

typedef int Status;

typedef struct Triple//三元组 
{
	int i, j;
	int data;
}Triple; 

typedef struct SqSMatrix//稀疏矩阵 
{
	Triple arr[MAXSIZE];
	int Rows, Cols, Nums;
}SqSMatrix;

Status CreateSMatrix(SqSMatrix &M)//创建稀疏矩阵 
{
	int k;
	printf("输入矩阵的行数、列数和非零元素个数：");
	scanf("%d %d %d", &M.Rows, &M.Cols, &M.Nums);
	printf("输入个非零元素的位置和值：\n");
	for(k = 0; k < M.Nums; k++)
		scanf("%d %d %d", &M.arr[k].i, &M.arr[k].j, &M.arr[k].data);	
	return OK;
}

Status PrintSMatrix(SqSMatrix M)//输出稀疏矩阵 
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

/*思路：
假设稀疏矩阵A有n列，则需要进行n躺扫描，
第k躺是在A.arr的j中查找列号为k的三元组，若存在，则把此三元组存放在B.arr的第k行。
*/ 
Status TransposeSMatrix(SqSMatrix A, SqSMatrix &B)//列序遍历的转置 
{
	//将稀疏矩阵A转置，结果放在稀疏矩阵B中
	B.Rows = A.Cols;
	B.Cols =  A.Rows;
	B.Nums = A.Nums;
	if(A.Nums > 0)//非零元素个数不为零 
	{
		int q = 0;//B.arr的当前位置 
		int k, p;
		for(k = 0; k < A.Cols; k++)//对A进行Cols趟扫描
		{
			for(p = 0; p < A.Nums; p++)//每趟对A的所有三元组进行扫描 
			{
				if(A.arr[p].j == k)//若列号为K，即依次找到了B.arr的第k行元素 
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
	printf("转置前：\n"); 
	PrintSMatrix(A);
	TransposeSMatrix(A, B);
	printf("转置后：\n"); 
	PrintSMatrix(B);
	return 0;
}

/*测试数据 

*/ 
