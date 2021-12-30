/*
���߰�Ȩֵ��С�������򣬲�����ѡ��һ���ߣ���ѡ�иñߺ�δ���ɻ�·����ѡ�߳ɹ���
�����е㶼������ʱ���㷨������
ע��Ҫ����һ�����鼯�����ÿ�������ϵĵ㣬�Դ����ж��Ƿ�ṹ�ɻ�·��
*/ 

#include <iostream>
#include <cstdlib>
#include <stdio.h>
using namespace std;
#define MAX_V 256

typedef struct Edge//v1,v2�涥�㣬weight��Ȩ�ء�
{
    int v1;
    int v2;
    int weight;
}Edge;

typedef struct mGraph
{
    int vexNum, eNum;
    Edge *p;//�߼����� 
    int vexName[MAX_V];
}mGraph;

void create_mGraph(mGraph &G)
{
	FILE *fp = fopen("14.txt", "r");
	if(!fp)
	{
		cout << "�ļ���ʧ�ܣ�\n";
		exit(0);
	}
	fscanf(fp, "%d %d", &G.vexNum, &G.eNum);
    int i,j;
    G.p = (Edge *)malloc(sizeof(Edge)*(G.eNum+1));
    for(i=0; i<G.eNum; i++)
    {
		G.vexName[i] = i+1;
        fscanf(fp, "%d %d %d", &G.p[i].v1, &G.p[i].v2, &G.p[i].weight);
    }
    for(i=0; i<G.eNum; i++)//ð�����򷨣�Ȩ�ش�С������ڱ߼�������
    {
        for(j=G.eNum-1; j>i; j--)
        {
            if(G.p[i].weight > G.p[j].weight)
            {
                G.p[G.eNum] = G.p[i];
                G.p[i] = G.p[j];
                G.p[j] = G.p[G.eNum];
            }
        }
    }
}

int Find(int *parent, int g)//���ظõ��Ӧ�ı�ǣ��Դ��ж��Ƿ��л�· 
{
    while(parent[g] != 0)
    {
        g = parent[g];
    }
    return g;
}

int Finish(mGraph G,int *parent)//�ж��������Ƿ���ɣ���ɵı�־���������ıߵ��ڶ����������1
{
    int i,n = 0;

    for(i=0; i<G.vexNum; i++)
    {
        if(parent[i])
        {
            n++;
        }
    }
    if(n == G.vexNum-1)
    {
        return 1;
    }
    return 0;
}

void MinTree_Kruskal(mGraph G)
{
	printf("Kruskal��\n");
    int i, a, b;
    int min_all = 0;
    int parent[G.vexNum];//��ÿ������Ϊ�����ı�� 

    for(i=0; i<G.vexNum; i++)//��ʼ��parent[]
    {
        parent[i] = 0;
    }
    for(i=0; i<G.eNum; i++)
    {
        a = Find(parent,G.p[i].v1);
        b = Find(parent,G.p[i].v2);

        if(a != b)//���a��b��������a��b��ͬһ���������ϣ����a��b������Ϊ���ɻ���������������
        {
            parent[a] = b;//��� 
            printf("%d->%d   %d\n", G.p[i].v1, G.p[i].v2, G.p[i].weight);
            min_all += G.p[i].weight;
        }
        if(Finish(G,parent))//��ɺ󷵻�
        {
			printf("Ȩֵ֮��Ϊ��%d\n", min_all);
            return ;
        }
    }
	
}

int  main()
{
    mGraph G;
    create_mGraph(G);
    MinTree_Kruskal(G);
    return 0;
}


