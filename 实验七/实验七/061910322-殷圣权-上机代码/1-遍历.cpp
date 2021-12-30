#include <iostream>
#include <cstdlib>

#define MAX_V 256

using namespace std;

typedef struct arcNode//�ߵĽṹ
{
	int adjvex;//
	struct arcNode *nextArc;
}arcNode;

typedef struct vexNode//����ṹ
{
	int data;
	arcNode *firstArc;
}vexNode;

typedef struct alGraph//�ڽӱ�ṹ 
{
	vexNode arr[MAX_V];
	int vexNum, arcNum;
	int type;
}alGraph;

//�����ڽӱ�
void create_graph(alGraph &G)
{
	cin >> G.type >> G.vexNum >> G.arcNum;
	int i, j, k;
	arcNode *p;
	for(i=0; i<G.vexNum; i++)
	{
		G.arr[i].data = i;
		G.arr[i].firstArc = NULL;
	}
	for(k=0; k<G.arcNum; k++)
	{
		cin >> i >> j;
		
		p = (arcNode *) malloc(sizeof(arcNode));
		p->adjvex = j;
		p->nextArc = G.arr[i].firstArc;
		G.arr[i].firstArc = p;
		
		if(G.type == 0)
		{
			p = (arcNode *) malloc(sizeof(arcNode));//����ͼ 
			p->adjvex = i;
			p->nextArc = G.arr[j].firstArc;
			G.arr[j].firstArc = p;
		}
	}
}

//������ȱ���
void DFS(alGraph G, int index, bool *visit)
{
	visit[index] = true;
	cout << G.arr[index].data;
	arcNode *p = G.arr[index].firstArc;
	while(p)
	{
		if(!visit[p->adjvex]) DFS(G, p->adjvex, visit);
		p = p->nextArc;
	}
} 
void DFS_visit(alGraph G)
{
	int i;
	bool visit[G.vexNum];
	for(i=0; i<G.vexNum; i++)
		visit[i] = false;
	for(i=0; i<G.vexNum; i++)
		if(!visit[i]) DFS(G, i, visit);
	cout << endl;
}

//������ȱ���
void BFS(alGraph G, int index, bool *visit)
{
	arcNode *p;
	int queue[MAX_V], front = 0, rear = 0, i;
	queue[rear++] = index;
	visit[index] = true;
	while(front != rear)
	{
		i = queue[front];
		front = (front + 1) % MAX_V;
		cout << G.arr[i].data;
		p = G.arr[i].firstArc;
		while(p)
		{
			if(!visit[p->adjvex])
			{
				queue[rear] = p->adjvex;
				rear = (rear + 1) % MAX_V;
				visit[p->adjvex] = true;
			}
			p = p->nextArc;
		}
	}
}
void BFS_visit(alGraph G)
{
	int i;
	bool visit[G.vexNum];
	for(i=0; i<G.vexNum; i++)
		visit[i] = false;
	for(i=0; i<G.vexNum; i++)
		if(!visit[i]) BFS(G, i, visit);
	cout << endl;
}

int main()
{
	alGraph G;
	create_graph(G);
	cout << "������ȱ�����";
	DFS_visit(G);
	cout << "������ȱ�����";
	BFS_visit(G);
	return 0;
}
//�������ݣ�0 9 11 0 1 0 2 0 3 1 4 2 4 3 5 4 6 4 7 5 7 6 8 7 8����P115
