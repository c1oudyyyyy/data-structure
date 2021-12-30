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

//���г�ʼ��
Status CreateLinkQueue(LinkQueue &Q)
{
	node *head = (node *) malloc(sizeof(node));//����ͷ��� 
	if(head == NULL) exit(ERROR);
	head->next = NULL;
	Q.tail = head; 
	head->prev = NULL;
	int n;
	printf("����Ԫ�ظ�����");
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

//���:��Ԫ�ؽ��ڶ�β�������¶�β 
Status EnQueue(LinkQueue &Q, int e)
{
	node *p = (node *) malloc(sizeof(node));
	if(p == NULL) exit(ERROR);
	p->data = e;
	p->next = Q.tail->next;
	p->prev = Q.tail;
	Q.tail->next->prev = p;
	Q.tail->next = p;
	
	Q.tail = p;//���±�βָ�� 
	return OK;
}

//���ӣ�ժ��ͷ�����һ����㣬���Ǳ�β�������ж�
Status DeQueue(LinkQueue &Q, int &e)
{
	if(Q.tail->next->next == Q.tail)//ֻ��һ��Ԫ�� 
	{
		e = Q.tail->data;
		free(Q.tail);
		Q.tail = NULL;
		printf("�����ѿ�\n");
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

//�������
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
	printf("��ʼ���У�");
	QueueTraverse(Q);
	EnQueue(Q, 6);
	printf("6��Ӻ�");
	QueueTraverse(Q);
	int e;
	DeQueue(Q, e);
	printf("ĳԪ�س��Ӻ�");
	QueueTraverse(Q);
	printf("����Ԫ��Ϊ��%d\n", e); 
	return 0;
}
