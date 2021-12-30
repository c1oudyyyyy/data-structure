#include <iostream>
#include <cstdlib>
using namespace std;

#define MAX_V 256

typedef struct edgenode
{
	struct edgenode *nextedge;
	int adjvcode;
}edgenode;

typedef struct vexnode
{
	edgenode *firstedge;
	int data;
}vexnode;

typedef struct graph
{
	vexnode adjlist[MAX_V];
	int vexnum, edgenum;
	int type;
}graph;

void create_graph(graph &G)
{
	cin >> G.type >> G.vexnum >> G.edgenum;
	int i, j, k;
	edgenode *p;
	for(k=1; k<=G.vexnum; k++)
	{
		G.adjlist[k].data = k;
		G.adjlist[k].firstedge = NULL;
	}
	for(k=1; k<=G.edgenum; k++)
	{
		cin >> i >> j;
		p = (edgenode *) malloc(sizeof(edgenode));
		if(!p) exit(0);
		p->adjvcode = j;
		p->nextedge = G.adjlist[i].firstedge;
		G.adjlist[i].firstedge = p;
		if(G.type == 0)
		{
			p = (edgenode *) malloc(sizeof(edgenode));
			if(!p) exit(0);
			p->adjvcode = i;
			p->nextedge = G.adjlist[j].firstedge;
			G.adjlist[j].firstedge = p;
		}
	}
}

void DFS(graph G, int u, int v, int d, int *visited, int *path, int k)
{
	path[d] = u;
	visited[u] = 1;
	int i;
	if(u == v && d == k)//若找到长度为k的简单路径，则输出 
	{
		for(i=1; i<=d; i++)
			cout << path[i];
		cout << endl;
	}
	else
	{
		edgenode *p = G.adjlist[u].firstedge;
		while(p)
		{
			if(!visited[p->adjvcode])
			{
				DFS(G, p->adjvcode, v, d+1, visited, path, k);
				visited[p->adjvcode] = 0;//恢复标记，使该点能被重新使用 
			}
			p = p->nextedge;
		}
	}
}

void length_k_path(graph G)
{
	int u, v, k, i;
	cin >> u >> v >> k;
	int visited[MAX_V], path[MAX_V];
	for(i=1; i<=G.vexnum; i++)
		visited[i] = 0;
	DFS(G, u, v, 1, visited, path, k);
}

int main()
{
	graph G;
	create_graph(G);
	length_k_path(G);
	return 0;
}

//测试数据：0 8 9 1 2 1 6 2 3 6 7 3 5 3 4 7 8 4 5 5 8 1 5 4。
