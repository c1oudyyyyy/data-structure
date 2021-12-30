/*
�Ƚ���������һ����ݽ��ߵ�ʱ��������һ����ݹ黹��ʱ������
Ȼ�󴴽�������ʽ����������ӣ���һ�����а�˳���Ž�Կ�׵���Ϣ����һ�����а�˳���Ż�Կ�׵���Ϣ��
Ȼ���ٽ��н�ͻ��Ĳ�����
���������Ϊ�黹��Կ�ף��������й黹�Ĳ���ֱ��Կ��ȫ���黹��
*/ 

#include<iostream>
#include<stdlib.h>
#include<stdio.h>
#include<algorithm>//ʹ��sort���� 
using namespace std;

struct key//Կ���Լ��軹��Ϣ 
{
	int identity;
	int starttime;
	int endtime;
};

struct keyinfo//Կ���Ƿ�黹 
{
	int identity;
	bool flag;
};

typedef struct QueueNode//Կ�׶��� 
{
	key keymessage;
	struct QueueNode* next;
}QueueNode,*Queueptr;

typedef struct//������Ϣ 
{
	Queueptr front;
	Queueptr rear;
	int length;
}LinkQueue;

key elem[256];
keyinfo kp[256];
int n, time, m;

int InitQueue(LinkQueue& Q)//��ʼ������ 
{
	Q.front = Q.rear = (QueueNode*)malloc(sizeof(struct QueueNode));
	if (!Q.front || !Q.rear)
	{
		cout << "����ռ�ʧ�ܣ�" << endl;
		return 0;
	}
	Q.front->next = NULL;
	Q.length = 0;
	return 1;
}

int EnQueue(LinkQueue& Q, key e)//��� 
{
	QueueNode* p = (QueueNode*)malloc(sizeof(struct QueueNode));
	if (!p)
	{
		cout << "�ռ�����ʧ��" << endl;
		return 0;
	}
	p->keymessage = e;
	p->next = NULL;
	Q.rear->next = p;
	Q.rear = p;
	Q.length++;
	return 1;
}

int DeQueue(LinkQueue& Q, key& e)//���� 
{
	if (Q.rear == Q.front)
	{
		cout << "�����в�����Ԫ��!" << endl;
		return 0;
	}
	QueueNode* p = (QueueNode*)malloc(sizeof(struct QueueNode));
	if (!p)
	{
		cout << "�ռ�����ʧ��" << endl;
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

int QueueTraverse(LinkQueue Q)//�������� 
{
	if (Q.rear == Q.front)
	{
		cout << "��������Ԫ�أ�" << endl;
		return 0;
	}
	QueueNode* p = (QueueNode*)malloc(sizeof(struct QueueNode));
	if (!p)
	{
		cout << "�ռ�����ʧ��" << endl;
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

bool QueueEmpty(LinkQueue Q)//�п� 
{
	if (Q.front == Q.rear)
		return true;
	return false;
}

bool cmp_starttime(const key &a,const key &b)//�ж�����Կ�׽��ߵ�ʱ�� 
{
	if (a.starttime == b.starttime)
		return false;
	return a.starttime < b.starttime;
}

bool cmp_endtime(const key &a,const key &b)//�ж�����Կ�׹黹��ʱ�� 
{
	if (a.endtime == b.endtime)
	{
		if (a.identity < b.identity)
			return true;
		return false;
	}
	return a.endtime < b.endtime;
}

void Initkeyinfo()//��ʼ���黹��Ϣ����ʼ��Կ��ȫ������ 
{
	for (int i = 1; i <= n; i++)
	{
		kp[i].flag = true;
		kp[i].identity = i;
	}
}

void PutKey(key a)//�黹Կ�� 
{
	for (int i = 1; i <= n; i++)
	{
		if (kp[i].flag == false)//�ô����Ի�Կ�� 
		{
			kp[i].identity = a.identity;
			kp[i].flag = true;
			i = n;
		}	
	}
}

void TakeKey(key a)//����Կ�� 
{
	for (int i = 1; i <= n; i++)
	{
		if (kp[i].identity == a.identity&&kp[i].flag==true)//�ô����Խ� 
		{
			kp[i].flag = false;
			kp[i].identity = -1;//��λ��Ϊ�� 
			break;
		}
	}
}

void Traversekey()//���Կ��˳�� 
{
	for (int i = 1; i < n; i++)
	{
		cout << kp[i].identity << " ";
	}
	cout << kp[n].identity;
	cout << endl;
}

void keymanage(LinkQueue& take, LinkQueue& back)//Կ�׹��� 
{
	int temp = 0;
	key tk, bk;
	DeQueue(take, tk);
	DeQueue(back, bk);
	//��ͻ� 
	while ((!QueueEmpty(take) && !QueueEmpty(back))||temp==1)
	{
		if (tk.starttime < bk.endtime)
		{
			TakeKey(tk);
			if (take.length == 0)
				break;
			DeQueue(take, tk);
			if (take.length == 0)
				temp = 1;//ȫ����� 
		}
		else
		{
			PutKey(bk);
			DeQueue(back, bk);
		}
	}
	temp = 0;
	//�� 
	while (!QueueEmpty(back)||temp==1)
	{
		PutKey(bk);
		if (temp == 1)
			break;
		DeQueue(back, bk);
		if (back.length == 0)
			temp = 1;//ȫ���黹 
	}
}

int main()
{
	//��ʼ�� 
	LinkQueue take,back;//��Կ�׶��кͻ�Կ�׶��� 
	InitQueue(take);
	InitQueue(back);
	FILE *fp = fopen("10.txt", "r");
	if(!fp) exit(0);
	fscanf(fp, "%d %d", &n, &m);
	Initkeyinfo();//��ʼ��Կ�׺� 
	for(int i=1;i<=m;i++)
	{
		fscanf(fp, "%d %d %d", &elem[i].identity, &elem[i].starttime, &time);
		elem[i].endtime = elem[i].starttime + time;
	}
	
	sort(elem+1, elem + m+1, cmp_starttime);//����ȡ�ߵ�ʱ�䣬��Կ�׽�������Ȼ��������� 
	for (int i = 1; i <= m; i++)
		EnQueue(take, elem[i]);
		
	sort(elem+1, elem + m+1, cmp_endtime);//���ݹ黹��ʱ�䣬��Կ�׽�������Ȼ����� 
	for (int i = 1; i <= m; i++)
		EnQueue(back, elem[i]);
		
	keymanage(take, back);//Կ�׹��� 
	
	Traversekey();//���Կ��˳��
	
	return 0;
}
