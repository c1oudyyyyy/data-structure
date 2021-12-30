#include <stdio.h>//ex0101_2.cpp
#include <stdlib.h>

#define ERROR 0
#define OK 1

typedef int Status;
typedef char ElemType;

typedef struct LNode
{
	ElemType data;
	struct LNode *next;
}LNode;

typedef struct ListInfo
{
	LNode *head;
	LNode *tail;
	LNode *pCurNode;
	int length;
}ListInfo;

Status InitList(ListInfo &L)
{
	L.head = (LNode *) malloc(sizeof(LNode));
	if(L.head == NULL) exit(ERROR);
	L.head->next = NULL;
	L.tail = L.head;
	L.pCurNode = L.head;
	L.length = 0;
	return OK;
}

Status CreateList(ListInfo &L)
{
	printf("������һ���ַ���");
	LNode *p;
	ElemType x;
	int i = 0;
	scanf("%c", &x);
	while(x != '\n')
	{
		i++;
		p = (LNode *) malloc(sizeof(LNode));
		p->data = x;
		p->next = NULL;
		L.tail->next = p;
		L.tail = p;
		scanf("%c", &x);
	}
	L.tail = p;
	L.length = i;
	return OK;
}

Status ListTraverse(ListInfo &L)
{
	if(L.head == NULL)
	{
		printf("�����ѱ�����\n");
		return ERROR;
	}
	if(L.head->next == NULL)
	{
		printf("����Ϊ��\n");
		return ERROR;
	} 
	LNode *p = L.head->next;
	while(p != NULL)
	{
		printf("%c", p->data);
		p = p->next;
	}
	printf("\n");
	return OK;
}

Status InsertElem(ListInfo &L, int i, ElemType e)
{
	if(i<1 || i>L.length+1)
	{
		printf("λ�ò�����\n");
		return ERROR;
	}
	LNode *p = L.head->next;
	LNode *s = (LNode *) malloc(sizeof(LNode));
	if(s == NULL) exit(ERROR);
	s->data = e;
	for(int j=1; j<i-1; j++)
		p = p->next;
	s->next = p->next;
	p->next = s;
	if(L.tail == p)
	{
		L.tail = s;
	}
	L.pCurNode = s;
	L.length += 1;
	return OK; 
}

Status DeleteElem(ListInfo &L, int i, ElemType &e)
{
	if(i<1 || i>L.length)
	{
		printf("λ�ò�����\n");
		return ERROR;
	}
	LNode *p, *q;
	p = L.head->next;
	for(int j=1; j<i-1; j++)
	{
		p = p->next;
	}
	e = p->next->data;
	q = p->next;
	p->next = q->next;
	if(L.tail == p)
	{
		L.tail = q;
	}
	L.length -= 1;
	return OK;
}

Status DestroyList(ListInfo &L)
{
	if(L.head->next != NULL)
	{
		LNode *p = L.head->next;
		L.head->next = p->next;
		free(p);
	}
	free(L.head);
	L.head = NULL;
	L.pCurNode = NULL;
	L.tail = NULL;
	L.length = 0;
	return OK;
}

Status ClearList(ListInfo &L)
{
	if(L.head->next != NULL)
	{
		LNode *p = L.head->next;
		L.head->next = p->next;
		free(p);
	}
	L.head->next = NULL;
	L.pCurNode = NULL;
	L.tail = NULL;
	L.length = 0;
	return OK;
}

bool ListEmpty(ListInfo L)
{
	if(L.head->next == NULL)
		return true;
	return false;
}

int ListLength(ListInfo L)
{
	return L.length;
}

Status GetElem(ListInfo L, int i, ElemType &e)
{
	if(i<1 || i>L.length)
	{
		printf("λ�ò�����\n");
		return ERROR;
	}
	LNode *p = L.head->next;
	for(int j=1; j<i; j++)
	{
		p = p->next;
	}
	e = p->data;
	L.pCurNode = p;
	return OK;
}

int LocateElem(ListInfo L, ElemType e)
{
	int i;
	LNode *p = L.head->next;
	for(i=1; i<=L.length; i++)
	{
		if(e == p->data)
		{
			L.pCurNode = p;
			return i;
		}
		p = p->next;
	}
	printf("û�и�Ԫ��\n");
	return ERROR;
}

Status PriorElem(ListInfo L, ElemType cur_e, ElemType &pre_e)
{
	int i;
	i = LocateElem(L, cur_e);
	if(i > 1)
	{
		GetElem(L, i-1, pre_e);
		return OK;
	}
	printf("����ʧ��\n");
	return ERROR;
}

Status NextElem(ListInfo L, ElemType cur_e, ElemType &next_e)
{
	int i;
	i = LocateElem(L, cur_e);
	if(i<L.length && i>0)
	{
		GetElem(L, i+1, next_e);
		return OK;
	}
	printf("����ʧ��\n");
	return ERROR;
}

Status SetElem(ListInfo &L, int i, ElemType &e)
{
	if(i<1 || i>L.length)
	{
		printf("λ�ò�����\n");
		return ERROR;
	}
	LNode *p = L.head->next;
	for(int j=1; j<i; j++)
	{
		p = p->next;
	}
	ElemType t;
	t = e;
	e = p->data;
	p->data = t;
	return OK;
}

int main()
{
	ListInfo L;
	InitList(L);
	CreateList(L);
	printf("��ʼ�ַ���");
	ListTraverse(L);
	int length;
	length = ListLength(L);
	printf("Ԫ�ظ�����%d\n", length);
	ElemType elem;
	GetElem(L, 2, elem);
	printf("�ڶ���Ԫ��Ϊ��%c\n", elem);
	int num;
	num = LocateElem(L, 'f');
	printf("Ԫ��f��λ��Ϊ��%d\n", num);
	ElemType pe, ne;
	PriorElem(L, 'f', pe);
	NextElem(L, 'f', ne);
	printf("f��ǰ��Ԫ��Ϊ��%c\n", pe);
	printf("f�ĺ��Ԫ��Ϊ��%c\n", ne);
	ElemType se = 'm';
	SetElem(L, 3, se);
	printf("������Ԫ����m�滻֮��");
	ListTraverse(L);
	printf("����һ��Ԫ�غ�"); 
	InsertElem(L, 2, 'b');
	ListTraverse(L);
	char e;
	printf("��ɾ��Ԫ�أ�");
	DeleteElem(L, 2, e);
	printf("%c\n", e);
	printf("ɾ����Ԫ�غ�");
	ListTraverse(L);
	int a = ListEmpty(L);
	printf("�˿��Ƿ��ǿձ�%d\n", a);
	ClearList(L);
	ListTraverse(L);
	int b = ListEmpty(L);
	printf("�˿��Ƿ��ǿձ�%d\n", b);
	DestroyList(L);
	ListTraverse(L);
	return 0;
}
