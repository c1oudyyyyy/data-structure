#include <stdio.h>
#include <stdlib.h>

#define OK 1
#define ERROR 0

typedef int Status;

typedef struct node
{
	struct node *next;
	int data;
}node;

typedef struct LinkQueue
{
	node *front;
	node *rear;
	int length;
}LinkQueue;

//初始化链式队列 
Status InitQueue(LinkQueue &Q)
{
	Q.front = (node *) malloc(sizeof(node));
	if(Q.front == NULL) exit(ERROR);
	Q.front->next = NULL;
	Q.rear = Q.front;
	Q.length = 0;
	return OK;
}

//销毁
Status DestroyQueue(LinkQueue &Q)
{
	if(Q.front != NULL)//队列存在 
	{
		while(Q.front->next != NULL)
		{
			node *p = Q.front->next;
			Q.front->next = p->next;
			free(p);
		}
		free(Q.front);
		Q.front = NULL;
		Q.rear = NULL;
		Q.length = 0;
		printf("队列已被销毁\n");
		return OK;
	}
	printf("队列不存在\n");
	return ERROR; 
} 

//清空
Status ClearQueue(LinkQueue &Q)
{
	if(Q.front != NULL && Q.front != Q.rear)//队列存在且非空 
	{
		while(Q.front->next != NULL)
		{
			node *p = Q.front->next;
			Q.front->next = p->next;
			free(p);
		}
		Q.rear = Q.front;
		Q.length = 0;
		printf("队列已被清空\n");
		return OK;
	}
	printf("队列不存在\n");
	return ERROR;
}

//判空
bool QueueEmpty(LinkQueue Q)
{
	if(Q.front != NULL)//队列存在 
	{
		if(Q.front == Q.rear)
			return true;
		return false;
	}
	printf("队列不存在\n");
	return true;
}

//获取元素个数
int QueueLength(LinkQueue Q)
{
	if(Q.front != NULL)//队列存在
	{ 
		return Q.length;
	}
	printf("队列不存在\n");
	return ERROR; 
}

//获取队头元素
Status GetHead(LinkQueue Q, int &e)
{
	if(Q.front != NULL && Q.front != Q.rear)//队列存在且非空
	{
		e = Q.front->next->data;
		return OK; 
	}
	printf("队列不存在或为空\n");
	return ERROR;
}

//遍历输出
Status QueueTraverse(LinkQueue Q)
{
	if(Q.front != NULL && Q.front != Q.rear)//队列存在且非空
	{
		node *p = Q.front->next;
		while(p != NULL)
		{
			printf("%d ", p->data);
			p = p->next;
		}
		printf("\n"); 
		return OK;
	}
	printf("队列不存在或为空\n");
	return ERROR;
}

//入队
Status EnQueue(LinkQueue &Q, int e)
{
	if(Q.front != NULL)//队列存在
	{
		node *p = (node *) malloc(sizeof(node));
		if(p == NULL) exit(ERROR); 
		p->data = e;
		p->next = NULL;
		Q.rear->next = p;
		Q.rear = p;
		Q.length += 1;
		return OK;
	}
	printf("队列不存在\n");
	return ERROR;
}

//出队
Status DeQueue(LinkQueue &Q, int &e)
{
	if(Q.front != NULL && Q.front != Q.rear)//队列存在且非空 
	{
		node *p = Q.front->next;
		Q.front->next = p->next;
		e = p->data;
		if(p == Q.rear)//更正队尾 
			Q.rear = Q.front;
		free(p);
		Q.length -= 1;
		return OK;
	}
	printf("队列不存在或为空\n");
	return ERROR;
}

//输入元素
Status InputElem(LinkQueue &Q)
{
	int i, n;
	printf("输入元素个数：");
	scanf("%d", &n);
	Q.length = n;
	printf("输入元素：");
	for(i = 1; i <= n; i++)
	{
		node *p = (node *) malloc(sizeof(node));
		if(p == NULL) exit(ERROR);
		scanf("%d", &p->data);
		p->next = NULL;
		Q.rear->next = p;
		Q.rear = p;
	}
	return OK;
} 

//测试函数
int main()
{
	LinkQueue Q;
	InitQueue(Q);
	InputElem(Q);
	QueueTraverse(Q);
	EnQueue(Q, 6);
	printf("元素6入队后：");
	QueueTraverse(Q);
	printf("此时元素个数为：%d\n", QueueLength(Q));
	int e;
	DeQueue(Q, e);
	printf("队头出队后：");
	QueueTraverse(Q);
	printf("出队元素为：%d\n", e);
	GetHead(Q, e);
	printf("此时队头元素为：%d\n", e);
	if(!QueueEmpty(Q))
		printf("此时队列不为空\n");
	ClearQueue(Q);
	if(QueueEmpty(Q))
		printf("此时队列为空\n");
	DestroyQueue(Q);
	QueueEmpty(Q);
	return 0;
} 
