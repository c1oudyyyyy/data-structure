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

typedef struct LinkStack//将n块蛋糕存入链式栈 
{
	node *head;
	node *tail;
	int length;
}LinkStack;

Status CreateStack(LinkStack &S, int n)//创建栈储存每块蛋糕的重量 
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

Status Pop(LinkStack &S, int &e)//弹栈，编号最小的蛋糕重量用e返回 
{
	if(S.head != NULL && S.head != S.tail)//栈存在且非空
	{
		node *p = S.head->next;
		e = p->data;
		S.head->next = p->next;
		if(p == S.tail) S.tail = S.head;
		free(p);
		S.length -= 1;
		return OK;
	}
	printf("蛋糕已分完\n");
	return ERROR;
}

//思路：依次弹栈，直至重量大于等于k，朋友数量+1 
Status FriendCount(LinkStack S, int k)//计算分到蛋糕的朋友数量 
{
	int m = 0;//每个朋友分得蛋糕的重量
	int e = 0;//编号最小的蛋糕重量
	int num = 0;//分到蛋糕的朋友的数量 
	while(Pop(S, e))//每次弹出编号最小的蛋糕重量 
	{
		m += e;
		if(S.length == 0)//剩下最后一块蛋糕时结束循环，朋友数量+1 
		{
			num++;
			break;
		}
		if(m >= k)//蛋糕重量累计大于等于k，进行下一次循环 
		{
			num++;
			m = 0;//重量清零
			continue; 
		}
	}
	printf("分到蛋糕的朋友数量：%d", num);
	return OK;
}

int main()
{
	int n, k;
	scanf("%d %d", &n, &k);
	LinkStack S;
	CreateStack(S, n); 
	FriendCount(S, k);
	return 0;
}
