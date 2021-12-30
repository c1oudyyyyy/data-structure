#include <stdio.h>
#include <stdlib.h>

#define OK 1
#define ERROR 0

typedef int Status;

typedef struct node
{
	node *next;
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
	L.head = (node *) malloc(sizeof(node));
	if(L.head == NULL) exit(ERROR);
	L.head->next = NULL;
	L.tail = L.head;
	int n, i;
	printf("����Ԫ�ظ�����");
	scanf("%d", &n);
	L.length = n;
	printf("����Ԫ�أ�");
	for(i=0; i<L.length; i++)
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

Status ListTraverse(ListInfo L)
{
	node *p = L.head->next;
	while(p != NULL)
	{
		printf("%d ", p->data);
		p = p->next;
	}
	printf("\n");
	return OK;
}


//�ҵ�һ��b���c����Ԫ��֮�������ж�a���Ƿ�����ͬԪ�أ�������ɾ�� 
Status DeleteBC_A(ListInfo Lb, ListInfo Lc, ListInfo &La)
{
	int same;//��ɾԪ�� 
	node *a, *b, *c, *prea;
	prea = La.head;
	a = prea->next;
	b = Lb.head->next;
	c = Lc.head->next;
	while(b != NULL)//����b�� 
	{
		c = Lc.head->next;//����c��㣬ʹ��ÿ�δ�ͷ��ʼ 
		
		while(c != NULL)//����c�� 
		{
			if(b->data == c->data)//�ҵ�b���c����Ԫ�أ��ж�a���Ƿ��У�����ɾ�� 
			{
				
				same = b->data;
				printf("%d \n", same); //���b��c����ͬԪ�� 
				
				prea = La.head;//����a��ǰ���͵�ǰ���
				a = prea->next;
				
				while(a != NULL)//����a��Ѱ����Ҫɾ����Ԫ�� 
				{
					if(a->data > same)//��a���Ԫ���Ѿ�����same��������ѭ�� 
						break;
					if(a->data == same)
					{
						//ɾ��a��� 
						node *s = a;
						prea->next = a->next;
						free(s);
						//����a��ǰ���͵�ǰ���
						if(prea->next == La.tail)
						{
							La.tail = prea;
							a == NULL;
						}
						else
						{
							a = prea->next;
						}
						continue; 
					}
					prea = prea->next;
					a = prea->next;
				}
			}
			c = c->next;
			if(c == NULL)//����ѭ�� 
				break;	
			if(c->data > b->data)//��c�ĵ�ǰԪ�ش���b��ǰ������һ��bԪ�� 
				break;
		}
		b = b->next;	
	}
	return OK;
}

int main()
{
	ListInfo La, Lb, Lc;
	InitList(La);
	InitList(Lb);
	InitList(Lc);
	DeleteBC_A(Lb, Lc, La);
	ListTraverse(La);
	return 0;
}
