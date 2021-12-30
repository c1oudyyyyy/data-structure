#include <stdio.h>
#include <stdlib.h>

#define OK 1
#define ERROR 0

typedef int Status;

typedef struct LNode//����ÿ��ʱ��εĽ�� 
{
	struct LNode *next;
	int startTime;//��ʼʱ�� 
	int endTime;//����ʱ�� 
}LNode;

typedef struct ListInfo
{
	LNode *head;
	LNode *tail;
	int length;
}ListInfo;

Status CreateList(ListInfo &L, int n)//β�巨 
{
	L.head = (LNode *) malloc(sizeof(LNode));
	if(L.head == NULL) exit(ERROR);
	L.head->next = NULL;
	L.tail = L.head;
	L.length = 0;
	LNode *p;
	for(int i=1; i<=n; i++)//ÿ����㴢��һ��ʱ��ε�ʼĩʱ�� 
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
		//���һ 
		while(w->endTime <= h->startTime) 
		{
			w = w->next;
			
			if(w == NULL) break;
		}
		//Ϊ�˾����������ѭ������ֹ���������ѭ�� 
		if(w == NULL)
		{
			if(h == NULL) break;
			
			else
			{
				h = h->next;
				continue;
			}
		}
		
		//����� 
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
		//Ϊ�˾����������ѭ������ֹ���������ѭ��
		if(w == NULL)
		{
			if(h == NULL) break;
			
			else
			{
				h = h->next;
				continue;
			}
		}
		
		//����� 
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
				if(h != NULL)//��W��Ԫ�ر�����ʱH��û������ 
				{
					w = LW.tail;//��H����ʣ��Ԫ�ض�����W�����Ԫ�ضԱ� 
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
