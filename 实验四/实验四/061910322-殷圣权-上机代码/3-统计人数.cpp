#include <stdio.h>
#include <stdlib.h>

#define OK 1
#define ERROR 0

typedef int Status;

typedef struct point
{
	int x;
	int y;
}point;

int main()
{
	//1��n�������λ�ü�¼
	int n, k, t, x1, yd, xr, yu;
	printf("n��k��t��x1��yd��xr��yu�ֱ�Ϊ�� ");
	scanf("%d %d %d %d %d %d %d", &n, &k, &t, &x1, &yd, &xr, &yu);
	int i, j;
	point people[n][t];
	for(i=0; i<n; i++)//��������¼
	{
		for(j=0; j<t; j++)
		{
			scanf("%d %d", &people[i][j].x, &people[i][j].y);
		}
	}
	
	//2���ж��Ƿ񾭹�����
	int pass = 0, stay = 0, p = 0, q;
	for(i=0; i<n; i++)
	{
		q = 0;//�ж��Ƿ񾭹� 
		p = 0;//�ж��Ƿ��� 
		for(j=0; j<t; j++)
		{
			if(people[i][j].x>=x1 && people[i][j].x<=xr && people[i][j].y>=yd && people[i][j].y<=yu)
			{
				q = 1;
				p++;
			}
			else
			{
				if(p >= k) 
					;
				else
					p = 0;//��û��������������p=0 
			}
		}
		if(q == 1)
			pass++;
		if(p >= k)
			stay++;
	}
	printf("%d\n%d", pass, stay);
	return 0;
}

/*��������

��������1��
5 2 6 20 40 100 80
100 80 100 80 100 80 100 80 100 80 100 80
60 50 60 46 60 42 60 38 60 34 60 30
10 60 14 62 18 66 22 74 26 86 30 100
90 31 94 35 98 39 102 43 106 47 110 51
0 20 4 20 8 20 12 20 16 20 20 20
�������1��
3
2

��������2��
1 3 8 0 0 10 10
-1 -1 0 0 0 0 -1 -1 0 0 -1 -1 0 0 0 0
�������2��
1
0

*/ 
