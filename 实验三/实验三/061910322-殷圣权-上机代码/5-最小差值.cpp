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

typedef struct LinkList
{
	node *head;
	node *tail;
	int length;
}LinkList;

Status CreateList(LinkList &S, int n)//创建链表，将n个正整数存入链表 
{
	S.head = (node *) malloc(sizeof(node));
	if(S.head == NULL) exit(ERROR);
	S.head->next = NULL;
	S.tail = S.head;
	
	int i;
	S.length = n;
	for(i = 1; i <= S.length; i++)
	{
		node *p = (node *) malloc(sizeof(node));
		if(p == NULL) exit(ERROR);
		scanf("%d", &p->data);
		p->next = NULL;
		S.tail->next = p;
		S.tail = p;
	}
	return OK;
}

Status BubbleSort(LinkList &S)//冒泡排序 
{
	int i, j;
	node *p;
	for(i=1; i<=S.length-1; i++)//进行length-1次冒泡 
	{
		p = S.head->next;
		for(j=1; j<=S.length-i; j++)//前length-i个元素两两比较 
			if(p->data > p->next->data)//相邻元素比较，大的元素往后 
			{	
				node *k = S.head;
				while(k->next != p)//k指向p的前一个结点 	
					k = k->next;
				k->next = p->next;//把p结点摘除
				p->next = k->next->next;//再把p结点接在p的后继结点的后面 
				k->next->next = p; 
			}
			else
				p = p->next;//若不比相邻元素大，则看下一个结点 
	}
	return OK;
}

//思路：先排序，依次进行相邻两数相减，与下一次的差比较，若更小，则更新最小值 
Status MinDiffer(LinkList S)//计算最小的差值（绝对值） 
{
	BubbleSort(S);//冒泡排序 
	int min = 0;//最小差值 
	node *pre = S.head->next;//当前结点前驱 
	node *p = pre->next;
	min = abs(pre->data - p->data);//前两元素之差
	while(p != NULL)//遍历 
	{
		if(abs(pre->data-p->data) < min)
		{
			min = abs(pre->data-p->data);
		}
		pre = pre->next;
		p = pre->next;
	}
	printf("差值(绝对值)的最小值为：%d", min);
	return OK;
}

int main()
{
	LinkList L;
	int n;
	scanf("%d", &n);
	CreateList(L, n);
	MinDiffer(L);
	return 0;
}
