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

//��ʼ����ʽ���� 
Status InitQueue(LinkQueue &Q)
{
	Q.front = (node *) malloc(sizeof(node));
	if(Q.front == NULL) exit(ERROR);
	Q.front->next = NULL;
	Q.rear = Q.front;
	Q.length = 0;
	return OK;
}

//����
Status DestroyQueue(LinkQueue &Q)
{
	if(Q.front != NULL)//���д��� 
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
		printf("�����ѱ�����\n");
		return OK;
	}
	printf("���в�����\n");
	return ERROR; 
} 

//���
Status ClearQueue(LinkQueue &Q)
{
	if(Q.front != NULL && Q.front != Q.rear)//���д����ҷǿ� 
	{
		while(Q.front->next != NULL)
		{
			node *p = Q.front->next;
			Q.front->next = p->next;
			free(p);
		}
		Q.rear = Q.front;
		Q.length = 0;
		printf("�����ѱ����\n");
		return OK;
	}
	printf("���в�����\n");
	return ERROR;
}

//�п�
bool QueueEmpty(LinkQueue Q)
{
	if(Q.front != NULL)//���д��� 
	{
		if(Q.front == Q.rear)
			return true;
		return false;
	}
	printf("���в�����\n");
	return true;
}

//��ȡԪ�ظ���
int QueueLength(LinkQueue Q)
{
	if(Q.front != NULL)//���д���
	{ 
		return Q.length;
	}
	printf("���в�����\n");
	return ERROR; 
}

//��ȡ��ͷԪ��
Status GetHead(LinkQueue Q, int &e)
{
	if(Q.front != NULL && Q.front != Q.rear)//���д����ҷǿ�
	{
		e = Q.front->next->data;
		return OK; 
	}
	printf("���в����ڻ�Ϊ��\n");
	return ERROR;
}

//�������
Status QueueTraverse(LinkQueue Q)
{
	if(Q.front != NULL && Q.front != Q.rear)//���д����ҷǿ�
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
	printf("���в����ڻ�Ϊ��\n");
	return ERROR;
}

//���
Status EnQueue(LinkQueue &Q, int e)
{
	if(Q.front != NULL)//���д���
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
	printf("���в�����\n");
	return ERROR;
}

//����
Status DeQueue(LinkQueue &Q, int &e)
{
	if(Q.front != NULL && Q.front != Q.rear)//���д����ҷǿ� 
	{
		node *p = Q.front->next;
		Q.front->next = p->next;
		e = p->data;
		if(p == Q.rear)//������β 
			Q.rear = Q.front;
		free(p);
		Q.length -= 1;
		return OK;
	}
	printf("���в����ڻ�Ϊ��\n");
	return ERROR;
}

//����Ԫ��
Status InputElem(LinkQueue &Q)
{
	int i, n;
	printf("����Ԫ�ظ�����");
	scanf("%d", &n);
	Q.length = n;
	printf("����Ԫ�أ�");
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

//���Ժ���
int main()
{
	LinkQueue Q;
	InitQueue(Q);
	InputElem(Q);
	QueueTraverse(Q);
	EnQueue(Q, 6);
	printf("Ԫ��6��Ӻ�");
	QueueTraverse(Q);
	printf("��ʱԪ�ظ���Ϊ��%d\n", QueueLength(Q));
	int e;
	DeQueue(Q, e);
	printf("��ͷ���Ӻ�");
	QueueTraverse(Q);
	printf("����Ԫ��Ϊ��%d\n", e);
	GetHead(Q, e);
	printf("��ʱ��ͷԪ��Ϊ��%d\n", e);
	if(!QueueEmpty(Q))
		printf("��ʱ���в�Ϊ��\n");
	ClearQueue(Q);
	if(QueueEmpty(Q))
		printf("��ʱ����Ϊ��\n");
	DestroyQueue(Q);
	QueueEmpty(Q);
	return 0;
} 
