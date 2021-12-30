/*
判断在某位置时下一次移动的方向有哪些，并标记哪些方向已经走过。
每走到一个位置将此位置信息压栈，直至走到终点，或者栈空时表示没有通路。
*/ 

#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cmath>
using namespace std;
#define MAX 500
 
struct Point//迷宫上的位置结构（栈类型） 
{
    int x, y;//坐标 
    char c;//位置上的符号 
	int vector[4], sum;///0 1 2 3 表示上下左右
    int visit[4];//访问标记 
}point[MAX][MAX];

typedef struct//栈结构 
{  
	Point base[MAX];
    int top;
}SqStack;

SqStack SqStackInit()//初始化栈
{
    SqStack S;
    S.top = -1;
    return S;
}

bool StackEmpty(SqStack S)//判断栈空
{
    if(S.top == -1)
        return true;
    else
        return false;
}

void SqStackPush(SqStack &S, Point x)//入栈
{
    if(S.top == MAX-1)
    {
        cout << "栈满！" << endl;
        return ;
    }
    S.base[++S.top] = x;
}

void SqStackPop(SqStack &S)//出栈
{
    if(S.top == -1)
    {
        cout << "栈空！" << endl;
        return ;
    }
    S.top--;
}

Point GetSqStackTop(SqStack S)//取栈顶元素
{
    return (S.base[S.top]);
}

void init(int n, int m)//对迷宫数据进行初始化 
{
    int a[4] = {1,-1,0,0};
    int b[4] = {0,0,-1,1};
    for(int i=1; i<=n; i++)
        for(int j=1;j<=m;j++)
        {   
			point[i][j].sum = 0;//表示共有几个方向可以走，初始化为0 
            for(int k=0;k<4;k++)//k取0、1、2、3时，依次表示上、下、左、右 
                if(point[i][j].c == '.' && point[i+a[k]][j+b[k]].c == '.')
                {
					point[i][j].vector[k] = 1;//该方向标记 
					point[i][j].sum++;
					point[i][j].visit[k] = 0;//访问标记，可走 
				}
                else//死路，不走 
				{
					point[i][j].vector[k] = 0;
					point[i][j].visit[k] = 1;//访问标记，不能走 
				}
        }
}

void show(int n, int m, char answer[][500])//输出迷宫路径图 
{
    for(int i=1; i<=n; i++)
    {
        for(int j=1; j<=m; j++)
            cout << answer[i][j];
        cout << endl;
    }
}

void solve(int n, int m)//寻找迷宫路径 
{  
	char answer[MAX][MAX];//结果迷宫线路图 
	SqStack S = SqStackInit();//初始化栈 
 	memset(answer, '.', sizeof(answer));//初始化结果迷宫图 
    int x, y, xx, yy;
    cout << "\n请输入入口位置：";
	cin >> x >> y;
	cout << "请输入出口位置：";
	cin >> xx >> yy;
    SqStackPush(S, point[x][y]);//将入口压栈
    while(!StackEmpty(S))//当栈非空时 
    {
        Point top = GetSqStackTop(S);//取栈顶元素 
        //show2(n,m);
        if(point[x][y].visit[0] == 0 && point[x][y].vector[0] == 1)//可以向上走 
    	{
        	point[x++][y].visit[0] = 1;
        	point[x][y].visit[1] = 1;
        	SqStackPush(S,point[x][y]);
   		}
    	else if(point[x][y].visit[1] == 0 && point[x][y].vector[1] == 1)//可以向下走 
    	{
       		point[x--][y].visit[1] = 1;
       		point[x][y].visit[0] = 1;
        	SqStackPush(S,point[x][y]);
    	}
    	else if(point[x][y].visit[2] == 0 && point[x][y].vector[2] == 1)//可以向左走 
    	{
        	point[x][y--].visit[2] = 1;
        	point[x][y].visit[3] = 1;
        	SqStackPush(S,point[x][y]);
    	}
    	else if(point[x][y].visit[3] == 0 && point[x][y].vector[3] == 1)//可以向右走 
    	{
        	point[x][y++].visit[3] = 1;
        	point[x][y].visit[2] = 1;
       		SqStackPush(S,point[x][y]);
    	}
    	//上下左右都走过了 
    	else if(point[x][y].visit[0] == 1 && point[x][y].visit[1] == 1 && point[x][y].visit[2] == 1 && point[x][y].visit[3] == 1)
    	{
			SqStackPop(S);//弹栈 
			if(StackEmpty(S))///当前点上下左右全访问过并且此点不是终点 
        	{
            	cout << "没有可行路径！\n";
				break;
        	}
		}
  		x = GetSqStackTop(S).x;
		y = GetSqStackTop(S).y;
 		if(point[x][y].x == xx && point[x][y].y == yy)//抵达终点 
        {       
			cout<<"\n找到迷宫路线：\n";
            while(!StackEmpty(S))
            {
                Point ans;
                ans.x = GetSqStackTop(S).x;
                ans.y = GetSqStackTop(S).y;
                SqStackPop(S);
             	x = ans.x;
				y = ans.y;
            	answer[x][y] = '@';
            }
            show(n, m, answer);
            break;
        }
    }
 
}
 
int main()
{
    int n, m;
	memset(point, 'x', sizeof(point));//初始化全墙壁
    cout << "欢迎来到迷宫问题\n--------------------------------------------------------\n生成迷宫如下：\n";
    FILE *fp = fopen("迷宫路.txt", "r");
	fscanf(fp, "%d %d", &n, &m);
    int k;
    for(int i=1; i<=n; i++)
    {
        for(int j=1; j<=m; j++)
        {
			fscanf(fp, "%d", &k);
			if(k == 0)
			{
				point[i][j].c = '.';
				cout << point[i][j].c;
			}
			else
				cout << '#';
			point[i][j].x = i;
			point[i][j].y = j;
		}
		cout << endl;
	}
    init(n, m);
    solve(n, m);
    fclose(fp);
    return 0;
}
