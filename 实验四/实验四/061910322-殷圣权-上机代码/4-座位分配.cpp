#include <stdio.h>
#include <stdlib.h>

#define OK 1
#define ERROR 1

typedef int Status;

typedef struct Seat//记录每个座位的数据 
{
	int Num;//座位号码 
	int someone;//判断该座位是否有人 
}Seat;

Status Arrangement(int p[ ],int n)
{
	Seat s[100];
	int i, k;
	for(i=0; i<100; i++)
	{
		s[i].Num = i+1;
		s[i].someone = 0;//0代表空座位，初始状态为空 
	}
	
	for(k=0; k<n; k++)
	{
		int Bought = 0;	//是否买了相邻座位的票，0代表没有 
		//1、有相邻座位 
		for(i=0; i<100; i++)
		{	
			if(s[i].someone == 0 && s[i+p[k]-1].someone == 0 && i/5 == (i+p[k]-1)/5)//若有相邻座位的票 
			{
				for(int j=i; j<i+p[k]; j++)
				{
					printf("%d ", s[j].Num);
					s[j].someone = 1;//该座位已被分配，状态为1
				}
				printf("\n");
				Bought = 1;//完成一次购买相邻座位的票 
				break;
			}
		}
		//如果已经买了相邻座位的票，则进行下一次买票，否则去买不相邻的票 
		if(Bought == 1)
			continue;
		//2、没有相邻座位
		if(96+p[k]>100 || 97+p[k]>100 || 98+p[k]>100 || 99+p[k]>100)
		{
			int vNum=0;
			for(int v=0; v<100; v++)
			{
				if(s[v].someone == 0)
				{
					printf("%d ", s[v].Num);
					s[v].someone = 1;
					vNum++;
				}
				if(vNum == p[k])
				{
					printf("\n");
					break;
				}
			}
		}
	}
	return OK; 
}
	
int main()
{
	int n;
	scanf("%d", &n);
	int p[n];
	int i;
	for(i=0; i<n; i++)
		scanf("%d", &p[i]);
	Arrangement(p, n);
	return 0;
}

/*测试数据

样例输入
4
2 5 4 2
样例输出
1 2
6 7 8 9 10
11 12 13 14
3 4
*/ 
