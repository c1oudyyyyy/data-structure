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
	printf("请输入元素个数：", &n);
	scanf("%d", &n);
	printf("请输入元素：\n");
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
	for(i=1; i<=L.length-1; i++)//进行length-1次冒泡 
	{
		p = L.head->next;
		for(j=1; j<=L.length-i; j++)//前length-i个元素两两比较 
		{
			if(p->data > p->next->data)//相邻元素比较，大的元素往后 
			{
				
				LNode *k = L.head;
				while(k->next != p)//k指向p的前一个结点 	
					k = k->next;
				
				k->next = p->next;//把p结点摘除
			
				p->next = k->next->next;//再把p结点接在p的后继结点的后面 
				k->next->next = p; 
			}
			else
				p = p->next;//若不比相邻元素大，则看下一个结点 
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
	printf("冒泡排序之后：\n"); 
	ListTraverse(L);
	return 0;
}
