#include <iostream>
#include <cstdlib>
using namespace std;

#define MAX_V 256
#define INFINITY 9999

typedef struct mGraph
{
	int vexName[MAX_V];
	int adjMatrix[MAX_V][MAX_V];
	int vexNum, eNum;
	int graphType;
}mGraph;

void create_mGraph(mGraph &G)
{
	cin >> G.graphType >> G.vexNum >> G.eNum;
	int i, j, weight, k;
	for(i=0; i<G.vexNum; i++)
		for(j=0; j<G.vexNum; j++)
			G.adjMatrix[i][j] = INFINITY;
			
	for(k=0; k<G.eNum; k++)
	{
		G.vexName[k] = k;
		cin >> i >> j >> weight;
		G.adjMatrix[i][j] = weight;
		if(G.graphType == 0)
			G.adjMatrix[j][i] = weight;
	}
}

void Dijkstra(mGraph G, int v)
{
	int dist[MAX_V], path[MAX_V], flag[MAX_V];//������������ 
	int i, j, k, m, mindist;
	for(i=0; i<G.vexNum; i++)//�����ʼ�� 
	{
		dist[i] = G.adjMatrix[v][i];
		if(dist[i] < INFINITY) path[i] = v;
		else path[i] = -1;
		flag[i] = 0;
	}
	dist[v] = 0;
	path[v] = 0;
	flag[v] = 1;
	for(i=0; i<G.vexNum-1; i++)//ѭ��ѡ��ʣ��Ķ��� 
	{
		//1��Ѱ�ҵ�ǰ������Դ������Ķ���k
		mindist = INFINITY;
		for(m=0; m<G.vexNum; m++)
			if(!flag[m] && dist[m] < mindist)
			{ 
				k = m;		
				mindist = dist[k];//�����ֵ
			} 
		flag[k] = 1;//�ҵ�����Ϊ��ѡ��״̬ 
		//2�����ݶ���k�������������㵽Դ��ľ���
		for(j=0; j<G.vexNum; j++)
			if(!flag[j] && mindist+G.adjMatrix[k][j] < dist[j])//��j����k��Դ���ԭ������ 
			{
				dist[j] = mindist + G.adjMatrix[k][j];
				path[j] = k;
			}
	}
	//��ӡ����;����Ķ���
	cout << "code" << '\t';
	for(i=0; i<G.vexNum; i++)
		cout << i << '\t' ;
	cout << endl;
	cout << "dist" << '\t';
	for(i=0; i<G.vexNum; i++)
		cout << dist[i] << '\t';
	cout << endl;
	cout << "path" << '\t';
	for(i=0; i<G.vexNum; i++)
		cout << path[i] << '\t';
	cout << endl;
}

int main()
{
	mGraph G;
	create_mGraph(G);
	Dijkstra(G, 0);
	return 0;
}

//�������ݣ�1 5 8 0 1 2 0 2 6 0 3 9 1 2 3 1 4 7 2 3 1 2 4 2 3 4 2�� 
