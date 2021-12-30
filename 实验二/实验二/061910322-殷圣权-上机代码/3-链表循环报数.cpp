#include <stdio.h>
#include <stdlib.h>

#define OK 1
#define ERROR 0

typedef int Status;

typedef struct LNode
{
	struct LNode *next;
	int data;
}LNode;

typedef struct ListInfo
{
	LNode *head;
	LNode *tail;
	int length;
}ListInfo;

Status InitList(ListInfo &L)
{
	L.head = (LNode *) malloc(sizeof(LNode));
	if(L.head == NULL) exit(ERROR);
	L.head->next = NULL;
	L.tail = L.head;
	L.length = 0;
	return OK;
}

Status InputElem(ListInfo &L)
{
	int n;
	printf("n = ");
	scanf("%d", &n);
	L.length = n;
	for(int i=1; i<=n; i++)
	{
		LNode *p = (LNode *) malloc(sizeof(LNode));
		if(p == NULL) exit(ERROR);
		p->data = i;
		p->next = NULL;
		L.tail->next = p;
		L.tail = p;
	}
	L.tail->next = L.head;//循环链表 
	return OK;
}

Status numberOff(ListInfo L, int m)
{
	LNode *pre = L.head;//当前结点前驱 
	LNode *p = L.head->next;//当前结点 
	if(p == L.head) return ERROR;//空表，直接返回
	while(L.head->next != L.head)//空表时停止 
	{
		int i = 1;
		while(i < m)
		{
			//向前报数 
			pre = p;
			p = p->next;
			i++;
			
			if(p == L.head)//跳过表头 
			{
				pre = p;
				p = p->next;
			}
		}
		//输出当前结点并删除 
		printf("%d ", p->data);
		pre->next = p->next;
		free(p);
		p = pre->next;
		if(p == L.head)//跳过表头 
		{
			pre = p;
			p = p->next;
		}
	}
	return OK;
}

int main()
{
	ListInfo L;
	InitList(L);
	InputElem(L);
	int m;
	printf("m = ");
	scanf("%d", &m);
	printf("出列顺序：\n"); 
	numberOff(L, m);
	return 0;
}
