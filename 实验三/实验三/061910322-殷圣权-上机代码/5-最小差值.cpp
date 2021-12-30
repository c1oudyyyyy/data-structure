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

typedef struct LinkList
{
	node *head;
	node *tail;
	int length;
}LinkList;

Status CreateList(LinkList &S, int n)//����������n���������������� 
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

Status BubbleSort(LinkList &S)//ð������ 
{
	int i, j;
	node *p;
	for(i=1; i<=S.length-1; i++)//����length-1��ð�� 
	{
		p = S.head->next;
		for(j=1; j<=S.length-i; j++)//ǰlength-i��Ԫ�������Ƚ� 
			if(p->data > p->next->data)//����Ԫ�رȽϣ����Ԫ������ 
			{	
				node *k = S.head;
				while(k->next != p)//kָ��p��ǰһ����� 	
					k = k->next;
				k->next = p->next;//��p���ժ��
				p->next = k->next->next;//�ٰ�p������p�ĺ�̽��ĺ��� 
				k->next->next = p; 
			}
			else
				p = p->next;//����������Ԫ�ش�����һ����� 
	}
	return OK;
}

//˼·�����������ν��������������������һ�εĲ�Ƚϣ�����С���������Сֵ 
Status MinDiffer(LinkList S)//������С�Ĳ�ֵ������ֵ�� 
{
	BubbleSort(S);//ð������ 
	int min = 0;//��С��ֵ 
	node *pre = S.head->next;//��ǰ���ǰ�� 
	node *p = pre->next;
	min = abs(pre->data - p->data);//ǰ��Ԫ��֮��
	while(p != NULL)//���� 
	{
		if(abs(pre->data-p->data) < min)
		{
			min = abs(pre->data-p->data);
		}
		pre = pre->next;
		p = pre->next;
	}
	printf("��ֵ(����ֵ)����СֵΪ��%d", min);
	return OK;
}

int main()
{
	LinkList L;
	int n;
	scanf("%d", &n);
	CreateList(L, n);
	MinDiffer(L);
	return 0;
}
