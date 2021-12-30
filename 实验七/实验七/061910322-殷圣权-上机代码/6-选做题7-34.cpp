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
    int count = 0;//已访问的顶点数量
    int stack[MAX_V], top = -1;//栈
    int in_degree[MAX_V];//储存顶点的入度
    int i, m = 0;
    for(i=0; i<G.vexNum; i++)//初始化顶点的入度
        in_degree[i] = 0;
    for(i=0; i<G.vexNum; i++)//统计每个顶点的入度
    {
        p = G.adjList[i].firstEdge;
        while(p)
        {
            in_degree[p->adjVcode]++;
            p = p->nextEdge;
        }
    }
    for(i=0; i<G.vexNum; i++)//将所有入度为0的顶点进栈
        if(in_degree[i] == 0) stack[++top] = i;
    while(top >= 0)//栈非空时循环
    {
        i = stack[top--];//弹栈并输出
        topo[m++] = G.adjList[i].data;
        count++;//已访问的数目+1
        //输出一个入度为0的顶点后，更新与之邻接的顶点的入度
        p = G.adjList[i].firstEdge;
        while(p)
        {
            in_degree[p->adjVcode]--;
            //如果入度为0，进栈
            if(in_degree[p->adjVcode] == 0) stack[++top] = p->adjVcode;
            p = p->nextEdge;
        }
    }
    if(count == G.vexNum) return true;//若访问到的顶点数等于顶点总数，则排序成功
    else return false;//否则排序失败

}

void vex_code(lGraph G)//编号 
{
    int topo[G.vexNum];
    if(topology(G, topo))//拓补排序成功 
    {
    	cout << "编号顺序如下：" << endl; 
	    for(int i=0; i<G.vexNum; i++)
	        cout << topo[i] ;
    }
    else
     cout << "无法编号。" << endl; 
}

int main()
{
    lGraph G;
    create_lGraph(G);
    vex_code(G);
    return 0;
}

//测试数据：1 9 11 0 1 0 2 0 3 1 4 2 4 3 5 4 6 4 7 5 7 6 8 7 8。书P115。0 1 1 2 2 3 3 0 0 4
