#include <stdio.h>
#include <stdlib.h>

#define OK 1
#define ERROR 0

#define SIZE 256

typedef int Status;

typedef struct BiTNode
{
	char data; 
	struct BiTNode *lchild, *rchild;
}BiTNode, *BiTree;

typedef struct node
{
	struct node *next;
	BiTNode *p;
	char tag;
}node;

typedef struct LinkStack
{
	node *head;
}LinkStack;

Status InitStack(LinkStack &S)
{
	S.head = (node *) malloc(sizeof(node));
	if(S.head == NULL) exit(ERROR);
	S.head->next = NULL;
	return OK;
}

Status Push(LinkStack &S, BiTNode *p)
{
	node *pp = (node *) malloc(sizeof(node));
	pp->p = p;
	pp->next = S.head->next;
	S.head->next = pp;
	return OK;
}

BiTNode *Pop(LinkStack &S)
{
	BiTNode *p = S.head->next->p;
	S.head->next = S.head->next->next;
	return p;
}

bool StackEmpty(LinkStack S)
{
	if(S.head->next == NULL)
		return true;
	return false;
}

Status PreCreateBiTree(BiTree &T)
{
	char ch;
	scanf("%c", &ch);
	if(ch == ' ')
		T = NULL;
	else
	{
		T = (BiTNode *) malloc(sizeof(BiTNode));
		if(T == NULL) exit(ERROR);
		T->data = ch;
		PreCreateBiTree(T->lchild);
		PreCreateBiTree(T->rchild);
	}
	return OK;
}

Status PreOrderTraverse1(BiTree T)//����������ݹ飩 
{
	if(T != NULL)
	{
		printf("%c ", T->data);
		PreOrderTraverse1(T->lchild);
		PreOrderTraverse1(T->rchild);
	}
	return OK;
}

Status PreOrderTraverse2(BiTree T)//����������ǵݹ飩
{
	LinkStack S;
	InitStack(S);
	BiTNode *p = T;
	while(p != NULL || !StackEmpty(S))
	{
		while(p != NULL) 
		{
			printf("%c ", p->data);//���ʸ���
			Push(S, p);
			p = p->lchild;//����������
		}
		if(!StackEmpty(S))
		{
			p = Pop(S);
			p = p->rchild;//���������� 
		}
	}
	return OK;
}

Status InOrderTraverse1(BiTree T)//����������ݹ飩
{
	if(T != NULL)
	{
		InOrderTraverse1(T->lchild);
		printf("%c ", T->data);
		InOrderTraverse1(T->rchild);
	}
	return OK;
}

Status InOrderTraverse2(BiTree T)//����������ǵݹ飩
{
	LinkStack S;
	InitStack(S);
	BiTNode *p = T;
	while(p != NULL || !StackEmpty(S))
	{
		while(p != NULL)//���������� 
		{
			Push(S, p);
			p = p->lchild;
		}
		if(!StackEmpty(S)) 
		{
			p = Pop(S);
			printf("%c ", p->data);//���ʸ���� 
			p = p->rchild;//����������
		}
	}
	return OK;
}

Status PostOrderTraverse1(BiTree T)//����������ݹ飩
{
	if(T != NULL)
	{
		PostOrderTraverse1(T->lchild);
		PostOrderTraverse1(T->rchild);
		printf("%c ", T->data);
	}
	return OK;
}

Status PostOrderTraverse2(BiTree T)//����������ǵݹ飩
{
	LinkStack S;
	InitStack(S);
	BiTNode *p = T;
	do
	{
		while(p != NULL)//���������� 
		{
			Push(S, p);
			S.head->next->tag = 'L';//��������� 
			p = p->lchild;
		}
		while(!StackEmpty(S) && S.head->next->tag == 'R')
		{
			p = Pop(S);
			printf("%c ", p->data);//���ʸ���� 
		}
		if(!StackEmpty(S))
		{
			S.head->next->tag = 'R';//��������� 
			p = S.head->next->p->rchild;//���������� 
		}
	}while(!StackEmpty(S));
}

Status LevelOrderTraverse(BiTree T)//��α��� 
{
	BiTNode *p;//����ָ�� 
	BiTree queue[SIZE];
	int front = 0, rear = 0;
	queue[rear] = T;//����� 
	rear = (rear+1)%SIZE;
	while(front != rear)
	{
		p = queue[front];
		front = (front+1+SIZE) % SIZE;
		printf("%c ", p->data);//���� 
		if(p->lchild != NULL)//�������ӣ���� 
		{
			queue[rear] = p->lchild;
			rear = (rear+1+SIZE) % SIZE;
		}
		if(p->rchild != NULL)//�����Һ��ӣ���� 
		{
			queue[rear] = p->rchild;
			rear = (rear+1+SIZE) % SIZE;
		}
	}
}

int main()
{
	BiTree T;
	printf("������Ԫ�أ�"); 
	PreCreateBiTree(T);
	printf("��������ݹ飺");
	PreOrderTraverse1(T);
	printf("\n");
	printf("��������ǵݹ飺");
	PreOrderTraverse2(T);
	printf("\n");
	printf("��������ݹ飺");
	InOrderTraverse1(T);
	printf("\n");
	printf("��������ǵݹ飺");
	InOrderTraverse2(T);
	printf("\n");
	printf("��������ݹ飺");
	PostOrderTraverse1(T);
	printf("\n");
	printf("��������ǵݹ飺");
	PostOrderTraverse2(T);
	printf("\n");
	printf("��α�����");
	LevelOrderTraverse(T);
	printf("\n");
	return 0;
}

//�������ݣ�ABDG  H   CE  FJ  K  �� 
