/*
改变迪杰斯特拉算法，将两站之间的距离转化为疲劳度。
记录上一条路径是大道还是小道，若为小道还需累加疲劳值。
*/ 

#include<iostream>
#include<vector>
#include<math.h>
using namespace std;

struct tow 
{
	int name;
	int type;
	int distance; 
};

struct Edge//边集 
{
	vector<tow> to;
	int name;
};

struct Graph//图的邻接表结构 
{
	vector<Edge> e;
	int vexnum, arcnum;
};

struct DjNode//迪杰斯特拉结点结构 
{
	int name;
	int distance;//距离源点 
	int pre;//上一个点 
	int flag;//是否选中 
	int type;//上一条路的类型 
	int sroad;//累计疲劳值 
};

DjNode* DJ = new DjNode[5000];

void Dj(int start, Graph G)//迪杰斯特拉算法 
{
	//初始化Dj数组
	for (int i = 0; i < G.vexnum; i++) 
	{
		DJ[i].distance = INT_MAX - 1;
		DJ[i].flag = false;
		DJ[i].name = G.e[i].name;
		DJ[i].pre = start;
		DJ[i].type = 0;
		DJ[i].sroad = 0;
	}
	DJ[start - 1].pre = start;
	DJ[start - 1].flag = true;
	DJ[start - 1].distance = 0;
	//还是初始化 
	for (int i = 0; i < G.e[start - 1].to.size(); i++)
	{ 
		if (G.e[start - 1].to[i].type == 0)//若为大道 
		{
			if (DJ[start - 1].distance + G.e[start-1].to[i].distance < DJ[G.e[start - 1].to[i].name - 1].distance)
			{
				DJ[G.e[start - 1].to[i].name - 1].distance = DJ[start - 1].distance + G.e[start - 1].to[i].distance;
				DJ[G.e[start - 1].to[i].name - 1].pre = start;
				DJ[G.e[start - 1].to[i].name - 1].type = 0;
				DJ[G.e[start - 1].to[i].name - 1].sroad = 0;
			}
		}
		else//若为小道 
		{
			if (DJ[start - 1].distance + G.e[start - 1].to[i].distance*G.e[start-1].to[i].distance < DJ[G.e[start - 1].to[i].name - 1].distance)
			{
				DJ[G.e[start - 1].to[i].name - 1].distance = DJ[start - 1].distance + G.e[start - 1].to[i].distance * G.e[start - 1].to[i].distance;
				DJ[G.e[start - 1].to[i].name - 1].pre = start;
				DJ[G.e[start - 1].to[i].name - 1].type = 1;
				DJ[G.e[start - 1].to[i].name - 1].sroad = G.e[start - 1].to[i].distance * G.e[start - 1].to[i].distance;
			}
		}
	}
	//循环选中剩余顶点 
	while (1)
	{
		int minnposition = 0, minn = INT_MAX;
		for (int i = 0; i < G.vexnum; i++)
		{
			if (DJ[i].flag == true)
				continue;
			if (DJ[i].distance < minn)//找出最小疲劳值 
			{
				minn = DJ[i].distance;
				minnposition = i;
			}
		}
		DJ[minnposition].flag = true;//选中
		//更新Dj数组
		for (int i = 0; i < G.e[minnposition].to.size(); i++)
		{
			if (G.e[minnposition].to[i].type == 0)//当前为大道 
			{
				if (DJ[minnposition].distance + G.e[minnposition].to[i].distance < DJ[G.e[minnposition].to[i].name - 1].distance)
				{
					//若当前距离小则赋值 
					DJ[G.e[minnposition].to[i].name - 1].distance = DJ[minnposition].distance + G.e[minnposition].to[i].distance;
					//更新上一点 
					DJ[G.e[minnposition].to[i].name - 1].pre = minnposition+1;
					//累计疲劳值清零 
					DJ[G.e[minnposition].to[i].name - 1].sroad = 0;
					//标记下一条路的上一条路为大道 
					DJ[G.e[minnposition].to[i].name - 1].type = 0;
				}
			}
			else if(G.e[minnposition].to[i].type==1&&DJ[minnposition].type==0)//当前为小道，上一次为大道 
			{
				if (DJ[minnposition].distance + G.e[minnposition].to[i].distance * G.e[minnposition].to[i].distance < DJ[G.e[minnposition].to[i].name - 1].distance)
				{
					DJ[G.e[minnposition].to[i].name - 1].distance = DJ[minnposition].distance + G.e[minnposition].to[i].distance * G.e[minnposition].to[i].distance;
					DJ[G.e[minnposition].to[i].name - 1].pre = minnposition+1;
					//增加疲劳值 
					DJ[G.e[minnposition].to[i].name - 1].sroad = G.e[minnposition].to[i].distance * G.e[minnposition].to[i].distance;
					DJ[G.e[minnposition].to[i].name - 1].type = 1;
				}
			}
			else if (G.e[minnposition].to[i].type == 1 && DJ[minnposition].type == 1)//当前和上一次均为小道 
			{
				if (DJ[minnposition].distance-DJ[minnposition].sroad + (sqrt(DJ[minnposition].sroad) + G.e[minnposition].to[i].distance) * (sqrt(DJ[minnposition].sroad) + G.e[minnposition].to[i].distance) < DJ[G.e[minnposition].to[i].name - 1].distance)
				{
					DJ[G.e[minnposition].to[i].name - 1].distance = DJ[minnposition].distance-DJ[minnposition].sroad + (sqrt(DJ[minnposition].sroad) + G.e[minnposition].to[i].distance) * (sqrt(DJ[minnposition].sroad) + G.e[minnposition].to[i].distance);
					DJ[G.e[minnposition].to[i].name - 1].pre = minnposition + 1;
					//疲劳值累加 
					DJ[G.e[minnposition].to[i].name - 1].sroad = (sqrt(DJ[minnposition].sroad) + G.e[minnposition].to[i].distance) * (sqrt(DJ[minnposition].sroad) + G.e[minnposition].to[i].distance);
					DJ[G.e[minnposition].to[i].name - 1].type = 1;
				}
			}
		}
		//判断是否全部选中 
		int sum = 0; 
		for (int i = 0; i < G.vexnum; i++)
		{
			if (DJ[i].flag == true)
			{
				sum++;
			}
		}
		if (sum == G.vexnum)
			break;
	}
}

int main()
{
	int n, m;
	Graph G;
	vector<tow> nope;
	FILE *fp = fopen("11.txt", "r");
	if(!fp) exit(0); 
	fscanf(fp, "%d %d", &n, &m);
	for (int i = 0; i < n; i++)
	{
		G.e.push_back({ nope,i + 1 });
	}
	G.vexnum = n;
	G.arcnum = m;
	while (m--)
	{
		int start, end,type,distance;
		fscanf(fp, "%d %d %d %d", &type, &start, &end, &distance);
		G.e[start - 1].to.push_back({end,type,distance});
		G.e[end - 1].to.push_back({start,type,distance});
	}
	Dj(1,G);
	cout << DJ[G.vexnum - 1].distance << endl;
	vector<int> sta;
	for (int i = 1; i < G.vexnum; i++)
	{
		int temp = DJ[i].name;
		while (DJ[temp - 1].pre != temp)
		{
			temp = DJ[temp - 1].pre;
			sta.push_back(temp);
		}
		//输出到达其他点的最小疲劳值 
		for (int i = sta.size() - 1; i >= 0; i--)
		{
			cout << sta[i] << "->";
		}
		cout << DJ[i].name << " 值:" << DJ[i].distance << endl;
		sta.clear();
	}
}
