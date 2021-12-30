/*
先将数据排序，一组根据借走的时间排序，另一组根据归还的时间排序，
然后创建两个链式队列依次入队，即一个队列按顺序存放借钥匙的信息，另一个队列按顺序存放还钥匙的信息。
然后再进行借和还的操作，
最后若还有为归还的钥匙，继续进行归还的操作直至钥匙全部归还。
*/ 

#include<iostream>
#include<stdlib.h>
#include<stdio.h>
#include<algorithm>//使用sort函数 
using namespace std;

struct key//钥匙以及借还信息 
{
	int identity;
	int starttime;
	int endtime;
};

struct keyinfo//钥匙是否归还 
{
	int identity;
	bool flag;
};

typedef struct QueueNode//钥匙队列 
{
	key keymessage;
	struct QueueNode* next;
}QueueNode,*Queueptr;

typedef struct//队列信息 
{
	Queueptr front;
	Queueptr rear;
	int length;
}LinkQueue;

key elem[256];
keyinfo kp[256];
int n, time, m;

int InitQueue(LinkQueue& Q)//初始化队列 
{
	Q.front = Q.rear = (QueueNode*)malloc(sizeof(struct QueueNode));
	if (!Q.front || !Q.rear)
	{
		cout << "申请空间失败！" << endl;
		return 0;
	}
	Q.front->next = NULL;
	Q.length = 0;
	return 1;
}

int EnQueue(LinkQueue& Q, key e)//入队 
{
	QueueNode* p = (QueueNode*)malloc(sizeof(struct QueueNode));
	if (!p)
	{
		cout << "空间申请失败" << endl;
		return 0;
	}
	p->keymessage = e;
	p->next = NULL;
	Q.rear->next = p;
	Q.rear = p;
	Q.length++;
	return 1;
}

int DeQueue(LinkQueue& Q, key& e)//出队 
{
	if (Q.rear == Q.front)
	{
		cout << "队列中不存在元素!" << endl;
		return 0;
	}
	QueueNode* p = (QueueNode*)malloc(sizeof(struct QueueNode));
	if (!p)
	{
		cout << "空间申请失败" << endl;
		return 0;
	}
	p = Q.front->next;
	e = p->keymessage;
	Q.front->next = p->next;
	if (Q.rear == p)
	{
		Q.rear = Q.front;
	}
	free(p);
	Q.length--;
	return 1;
}

int QueueTraverse(LinkQueue Q)//遍历队列 
{
	if (Q.rear == Q.front)
	{
		cout << "队列中无元素！" << endl;
		return 0;
	}
	QueueNode* p = (QueueNode*)malloc(sizeof(struct QueueNode));
	if (!p)
	{
		cout << "空间申请失败" << endl;
		return 0;
	}
	p = Q.front->next;
	while (p != NULL)
	{
		cout << p->keymessage.identity << " " << p->keymessage.starttime << " " << p->keymessage.endtime << endl;
		p = p->next;
	}
	return 1;
}

bool QueueEmpty(LinkQueue Q)//判空 
{
	if (Q.front == Q.rear)
		return true;
	return false;
}

bool cmp_starttime(const key &a,const key &b)//判断两把钥匙借走的时间 
{
	if (a.starttime == b.starttime)
		return false;
	return a.starttime < b.starttime;
}

bool cmp_endtime(const key &a,const key &b)//判断两把钥匙归还的时间 
{
	if (a.endtime == b.endtime)
	{
		if (a.identity < b.identity)
			return true;
		return false;
	}
	return a.endtime < b.endtime;
}

void Initkeyinfo()//初始化归还信息，初始化钥匙全部都在 
{
	for (int i = 1; i <= n; i++)
	{
		kp[i].flag = true;
		kp[i].identity = i;
	}
}

void PutKey(key a)//归还钥匙 
{
	for (int i = 1; i <= n; i++)
	{
		if (kp[i].flag == false)//该处可以还钥匙 
		{
			kp[i].identity = a.identity;
			kp[i].flag = true;
			i = n;
		}	
	}
}

void TakeKey(key a)//借走钥匙 
{
	for (int i = 1; i <= n; i++)
	{
		if (kp[i].identity == a.identity&&kp[i].flag==true)//该处可以借 
		{
			kp[i].flag = false;
			kp[i].identity = -1;//该位置为空 
			break;
		}
	}
}

void Traversekey()//输出钥匙顺序 
{
	for (int i = 1; i < n; i++)
	{
		cout << kp[i].identity << " ";
	}
	cout << kp[n].identity;
	cout << endl;
}

void keymanage(LinkQueue& take, LinkQueue& back)//钥匙管理 
{
	int temp = 0;
	key tk, bk;
	DeQueue(take, tk);
	DeQueue(back, bk);
	//借和还 
	while ((!QueueEmpty(take) && !QueueEmpty(back))||temp==1)
	{
		if (tk.starttime < bk.endtime)
		{
			TakeKey(tk);
			if (take.length == 0)
				break;
			DeQueue(take, tk);
			if (take.length == 0)
				temp = 1;//全部借出 
		}
		else
		{
			PutKey(bk);
			DeQueue(back, bk);
		}
	}
	temp = 0;
	//还 
	while (!QueueEmpty(back)||temp==1)
	{
		PutKey(bk);
		if (temp == 1)
			break;
		DeQueue(back, bk);
		if (back.length == 0)
			temp = 1;//全部归还 
	}
}

int main()
{
	//初始化 
	LinkQueue take,back;//拿钥匙队列和还钥匙队列 
	InitQueue(take);
	InitQueue(back);
	FILE *fp = fopen("10.txt", "r");
	if(!fp) exit(0);
	fscanf(fp, "%d %d", &n, &m);
	Initkeyinfo();//初始化钥匙盒 
	for(int i=1;i<=m;i++)
	{
		fscanf(fp, "%d %d %d", &elem[i].identity, &elem[i].starttime, &time);
		elem[i].endtime = elem[i].starttime + time;
	}
	
	sort(elem+1, elem + m+1, cmp_starttime);//根据取走的时间，对钥匙进行排序然后依次入队 
	for (int i = 1; i <= m; i++)
		EnQueue(take, elem[i]);
		
	sort(elem+1, elem + m+1, cmp_endtime);//根据归还的时间，对钥匙进行排序然后入队 
	for (int i = 1; i <= m; i++)
		EnQueue(back, elem[i]);
		
	keymanage(take, back);//钥匙管理 
	
	Traversekey();//输出钥匙顺序
	
	return 0;
}
