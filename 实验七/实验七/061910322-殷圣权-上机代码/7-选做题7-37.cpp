#include <iostream>
#include <cstdlib>
using namespace std;

#define MAX_V 256

typedef struct edgeNode
{
	struct edgeNode *nextEdge;
	int adjVcode;
}edgeNode;

typedef struct vexNode
{
	edgeNode *firstEdge;
	int data;
}vexNode;

typedef struct lGraph
{
	vexNode adjList[MAX_V];
	int vexNum, edgeNum;
	int graphType;
}lGraph;

int maxd, visit[MAX_V], path[MAX_V], mlp[MAX_V];

void create_lGraph(lGraph &G)
{ 
	cin >> G.graphType >> G.vexNum >> G.edgeNum;
	int i, j, k;
	for(i=0; i<G.vexNum; i++)
	{
		G.adjList[i].data = i;
		G.adjList[i].firstEdge = NULL;
	}
	edgeNode *p;
	for(k=0; k<G.edgeNum; k++)
	{
		cin >> i >> j;
		p = (edgeNode *) malloc(sizeof(edgeNode));
		if(!p) exit(0);
		p->adjVcode = j;
		p->nextEdge = G.adjList[i].firstEdge;
		G.adjList[i].firstEdge = p;
		if(G.graphType == 0)//若为无向图 
		{
			p = (edgeNode *) malloc(sizeof(edgeNode));
			if(!p) exit(0);
			p->adjVcode = i;
			p->nextEdge = G.adjList[j].firstEdge;
			G.adjList[j].firstEdge = p;
		}
	}
}

void DFS(lGraph G, int i, int d)//深度优先遍历
{
	visit[i] = 1;//标为已访问状态 
	path[d] = i;//加入当前路径 
	int j; 
	if(maxd < d && !G.adjList[i].firstEdge)//若为当前路径已走到底且是当前最长路径 
	{
		for(j=0; j<=d; j++)//更新最长路径 
			mlp[j] = path[j];
		maxd = d;//更新长度 
	}
	else//否则继续搜索邻接点 
	{	
		edgeNode *p;
		for(p = G.adjList[i].firstEdge; p; p = p->nextEdge)//若邻接点不为空，则递归调用深度优先遍历 
		{
			j = p->adjVcode;
			if(!visit[j])
				DFS(G, j, d+1);
		}
	}
	path[i] = -1;//还未发现最长路径，则路径回退，访问数组归零 
	visit[i] = 0;
}

void longest_path(lGraph G)//求有向无环图的最长路径 
{
	maxd = 0;//最长路径长初始化为0 
	int in_degree[MAX_V];//储存顶点的入度
    int i, j;
    for(i=0; i<MAX_V; i++)//初始化当前路径和最长路径 
    {
    	path[i] = -1;
    	mlp[i] = -1;
	}
    for(i=0; i<G.vexNum; i++)//顶点的入度初始化为0 
        in_degree[i] = 0;
    for(i=0; i<G.vexNum; i++)//统计每个顶点的入度
    {
        edgeNode *p = G.adjList[i].firstEdge;
        while(p)
        {
            in_degree[p->adjVcode]++;
            p = p->nextEdge;
        }
    }
    for(i=0; i<G.vexNum; i++)
    {
    	for(j=0; j<G.vexNum; j++)//每次都将访问数组清零 
    		visit[j] = 0;
    	if(!in_degree[i]) DFS(G, i, 0);//以入度为0的顶点为起始点，寻找最大路径
	}
	cout << "最长路径：";
	for(i=0; mlp[i] != -1; i++)
		cout << mlp[i] << '\t';
	cout << endl << "路径长度为：" << maxd << endl;
}

int main()
{
    lGraph G;
    create_lGraph(G);
    longest_path(G);
    return 0;
}

//测试数据：1 9 11 0 1 0 2 0 3 1 4 2 4 3 5 4 6 4 7 5 7 6 8 7 8。p115 
//1 12 11 0 1 1 6 6 7 1 2 2 3 3 8 8 9 9 10 10 11 3 4 4 5。 1 5 8 0 1 0 2 0 3 1 2 3 2 4 1 4 2 4 3。 p97 
