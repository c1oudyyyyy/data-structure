#include <stdio.h>//ex0104.cpp
#include <iostream>
#include <stdlib.h>
#define ERROR 0
#define OK 1

typedef int Status;

int red, yellow, green;

typedef struct LNode
{
	struct LNode *next;
	int k;
	int t;
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

Status InputElem(ListInfo &L, int n)
{
	LNode *p;
	int x, y, i;
	scanf("%d %d", &x, &y);
	for(i=0; i<n; i++)
	{
		p = (LNode *) malloc(sizeof(LNode));
		p->k = x;
		p->t = y;
		p->next = NULL;
		L.tail->next = p;
		L.tail = p;
		if(i < n-1)
			scanf("%d %d", &x, &y);
	}
	L.tail = p;
	L.length = n;
	return OK;
}

Status Time(ListInfo L, int &time)
{
	LNode *p = L.head->next;
	while(p != NULL)
	{
		int i, s;
		s = red+yellow+green;
		i = time/s;
		if(p->k == 0)
			time += p->t;
		else if(p->k == 1)
		{								
			if(p->t > time-i*s )
				time += (p->t - time+i*s);
			else if(time-i*s>p->t && time-i*s<p->t+green)
				time += 0;
			else if(time-i*s>p->t+green && time-i*s<p->t+green+yellow)
				time += (yellow-(time-i*s-p->t-green));		
		}	else if(time-i*s>p->t+green+yellow && time-i*s<p->t+green+yellow+red)
				time += (red-(time-i*s-p->t-yellow-green));
		else if(p->k == 2)
		{
			
			if(p->t > time-i*s)
			
				
				time += (p->t - time+i*s);
			else if( (time-i*s > p->t) && (time-i*s < p->t+red) )
			
			
				time += (red-time+i*s+p->t);
			else if( (time-i*s > p->t+red) && (time-i*s < p->t+red+green) )
			
				
				time += 0;
			else if(time-i*s>p->t+red+green && time-i*s<p->t+red+green+yellow)
				time += (yellow-(time-i*s-p->t-red-green));				
		}
		else if(p->k == 3)
		{
			if(p->t > time-i*s)
				time += 0;
			else if(time-i*s>p->t && time-i*s<p->t+yellow)
				time += (yellow-(time-i*s-p->t));
			else if(time-i*s>p->t+yellow && time-i*s<p->t+yellow+red)
				time += (red-(time-i*s-p->t-yellow));
			else if(time-i*s>p->t+yellow+red && time-i*s<p->t+yellow+red+green)
				time += 0;
		}
		p = p->next;
	}
	return OK;
}

Status ListTraverse(ListInfo &L)
{
	if(L.head == NULL)
	{
		printf("链表已被销毁\n");
		return ERROR;
	}
	if(L.head->next == NULL)
	{
		printf("链表为空\n");
		return ERROR;
	} 
	LNode *p = L.head->next;
	while(p != NULL)
	{
		printf("%d %d\n", p->k, p->t);
		p = p->next;
	}
	printf("\n");
	return OK;
}

int main()
{
	ListInfo L;
	InitList(L);
	printf("设置红绿灯时间：\n");
	scanf("%d %d %d", &red, &yellow, &green);
	int n;
	printf("设置路段和红绿灯总数：\n");
	scanf("%d", &n);
	printf("设置每段路所需时间以及出发时刻各红绿灯情况\n");
	InputElem(L, n);
	int t = 0;
	Time(L, t);
	printf("回家时间为：%d\n", t);
	return 0;
}



