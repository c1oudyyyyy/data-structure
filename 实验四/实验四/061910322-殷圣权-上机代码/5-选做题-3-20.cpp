#include <stdio.h>
#include <stdlib.h>

#define OK 1
#define ERROR 0

#define SIZE 256

#define M	8
#define N	8

typedef int Status;

typedef struct
{
	int x;
	int y;
}point;//��λ�� 

typedef struct point_data
{
	int Color;
	int Visited;
	point seat;
}point_data;//�����ɫ���Ƿ�Ⱦɫ�Լ�λ�� 

typedef struct Stack
{
	point_data *pBase;
	point_data *pTop;
}Stack;

Status InitStack(Stack &s)//��ʼ��˳��ջ 
{
	s.pBase = (point_data *) malloc(SIZE * sizeof(point_data));
	if(s.pBase == NULL) exit(ERROR);
	s.pTop = s.pBase;
	return OK;
}

Status Push(Stack &s, point_data e)//ѹջ 
{
	if(s.pTop - s.pBase == SIZE) return ERROR;
	*s.pTop++ = e;
	return OK;
}

Status Pop(Stack &s, point_data &e)//��ջ 
{
	if(s.pTop == s.pBase) return ERROR;
	e = *--s.pTop;
	return OK;
}

bool StackEmpty(Stack s)//�п� 
{
	if(s.pTop == s.pBase) return true;
	else return false;
}

point_data g[M][N];//����һ��ͼ������ 
Status CreateGDS(point_data g[M][N])
{
	int i, j;
	for(i=0; i<M; i++)
		for(j=0; j<N; j++)
		{
			g[i][j].seat.x = i;
			g[i][j].seat.y = j;
			g[i][j].Visited = 0;//0����δ��Ⱦɫ��1����Ⱦɫ 
			g[i][j].Color = 0;
		}
		
	for(i=2; i<5; i++)
		for(j=2; j<4; j++)
			g[i][j].Color = 9;
			
	for(i=5; i<M-1; i++)
		for(j=3; j<6; j++)
			g[i][j].Color = 9;
	
	return OK;
}

Status ShowGraphArray(point_data g[M][N])//��ӡͼ�� 
{
	int i, j;
	for(i=0; i<M; i++)
	{
		for(j=0; j<N; j++)
			printf("%d ", g[i][j].Color);
		printf("\n");
	}
	return OK;
}

//Ⱦɫ˼·�� 
Status RegionFilling(point_data g[M][N], point Cur, int NewColor) 
{
	Stack s;
	InitStack(s);
	point_data e;
	int OldColor = g[Cur.x][Cur.y].Color;//�洢Ⱦɫǰ����ɫ 
	
	Push(s, g[Cur.x][Cur.y]);
	while(!StackEmpty(s))//ջ��ʱ��ֹͣѭ�� 
	{
		Pop(s,e);//��ջ��Ⱦɫ 
		Cur = e.seat;
		g[Cur.x][Cur.y].Color = NewColor;//Ⱦɫ 
		g[Cur.x][Cur.y].Visited = 1;//���Ϊ1��˵���ѱ�Ⱦɫ 
		//�����ڵ��������ҪȾɫ��ѹջ
		if(Cur.x<M && !g[Cur.x+1][Cur.y].Visited && g[Cur.x+1][Cur.y].Color==OldColor)
			Push(s ,g[Cur.x+1][Cur.y]);
		if(Cur.x>0 && !g[Cur.x-1][Cur.y].Visited && g[Cur.x-1][Cur.y].Color==OldColor)
			Push(s, g[Cur.x-1][Cur.y]);
		if(Cur.y<N && !g[Cur.x][Cur.y+1].Visited && g[Cur.x][Cur.y+1].Color==OldColor)
			Push(s, g[Cur.x][Cur.y+1]);
		if(Cur.y>0 && !g[Cur.x][Cur.y-1].Visited && g[Cur.x][Cur.y-1].Color==OldColor)
			Push(s, g[Cur.x][Cur.y-1]);
	}
	return OK;
}

int main()
{
	CreateGDS(g);
	ShowGraphArray(g);
	point Start;
	Start.x = 5;//Ⱦɫλ��Ϊ��5��5�� 
	Start.y = 5;
	RegionFilling(g, Start, 1);
	printf("Ⱦɫ֮��\n");
	ShowGraphArray(g);
	return 0;
}

