#include <stdio.h>//ex0103_2.cpp
#include <stdlib.h>
#define ERROR 0
#define OK 1

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
	LNode *pCurNode;
	int length;
}ListInfo;

Status InitList(ListInfo &L)
{
	L.head = (LNode *) malloc(sizeof(LNode));
	if(L.head == NULL) exit(ERROR);
	L.head->next = NULL;
	L.tail = L.head;
	L.pCurNode = L.head;
	L.length = 0;
	return OK;
}

Status InputElem(ListInfo &L)
{
	LNode *p;
	int x;
	int i = 0;
	scanf("%d", &x);
	while(x != -1)
	{
		i++;
		p = (LNode *) malloc(sizeof(LNode));
		p->data = x;
		p->next = NULL;
		L.tail->next = p;
		L.tail = p;
		scanf("%d", &x);
	}
	L.tail = p;
	L.length = i;
	return OK;
}

Status ListTraverse(ListInfo &L)
{
	
	if(L.head == NULL)
	{
		printf("链表已被销毁\n");
		return ERROR;
	}
	if(L.head->next == NULL)
	{
		printf("链表为空\n");
		return ERROR;
	} 
	LNode *p = L.head->next;
	while(p != NULL)
	{
		printf("%d ", p->data);
		p = p->next;
	}
	printf("\n");
	return OK;
}


Status DeleteRepeat(ListInfo &L)
{
	int i, j=1;
	LNode *p = L.head->next;
	LNode *q;
	while(p != NULL)
	{
		q = p;
		while(q->next != NULL)
		{
			if(q->next->data == p->data)
			{
				LNode *r = q->next;
				q->next = r->next;
				free(r);
			}
			else
				q = q->next;
		}
		p = p->next;		
	} 
	return OK;
}

int main()
{
	ListInfo L;
	InitList(L);
	InputElem(L);
	DeleteRepeat(L);
	printf("删除重复数据之后：");
	ListTraverse(L);
	return 0;
}
