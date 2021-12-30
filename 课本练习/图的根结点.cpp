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
1�������ж�ÿ����u�Ƿ�Ϊ�����������
	1���ж�u�������v�Ƿ���·��
		1����uΪ��ʼ�����һ��DFS���۲������v�Ƿ񱻷��ʣ��������ʣ���˵����ͨ
			�����ֲ���ͨ������һ����u
	2��Ϊ������� 
*/
void DFS(graph G, int u, int cur_u, int i, int *visited)
{
	edgenode *p = G.adjlist[cur_u].firstedge;
	while(p)
	{
		edgenode *q = p;
		while(q)//�ȿ��ڽӵ������յ� 
		{
			if(q->adjvcode == i)
			{
				visited[i] = 1;
				break;
			}
			q = q->nextedge;
		}
		if(p->adjvcode == u) break;//�����ֻ�·������ѭ�� 
		if(p->adjvcode == i)//��ͨ 
		{
			visited[i] = 1;
			break;
		}
		DFS(G, u, p->adjvcode, i, visited);
		p = p->nextedge;
	}
}

bool i_root(graph G, int u, int *visited)
{
	int i;
	for(i=1; i<=G.vexnum; i++)//i<=G.vexnum && i!=u��������������Ϊ�޷�������һ�Σ�ֱ������ѭ�� 
	{	
		if(i == u) continue;//�������յ���ͬ�������� 
		DFS(G, u, u, i, visited);
		if(visited[i] == 0) return false;
	}
	return true;
}

void all_root(graph G)
{
	int i, visited[MAX_V], j;
	for(i=1; i<=G.vexnum; i++)
	{
		for(j=1; j<=G.vexnum; j++)
			visited[j] = 0;
		if(i_root(G, i, visited))//����Ǹ���㣬����� 
			cout << i << '\t';
	}
}

int main()
{
	graph G;
	create_graph(G);
	all_root(G);
	return 0;
}

//�������ݣ�1 6 10 1 2 5 2 1 4 5 4 3 1 3 2 3 4 3 5 6 3 2 6��
