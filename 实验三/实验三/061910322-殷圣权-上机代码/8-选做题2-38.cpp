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

Status CreateList(LinkList &L)//����˫��ѭ������ 
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
		p->freq = 0;//��ʼ��Ƶ��Ϊ0 
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

//˼·�����ҵ�ֵΪe�Ľ�㣬freq+1�� Ȼ��Ա�ǰ����㣬��freq������ǰ�ƣ�ֱ��freq��ǰ��С 
Status LocateElem(LinkList &L, int e)
{
	node *p = L.head->next;
	while(p->data != e)//�ҵ�ֵΪe�Ľ�� 
		p = p->next;
	p->freq += 1;//Ƶ��+1 
	node *prep = p->pre;//ǰ�����
	while(p->freq > prep->freq && p != L.head->next)//��Ƶ��С��ǰ����pΪ��һ����㣬����ѭ�� 
	{
		prep->next = p->next;//��ժ�����ٽ���ǰ��֮ǰ
		p->next->pre = prep;
		p->pre = prep->pre;
		p->next = prep;
		prep->pre->next = p;
		prep->pre = p;
		
		prep = p->pre;//����ǰ�� 
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
	printf("��������5��һ��3��"); 
	ListTraverse(L);
	return 0;
}
