/*
使用两个单链表分别存放当前进程信息以及所有进程信息（作为对照），
使用一个双链表存放已结束进程信息。
当前进程经对照后得出进程运行时间，
若有新进程出现，插入对照链表，
然后再与当前进程链表对比得出已结束进程，并在对照链表中删除。
*/

#include<iostream>
#include<ctime>
#include<stdlib.h>
#include<stdio.h>
#include<vector>
#include<iomanip>
#include<cstring>
#include <windows.h>
#define Ok 1
#define Error 0
using namespace std;
vector<char*> vl;
class task
{
public:
	char name[128];
	int memory;
	SYSTEMTIME start;
	SYSTEMTIME end;
	double time;
	task(char* t) : memory(0)
	{
		char* b = t + 1, *p = t + 1;
		while (*p)
		{
			if (*p == '"')
			{
				*p = 0;
				strcpy(name, b);
				break;
			}
			p++;
		}
		for (b = p + 1; p[1] != 'K'; p++)
			if (*p == '"')
				b = p;
		for (char* c = b + 1; c != p; c++)
			if (*c == ',')
				continue;
			else
				memory = 10 * memory + *c - '0';

	}
	bool operator<(task& t) { return this->memory < t.memory; }//排序 
};

typedef struct DLNode//双链表结点 
{
	task end;
	struct DLNode* prior, * next;
}DLNode, * DLinkList;

typedef struct LNode//单链表结点 
{
	task run;
	struct LNode* next;
}LNode, * LinkList;

int InitDList(DLinkList& L);//初始化双链表 
int InitList(LinkList& L);//初始化单链表 
int ClearDList(DLinkList& L);//清空双链表
int ClearList(LinkList& L);//清空单链表
int insertDList(DLinkList& L, DLNode* p);//插入双链表
int insertList(LinkList& L, LNode* p);//插入单链表
void TraverseDList(DLinkList L);//遍历双链表
void TraverseList(LinkList L);//遍历单链表
int showpresent(LinkList& L, LinkList LL, DLinkList& Lt);//显示当前进程
int showend(DLinkList& L, LinkList LL, LinkList Lt);//显示结束进程
int InitLL(LinkList& L);//初始化对照链表
int circuit(DLinkList& L, LinkList L1);//根据当前删除结束进程
int circuitll(LinkList& pre, LinkList now);//根据现在校验对照组

int main()
{
	LinkList L, LL;//LL-对照,L-当前进程 
	DLinkList L2;//已结束进程 
	InitList(L);
	InitList(LL);
	InitDList(L2);
	InitLL(LL);
	long t = time(NULL);
	while (1)
	{
		ClearList(L);
		showpresent(L, LL, L2);
		circuit(L2, L);
		showend(L2, LL, L);
		circuitll(LL, L);
		//getchar();//暂停服务
	}
}

int InitDList(DLinkList& L)//初始化双链表
{
	L = (DLNode*)malloc(sizeof(struct DLNode));
	if (!L)
		return Error;
	L->next = NULL;
	L->prior = NULL;
	return Ok;
}

int InitList(LinkList& L)//初始化单链表
{
	L = (LNode*)malloc(sizeof(struct LNode));
	if (!L)
		return Error;
	L->next = NULL;
	return 1;
}

int ClearDList(DLinkList& L)//清空双链表
{
	free(L->next);
	L->next = NULL;
	return 1;
}

int ClearList(LinkList& L)//清空单链表
{
	free(L->next);
	L->next = NULL;
	return 1;
}

int insertDList(DLinkList& L, DLNode* p)//插入双链表 
{
	DLNode* temp = L->next, * temp2 = L->next;
	if (!temp)
	{
		L->next = p;
		p->prior = L;
		return Ok;
	}
	while (temp)
	{
		if (temp->end.end.wHour > p->end.end.wHour || (temp->end.end.wHour == p->end.start.wHour && temp->end.end.wMinute > p->end.end.wMinute) || (temp->end.end.wHour == p->end.end.wHour && temp->end.end.wMinute == p->end.end.wMinute && temp->end.end.wSecond > p->end.end.wMinute))
			temp = temp->next;
		else
			break;
	}
	if (!temp)
	{
		while (temp2->next != NULL)
			temp2 = temp2->next;
		temp2->next = p;
		p->prior = temp2;
		return Ok;
	}
	temp->prior->next = p;
	p->next = temp;
	p->prior = temp->prior;
	temp->prior = p;
	return Ok;
}

int insertList(LinkList& L, LNode* p)//插入单链表 
{
	LNode* temp = L->next, * temp2=L;
	if (L->next == NULL)
	{
		L->next = p;
		return 1;
	}
	while (temp)
	{
		if (temp->run.memory >= p->run.memory)
			temp = temp->next;
		else
			break;
	}
	if (!temp)
	{
		while (temp2->next != NULL)
			temp2 = temp2->next;
		temp2->next = p;
		return 1;
	}
	while (temp2->next != temp)
		temp2 = temp2->next;
	temp2->next = p;
	p->next = temp;
	return 1;
}

void TraverseDList(DLinkList L)//遍历双链表 
{
	DLNode* temp = L->next;
	cout << setw(50) << left << "\n已结束进程名称";
	cout << setw(15) << left << "内存调用";
	cout << setw(10) << left << "持续时间";
	cout << setw(10) << left << "结束时间" << endl;
	cout << "===================================================================================================" << endl;
	while (temp)
	{
		cout << setw(50) << left << temp->end.name;
		cout << setw(15) << left << temp->end.memory;
		cout << left << temp->end.time << "s" << '\t';
		cout << left << temp->end.start.wHour << "h" << temp->end.start.wMinute << "min" << temp->end.start.wSecond << "s" << endl;
		temp = temp->next; 
	}
	cout << "---------------------------------------------------------------------------------------------------" << endl;
}

void TraverseList(LinkList L)//遍历单链表 
{
	LNode* temp = L->next;
	cout << setw(70) << left << "\n当前进程名称";
	cout << setw(15) << left << "内存调用";
	cout << setw(10) << left << "持续时间" << endl;
	cout << "=======================================================================================================" << endl;
	while (temp)
	{
		cout << setw(70) << left << temp->run.name;
		cout << setw(15) << left << temp->run.memory;
		cout << setw(10) << left << (double)temp->run.time << "s" << endl;
		temp = temp->next;
	}
	cout << "---------------------------------------------------------------------------------------------------" << endl;
}

int showpresent(LinkList& L, LinkList LL, DLinkList& Lt)//显示当前进程 
{
	int flag = 0;
	char buffer[128], cmd[] = "tasklist /FO CSV";
	FILE* pipe = _popen(cmd, "r");
	if (!pipe)
		return Error;
	fgets(buffer, 128, pipe);
	while (!feof(pipe))
	{
		if (fgets(buffer, 128, pipe))
		{
			flag = 0;
			LNode* p = (LNode*)malloc(sizeof(struct LNode));
			LNode* temp;
			temp = LL->next;
			p->run = task(buffer);
			p->next = NULL;
			GetLocalTime(&p->run.start);
			while (temp)
			{
				if (strcmp(temp->run.name, p->run.name) == 0)
				{
					flag = 1;
					p->run.time = (p->run.start.wMinute - temp->run.start.wMinute) * 60.0 + (p->run.start.wSecond - temp->run.start.wSecond) * 1.0 + (p->run.start.wMilliseconds - temp->run.start.wMilliseconds) * 0.001;
					break;
				}
				temp = temp->next;
			}
			if (flag == 0)
				p->run.time = 0;
			insertList(L, p);
		}
	}
	_pclose(pipe);
	TraverseList(L);
}

int showend(DLinkList& L, LinkList LL, LinkList Lt)//显示结束进程 
{
	int i = 0;
	int flag = 0;
	LNode* temp = LL->next, * temp2 = Lt->next;
	vector<char*> vnow;
	while (temp2)
	{
		vnow.push_back(temp2->run.name);
		temp2 = temp2->next;
	}
	while (temp)
	{
		int flag = 0;
		vector<char*>::iterator iter;
		iter = vnow.begin();
		while (iter != vnow.end())//LL在Lt中找不到
		{
			if (strcmp(*iter, temp->run.name) == 0)
			{
				flag = 1;
				break;
			}
			iter++;
		}
		if (flag == 0)
		{
			DLNode* s = (DLNode*)malloc(sizeof(struct DLNode));
			strcpy(s->end.name, temp->run.name);
			s->end.memory = temp->run.memory;
			s->end.start = temp->run.start;
			s->next = NULL;
			SYSTEMTIME now;
			GetLocalTime(&now);
			GetLocalTime(&s->end.end);
			s->end.time = (now.wMinute - s->end.start.wMinute) * 60.0 + (now.wSecond - s->end.start.wSecond) * 1.0 + (now.wMilliseconds - s->end.start.wMilliseconds) * 0.001;
			s->end.start = now;
			insertDList(L, s);
			vl.push_back(s->end.name);
		}
		temp = temp->next;
	}
	TraverseDList(L);
	return 1;
}

int InitLL(LinkList& L)//初始化对照链表 
{
	char buffer[128], cmd[] = "tasklist /FO CSV";
	FILE* pipe = _popen(cmd, "r");
	if (!pipe)
		return Error;
	fgets(buffer, 128, pipe);
	while (!feof(pipe))
	{
		if (fgets(buffer, 128, pipe))
		{
			LNode* p = (LNode*)malloc(sizeof(struct LNode));
			p->run = task(buffer);
			p->next = NULL;
			GetLocalTime(&p->run.start);
			insertList(L, p);
		}
	}
	_pclose(pipe);
}

int circuit(DLinkList& L, LinkList L1)//根据present删除结束进程 
{
	LNode* temp = L1->next;
	while (temp)
	{
		vector<char*>::iterator iter;
		iter = vl.begin();
		while (iter != vl.end())
		{
			if (strcmp(*iter, temp->run.name) == 0)
			{
				DLNode* temp3 = L->next;
				while (strcmp(*iter, temp3->end.name) != 0)
				{
					temp3 = temp3->next;
				}
				DLNode* temp2 = L;
				while (temp2->next != temp3)
				{
					temp2 = temp2->next;
				}
				temp2->next = temp3->next;
				vl.erase(iter);
				break;
			}
			iter++;
		}
		temp = temp->next;
	}
	return 1;
}

int circuitll(LinkList& pre, LinkList now)//根据现在校验对照组 
{
	vector<char*> prev;
	LNode* temp = now->next, * temp2 = pre->next;
	while (temp2)
	{
		prev.push_back(temp2->run.name);
		temp2 = temp2->next;
	}
	temp = now->next, temp2 = pre->next;
	while (temp2)//寻找now中不存在的删掉
	{
		temp = now->next;
		int flag = 0;
		while (temp)
		{
			if (strcmp(temp->run.name, temp2->run.name) == 0)
			{
				flag = 1;
				break;
			}
			temp = temp->next;
		}
		if (flag == 0)
		{
			LNode* temp3 = pre->next;
			while (temp3->next != temp2)
			{
				temp3 = temp3->next;
			}
			temp2 = temp2->next;
			temp3->next = temp2;
			continue;
		}
		temp2 = temp2->next;
	}
	temp = now->next, temp2 = pre->next;
	while (temp)//now中存在但LL不存在的添加
	{
		int flag = 0;
		vector<char*>::iterator it;
		it = prev.begin();
		while (it != prev.end())
		{
			if (strcmp(*it, temp->run.name) == 0)//LL中存在的
			{
				flag = 1;
				break;
			}
			it++;
		}
		if (flag == 0)
		{
			LNode* s = (LNode*)malloc(sizeof(struct LNode));
			strcpy(s->run.name, temp->run.name);
			s->run.memory = temp->run.memory;
			s->run.start = temp->run.start;
			s->run.time = temp->run.time;
			insertList(pre, s);
		}
		temp = temp->next;
	}
	return 1;
}
