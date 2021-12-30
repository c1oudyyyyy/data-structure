#include <iostream>
#include <cstdlib>
using namespace std;

#define MAX_V 256

typedef struct edgenode
{
	struct edgenode *nextedge;
	int adjvcode;
	int weight;
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
	G.type = 0;
	cin  >> G.vexnum >> G.edgenum;
	int i, j, k, weight;
	edgenode *p;
	for(k=1; k<=G.vexnum; k++)
	{
		G.adjlist[k].data = k;
		G.adjlist[k].firstedge = NULL;
	}
	for(k=1; k<=G.edgenum; k++)
	{
		cin >> i >> j >> weight;
		p = (edgenode *) malloc(sizeof(edgenode));
		if(!p) exit(0);
		p->adjvcode = j;
		p->weight = weight;
		p->nextedge = G.adjlist[i].firstedge;
		G.adjlist[i].firstedge = p;
		if(G.type == 0)
		{
			p = (edgenode *) malloc(sizeof(edgenode));
			if(!p) exit(0);
			p->adjvcode = i;
			p->weight = weight;
			p->nextedge = G.adjlist[j].firstedge;
			G.adjlist[j].firstedge = p;
		}
	}
}


int minnn = 9999;
//求从顶点u出发到顶点v的所有简单路径
void DFS(graph G, int u, int v, int d, int *visited, int *path)
{
	path[d] = u;
	visited[u] = 1;
	int i;
	
	if(u == v)//找到路径，判断最长时间是否小于当前的最长时间，若是则替换 
	{
		int day_max = 0;
		//for(i=1; i<=d; i++)
		//	cout << path[i];
		//cout << endl;
		i = 1;
		while(i != d)
		{
			edgenode *p = G.adjlist[path[i++]].firstedge;
			while(p)
			{
				if(p->adjvcode == path[i])
				{
					break;
				}
				
				p = p->nextedge;
			}
		
			if(day_max < p->weight )
				day_max = p->weight;//当前路径最长天数 
		}
		
		if(day_max < minnn)
			minnn = day_max;
	}

	else
	{
		edgenode *p = G.adjlist[u].firstedge;
		while(p)
		{
			if(!visited[p->adjvcode])
			{
				DFS(G, p->adjvcode, v, d+1, visited, path);
				visited[p->adjvcode] = 0;
			}
			p = p->nextedge;
		}
	}
}

void all_simple_path(graph G)
{
	int visited[MAX_V], path[MAX_V];
	int i, u, v; 
	for(i=1; i<=G.vexnum; i++)
		visited[i] = 0;
	DFS(G, 1, G.vexnum, 1, visited, path);
}
int main()
{
	graph G;
	create_graph(G);
	all_simple_path(G);
	cout << minnn << endl;
	return 0;
}
 
