#include <iostream>
#include <cstdlib>
#include <stdio.h>
using namespace std;

#define MAX_V 256
#define INFINITY 9999

typedef struct mGraph
{
	int vexName[MAX_V];
	int adjMatrix[MAX_V][MAX_V];
	int vexNum, eNum;
}mGraph;

typedef struct closest//辅助结构 
{
	int vexcode;
	int lowcost;
}closest;

void create_mGraph(mGraph &G)
{
	FILE *fp = fopen("14.txt", "r");
	if(!fp)
	{
		cout << "文件打开失败！\n";
		exit(0);
	}
	fscanf(fp, "%d %d", &G.vexNum, &G.eNum);
	int i, j, weight, k;
	for(i=1; i<=G.vexNum; i++)
	{
		for(j=1; j<=G.vexNum; j++)
		{
			if(i != j)
				G.adjMatrix[i][j] = INFINITY;
			else
				G.adjMatrix[i][j] = 0;
		}
	}
	for(k=1; k<=G.eNum; k++)
	{
		G.vexName[k] = k;
		fscanf(fp, "%d %d %d", &i, &j, &weight);
		G.adjMatrix[i][j] = weight;
		G.adjMatrix[j][i] = weight;
	}
	fclose(fp);
}

void  minSpanningTree_prim(mGraph G, int v)//利用普利姆算法，从顶点v出发求最小生成树 
{
	int i, j, k, min, min_all = 0;
	closest clo[MAX_V];//初始化clo数组
	for(j=1; j<=G.vexNum; j++) 
	{
		clo[j].vexcode = v;
		clo[j].lowcost = G.adjMatrix[v][j];
	}
	clo[v].lowcost = 0;//标记v已经被选中（第一个被选中的麦田） 
	for(i=2; i<=G.vexNum; i++)//将剩余的顶点加入最小生成树 
	{
		min = INFINITY;
		for(j=1; j<=G.vexNum; j++)//在clo数组中寻找lowcost非零的最小值 
		{
			if(clo[j].lowcost && clo[j].lowcost < min)
			{
				min = clo[j].lowcost;
				k = j;
			}
		}
		cout << "麦田" << k << "与" << "麦田" << clo[k].vexcode << '\t';
		min_all += min;//累加修建水渠的代价 
		clo[k].lowcost = 0;//选中本轮中lowcost最小的顶点 
		for(j=1; j<=G.vexNum; j++)//更新clo数组 
		{
			if(G.adjMatrix[k][j] < clo[j].lowcost)//不在树上的顶点到顶点k的距离比原来的lowcost小 
			{
				clo[j].lowcost = G.adjMatrix[k][j];
				clo[j].vexcode = k;
			}
		}
	}
	cout << '\n' << min_all << endl;
}

int main()
{
	mGraph G;
	create_mGraph(G);
	minSpanningTree_prim(G, 1);
	return 0;
}

/*
输入样例:
4 4
1 2 1 
2 3 4
2 4 2
3 4 3  
输出样例:
6  
建立以下3条水渠：麦田1与麦田2、麦田2与麦田4、麦田4与麦田3。
*/ 
