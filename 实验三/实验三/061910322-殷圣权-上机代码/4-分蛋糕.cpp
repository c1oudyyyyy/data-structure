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

typedef struct LinkStack//��n�鵰�������ʽջ 
{
	node *head;
	node *tail;
	int length;
}LinkStack;

Status CreateStack(LinkStack &S, int n)//����ջ����ÿ�鵰������� 
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

Status Pop(LinkStack &S, int &e)//��ջ�������С�ĵ���������e���� 
{
	if(S.head != NULL && S.head != S.tail)//ջ�����ҷǿ�
	{
		node *p = S.head->next;
		e = p->data;
		S.head->next = p->next;
		if(p == S.tail) S.tail = S.head;
		free(p);
		S.length -= 1;
		return OK;
	}
	printf("�����ѷ���\n");
	return ERROR;
}

//˼·�����ε�ջ��ֱ���������ڵ���k����������+1 
Status FriendCount(LinkStack S, int k)//����ֵ�������������� 
{
	int m = 0;//ÿ�����ѷֵõ��������
	int e = 0;//�����С�ĵ�������
	int num = 0;//�ֵ���������ѵ����� 
	while(Pop(S, e))//ÿ�ε��������С�ĵ������� 
	{
		m += e;
		if(S.length == 0)//ʣ�����һ�鵰��ʱ����ѭ������������+1 
		{
			num++;
			break;
		}
		if(m >= k)//���������ۼƴ��ڵ���k��������һ��ѭ�� 
		{
			num++;
			m = 0;//��������
			continue; 
		}
	}
	printf("�ֵ����������������%d", num);
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
