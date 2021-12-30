#include <iostream>
#include <cstdlib>
#include <cstring> 
using namespace std;

#define MAX_V 20//��󶥵���

typedef struct
{
	int code;//������
	char name;//��������
}vertexType;

typedef struct
{
	int arcs[MAX_V][MAX_V];//�ڽӾ���
	int vexNum, arcNum;//�������ͱ���
	vertexType vexs[MAX_V];//������Ϣ
	int graph_type;
}mGraph;

//1����������ͼ
void create_graph(mGraph &G)
{
	cin >> G.graph_type >> G.vexNum >> G.arcNum;
	int i, j, k;
	for(i=0; i<G.vexNum; i++)
	{
		G.vexs[i].code = i;//���붥����Ϣ
		cin >> G.vexs[i].name;
	}
	for(i=0; i<G.vexNum; i++)
		for(j=0; j<G.vexNum; j++)
			G.arcs[i][j] = 0;//����ͼ�ڽӾ����ʼ��
	for(k=0; k<G.arcNum; k++)
	{
		cin >> i >> j;
		G.arcs[i][j] = 1;//���ڱ���ֵ
		if(G.graph_type == 0)//��Ϊ����ͼ����ԳƵı߸�ֵ
			G.arcs[j][i] = 1;
	} 
}

//2������
void destroy_graph(mGraph &G)
{
	//�ڽӾ�������
	int i, j;
	for(i=0; i<G.vexNum; i++)
		for(j=0; j<G.vexNum; j++)
			G.arcs[i][j] = 0;
	//���������Ϣ
	for(i=0; i<G.vexNum; i++)
	{
		G.vexs[i].code = 0;
		G.vexs[i].name = '0';
	}
	//���������ߵ���Ŀ����
	G.vexNum = 0;
	G.arcNum = 0; 
}

//3�����ض���Ԫ��,vΪ������ 
char get_vex(mGraph G, int v)
{
	return G.vexs[v].name;
} 

//4�����ص�һ���ڽӵ�,vΪ������ 
char first_adjVex(mGraph G, int v)
{
	int j;
	for(j=0; j<G.vexNum; j++)
		if(G.arcs[v][j])
			return G.vexs[j].name;
	return -1;
} 

//5������v�����w����һ���ڽӵ㣬v��wΪ������ 
char next_adjVex(mGraph G, int v, int w)
{
	int j;
	if(w == G.vexNum-1) return -1; 
	for(j=0; j<G.vexNum; j++)
		if(G.arcs[v][j] && j>w)
			return G.vexs[j].name;
	return -1; 
}
 
//6��������ȱ���
void DFS(mGraph G, int *visit, int index)
{
	int i;
	cout << G.vexs[index].name;
	visit[index] = 1;
	for(i=0; i<G.vexNum; i++)
		if(G.arcs[index][i] && !visit[i])
			DFS(G, visit, i);
}
void DFS_traverse(mGraph G)
{
	int i, *visit;
	visit = (int *) malloc(G.vexNum * sizeof(int));
	memset(visit, 0, G.vexNum * sizeof(int));//������visit�ڵ�ֵ��ʼ��Ϊ0 
	for(i=0; i<G.vexNum; i++)
		if(!visit[i])
			DFS(G, visit, i);
	free(visit);
	cout << endl; 
}

//7��������ȱ���
void BFS(mGraph G, int *visit, int index)
{
	int queue[MAX_V], front = 0, rear = 0;
	queue[rear] = index;
	rear = (rear + 1) % MAX_V;
	visit[index] = 1;
	while(front != rear)
	{
		int i;
		int k = queue[front];//��ͷ����
		front = (front + 1) % MAX_V;
		cout << G.vexs[k].name;//���� 
		for(i=0; i<G.vexNum; i++)
			if(G.arcs[k][i] && !visit[i])
			{
				queue[rear] = i;
				rear = (rear + 1) % MAX_V;
				visit[i] = 1;
			}
	} 
} 
void BFS_traverse(mGraph G)
{
	int i, *visit;
	visit = (int *) malloc(G.vexNum * sizeof(int));
	memset(visit, 0, G.vexNum * sizeof(int));
	for(i=0; i<G.vexNum; i++)
		if(!visit[i])
			BFS(G, visit, i);
	free(visit);
	cout << endl; 
}

//8����ͼ������µĶ���v, vΪ��������
void InsertVex(mGraph &G, char v)
{
	G.vexs[G.vexNum].code = G.vexNum;//��ֵ������
	G.vexs[G.vexNum].name = v;//��ֵ��������
	int i;
	for(i=0; i<G.vexNum; i++)//�����ڽӾ��� 
	{
		G.arcs[G.vexNum][i] = 0;
		G.arcs[i][G.vexNum] = 0;
	}
	G.vexNum++;//���¶�����
}

//9����ͼ������µı�<v, w>��v��wΪ�������� 
void InsertArc(mGraph &G, char v, char w)
{
	int i, j, k;
	//�ҵ�����������ı��
	for(k=0; k<G.vexNum; k++)
	{
		if(G.vexs[k].name == v)
			i = k;
		if(G.vexs[k].name == w)
			j = k;
	}
	//�����ڽӾ���
	G.arcs[i][j] = 1;
	G.arcs[j][i] = 1;
	//���±ߵ���Ŀ
	G.arcNum++; 
}

//10��ɾ������v������ر�
void deleteVex(mGraph &G, char v)
{
	//�ҵ�����v�ı��vN
	int i, j, vN, arc_delete = 0;
	for(i=0; i<G.vexNum; i++)
		if(G.vexs[i].name == v)
		{
			vN = i;
			break;
		}
	//������Ҫɾ���ı��� 
	for(j=0; j<G.vexNum; j++)
		if(G.arcs[vN][j] == 1)
			arc_delete++;
	//���¶�������
	for(i=vN; i<G.vexNum-1; i++)
		G.vexs[i].name = G.vexs[i+1].name;
	//�����ڽӾ���
	for(i=vN; i<G.vexNum-1; i++)
		for(j=0; j<G.vexNum; j++)
			G.arcs[i][j] = G.arcs[i+1][j];
	for(j=vN; j<G.vexNum-1; j++)
		for(i=0; i<G.vexNum-1; i++)
			G.arcs[i][j] = G.arcs[i][j+1];
	//���¶����� 
	G.vexNum--;
	//���±ߵ���Ŀ
	G.arcNum -= arc_delete;
}

//11��ɾ����<v, w>
void DeleteArc(mGraph &G, char v, char w)
{
	//���ҵ�v�� w�����Ӧ�ı��
	int v_code, w_code, i, j;
	for(i=0; i<G.vexNum; i++)
	{
		if(G.vexs[i].name == v)
			v_code = i;
		if(G.vexs[i].name == w)
			w_code = i;
	}
	//�����ڽӾ���
	G.arcs[v_code][w_code] = 0;
	G.arcs[w_code][v_code] = 0;
	//���±ߵ���Ŀ
	G.arcNum--;
}

int main()
{
	mGraph G;
	create_graph(G);
	cout << "���Ϊ0�Ķ���Ϊ��" << get_vex(G, 0) << endl;
	cout << "���Ϊ0�Ķ���ĵ�һ���ڽӵ�Ϊ��" << first_adjVex(G, 0) << endl;
	cout << "���Ϊ0�Ķ�������ڱ��Ϊ1�Ķ������һ���ڽӵ�Ϊ��" << next_adjVex(G, 0, 1) << endl;
	cout << "������ȱ�����";
	DFS_traverse(G);
	cout << "������ȱ�����";
	BFS_traverse(G); 
	InsertVex(G, '9');
	cout << "��Ӷ���9��(������ȱ���)��" ;
	BFS_traverse(G);
	InsertArc(G, '4', '9');
	cout << "��ӱߣ�4,9����(������ȱ���)��" ;
	BFS_traverse(G);
	deleteVex(G, '2');
	cout << "ɾ������2��(������ȱ���)��";
	BFS_traverse(G);
	//cout << " " << endl;
	DeleteArc(G, '0', '3');
	cout << "ɾ����<0,3>��(������ȱ���)��";
	BFS_traverse(G);
	destroy_graph(G);
	return 0;
}
//�������ݣ�0 9 11 0 1 2 3 4 5 6 7 8 0 1 0 2 0 3 1 4 2 4 3 5 4 6 4 7 5 7 6 8 7 8��
