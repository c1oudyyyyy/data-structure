#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
	struct node *next;
	int freq;//�������� 
}node;

typedef struct list
{
	node *head;
	node *tail;
}list;

void create_list(list &L)//����ѭ������ 
{
	L.head = (node *) malloc(sizeof(node));
	if(L.head == NULL) exit(0);
	L.head->next = NULL;
	L.tail = L.head;
	for(int i=1; i<=4; i++)//���ұ�����Ӧ1234
	{
		node *p = (node *) malloc(sizeof(node));
		if(p == NULL) exit(0);
		p->freq = 0;//����������ʼ��Ϊ0 
		p->next = NULL;
		L.tail->next = p;
		L.tail = p;
	}
	L.tail->next = L.head;//ѭ������ 
}
 
void number_off(list &L, int n) 
{
	int i = 1;//����������
	int num = 1;//�����ĸ��� 
	node *p = L.head->next;
	do//ѭ����������
	{
		if( i%7 == 0 || i%10 == 7 || (i/10)%10 == 7 )//�ߵı������������ߣ�����
		{
			p->freq++;
			i++;
			p = p->next;
			if(p == L.head) p = p->next;//������ͷ
			continue;
		}
		p = p->next;
		if(p == L.head) p = p->next;//������ͷ 
		i++;
		num++;//��������+1 
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
����1���룺
20
����1�����
2
1
1
0

����2���룺
66
����2�����
7
5
11
5
*/ 

