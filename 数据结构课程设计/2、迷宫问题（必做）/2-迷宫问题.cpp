/*
�ж���ĳλ��ʱ��һ���ƶ��ķ�������Щ���������Щ�����Ѿ��߹���
ÿ�ߵ�һ��λ�ý���λ����Ϣѹջ��ֱ���ߵ��յ㣬����ջ��ʱ��ʾû��ͨ·��
*/ 

#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cmath>
using namespace std;
#define MAX 500
 
struct Point//�Թ��ϵ�λ�ýṹ��ջ���ͣ� 
{
    int x, y;//���� 
    char c;//λ���ϵķ��� 
	int vector[4], sum;///0 1 2 3 ��ʾ��������
    int visit[4];//���ʱ�� 
}point[MAX][MAX];

typedef struct//ջ�ṹ 
{  
	Point base[MAX];
    int top;
}SqStack;

SqStack SqStackInit()//��ʼ��ջ
{
    SqStack S;
    S.top = -1;
    return S;
}

bool StackEmpty(SqStack S)//�ж�ջ��
{
    if(S.top == -1)
        return true;
    else
        return false;
}

void SqStackPush(SqStack &S, Point x)//��ջ
{
    if(S.top == MAX-1)
    {
        cout << "ջ����" << endl;
        return ;
    }
    S.base[++S.top] = x;
}

void SqStackPop(SqStack &S)//��ջ
{
    if(S.top == -1)
    {
        cout << "ջ�գ�" << endl;
        return ;
    }
    S.top--;
}

Point GetSqStackTop(SqStack S)//ȡջ��Ԫ��
{
    return (S.base[S.top]);
}

void init(int n, int m)//���Թ����ݽ��г�ʼ�� 
{
    int a[4] = {1,-1,0,0};
    int b[4] = {0,0,-1,1};
    for(int i=1; i<=n; i++)
        for(int j=1;j<=m;j++)
        {   
			point[i][j].sum = 0;//��ʾ���м�����������ߣ���ʼ��Ϊ0 
            for(int k=0;k<4;k++)//kȡ0��1��2��3ʱ�����α�ʾ�ϡ��¡����� 
                if(point[i][j].c == '.' && point[i+a[k]][j+b[k]].c == '.')
                {
					point[i][j].vector[k] = 1;//�÷����� 
					point[i][j].sum++;
					point[i][j].visit[k] = 0;//���ʱ�ǣ����� 
				}
                else//��·������ 
				{
					point[i][j].vector[k] = 0;
					point[i][j].visit[k] = 1;//���ʱ�ǣ������� 
				}
        }
}

void show(int n, int m, char answer[][500])//����Թ�·��ͼ 
{
    for(int i=1; i<=n; i++)
    {
        for(int j=1; j<=m; j++)
            cout << answer[i][j];
        cout << endl;
    }
}

void solve(int n, int m)//Ѱ���Թ�·�� 
{  
	char answer[MAX][MAX];//����Թ���·ͼ 
	SqStack S = SqStackInit();//��ʼ��ջ 
 	memset(answer, '.', sizeof(answer));//��ʼ������Թ�ͼ 
    int x, y, xx, yy;
    cout << "\n���������λ�ã�";
	cin >> x >> y;
	cout << "���������λ�ã�";
	cin >> xx >> yy;
    SqStackPush(S, point[x][y]);//�����ѹջ
    while(!StackEmpty(S))//��ջ�ǿ�ʱ 
    {
        Point top = GetSqStackTop(S);//ȡջ��Ԫ�� 
        //show2(n,m);
        if(point[x][y].visit[0] == 0 && point[x][y].vector[0] == 1)//���������� 
    	{
        	point[x++][y].visit[0] = 1;
        	point[x][y].visit[1] = 1;
        	SqStackPush(S,point[x][y]);
   		}
    	else if(point[x][y].visit[1] == 0 && point[x][y].vector[1] == 1)//���������� 
    	{
       		point[x--][y].visit[1] = 1;
       		point[x][y].visit[0] = 1;
        	SqStackPush(S,point[x][y]);
    	}
    	else if(point[x][y].visit[2] == 0 && point[x][y].vector[2] == 1)//���������� 
    	{
        	point[x][y--].visit[2] = 1;
        	point[x][y].visit[3] = 1;
        	SqStackPush(S,point[x][y]);
    	}
    	else if(point[x][y].visit[3] == 0 && point[x][y].vector[3] == 1)//���������� 
    	{
        	point[x][y++].visit[3] = 1;
        	point[x][y].visit[2] = 1;
       		SqStackPush(S,point[x][y]);
    	}
    	//�������Ҷ��߹��� 
    	else if(point[x][y].visit[0] == 1 && point[x][y].visit[1] == 1 && point[x][y].visit[2] == 1 && point[x][y].visit[3] == 1)
    	{
			SqStackPop(S);//��ջ 
			if(StackEmpty(S))///��ǰ����������ȫ���ʹ����Ҵ˵㲻���յ� 
        	{
            	cout << "û�п���·����\n";
				break;
        	}
		}
  		x = GetSqStackTop(S).x;
		y = GetSqStackTop(S).y;
 		if(point[x][y].x == xx && point[x][y].y == yy)//�ִ��յ� 
        {       
			cout<<"\n�ҵ��Թ�·�ߣ�\n";
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
	memset(point, 'x', sizeof(point));//��ʼ��ȫǽ��
    cout << "��ӭ�����Թ�����\n--------------------------------------------------------\n�����Թ����£�\n";
    FILE *fp = fopen("�Թ�·.txt", "r");
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
