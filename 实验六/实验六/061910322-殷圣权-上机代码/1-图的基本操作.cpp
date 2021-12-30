#include <iostream>
#include <cstdlib>
#include <cstring> 
using namespace std;

#define MAX_V 20//最大顶点数

typedef struct
{
	int code;//顶点编号
	char name;//顶点名字
}vertexType;

typedef struct
{
	int arcs[MAX_V][MAX_V];//邻接矩阵
	int vexNum, arcNum;//顶点数和边数
	vertexType vexs[MAX_V];//顶点信息
	int graph_type;
}mGraph;

//1、创建无向图
void create_graph(mGraph &G)
{
	cin >> G.graph_type >> G.vexNum >> G.arcNum;
	int i, j, k;
	for(i=0; i<G.vexNum; i++)
	{
		G.vexs[i].code = i;//输入顶点信息
		cin >> G.vexs[i].name;
	}
	for(i=0; i<G.vexNum; i++)
		for(j=0; j<G.vexNum; j++)
			G.arcs[i][j] = 0;//无向图邻接矩阵初始化
	for(k=0; k<G.arcNum; k++)
	{
		cin >> i >> j;
		G.arcs[i][j] = 1;//存在边则赋值
		if(G.graph_type == 0)//若为无向图，则对称的边赋值
			G.arcs[j][i] = 1;
	} 
}

//2、销毁
void destroy_graph(mGraph &G)
{
	//邻接矩阵清零
	int i, j;
	for(i=0; i<G.vexNum; i++)
		for(j=0; j<G.vexNum; j++)
			G.arcs[i][j] = 0;
	//清除顶点信息
	for(i=0; i<G.vexNum; i++)
	{
		G.vexs[i].code = 0;
		G.vexs[i].name = '0';
	}
	//顶点数，边的数目清零
	G.vexNum = 0;
	G.arcNum = 0; 
}

//3、返回顶点元素,v为顶点编号 
char get_vex(mGraph G, int v)
{
	return G.vexs[v].name;
} 

//4、返回第一个邻接点,v为顶点编号 
char first_adjVex(mGraph G, int v)
{
	int j;
	for(j=0; j<G.vexNum; j++)
		if(G.arcs[v][j])
			return G.vexs[j].name;
	return -1;
} 

//5、返回v相对于w的下一个邻接点，v和w为顶点编号 
char next_adjVex(mGraph G, int v, int w)
{
	int j;
	if(w == G.vexNum-1) return -1; 
	for(j=0; j<G.vexNum; j++)
		if(G.arcs[v][j] && j>w)
			return G.vexs[j].name;
	return -1; 
}
 
//6、深度优先遍历
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
	memset(visit, 0, G.vexNum * sizeof(int));//将数组visit内的值初始化为0 
	for(i=0; i<G.vexNum; i++)
		if(!visit[i])
			DFS(G, visit, i);
	free(visit);
	cout << endl; 
}

//7、广度优先遍历
void BFS(mGraph G, int *visit, int index)
{
	int queue[MAX_V], front = 0, rear = 0;
	queue[rear] = index;
	rear = (rear + 1) % MAX_V;
	visit[index] = 1;
	while(front != rear)
	{
		int i;
		int k = queue[front];//队头出队
		front = (front + 1) % MAX_V;
		cout << G.vexs[k].name;//访问 
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

//8、在图中添加新的顶点v, v为顶点名字
void InsertVex(mGraph &G, char v)
{
	G.vexs[G.vexNum].code = G.vexNum;//赋值顶点编号
	G.vexs[G.vexNum].name = v;//赋值顶点名字
	int i;
	for(i=0; i<G.vexNum; i++)//更新邻接矩阵 
	{
		G.arcs[G.vexNum][i] = 0;
		G.arcs[i][G.vexNum] = 0;
	}
	G.vexNum++;//更新顶点数
}

//9、在图中添加新的边<v, w>，v和w为顶点名字 
void InsertArc(mGraph &G, char v, char w)
{
	int i, j, k;
	//找到这两个顶点的编号
	for(k=0; k<G.vexNum; k++)
	{
		if(G.vexs[k].name == v)
			i = k;
		if(G.vexs[k].name == w)
			j = k;
	}
	//更新邻接矩阵
	G.arcs[i][j] = 1;
	G.arcs[j][i] = 1;
	//更新边的数目
	G.arcNum++; 
}

//10、删除顶点v及其相关边
void deleteVex(mGraph &G, char v)
{
	//找到顶点v的编号vN
	int i, j, vN, arc_delete = 0;
	for(i=0; i<G.vexNum; i++)
		if(G.vexs[i].name == v)
		{
			vN = i;
			break;
		}
	//计算需要删除的边数 
	for(j=0; j<G.vexNum; j++)
		if(G.arcs[vN][j] == 1)
			arc_delete++;
	//更新顶点数组
	for(i=vN; i<G.vexNum-1; i++)
		G.vexs[i].name = G.vexs[i+1].name;
	//更新邻接矩阵
	for(i=vN; i<G.vexNum-1; i++)
		for(j=0; j<G.vexNum; j++)
			G.arcs[i][j] = G.arcs[i+1][j];
	for(j=vN; j<G.vexNum-1; j++)
		for(i=0; i<G.vexNum-1; i++)
			G.arcs[i][j] = G.arcs[i][j+1];
	//更新顶点数 
	G.vexNum--;
	//更新边的数目
	G.arcNum -= arc_delete;
}

//11、删除边<v, w>
void DeleteArc(mGraph &G, char v, char w)
{
	//先找到v， w顶点对应的编号
	int v_code, w_code, i, j;
	for(i=0; i<G.vexNum; i++)
	{
		if(G.vexs[i].name == v)
			v_code = i;
		if(G.vexs[i].name == w)
			w_code = i;
	}
	//更新邻接矩阵
	G.arcs[v_code][w_code] = 0;
	G.arcs[w_code][v_code] = 0;
	//更新边的数目
	G.arcNum--;
}

int main()
{
	mGraph G;
	create_graph(G);
	cout << "编号为0的顶点为：" << get_vex(G, 0) << endl;
	cout << "编号为0的顶点的第一个邻接点为：" << first_adjVex(G, 0) << endl;
	cout << "编号为0的顶点相对于编号为1的顶点的下一个邻接点为：" << next_adjVex(G, 0, 1) << endl;
	cout << "深度优先遍历：";
	DFS_traverse(G);
	cout << "广度优先遍历：";
	BFS_traverse(G); 
	InsertVex(G, '9');
	cout << "添加顶点9后(广度优先遍历)：" ;
	BFS_traverse(G);
	InsertArc(G, '4', '9');
	cout << "添加边（4,9）后(广度优先遍历)：" ;
	BFS_traverse(G);
	deleteVex(G, '2');
	cout << "删除顶点2后(广度优先遍历)：";
	BFS_traverse(G);
	//cout << " " << endl;
	DeleteArc(G, '0', '3');
	cout << "删除边<0,3>后(广度优先遍历)：";
	BFS_traverse(G);
	destroy_graph(G);
	return 0;
}
//测试数据：0 9 11 0 1 2 3 4 5 6 7 8 0 1 0 2 0 3 1 4 2 4 3 5 4 6 4 7 5 7 6 8 7 8。
