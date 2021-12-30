#include <stdio.h>//ex0105.cpp
#include <stdlib.h>

#define ERROR 0
#define OK 1

typedef int Status;

typedef struct LNode
{
	int jump;
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

Status InputElem(ListInfo &L)
{
	LNode *p;
	int x;
	int i = 0;
	scanf("%d", &x);
	while(x != 0)
	{
		i++;
		p = (LNode *) malloc(sizeof(LNode));
		p->jump = x;
		p->next = NULL;
		L.tail->next = p;
		L.tail = p;
		scanf("%d", &x);
	}
	L.tail = p;
	L.length = i;
	return OK;
}

Status Score(ListInfo L, int &s)
{
	LNode *p = L.head->next;
	int pre = 0;
	while(p != NULL)
	{
		if(p->jump == 1)	
		{
			s += 1;
			pre = 0;
		}
		else if(p->jump == 2)
		{
			if(pre == 0)
			{
				s += 2;
				pre += 2;
			}
			else if(pre%2 == 0)
			{
				s += (pre+=2);
			}							
		}					
		p = p->next;
	}
	return OK;
}

int main()
{
	int s = 0;
	ListInfo L;
	InitList(L);
	printf("游戏开始，请您输入跳跃情况：\n");
	InputElem(L);
	Score(L, s);
	printf("本次得分为：%d\n", s);
	return 0;
}
