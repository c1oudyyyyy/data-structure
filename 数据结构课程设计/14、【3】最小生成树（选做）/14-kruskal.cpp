/*
将边按权值大小升序排序，并依次选择一条边，若选中该边后未构成回路，则选边成功，
当所有点都在树上时，算法结束。
注意要设置一个并查集，标记每个在树上的点，以此来判断是否会构成回路。
*/ 

#include <iostream>
#include <cstdlib>
#include <stdio.h>
using namespace std;
#define MAX_V 256

typedef struct Edge//v1,v2存顶点，weight存权重。
{
    int v1;
    int v2;
    int weight;
}Edge;

typedef struct mGraph
{
    int vexNum, eNum;
    Edge *p;//边集数组 
    int vexName[MAX_V];
}mGraph;

void create_mGraph(mGraph &G)
{
	FILE *fp = fopen("14.txt", "r");
	if(!fp)
	{
		cout << "文件打开失败！\n";
		exit(0);
	}
	fscanf(fp, "%d %d", &G.vexNum, &G.eNum);
    int i,j;
    G.p = (Edge *)malloc(sizeof(Edge)*(G.eNum+1));
    for(i=0; i<G.eNum; i++)
    {
		G.vexName[i] = i+1;
        fscanf(fp, "%d %d %d", &G.p[i].v1, &G.p[i].v2, &G.p[i].weight);
    }
    for(i=0; i<G.eNum; i++)//冒泡排序法，权重从小到大存在边集数组中
    {
        for(j=G.eNum-1; j>i; j--)
        {
            if(G.p[i].weight > G.p[j].weight)
            {
                G.p[G.eNum] = G.p[i];
                G.p[i] = G.p[j];
                G.p[j] = G.p[G.eNum];
            }
        }
    }
}

int Find(int *parent, int g)//返回该点对应的标记，以此判断是否有回路 
{
    while(parent[g] != 0)
    {
        g = parent[g];
    }
    return g;
}

int Finish(mGraph G,int *parent)//判断生成树是否完成，完成的标志是生成树的边等于顶点的数量减1
{
    int i,n = 0;

    for(i=0; i<G.vexNum; i++)
    {
        if(parent[i])
        {
            n++;
        }
    }
    if(n == G.vexNum-1)
    {
        return 1;
    }
    return 0;
}

void MinTree_Kruskal(mGraph G)
{
	printf("Kruskal：\n");
    int i, a, b;
    int min_all = 0;
    int parent[G.vexNum];//对每个点标记为父结点的编号 

    for(i=0; i<G.vexNum; i++)//初始化parent[]
    {
        parent[i] = 0;
    }
    for(i=0; i<G.eNum; i++)
    {
        a = Find(parent,G.p[i].v1);
        b = Find(parent,G.p[i].v2);

        if(a != b)//如果a与b相等则代表a和b在同一颗生成树上，如果a和b连接则为生成环，不符合生成树
        {
            parent[a] = b;//标记 
            printf("%d->%d   %d\n", G.p[i].v1, G.p[i].v2, G.p[i].weight);
            min_all += G.p[i].weight;
        }
        if(Finish(G,parent))//完成后返回
        {
			printf("权值之和为：%d\n", min_all);
            return ;
        }
    }
	
}

int  main()
{
    mGraph G;
    create_mGraph(G);
    MinTree_Kruskal(G);
    return 0;
}


