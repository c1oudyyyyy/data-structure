#include <stdio.h>
#include <stdlib.h>

#define OK 1
#define ERROR 0

typedef int Status;

typedef struct Node
{
	struct Node *next;
	int data;
}node;

typedef struct ListInfo
{
	node *head;
	node *tail;
	int length;
}ListInfo;

Status InitList(ListInfo &L)
{
	int n, i;
	scanf("%d", &n);
	L.head = (node *) malloc(sizeof(node));
	if(L.head == NULL) exit(ERROR);
	L.head->next = NULL;
	L.tail = L.head;
	L.length = n;
	for(i=1; i<=n; i++)
	{
		node *p = (node *) malloc(sizeof(node));
		if(p == NULL) exit(ERROR);
		scanf("%d", &p->data);
		p->next = NULL;
		L.tail->next = p;
		L.tail = p;
	}
	return OK;
}

//ÿ�ν�b���һ��Ԫ��������a��Ԫ�رȽϣ���b����ժ�������뵽a�����ʵ�λ�ã��������a�� 
Status SortAB(ListInfo &La, ListInfo Lb)
{
	//1���ϲ� 
	node *prev = La.head;//a���еĵ�ǰ���ǰ�� 
	node *p = prev->next;//a���еĵ�ǰ��� 
	while(Lb.head->next != NULL)//��b��Ϊ�� 
	{
		while(p != NULL)//������a��Ѱ�Һ���λ�ò���b���һ��Ԫ�� 
		{
			if(p->data >= Lb.head->next->data)
			{
				//ժ��b��ͷ��Ľ��
				node *s = Lb.head->next;
				Lb.head->next = s->next;
				//��ժ���Ľ�����a��ǰ���֮ǰ
				s->next = p;
				prev->next = s;
				//����ǰ���͵�ǰ��� 
				prev = La.head;
				p = prev->next;
				//����һ��b���� 
				break;
			}
			prev = prev->next;
			p = prev->next;
			
		}
		//a���е�Ԫ�ؾ���С�������a��β
		if(Lb.head->next->data >= La.tail->data)
		{
			//ժ�� 
			node *m = Lb.head->next;
			Lb.head->next = m->next;
			m->next = NULL;
			//���ڱ�β
			La.tail->next = m;
			La.tail = m;
		}
	}
	
	//2�����ã��ӵ�һ��Ԫ�ؿ�ʼ���ν����ժ�������ڱ�ͷ��
	node *r = La.head->next;//ָ��տ�ʼ�ĵ�һ��Ԫ�� 
	while(r->next != NULL)//���տ�ʼ�ĵ�һ��Ԫ��֮��Ϊ�գ���������ɣ�����ѭ�� 
	{
		//ժ����ʼʱ�̵�һ������ĵ�һ����� 
		node *s = r->next;
		r->next = s->next;
		//��ժ���Ľ����ڱ�ͷ��
		s->next = La.head->next;
		La.head->next = s; 
	}
	
	return OK;
}

Status ListTraverse(ListInfo L)
{
	node *p = L.head->next;
	while(p != NULL)
	{
		printf("%d ", p->data);
		p = p->next;
	}
	return OK;
}


int main()
{
	ListInfo La, Lb;
	InitList(La);
	InitList(Lb);
	SortAB(La, Lb);
	ListTraverse(La);
	return 0;
}
