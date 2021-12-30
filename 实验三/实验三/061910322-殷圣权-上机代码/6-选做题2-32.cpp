#include <stdio.h>
#include <stdlib.h>

#define OK 1
#define ERROR 0

typedef int Status;

typedef struct node
{
	struct node *next;
	struct node *pre;//��������ѭ������ʱָ��� 
	int data;
}node;

typedef struct LinkList
{
	node *head;
	node *tail;
	int length;
}LinkList;

Status CreateSingle(LinkList &L)//��������ѭ������ 
{
	L.head = (node *) malloc(sizeof(node));
	if(L.head == NULL) exit(ERROR);
	L.head->next = NULL;
	L.head->pre = NULL;
	L.tail = L.head;
	
	int n, i;
	printf("����Ԫ�ظ�����");
	scanf("%d", &n);
	L.length = n;
	printf("����Ԫ�أ�");
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

Status SingleToDouble(LinkList &L)//������ѭ�������Ϊ˫��ѭ������
{
	node *prep, *p;
	prep = L.head;//ָ��ǰ���ǰ�� 
	p = prep->next;
	while(p != L.head)
	{
		p->pre = prep;//��ǰ���preָ��ָ��ǰ�� 
		prep = prep->next;
		p = prep->next;
	}
	L.head->pre = L.tail;
	return OK;
}

Status ListTraverse(LinkList L)//����preָ���������������������Ƿ��޸ĳɹ� 
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
	printf("�����޸ĺõ�preָ������������"); 
	ListTraverse(L);
	return 0;
}
