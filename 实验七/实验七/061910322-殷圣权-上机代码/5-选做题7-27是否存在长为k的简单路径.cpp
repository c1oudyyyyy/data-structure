#include <iostream>
#include <cstdlib>
using namespace std;

#define MAX_V 256

typedef struct edgeNode//�ߵĽṹ 
{
	int adjVcode;
	struct edgeNode *nextEdge;
}edgeNode;

typedef struct vexNode//����ṹ 
{
	int data;
	edgeNode *firstEdge;
}vexNode;

typedef struct lGraph//�ڽӱ�ṹ
{
	vexNode adjList[MAX_V];
	int vexNum, edgeNum;
	int graphType;
}lGraph;

void create_lGraph(lGraph &G)//�����ڽӱ� 
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
	path[d] = v1;//����ǰ����ʼ�����·������ 
	visit[v1] = 1;//���ʱ�ǣ���ֹ�ظ�
	if(d > k) return ;//��ǰ·��������kʱ������ 
	if(v1 == v2 && d == k) //�ҵ���Ϊk��·��������� 
	{
		for(int i=0; i<=k; i++)
			cout << path[i];
		cout << endl;
	}
	else//����������� 
	{
		p = G.adjList[v1].firstEdge;//��ǰ��ʼ��ĵ�һ���ڽӵ� 
		while(p)
		{
			if(!visit[p->adjVcode])//�����ڽӵ�Ϊ�����ʣ�������Ϊ��ʼ����еݹ���� 
			{
				find_path(G, p->adjVcode, v2, k, d+1, path, visit);
				visit[p->adjVcode] = 0;//�ָ����ʱ�ǣ��Ǹ��ڽӵ��ܹ�����ʹ�� 
			}
			p = p->nextEdge;
		}
	}
}
void bool_path(lGraph G)
{
	//v1��v2Ϊ�����ţ�kΪ·�����ȣ�dΪ��ǰ·���ĳ��ȣ�path[]���·���ϵĶ��㣬visit[]Ϊ���ʱ�ǵĸ������� 
	int i, v1, v2, k, path[G.vexNum], visit[G.vexNum];
	cin >> v1 >> v2 >> k;
	for(i=0; i<G.vexNum; i++)//��ʼ���������� 
		visit[i] = 0;
	find_path(G, v1, v2, k, 0, path, visit);
}

int main()
{
	lGraph G;
	cout << "����ͼ����Ϣ��";
	create_lGraph(G);
	cout << "������ֹ�����ź�·�����ȣ�";
	bool_path(G);
	return 0;
}

//�������ݣ�0 9 11 0 1 0 2 0 3 1 4 2 4 3 5 4 6 4 7 5 7 6 8 7 8����P115��0 8 4�� 
