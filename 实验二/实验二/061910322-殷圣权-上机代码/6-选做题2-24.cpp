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

//每次将b表第一个元素依次与a表元素比较，将b表结点摘除并插入到a表中适当位置，最后逆置a表 
Status SortAB(ListInfo &La, ListInfo Lb)
{
	//1、合并 
	node *prev = La.head;//a表中的当前结点前驱 
	node *p = prev->next;//a表中的当前结点 
	while(Lb.head->next != NULL)//当b表不为空 
	{
		while(p != NULL)//遍历表a，寻找合适位置插入b表第一个元素 
		{
			if(p->data >= Lb.head->next->data)
			{
				//摘除b表头后的结点
				node *s = Lb.head->next;
				Lb.head->next = s->next;
				//将摘除的结点接在a表当前结点之前
				s->next = p;
				prev->next = s;
				//修正前驱和当前结点 
				prev = La.head;
				p = prev->next;
				//看下一个b表结点 
				break;
			}
			prev = prev->next;
			p = prev->next;
			
		}
		//a表中的元素均较小，则接在a表尾
		if(Lb.head->next->data >= La.tail->data)
		{
			//摘除 
			node *m = Lb.head->next;
			Lb.head->next = m->next;
			m->next = NULL;
			//接在表尾
			La.tail->next = m;
			La.tail = m;
		}
	}
	
	//2、逆置：从第一个元素开始依次将结点摘除并接在表头后
	node *r = La.head->next;//指向刚开始的第一个元素 
	while(r->next != NULL)//若刚开始的第一个元素之后为空，则逆置完成，结束循环 
	{
		//摘除起始时刻第一个结点后的第一个结点 
		node *s = r->next;
		r->next = s->next;
		//将摘除的结点接在表头后
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
