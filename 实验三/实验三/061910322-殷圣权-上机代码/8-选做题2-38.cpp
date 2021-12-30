#include <stdio.h>
#include <stdlib.h>

#define OK 1
#define ERROR 0

typedef int Status;

typedef struct node
{
	struct node *next;
	struct node *pre;
	int freq; 
	int data;
}node;

typedef struct LinkList
{
	node *head;
	node *tail;
	int length;
}LinkList;

Status CreateList(LinkList &L)//创建双向循环链表 
{
	L.head = (node *) malloc(sizeof(node));
	if(L.head == NULL) exit(ERROR);
	L.head->next = NULL;
	L.head->pre = NULL;
	L.tail = L.head;
	
	int n, i;
	printf("输入元素个数：");
	scanf("%d", &n);
	L.length = n;
	printf("输入元素：");
	for(i = 1; i <= L.length; i++)
	{
		node *p = (node *) malloc(sizeof(node));
		if(p == NULL) exit(ERROR);
		p->freq = 0;//初始化频度为0 
		scanf("%d", &p->data);
		p->next = NULL;
		p->pre = L.tail;
		L.tail->next = p;
		L.tail = p;
	}
	L.tail->next = L.head;
	L.head->pre = L.tail;
	return OK;
}

//思路：先找到值为e的结点，freq+1， 然后对比前驱结点，若freq大则往前移，直至freq比前驱小 
Status LocateElem(LinkList &L, int e)
{
	node *p = L.head->next;
	while(p->data != e)//找到值为e的结点 
		p = p->next;
	p->freq += 1;//频度+1 
	node *prep = p->pre;//前驱结点
	while(p->freq > prep->freq && p != L.head->next)//当频度小于前驱或p为第一个结点，结束循环 
	{
		prep->next = p->next;//先摘除，再接在前驱之前
		p->next->pre = prep;
		p->pre = prep->pre;
		p->next = prep;
		prep->pre->next = p;
		prep->pre = p;
		
		prep = p->pre;//更新前驱 
	} 
	return OK;
}

Status ListTraverse(LinkList L)
{
	node *p = L.head->next;
	while(p != L.head)
	{
		printf("%d ", p->data);
		p = p->next;
	}
	return OK;
}

int main()
{
	LinkList L;
	CreateList(L);
	LocateElem(L, 5); 
	LocateElem(L, 5); 
	LocateElem(L, 3); 
	printf("查找两次5，一次3后："); 
	ListTraverse(L);
	return 0;
}
