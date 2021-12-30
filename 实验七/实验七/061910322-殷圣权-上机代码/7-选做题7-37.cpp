#include <iostream>
#include <cstdlib>
using namespace std;

#define MAX_V 256

typedef struct edgeNode
{
	struct edgeNode *nextEdge;
	int adjVcode;
}edgeNode;

typedef struct vexNode
{
	edgeNode *firstEdge;
	int data;
}vexNode;

typedef struct lGraph
{
	vexNode adjList[MAX_V];
	int vexNum, edgeNum;
	int graphType;
}lGraph;

int maxd, visit[MAX_V], path[MAX_V], mlp[MAX_V];

void create_lGraph(lGraph &G)
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
		if(G.graphType == 0)//��Ϊ����ͼ 
		{
			p = (edgeNode *) malloc(sizeof(edgeNode));
			if(!p) exit(0);
			p->adjVcode = i;
			p->nextEdge = G.adjList[j].firstEdge;
			G.adjList[j].firstEdge = p;
		}
	}
}

void DFS(lGraph G, int i, int d)//������ȱ���
{
	visit[i] = 1;//��Ϊ�ѷ���״̬ 
	path[d] = i;//���뵱ǰ·�� 
	int j; 
	if(maxd < d && !G.adjList[i].firstEdge)//��Ϊ��ǰ·�����ߵ������ǵ�ǰ�·�� 
	{
		for(j=0; j<=d; j++)//�����·�� 
			mlp[j] = path[j];
		maxd = d;//���³��� 
	}
	else//������������ڽӵ� 
	{	
		edgeNode *p;
		for(p = G.adjList[i].firstEdge; p; p = p->nextEdge)//���ڽӵ㲻Ϊ�գ���ݹ����������ȱ��� 
		{
			j = p->adjVcode;
			if(!visit[j])
				DFS(G, j, d+1);
		}
	}
	path[i] = -1;//��δ�����·������·�����ˣ������������ 
	visit[i] = 0;
}

void longest_path(lGraph G)//�������޻�ͼ���·�� 
{
	maxd = 0;//�·������ʼ��Ϊ0 
	int in_degree[MAX_V];//���涥������
    int i, j;
    for(i=0; i<MAX_V; i++)//��ʼ����ǰ·�����·�� 
    {
    	path[i] = -1;
    	mlp[i] = -1;
	}
    for(i=0; i<G.vexNum; i++)//�������ȳ�ʼ��Ϊ0 
        in_degree[i] = 0;
    for(i=0; i<G.vexNum; i++)//ͳ��ÿ����������
    {
        edgeNode *p = G.adjList[i].firstEdge;
        while(p)
        {
            in_degree[p->adjVcode]++;
            p = p->nextEdge;
        }
    }
    for(i=0; i<G.vexNum; i++)
    {
    	for(j=0; j<G.vexNum; j++)//ÿ�ζ��������������� 
    		visit[j] = 0;
    	if(!in_degree[i]) DFS(G, i, 0);//�����Ϊ0�Ķ���Ϊ��ʼ�㣬Ѱ�����·��
	}
	cout << "�·����";
	for(i=0; mlp[i] != -1; i++)
		cout << mlp[i] << '\t';
	cout << endl << "·������Ϊ��" << maxd << endl;
}

int main()
{
    lGraph G;
    create_lGraph(G);
    longest_path(G);
    return 0;
}

//�������ݣ�1 9 11 0 1 0 2 0 3 1 4 2 4 3 5 4 6 4 7 5 7 6 8 7 8��p115 
//1 12 11 0 1 1 6 6 7 1 2 2 3 3 8 8 9 9 10 10 11 3 4 4 5�� 1 5 8 0 1 0 2 0 3 1 2 3 2 4 1 4 2 4 3�� p97 
