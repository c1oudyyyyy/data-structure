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
		int k = 0;//���������еĸ��� 
		int s = 0;//�ĸ����еĸ��� 
		int flag = 0;//�Ƿ��������Ҷ��У�0����� 
		for(j = 1; j<=n; j++)//ͳ�����������������ĸ��� 
		{
			if(a[j].x == x+1 && a[j].y == y) k++;
			if(a[j].x == x-1 && a[j].y == y) k++;
			if(a[j].x == x && a[j].y == y+1) k++;
			if(a[j].x == x && a[j].y == y-1) k++;
		}
		if(k == 4)//���õ��������Ҷ������� 
		{
			flag = 1;//��� 
			s = 0;
			for(j = 1; j<=n; j++)//ͳ���ĸ����еĸ��� 
			{
				if(a[j].x == x+1 && a[j].y == y+1) s++;
				if(a[j].x == x+1 && a[j].y == y-1) s++;
				if(a[j].x == x-1 && a[j].y == y+1) s++;
				if(a[j].x == x-1 && a[j].y == y-1) s++;
			}
		}
		if(flag == 1)//���� 
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
	int ss[5];//���ֵ÷ֵĸ��� 
	for(i=0; i<5; i++)//��ʼ�� 
		ss[i] = 0;
	score(a, n, ss);
	
	return 0;
}

/*
����1���룺
7
1 2
2 1
0 0
1 1
1 0
2 0
0 1
����1�����
0
0
1
0
0
*/
