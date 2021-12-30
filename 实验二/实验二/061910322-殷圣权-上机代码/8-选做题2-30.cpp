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
	printf("输入元素个数：");
	scanf("%d", &n);
	L.length = n;
	printf("输入元素：");
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


//找到一个b表和c表共有元素之后立即判断a表是否有相同元素，若有则删除 
Status DeleteBC_A(ListInfo Lb, ListInfo Lc, ListInfo &La)
{
	int same;//待删元素 
	node *a, *b, *c, *prea;
	prea = La.head;
	a = prea->next;
	b = Lb.head->next;
	c = Lc.head->next;
	while(b != NULL)//遍历b表 
	{
		c = Lc.head->next;//修正c结点，使其每次从头开始 
		
		while(c != NULL)//遍历c表 
		{
			if(b->data == c->data)//找到b表和c表共有元素，判断a表是否有，有则删除 
			{
				
				same = b->data;
				printf("%d \n", same); //输出b和c表相同元素 
				
				prea = La.head;//修正a表前驱和当前结点
				a = prea->next;
				
				while(a != NULL)//遍历a表，寻找需要删除的元素 
				{
					if(a->data > same)//若a表的元素已经大于same，则跳出循环 
						break;
					if(a->data == same)
					{
						//删除a结点 
						node *s = a;
						prea->next = a->next;
						free(s);
						//修正a表前驱和当前结点
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
			if(c == NULL)//结束循环 
				break;	
			if(c->data > b->data)//若c的当前元素大于b当前，则看下一个b元素 
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
