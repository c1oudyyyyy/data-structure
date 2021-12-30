#include <stdio.h>
#include <stdlib.h>

#define OK 1
#define ERROR 0

#define ROWS 5
#define COLS 5

typedef int Status;

/*思路： 
从第一行开始，找出每行的最小值，然后找出最小值所在列的最大值，
若最大值依然是这个最小值，则输出此元素的位置。 
*/ 
int main()
{
	//创建矩阵 
	int i, j;
	int M[ROWS][COLS];
	printf("输入矩阵元素：\n");
	for(i=0; i<ROWS; i++)
	{
		for(j=0; j<COLS; j++)
		{
			scanf("%d", &M[i][j]); 
		}
	}
	//寻找鞍点
	for(i=0; i<ROWS; i++)
	{
		int min = M[i][0];//初始化最小值为每行第一个 
		int min_j = 0, max_i = i;;//记录最小值所在的列和最大值所在的行，初始化为第一列和第i行 
		for(j=1; j<COLS; j++)
		{
			if(M[i][j] < min)
			{
				min = M[i][j];
				min_j = j;
			}
		}//找到该行的最小值
		//看是否有多个最小值
		int min_j_arr[COLS], k = 0;//储存最小值所在的列数
		for(j=0; j<COLS; j++)
		{
			if(M[i][j] == min)
			{
				min_j_arr[k++] = j; 
			}
		}
		int j_num = k;//储存最小值的列数（该行最小值的个数） 
		//判断在最小值所在列是否有比该最小值大的值，若有则不是鞍点 
		int max = min;//该列最大值
		int sp = 1;//判断是否为鞍点，0为不是，1为是
		for(int o=0; o<j_num; o++)//遍历最小值所在的列 
		{ 
			for(int k = 0; k<ROWS; k++)
			{
				if(M[k][min_j_arr[o]] > max)
				{
					sp = 0;//不是鞍点 
					break;//该点不是鞍点，直接跳出循环 
				}
			} 
			if(sp == 1)//是鞍点，输出值和位置 
			{
				printf("鞍点元素值为：%d，在第%d行，第%d列\n", max, max_i+1, min_j_arr[o]+1);
			}
		}
	} 
	return 0;
}

/*测试数据
3 2 1 1 5
9 2 7 5 11
6 5 7 2 9
7 6 8 6 10
5 3 2 0 6 
*/ 
