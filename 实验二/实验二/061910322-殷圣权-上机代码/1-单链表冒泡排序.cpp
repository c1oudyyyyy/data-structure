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

Status BubbleSort(ListInfo &L)
{
	int i, j;
	LNode *p;
	for(i=1; i<=L.length-1; i++)//����length-1��ð�� 
	{
		p = L.head->next;
		for(j=1; j<=L.length-i; j++)//ǰlength-i��Ԫ�������Ƚ� 
		{
			if(p->data > p->next->data)//����Ԫ�رȽϣ����Ԫ������ 
			{
				
				LNode *k = L.head;
				while(k->next != p)//kָ��p��ǰһ����� 	
					k = k->next;
				
				k->next = p->next;//��p���ժ��
			
				p->next = k->next->next;//�ٰ�p������p�ĺ�̽��ĺ��� 
				k->next->next = p; 
			}
			else
				p = p->next;//����������Ԫ�ش�����һ����� 
		}
	}
	return OK;
}

int main()
{
	ListInfo L;
	InitList(L);
	InputElem(L);
	BubbleSort(L);
	printf("ð������֮��\n"); 
	ListTraverse(L);
	return 0;
}
