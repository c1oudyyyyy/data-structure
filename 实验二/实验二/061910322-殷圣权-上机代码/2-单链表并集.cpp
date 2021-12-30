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

//依次将b表中的元素与a表中的比较，将此结点的元素插入a表中合适的位置
Status ListUnion(ListInfo &La, ListInfo Lb)
{
	LNode *prea, *a, *preb, *b;//定义当前结点和前驱结点 
	prea = La.head;
	a = prea->next;
	preb = Lb.head;
	b = preb->next;
	
	//删除a表中重复的元素
	while(a != NULL)
	{
		if(prea->data == a->data)//若相邻元素相等，则删除当前结点 
		{	 
			LNode *o = a;//删除当前结点
			prea->next = a->next;
			free(o);
			
			if(prea->next == NULL)//修正前驱和当前结点 
				a = NULL;
			else
				a = prea->next;
			
			continue;//看下一组相邻元素
		}
		prea = prea->next;//看下一组相邻元素
		a = prea->next; 
	}
	
	prea = La.head;//修正前驱和当前结点 
	a = prea->next;
	
	while(b != NULL)//遍历b表 
	{
		while(a != NULL)//遍历a表，在a表寻找合适位置插入b表当前结点
		{
			if(b->data > a->data)//位置找到，插入到a结点前，并跳出循环看下一个b表结点 
			{
				LNode *s = (LNode *) malloc(sizeof(LNode));//创建新结点 
				s->data = b->data;
				
	 			s->next = a;//插入新结点 
	 			prea->next = s;
	 			
	 			prea = La.head;//修正前驱和当前结点 
				a = prea->next; 
	 			break;
			}
			
			if(b->data == a->data)//若相等，则跳过 
				break;
				
			prea = prea->next;
			a = prea->next; 
		}
		//位置没找到，说明当前结点的元素小于a表所有元素，插入到a表表尾
		if(b->data < La.tail->data)
		{
			LNode *w = (LNode *) malloc(sizeof(LNode));
			w->data = b->data;
			w->next = NULL;
			La.tail->next = w;
			La.tail = w;
		}
		
		preb = preb->next;//b表下一个结点 
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
	printf("合并之后：\n");
	ListTraverse(La);
	return 0;
}
