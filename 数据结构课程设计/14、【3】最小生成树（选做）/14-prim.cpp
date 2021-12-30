#include <iostream>
#include <cstdlib>
#include <stdio.h>
using namespace std;

#define MAX_V 256
#define INFINITY 9999

typedef struct mGraph
{
	int vexName[MAX_V];
	int adjMatrix[MAX_V][MAX_V];
	int vexNum, eNum;
}mGraph;

typedef struct closest//�����ṹ 
{
	int vexcode;
	int lowcost;
}closest;

void create_mGraph(mGraph &G)
{
	FILE *fp = fopen("14.txt", "r");
	if(!fp)
	{
		cout << "�ļ���ʧ�ܣ�\n";
		exit(0);
	}
	fscanf(fp, "%d %d", &G.vexNum, &G.eNum);
	int i, j, weight, k;
	for(i=1; i<=G.vexNum; i++)
	{
		for(j=1; j<=G.vexNum; j++)
		{
			if(i != j)
				G.adjMatrix[i][j] = INFINITY;
			else
				G.adjMatrix[i][j] = 0;
		}
	}
	for(k=1; k<=G.eNum; k++)
	{
		G.vexName[k] = k;
		fscanf(fp, "%d %d %d", &i, &j, &weight);
		G.adjMatrix[i][j] = weight;
		G.adjMatrix[j][i] = weight;
	}
	fclose(fp);
}

void  minSpanningTree_prim(mGraph G, int v)//��������ķ�㷨���Ӷ���v��������С������ 
{
	printf("Prim��\n");
	int i, j, k, min, min_all = 0;
	closest clo[MAX_V];//��ʼ��clo����
	for(j=1; j<=G.vexNum; j++) 
	{
		clo[j].vexcode = v;
		clo[j].lowcost = G.adjMatrix[v][j];
	}
	clo[v].lowcost = 0;//���v�Ѿ���ѡ�� 
	for(i=2; i<=G.vexNum; i++)//��ʣ��Ķ��������С������ 
	{
		min = INFINITY;
		for(j=1; j<=G.vexNum; j++)//��clo������Ѱ��lowcost�������Сֵ 
		{
			if(clo[j].lowcost && clo[j].lowcost < min)
			{
				min = clo[j].lowcost;
				k = j;
			}
		}
		printf("%d->%d   %d\n",k,clo[k].vexcode,G.adjMatrix[k][clo[k].vexcode]);
		min_all += min; 
		clo[k].lowcost = 0;//ѡ�б�����lowcost��С�Ķ��� 
		for(j=1; j<=G.vexNum; j++)//����clo���� 
		{
			if(G.adjMatrix[k][j] < clo[j].lowcost)//�������ϵĶ��㵽����k�ľ����ԭ����lowcostС 
			{
				clo[j].lowcost = G.adjMatrix[k][j];
				clo[j].vexcode = k;
			}
		}
	}
	printf("Ȩֵ֮��Ϊ��%d\n", min_all);
}

int main()
{
	mGraph G;
	create_mGraph(G);
	minSpanningTree_prim(G, 1);
	return 0;
}

