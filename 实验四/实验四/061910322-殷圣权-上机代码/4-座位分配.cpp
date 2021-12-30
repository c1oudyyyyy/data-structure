#include <stdio.h>
#include <stdlib.h>

#define OK 1
#define ERROR 1

typedef int Status;

typedef struct Seat//��¼ÿ����λ������ 
{
	int Num;//��λ���� 
	int someone;//�жϸ���λ�Ƿ����� 
}Seat;

Status Arrangement(int p[ ],int n)
{
	Seat s[100];
	int i, k;
	for(i=0; i<100; i++)
	{
		s[i].Num = i+1;
		s[i].someone = 0;//0�������λ����ʼ״̬Ϊ�� 
	}
	
	for(k=0; k<n; k++)
	{
		int Bought = 0;	//�Ƿ�����������λ��Ʊ��0����û�� 
		//1����������λ 
		for(i=0; i<100; i++)
		{	
			if(s[i].someone == 0 && s[i+p[k]-1].someone == 0 && i/5 == (i+p[k]-1)/5)//����������λ��Ʊ 
			{
				for(int j=i; j<i+p[k]; j++)
				{
					printf("%d ", s[j].Num);
					s[j].someone = 1;//����λ�ѱ����䣬״̬Ϊ1
				}
				printf("\n");
				Bought = 1;//���һ�ι���������λ��Ʊ 
				break;
			}
		}
		//����Ѿ�����������λ��Ʊ���������һ����Ʊ������ȥ�����ڵ�Ʊ 
		if(Bought == 1)
			continue;
		//2��û��������λ
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

/*��������

��������
4
2 5 4 2
�������
1 2
6 7 8 9 10
11 12 13 14
3 4
*/ 
