#include <stdio.h>
#include <stdlib.h>

#define OK 1
#define ERROR 0

typedef int Status;

typedef struct LNode
{
	struct LNode *next;
	int data;
}LNode;

typedef struct ListInfo
{
	LNode *head;
	LNode *tail;
	int length;
}ListInfo;

Status InitList(ListInfo &L)
{
	L.head = (LNode *) malloc(sizeof(LNode));
	if(L.head == NULL) exit(ERROR);
	L.head->next = NULL;
	L.tail = L.head;
	L.length = 0;
	return OK;
}

Status InputElem(ListInfo &L)
{
	int n;
	LNode *p;
	printf("������Ԫ�ظ�����", &n);
	scanf("%d", &n);
	printf("������Ԫ�أ�\n");
	for(int i=1; i<=n; i++)
	{
		p = (LNode *) malloc(sizeof(LNode));
		if(p == NULL) exit(ERROR);
		scanf("%d", &p->data);
		p->next = NULL;
		L.tail->next = p;
		L.tail = p;
	}
	L.length = n;
	return OK;
}

Status ListTraverse(ListInfo L)
{
	LNode *p = L.head->next;
	while(p != NULL)
	{
		printf("%d ", p->data);
		p = p->next;
	}
	printf("\n");
	return OK;
}

//���ν�b���е�Ԫ����a���еıȽϣ����˽���Ԫ�ز���a���к��ʵ�λ��
Status ListUnion(ListInfo &La, ListInfo Lb)
{
	LNode *prea, *a, *preb, *b;//���嵱ǰ����ǰ����� 
	prea = La.head;
	a = prea->next;
	preb = Lb.head;
	b = preb->next;
	
	//ɾ��a�����ظ���Ԫ��
	while(a != NULL)
	{
		if(prea->data == a->data)//������Ԫ����ȣ���ɾ����ǰ��� 
		{	 
			LNode *o = a;//ɾ����ǰ���
			prea->next = a->next;
			free(o);
			
			if(prea->next == NULL)//����ǰ���͵�ǰ��� 
				a = NULL;
			else
				a = prea->next;
			
			continue;//����һ������Ԫ��
		}
		prea = prea->next;//����һ������Ԫ��
		a = prea->next; 
	}
	
	prea = La.head;//����ǰ���͵�ǰ��� 
	a = prea->next;
	
	while(b != NULL)//����b�� 
	{
		while(a != NULL)//����a����a��Ѱ�Һ���λ�ò���b��ǰ���
		{
			if(b->data > a->data)//λ���ҵ������뵽a���ǰ��������ѭ������һ��b���� 
			{
				LNode *s = (LNode *) malloc(sizeof(LNode));//�����½�� 
				s->data = b->data;
				
	 			s->next = a;//�����½�� 
	 			prea->next = s;
	 			
	 			prea = La.head;//����ǰ���͵�ǰ��� 
				a = prea->next; 
	 			break;
			}
			
			if(b->data == a->data)//����ȣ������� 
				break;
				
			prea = prea->next;
			a = prea->next; 
		}
		//λ��û�ҵ���˵����ǰ����Ԫ��С��a������Ԫ�أ����뵽a���β
		if(b->data < La.tail->data)
		{
			LNode *w = (LNode *) malloc(sizeof(LNode));
			w->data = b->data;
			w->next = NULL;
			La.tail->next = w;
			La.tail = w;
		}
		
		preb = preb->next;//b����һ����� 
		b = preb->next;
	}
	return OK;
}

int main()
{
	ListInfo La, Lb;
	InitList(La);
	InitList(Lb);
	InputElem(La);
	InputElem(Lb);
	ListUnion(La, Lb);
	printf("�ϲ�֮��\n");
	ListTraverse(La);
	return 0;
}
