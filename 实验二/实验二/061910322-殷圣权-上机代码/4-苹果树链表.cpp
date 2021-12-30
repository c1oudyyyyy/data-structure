#include <stdio.h>
#include <stdlib.h>

#define OK 1
#define ERROR 0

typedef int Status;

typedef struct LNode
{
	struct LNode *next;
	int operate; 
}LNode;

typedef struct ListInfo
{
	LNode *head;
	LNode *tail;
	int operateNumber;
	int AppleNumber; //苹果数量 
	int AppleOffTreeNum;//是否掉落苹果 
}ListInfo;//一棵苹果树的数据 

Status CreateList(ListInfo &L)
{
	L.head = (LNode *) malloc(sizeof(LNode));
	if(L.head == NULL) exit(ERROR);
	L.head->next = NULL;
	L.tail = L.head;
	int m;
	scanf("%d", &m);
	for(int i=1; i<=m; i++)
	{
		LNode *p = (LNode *) malloc(sizeof(LNode));
		if(p == NULL) exit(ERROR);
		scanf("%d", &p->operate);
		p->next = NULL;
		L.tail->next = p;
		L.tail = p;
	}
	L.AppleNumber = 0;
	L.AppleOffTreeNum = 0;
	L.operateNumber = m;
	return OK;
}

Status Operation(ListInfo &L)//对每一棵苹果树的操作
{
	LNode *p = L.head->next;
	while(p != NULL)//遍历每一个结点 
	{
		if(p->operate > 0)//若大于0 
		{
			if(p == L.head->next)//若是第一个结点 
				L.AppleNumber += p->operate;//直接赋值给苹果数量 
			else
			{
				if(p->operate < L.AppleNumber)// 若不是第一个结点，且比苹果数量少 
				{
					//说明掉落了苹果，掉落棵树赋值为1，并把苹果数量赋值为当前数量 
					L.AppleOffTreeNum = 1;
					L.AppleNumber = p->operate;
				}
			}
		}
		
		else//若小于0，则苹果数量减少 
			L.AppleNumber += p->operate;
		 
		p = p->next;//下一个结点 
	}
	return OK;
}

int main()
{
	int N, T = 0, D = 0, E = 0, i;
	scanf("%d", &N);
	ListInfo L[N];//定义N个链表 
	for(i=1; i<=N; i++)
	{
		CreateList(L[i]);
		Operation(L[i]);
		T += L[i].AppleNumber; //每一棵苹果树的苹果数量的累加 
		D += L[i].AppleOffTreeNum;//掉落苹果的苹果树的棵数累加 
	}
	
	//计算连续三棵树掉落的组数
	//1、只包含有头或尾的连续的三棵树  
	for(i=2; i<=N-1; i++)
		if(L[i-1].AppleOffTreeNum + L[i].AppleOffTreeNum + L[i+1].AppleOffTreeNum == 3)
			E += 1;
	//2、包含头和尾连续的三棵树 
	if(L[N].AppleOffTreeNum + L[1].AppleOffTreeNum + L[2].AppleOffTreeNum == 3)
		E += 1;
	if(L[N-1].AppleOffTreeNum + L[N].AppleOffTreeNum + L[1].AppleOffTreeNum == 3)
		E += 1;
		
	printf("%d %d %d", T, D, E);
	
	return 0;
}
