#include <iostream>
#include <cstdlib>
using namespace std;

typedef struct pos
{
	int x;
	int y;
}pos;

void score(pos a[], int n, int ss[])
{
	int i, j;
	for(i=1; i<=n; i++)
	{
		int x = a[i].x;
		int y = a[i].y;
		int k = 0;//上下左右有的个数 
		int s = 0;//四个角有的个数 
		int flag = 0;//是否上下左右都有，0代表否 
		for(j = 1; j<=n; j++)//统计上下左右有垃圾的个数 
		{
			if(a[j].x == x+1 && a[j].y == y) k++;
			if(a[j].x == x-1 && a[j].y == y) k++;
			if(a[j].x == x && a[j].y == y+1) k++;
			if(a[j].x == x && a[j].y == y-1) k++;
		}
		if(k == 4)//若该点上下左右都有垃圾 
		{
			flag = 1;//标记 
			s = 0;
			for(j = 1; j<=n; j++)//统计四个角有的个数 
			{
				if(a[j].x == x+1 && a[j].y == y+1) s++;
				if(a[j].x == x+1 && a[j].y == y-1) s++;
				if(a[j].x == x-1 && a[j].y == y+1) s++;
				if(a[j].x == x-1 && a[j].y == y-1) s++;
			}
		}
		if(flag == 1)//评分 
			ss[s]++;
	}
	
	for(i=0; i<5; i++)
		cout << ss[i] << endl;
}

int main()
{
	int n;
	cin >> n;
	int i;
	pos a[256];
	for(i=1; i<=n; i++)
		cin >> a[i].x >> a[i].y;
	int ss[5];//五种得分的个数 
	for(i=0; i<5; i++)//初始化 
		ss[i] = 0;
	score(a, n, ss);
	
	return 0;
}

/*
样例1输入：
7
1 2
2 1
0 0
1 1
1 0
2 0
0 1
样例1输出：
0
0
1
0
0
*/
