#include <iostream>
#include <cstdlib>
using namespace std;

#define MAX_V 256
#define INFINITY 9999

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

typedef struct Closet
{
	int lowcost;
	int vexcode;
}Closet;

void create_graph(graph &G)
{
	cin >> G.type >> G.vexnum >> G.edgenum;
	int i, j, k, w;
	edgenode *p;
	for(k=1; k<=G.vexnum; k++)
	{
		G.adjlist[k].data = k;
		G.adjlist[k].firstedge = NULL;
	}
	for(k=1; k<=G.edgenum; k++)
	{
		cin >> i >> j >> w;
		p = (edgenode *) malloc(sizeof(edgenode));
		if(!p) exit(0);
		p->adjvcode = j;
		p->weight = w;
		p->nextedge = G.adjlist[i].firstedge;
		G.adjlist[i].firstedge = p;
		if(G.type == 0)
		{
			p = (edgenode *) malloc(sizeof(edgenode));
			if(!p) exit(0);
			p->adjvcode = i;
			p->weight = w;
			p->nextedge = G.adjlist[j].firstedge;
			G.adjlist[j].firstedge = p;
		}
	}
}

//从顶点v开始构建最小生成树 
void Prim(graph G, int v)
{
	Closet closet[MAX_V];
	int i, j;
	edgenode *p = G.adjlist[v].firstedge;
	//1、初始化closet数组 
	for(i=1; i<=G.vexnum; i++)
	{
		closet[i].vexcode = v;
		closet[i].lowcost = INFINITY;
	}
	while(p)
	{
		closet[p->adjvcode].lowcost = p->weight;
		p = p->nextedge;
	}
	closet[v].lowcost = 0;//选定起点 
	
	for(j=1; j<=G.vexnum-1; j++)//选定剩余的n-1个顶点 
	{
		//2、寻找lowcost的非零最小值和最小值所在的位置 
		int min = INFINITY, k;
		for(i=1; i<=G.vexnum; i++)
		{
			if(closet[i].lowcost < min && closet[i].lowcost != 0)
			{
				min = closet[i].lowcost;
				k = i;
			}
		}
		//3、选中最小值所在的不在树上的顶点
		cout << "边：" << closet[k].vexcode << '\t' << k << '\t' << "权：" << min << endl;
		closet[k].lowcost = 0;
		//4、更新closet数组
		for(i=1; i<=G.vexnum; i++)
		{
			edgenode *q = G.adjlist[k].firstedge;
			while(q)//寻找k到i的边 
			{
				if(q->adjvcode == i)
					break;
				q = q->nextedge;
			}
			if(q && q->adjvcode == i)
			{
				if(closet[i].lowcost != 0 && closet[i].lowcost > q->weight)
				{
					closet[i].vexcode = k;
					closet[i].lowcost = q->weight;
				}
			}
		}
	}
}

int main()
{
	graph G;
	create_graph(G);
	Prim(G, 1);
	return 0; 
}

//测试数据：0 7 12 1 2 2 1 3 6 1 4 8 2 5 10 2 4 7 3 6 5 3 4 2 6 7 9 6 4 1 7 5 6 7 4 4 5 4 3。
