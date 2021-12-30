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
}point;//点位置 

typedef struct point_data
{
	int Color;
	int Visited;
	point seat;
}point_data;//点的颜色、是否被染色以及位置 

typedef struct Stack
{
	point_data *pBase;
	point_data *pTop;
}Stack;

Status InitStack(Stack &s)//初始化顺序栈 
{
	s.pBase = (point_data *) malloc(SIZE * sizeof(point_data));
	if(s.pBase == NULL) exit(ERROR);
	s.pTop = s.pBase;
	return OK;
}

Status Push(Stack &s, point_data e)//压栈 
{
	if(s.pTop - s.pBase == SIZE) return ERROR;
	*s.pTop++ = e;
	return OK;
}

Status Pop(Stack &s, point_data &e)//弹栈 
{
	if(s.pTop == s.pBase) return ERROR;
	e = *--s.pTop;
	return OK;
}

bool StackEmpty(Stack s)//判空 
{
	if(s.pTop == s.pBase) return true;
	else return false;
}

point_data g[M][N];//生成一个图像区域 
Status CreateGDS(point_data g[M][N])
{
	int i, j;
	for(i=0; i<M; i++)
		for(j=0; j<N; j++)
		{
			g[i][j].seat.x = i;
			g[i][j].seat.y = j;
			g[i][j].Visited = 0;//0代表未被染色，1代表被染色 
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

Status ShowGraphArray(point_data g[M][N])//打印图像 
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

//染色思路： 
Status RegionFilling(point_data g[M][N], point Cur, int NewColor) 
{
	Stack s;
	InitStack(s);
	point_data e;
	int OldColor = g[Cur.x][Cur.y].Color;//存储染色前的颜色 
	
	Push(s, g[Cur.x][Cur.y]);
	while(!StackEmpty(s))//栈空时，停止循环 
	{
		Pop(s,e);//弹栈并染色 
		Cur = e.seat;
		g[Cur.x][Cur.y].Color = NewColor;//染色 
		g[Cur.x][Cur.y].Visited = 1;//标记为1，说明已被染色 
		//若相邻点存在且需要染色则压栈
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
	Start.x = 5;//染色位置为（5，5） 
	Start.y = 5;
	RegionFilling(g, Start, 1);
	printf("染色之后：\n");
	ShowGraphArray(g);
	return 0;
}

