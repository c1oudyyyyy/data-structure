#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
	struct node *next;
	int freq;//跳过次数 
}node;

typedef struct list
{
	node *head;
	node *tail;
}list;

void create_list(list &L)//创建循环链表 
{
	L.head = (node *) malloc(sizeof(node));
	if(L.head == NULL) exit(0);
	L.head->next = NULL;
	L.tail = L.head;
	for(int i=1; i<=4; i++)//甲乙丙丁对应1234
	{
		node *p = (node *) malloc(sizeof(node));
		if(p == NULL) exit(0);
		p->freq = 0;//跳过次数开始均为0 
		p->next = NULL;
		L.tail->next = p;
		L.tail = p;
	}
	L.tail->next = L.head;//循环链表 
}
 
void number_off(list &L, int n) 
{
	int i = 1;//报数的数字
	int num = 1;//报数的个数 
	node *p = L.head->next;
	do//循环遍历链表
	{
		if( i%7 == 0 || i%10 == 7 || (i/10)%10 == 7 )//七的倍数或数字有七，跳过
		{
			p->freq++;
			i++;
			p = p->next;
			if(p == L.head) p = p->next;//跳过表头
			continue;
		}
		p = p->next;
		if(p == L.head) p = p->next;//跳过表头 
		i++;
		num++;//报数个数+1 
	}while(num <= n);
}

int main()
{
	list L;
	create_list(L);
	node *p = L.head->next;
	int n;
	scanf("%d", &n);
	number_off(L, n);
	while(p != L.head)
	{
		printf("%d\n", p->freq);
		p = p->next;
	}
	return 0;
}

/*
样例1输入：
20
样例1输出：
2
1
1
0

样例2输入：
66
样例2输出：
7
5
11
5
*/ 

