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

//˼·���ȶ���ͷβ�����Ϊͷ��Ȼ��ÿ��һ����㽫���ժ�������ν�������ˣ�ֱ�����һ�����Ϊֹ 
Status ListTrans(LinkList &L)
{
	L.tail->next = NULL;
	L.head->pre = NULL;
	node *prep = L.head->next;//��ǰ���ǰ��
	node *p = prep->next;
	node *tailleft = L.head;//ָ����Ѻ�������˵�ĩβ 
	while(p != L.tail && p != NULL) //������β����β���֮�� ����ѭ�� 
	{
		prep->next = p->next;//ժ����ǰ��㲢�������������
		p->next->pre = prep;
		p->pre = NULL;
		p->next = tailleft;
		tailleft->pre = p;
		tailleft = p;
		
		prep = prep->next;//��һ��
		p = prep->next;
	}
	L.tail->next = tailleft;//��β����
	tailleft->pre = L.tail;
	
	L.tail = L.head->pre;//�޸�βָ�� 
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
