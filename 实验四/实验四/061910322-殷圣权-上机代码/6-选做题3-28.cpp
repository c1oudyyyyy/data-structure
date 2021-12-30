#include <stdio.h>
#include <stdlib.h>

#define OK 1
#define ERROR 0

typedef int Status;

typedef struct node
{
	struct node *next;
	struct node *prev;
	int data;
}node;

typedef struct LinkQueue
{
	node *tail;
	int length;
}LinkQueue;

//队列初始化
Status CreateLinkQueue(LinkQueue &Q)
{
	node *head = (node *) malloc(sizeof(node));//创建头结点 
	if(head == NULL) exit(ERROR);
	head->next = NULL;
	Q.tail = head; 
	head->prev = NULL;
	int n;
	printf("输入元素个数：");
	scanf("%d", &n);
	for(int i=1; i<=n; i++)
	{
			node *p = (node *) malloc(sizeof(node));
			if(p == NULL) exit(ERROR);
			scanf("%d", &p->data);
			p->prev = Q.tail;
			p->next = NULL;
			Q.tail->next = p;
			Q.tail = p;
	}
	Q.tail->next = head;
	head->prev = Q.tail;
	return OK;
}

//入队:把元素接在队尾，并更新队尾 
Status EnQueue(LinkQueue &Q, int e)
{
	node *p = (node *) malloc(sizeof(node));
	if(p == NULL) exit(ERROR);
	p->data = e;
	p->next = Q.tail->next;
	p->prev = Q.tail;
	Q.tail->next->prev = p;
	Q.tail->next = p;
	
	Q.tail = p;//更新表尾指针 
	return OK;
}

//出队：摘除头结点后第一个结点，若是表尾则另外判断
Status DeQueue(LinkQueue &Q, int &e)
{
	if(Q.tail->next->next == Q.tail)//只有一个元素 
	{
		e = Q.tail->data;
		free(Q.tail);
		Q.tail = NULL;
		printf("链队已空\n");
		return OK;
	}
	
	else
	{
		e = Q.tail->next->next->data;
		node *p = Q.tail->next->next;
		Q.tail->next->next = p->next;
		p->next->prev = Q.tail->next;
		free(p);
		return OK;
	}
}

//遍历输出
Status QueueTraverse(LinkQueue Q)
{
	node *p = Q.tail->next->next;
	while(p != Q.tail->next)
	{
		printf("%d ", p->data);
		p = p->next;
	}
	printf("\n");
	return OK;
} 

int main()
{
	LinkQueue Q;
	CreateLinkQueue(Q);
	printf("初始队列：");
	QueueTraverse(Q);
	EnQueue(Q, 6);
	printf("6入队后：");
	QueueTraverse(Q);
	int e;
	DeQueue(Q, e);
	printf("某元素出队后：");
	QueueTraverse(Q);
	printf("出队元素为：%d\n", e); 
	return 0;
}
