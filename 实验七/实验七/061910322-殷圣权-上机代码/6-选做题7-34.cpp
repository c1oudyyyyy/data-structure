#include <iostream>
#include <cstdlib>
using namespace std;

#define MAX_V 256

typedef struct edgeNode
{
    int adjVcode;
    struct edgeNode *nextEdge;
}edgeNode;

typedef struct vexNode
{
    int data;
    edgeNode *firstEdge;
}vexNode;

typedef struct lGraph
{
    vexNode adjList[MAX_V];
    int vexNum, edgeNum;
    int graphType;
}lGraph;

void create_lGraph(lGraph &G)
{
    cin >> G.graphType >> G.vexNum >> G.edgeNum;
    int i, j ,k;
    for(k=0; k<G.vexNum; k++)
    {
        G.adjList[k].data = k;
        G.adjList[k].firstEdge = NULL;
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

bool topology(lGraph G, int *topo)
{
    edgeNode *p;
    int count = 0;//�ѷ��ʵĶ�������
    int stack[MAX_V], top = -1;//ջ
    int in_degree[MAX_V];//���涥������
    int i, m = 0;
    for(i=0; i<G.vexNum; i++)//��ʼ����������
        in_degree[i] = 0;
    for(i=0; i<G.vexNum; i++)//ͳ��ÿ����������
    {
        p = G.adjList[i].firstEdge;
        while(p)
        {
            in_degree[p->adjVcode]++;
            p = p->nextEdge;
        }
    }
    for(i=0; i<G.vexNum; i++)//���������Ϊ0�Ķ����ջ
        if(in_degree[i] == 0) stack[++top] = i;
    while(top >= 0)//ջ�ǿ�ʱѭ��
    {
        i = stack[top--];//��ջ�����
        topo[m++] = G.adjList[i].data;
        count++;//�ѷ��ʵ���Ŀ+1
        //���һ�����Ϊ0�Ķ���󣬸�����֮�ڽӵĶ�������
        p = G.adjList[i].firstEdge;
        while(p)
        {
            in_degree[p->adjVcode]--;
            //������Ϊ0����ջ
            if(in_degree[p->adjVcode] == 0) stack[++top] = p->adjVcode;
            p = p->nextEdge;
        }
    }
    if(count == G.vexNum) return true;//�����ʵ��Ķ��������ڶ���������������ɹ�
    else return false;//��������ʧ��

}

void vex_code(lGraph G)//��� 
{
    int topo[G.vexNum];
    if(topology(G, topo))//�ز�����ɹ� 
    {
    	cout << "���˳�����£�" << endl; 
	    for(int i=0; i<G.vexNum; i++)
	        cout << topo[i] ;
    }
    else
     cout << "�޷���š�" << endl; 
}

int main()
{
    lGraph G;
    create_lGraph(G);
    vex_code(G);
    return 0;
}

//�������ݣ�1 9 11 0 1 0 2 0 3 1 4 2 4 3 5 4 6 4 7 5 7 6 8 7 8����P115��0 1 1 2 2 3 3 0 0 4
