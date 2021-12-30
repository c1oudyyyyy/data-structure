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
	int n;
	LNode *p;
	printf("请输入元素个数：", &n);
	scanf("%d", &n);
	printf("请输入元素：\n");
	for(int i=1; i<=n; i++)
	{
		p = (LNode *) malloc(sizeof(LNode));
		if(p == NULL) exit(ERROR);
		scanf("%d", &p->data);
		p->next = NULL;
		L.tail->next = p;
		L.tail = p;
	}
	L.length = n;
	return OK;
}

Status ListTraverse(ListInfo L)
{
	LNode *p = L.head->next;
	while(p != NULL)
	{
		printf("%d ", p->data);
		p = p->next;
	}
	printf("\n");
	return OK;
}

Status DeleteBetween(ListInfo &L, int mink, int maxk)
{
	LNode *p, *q, *pre;
	p = L.head->next;
	pre = p;//p结点前驱 
	p = p->next;
	while(p != NULL && p->data < maxk)
	{
		if(p->data <= mink)
		{	//下一个 
			pre = p;
			p = p->next;
		}
		else
		{	//删除当前结点 
			pre->next = p->next;
			q = p;
			p = p->next;
			free(q);
		}
	}
	return OK;
}

int main()
{
	ListInfo L;
	int mink, maxk;
	InitList(L);
	InputElem(L);
	printf("输入mink和maxk\n");
	scanf("%d %d", &mink, &maxk);
	DeleteBetween(L, mink, maxk);
	ListTraverse(L);
	return 0;
}
