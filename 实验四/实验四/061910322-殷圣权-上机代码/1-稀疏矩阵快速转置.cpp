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

Status CreateSMatrix(SqSMatrix &M)//创建稀疏矩阵——————行优先 
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
遍历两次A的三元组，第一次统计A中每列三元组的个数，即B中每行三元组的个数，
以便算出B每行三元组的起始位置，第二次遍历A时把三元组放在B中相应位置。
*/ 
Status FastTransposeSMatrix(SqSMatrix A, SqSMatrix &B)
{
	//将稀疏矩阵A转置，结果放在稀疏矩阵B中
	B.Cols = A.Rows;
	B.Rows = A.Cols;
	B.Nums = A.Nums;
	if(A.Nums > 0)//非零元素个数不为零
	{
		//1、统计A中每列的非零元素个数，存在数组rowNum中 
		int rowNum[A.Cols];
		int k, p, q;
		for(k = 0; k < A.Cols; k++)//数组清零 
			rowNum[k] = 0;
		for(p = 0; p < A.Nums; p++)//统计A每列（即B每行）非零元素个数
			rowNum[A.arr[p].j]++;
		//2、计算B中每行三元组的起始位置,存在数组rowStart中 
		int rowStart[A.Cols];
		rowStart[0] = 0;
		for(k = 1; k < A.Cols; k++)
			rowStart[k] = rowStart[k-1] + rowNum[k-1];//第k行的起始位置 = 上一行的起始位置 + 上一行的非零元素个数 
		//3、遍历A的三元组，进行转置
		for(p = 0; p < A.Nums; p++)
		{
			q = rowStart[A.arr[p].j];//取出B当前行的起始位置
			B.arr[q].i = A.arr[p].j;
			B.arr[q].j = A.arr[p].i;
			B.arr[q].data = A.arr[p].data;
			rowStart[A.arr[p].j]++;//B当前行起始位置+1，为该行下一个三元组的放入做准备 
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
	FastTransposeSMatrix(A, B);
	printf("转置后：\n"); 
	PrintSMatrix(B);
	return 0;
}

/*测试数据 
5 6 5
0 2 4
1 1 6
3 0 5
3 4 3
4 2 7
*/ 
