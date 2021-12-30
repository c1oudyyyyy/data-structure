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

//�Ӷ���v��ʼ������С������ 
void Prim(graph G, int v)
{
	Closet closet[MAX_V];
	int i, j;
	edgenode *p = G.adjlist[v].firstedge;
	//1����ʼ��closet���� 
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
	closet[v].lowcost = 0;//ѡ����� 
	
	for(j=1; j<=G.vexnum-1; j++)//ѡ��ʣ���n-1������ 
	{
		//2��Ѱ��lowcost�ķ�����Сֵ����Сֵ���ڵ�λ�� 
		int min = INFINITY, k;
		for(i=1; i<=G.vexnum; i++)
		{
			if(closet[i].lowcost < min && closet[i].lowcost != 0)
			{
				min = closet[i].lowcost;
				k = i;
			}
		}
		//3��ѡ����Сֵ���ڵĲ������ϵĶ���
		cout << "�ߣ�" << closet[k].vexcode << '\t' << k << '\t' << "Ȩ��" << min << endl;
		closet[k].lowcost = 0;
		//4������closet����
		for(i=1; i<=G.vexnum; i++)
		{
			edgenode *q = G.adjlist[k].firstedge;
			while(q)//Ѱ��k��i�ı� 
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

//�������ݣ�0 7 12 1 2 2 1 3 6 1 4 8 2 5 10 2 4 7 3 6 5 3 4 2 6 7 9 6 4 1 7 5 6 7 4 4 5 4 3��
