#include <stdio.h>
#include <stdlib.h>

#define OK 1
#define ERROR 0

typedef int Status;

typedef struct node
{
	struct node *next;
	struct node *pre; 
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

//思路：先断裂头尾，左端为头，然后每隔一个结点将结点摘除并依次接在最左端，直至最后一个结点为止 
Status ListTrans(LinkList &L)
{
	L.tail->next = NULL;
	L.head->pre = NULL;
	node *prep = L.head->next;//当前结点前驱
	node *p = prep->next;
	node *tailleft = L.head;//指向断裂后链表左端的末尾 
	while(p != L.tail && p != NULL) //当到达尾结点或尾结点之后 结束循环 
	{
		prep->next = p->next;//摘除当前结点并接在链表最左端
		p->next->pre = prep;
		p->pre = NULL;
		p->next = tailleft;
		tailleft->pre = p;
		tailleft = p;
		
		prep = prep->next;//下一个
		p = prep->next;
	}
	L.tail->next = tailleft;//首尾相连
	tailleft->pre = L.tail;
	
	L.tail = L.head->pre;//修改尾指针 
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
	ListTrans(L);
	ListTraverse(L);
	return 0;
}
