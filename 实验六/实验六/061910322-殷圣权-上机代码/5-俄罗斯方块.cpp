#include <iostream>
using namespace std;

typedef struct point 
{
	int x, y;
}point;

int main()
{
	int g[19][10], g_new[4][4], i, j, k = 0, col_start;
	//���� 
	for(i=0; i<15; i++)
		for(j=0; j<10; j++)
			cin >> g[i][j];
	for(i=15; i<19; i++)
		for(j=0; j<10; j++)
			g[15][j] = 1;
	for(i=0; i<4; i++)
		for(j=0; j<4; j++)
			cin >> g_new[i][j];
	cin >> col_start;
	//�洢���ͼ������ֵ��λ�� 
	point block[4];
	for(i=0; i<4; i++)
		for(j=0; j<4; j++)
			if(g_new[i][j] == 1)
			{
				block[k].x = i;
				block[k].y = j;
				k++;
			}
	int count = k;
	//��ʼ���䣬����1�غ�ʱֹͣ���� 
	int flag = 0;//�Ƿ����غϵı�־ 
	for(i=1; i<15; i++)
	{
		for(k=0; k<4; k++)
			if(g[i+block[k].x][col_start-1+block[k].y] == 1)
			{
				flag = 1;
				break;
			}
		if(flag) break;
	}
	//���ð��ͼ�� 
	for(k=0; k<count; k++)
		g[i-1+block[k].x][col_start-1+block[k].y] = 1;
	//��ӡ
	for(i=0; i<15; i++)
	{
		for(j=0; j<10; j++)
			cout << g[i][j] << ' ';
		cout << endl;
	}
	return 0;
}
/*
�������ݣ�
0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 1 0 0
0 0 0 0 0 0 1 0 0 0
0 0 0 0 0 0 1 0 0 0
1 1 1 0 0 0 1 1 1 1
0 0 0 0 1 0 0 0 0 0
0 0 0 0
0 1 1 1
0 0 1 1
0 0 0 0
3
���������
0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 1 0 0
0 0 0 0 0 0 1 0 0 0
0 0 0 0 0 0 1 0 0 0
1 1 1 1 1 1 1 1 1 1
0 0 0 0 1 1 0 0 0 0

*/ 
