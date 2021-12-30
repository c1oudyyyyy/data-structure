#include <stdio.h>
#include <stdlib.h>

#define OK 1
#define ERROR 0

typedef int Status;

typedef struct node
{
	struct node *next;
	struct node *pre;//创建单向循环链表时指向空 
	int data;
}node;

typedef struct LinkList
{
	node *head;
	node *tail;
	int length;
}LinkList;

Status CreateSingle(LinkList &L)//创建单向循环链表 
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
		p->pre = NULL;
		L.tail->next = p;
		L.tail = p;
	}
	L.tail->next = L.head;
	return OK;
}

Status SingleToDouble(LinkList &L)//将单向循环链表改为双向循环链表
{
	node *prep, *p;
	prep = L.head;//指向当前结点前驱 
	p = prep->next;
	while(p != L.head)
	{
		p->pre = prep;//当前结点pre指针指向前驱 
		prep = prep->next;
		p = prep->next;
	}
	L.head->pre = L.tail;
	return OK;
}

Status ListTraverse(LinkList L)//利用pre指针逆向遍历输出链表，测试是否修改成功 
{
	node *p = L.tail;
	while(p != L.head)
	{
		printf("%d ", p->data);
		p = p->pre;
	}
	return OK;
}

int main()
{
	LinkList L;
	CreateSingle(L);
	SingleToDouble(L);
	printf("利用修改好的pre指针遍历输出链表："); 
	ListTraverse(L);
	return 0;
}
