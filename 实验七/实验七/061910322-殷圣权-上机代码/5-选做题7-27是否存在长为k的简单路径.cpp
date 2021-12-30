#include <iostream>
#include <cstdlib>
using namespace std;

#define MAX_V 256

typedef struct edgeNode//边的结构 
{
	int adjVcode;
	struct edgeNode *nextEdge;
}edgeNode;

typedef struct vexNode//顶点结构 
{
	int data;
	edgeNode *firstEdge;
}vexNode;

typedef struct lGraph//邻接表结构
{
	vexNode adjList[MAX_V];
	int vexNum, edgeNum;
	int graphType;
}lGraph;

void create_lGraph(lGraph &G)//创建邻接表 
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
		
		if(G.graphType == 0)
		{
			p = (edgeNode *) malloc(sizeof(edgeNode));
			if(!p) exit(0);
			p->adjVcode = i;
			p->nextEdge = G.adjList[j].firstEdge;
			G.adjList[j].firstEdge = p;
		}
	}
}

void find_path(lGraph G, int v1, int v2, int k, int d, int *path, int *visit)
{
	edgeNode *p;
	path[d] = v1;//将当前的起始点放入路径数组 
	visit[v1] = 1;//访问标记，防止重复
	if(d > k) return ;//当前路径长大于k时，返回 
	if(v1 == v2 && d == k) //找到长为k的路径，则输出 
	{
		for(int i=0; i<=k; i++)
			cout << path[i];
		cout << endl;
	}
	else//否则继续搜索 
	{
		p = G.adjList[v1].firstEdge;//当前起始点的第一个邻接点 
		while(p)
		{
			if(!visit[p->adjVcode])//若该邻接点为被访问，则以它为起始点进行递归调用 
			{
				find_path(G, p->adjVcode, v2, k, d+1, path, visit);
				visit[p->adjVcode] = 0;//恢复访问标记，是该邻接点能够重新使用 
			}
			p = p->nextEdge;
		}
	}
}
void bool_path(lGraph G)
{
	//v1、v2为顶点编号，k为路径长度，d为当前路径的长度，path[]存放路径上的顶点，visit[]为访问标记的辅助数组 
	int i, v1, v2, k, path[G.vexNum], visit[G.vexNum];
	cin >> v1 >> v2 >> k;
	for(i=0; i<G.vexNum; i++)//初始化辅助数组 
		visit[i] = 0;
	find_path(G, v1, v2, k, 0, path, visit);
}

int main()
{
	lGraph G;
	cout << "输入图中信息：";
	create_lGraph(G);
	cout << "输入起止顶点编号和路径长度：";
	bool_path(G);
	return 0;
}

//测试数据：0 9 11 0 1 0 2 0 3 1 4 2 4 3 5 4 6 4 7 5 7 6 8 7 8。书P115。0 8 4。 
