#include <stdio.h>
#include <stdlib.h>

#define OK 1
#define ERROR 0

typedef int Status;

typedef struct LNode//储存每个时间段的结点 
{
	struct LNode *next;
	int startTime;//开始时间 
	int endTime;//结束时间 
}LNode;

typedef struct ListInfo
{
	LNode *head;
	LNode *tail;
	int length;
}ListInfo;

Status CreateList(ListInfo &L, int n)//尾插法 
{
	L.head = (LNode *) malloc(sizeof(LNode));
	if(L.head == NULL) exit(ERROR);
	L.head->next = NULL;
	L.tail = L.head;
	L.length = 0;
	LNode *p;
	for(int i=1; i<=n; i++)//每个结点储存一个时间段的始末时间 
	{
		p = (LNode *) malloc(sizeof(LNode));
		if(p == NULL) exit(ERROR);
		scanf("%d %d", &p->startTime, &p->endTime);
		p->next = NULL;
		L.tail->next = p;
		L.tail = p;
	}
	L.length = n;
	return OK;
}

Status  talkTime(ListInfo LH, ListInfo LW)
{
	int t = 0;
	
	LNode *h = LH.head->next;
	LNode *w = LW.head->next;
	
	while(w != NULL || h != NULL)
	{
		//情况一 
		while(w->endTime <= h->startTime) 
		{
			w = w->next;
			
			if(w == NULL) break;
		}
		//为了尽快结束本次循环，防止进行下面的循环 
		if(w == NULL)
		{
			if(h == NULL) break;
			
			else
			{
				h = h->next;
				continue;
			}
		}
		
		//情况二 
		while(w->endTime > h->startTime && w->endTime <= h->endTime)
		{
			if(w->startTime < h->startTime)
			{
				t += (w->endTime - h->startTime);
				w = w->next;
				if(w == NULL) break;
				continue;
			}
			
			else if(w->startTime >= h->startTime)
			{
				t += (w->endTime - w->startTime);
				w = w->next;
				if(w == NULL) break;
				continue;
			}
			
		}
		//为了尽快结束本次循环，防止进行下面的循环
		if(w == NULL)
		{
			if(h == NULL) break;
			
			else
			{
				h = h->next;
				continue;
			}
		}
		
		//情况三 
		while(w->endTime > h->endTime)
		{
			
			if(w->startTime <= h->startTime)
			{
				t += (h->endTime - h->startTime);
				w = w->next;
				if(w == NULL) break;
				continue;
			}
			
			if(w->startTime > h->startTime && w->startTime < h->endTime)
			{
				t += (h->endTime - w->startTime);
				w = w->next;
				if(w == NULL) break;
				continue;
			}
			
			if(w->startTime >= h->endTime) break; 
		}
		
		
		if(w == NULL)
		{
			if(h == NULL) break;
			
			else
			{
				h = h->next;
				if(h != NULL)//当W表元素遍历完时H表还没遍历完 
				{
					w = LW.tail;//把H表中剩余元素都来和W表最后元素对比 
				}
				continue;
			}
		}
		
		h = h->next;
	}
	
	printf("%d", t);
	
	return OK;
}

int main()
{
	ListInfo LH, LW;
	int n;
	scanf("%d", &n); 
	CreateList(LH, n);
	CreateList(LW, n);
	talkTime(LH, LW);
	return 0;
}
