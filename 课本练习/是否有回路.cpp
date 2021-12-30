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

/*
进行vexnum次DFS，若第i次访问到i，则把visited[i]置为1，表示i点有回路
*/
int flag = 0;
void DFS(graph G, int i, int *visited)
{
	edgenode *p = G.adjlist[i].firstedge;
	while(p)
	{
		
		edgenode *q = p;
		while(q)
		{
			if(q->adjvcode == 1)
			{
				visited[i] = 1;
				flag = 1;
				break;
			}
			q = q->nextedge;
		}
		if(flag) break;
		if(p->adjvcode == i)
		{
			visited[i] = 1;
			break;
		}
		DFS(G, p->adjvcode, visited);
		p = p->nextedge;
	}
}

void cycle(graph G)
{
	int visited[MAX_V], i;
	for(i=1; i<=G.vexnum; i++)
		visited[i] = 0;
	for(i=1; i<=G.vexnum; i++)
	{
		flag = 0;
		DFS(G, i, visited);
		if(visited[i])
			cout << i << '\t';
	}
}

int main()
{
	graph G;
	create_graph(G);
	cycle(G);
	return 0;
 } 
