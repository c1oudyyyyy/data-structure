#include <iostream>
#include <cstdlib>
using namespace std;

#define MAX_V 256

typedef struct edgenode
{
	struct edgenode *nextedge;
	int adjcode;
}edgenode;

typedef struct vexnode
{
	edgenode *firstedge;
	int data;
}vexnode;

typedef struct graph
{
	int vexnum, edgenum;
	int type;
	vexnode adjlist[MAX_V];
}graph;

void creategraph(graph &G)
{
	cin >> G.type >> G.vexnum >> G.edgenum;
	int i, j, k;
	for(k=1; k<=G.vexnum; k++)
	{
		G.adjlist[k].data = k;
		G.adjlist[k].firstedge = NULL;
	}
	edgenode *p;
	for(k=1; k<=G.edgenum; k++)
	{
		cin >> i >> j;
		p = (edgenode *) malloc(sizeof(edgenode));
		p->adjcode = j;
		p->nextedge = G.adjlist[i].firstedge;
		G.adjlist[i].firstedge = p;
		if(G.type == 0)
		{
			p = (edgenode *) malloc(sizeof(edgenode));
			p->adjcode = i;
			p->nextedge = G.adjlist[j].firstedge;
			G.adjlist[j].firstedge = p;
		}
	}
}

 
//u为当前点，v为终点，path存储路径，d为顶点数，visited为访问标记数组 
void DFS(graph G, int u, int v, int *path, int d, bool *visited)
{
	path[d] = u;//进入路径 
	visited[d] = true;//标记 
	int i;
	edgenode *p = G.adjlist[u].firstedge;
	if(p->adjcode == v && d >2)
	{
		for(i=1; i<=d; i++)
			cout << path[i];
		cout << v << endl;
	}
	else
	{ 
		while(p)
		{
			if(!visited[p->adjcode])
			{
				DFS(G, p->adjcode, v, path, d+1, visited);
				visited[u] = false;
			}
			p = p->nextedge;
		}
	}
}

void all_circle_path(graph G, int v)
{
	bool visited[G.vexnum+1];
	int i;
	for(i=1; i<=G.vexnum; i++)//初始化访问标记数组 
		visited[i] = false;
	int path[MAX_V];
	DFS(G, v, v, path, 1, visited);
}

int main()
{
	graph G;
	creategraph(G);
	all_circle_path(G, 1);
	return 0;
}

//测试数据：0 7 8 1 2 1 3 1 4 1 6 2 3 2 7 3 4 4 5。
