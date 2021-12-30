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

Status PreOrderTraverse1(BiTree T)//先序遍历（递归） 
{
	if(T != NULL)
	{
		printf("%c ", T->data);
		PreOrderTraverse1(T->lchild);
		PreOrderTraverse1(T->rchild);
	}
	return OK;
}

Status PreOrderTraverse2(BiTree T)//先序遍历（非递归）
{
	LinkStack S;
	InitStack(S);
	BiTNode *p = T;
	while(p != NULL || !StackEmpty(S))
	{
		while(p != NULL) 
		{
			printf("%c ", p->data);//访问根结
			Push(S, p);
			p = p->lchild;//遍历左子树
		}
		if(!StackEmpty(S))
		{
			p = Pop(S);
			p = p->rchild;//遍历右子树 
		}
	}
	return OK;
}

Status InOrderTraverse1(BiTree T)//中序遍历（递归）
{
	if(T != NULL)
	{
		InOrderTraverse1(T->lchild);
		printf("%c ", T->data);
		InOrderTraverse1(T->rchild);
	}
	return OK;
}

Status InOrderTraverse2(BiTree T)//中序遍历（非递归）
{
	LinkStack S;
	InitStack(S);
	BiTNode *p = T;
	while(p != NULL || !StackEmpty(S))
	{
		while(p != NULL)//遍历左子树 
		{
			Push(S, p);
			p = p->lchild;
		}
		if(!StackEmpty(S)) 
		{
			p = Pop(S);
			printf("%c ", p->data);//访问根结点 
			p = p->rchild;//遍历右子树
		}
	}
	return OK;
}

Status PostOrderTraverse1(BiTree T)//后序遍历（递归）
{
	if(T != NULL)
	{
		PostOrderTraverse1(T->lchild);
		PostOrderTraverse1(T->rchild);
		printf("%c ", T->data);
	}
	return OK;
}

Status PostOrderTraverse2(BiTree T)//后序遍历（非递归）
{
	LinkStack S;
	InitStack(S);
	BiTNode *p = T;
	do
	{
		while(p != NULL)//遍历左子树 
		{
			Push(S, p);
			S.head->next->tag = 'L';//标记左子树 
			p = p->lchild;
		}
		while(!StackEmpty(S) && S.head->next->tag == 'R')
		{
			p = Pop(S);
			printf("%c ", p->data);//访问根结点 
		}
		if(!StackEmpty(S))
		{
			S.head->next->tag = 'R';//标记右子树 
			p = S.head->next->p->rchild;//遍历右子树 
		}
	}while(!StackEmpty(S));
}

Status LevelOrderTraverse(BiTree T)//层次遍历 
{
	BiTNode *p;//遍历指针 
	BiTree queue[SIZE];
	int front = 0, rear = 0;
	queue[rear] = T;//根入队 
	rear = (rear+1)%SIZE;
	while(front != rear)
	{
		p = queue[front];
		front = (front+1+SIZE) % SIZE;
		printf("%c ", p->data);//访问 
		if(p->lchild != NULL)//若有左孩子，入队 
		{
			queue[rear] = p->lchild;
			rear = (rear+1+SIZE) % SIZE;
		}
		if(p->rchild != NULL)//若有右孩子，入队 
		{
			queue[rear] = p->rchild;
			rear = (rear+1+SIZE) % SIZE;
		}
	}
}

int main()
{
	BiTree T;
	printf("请输入元素："); 
	PreCreateBiTree(T);
	printf("先序遍历递归：");
	PreOrderTraverse1(T);
	printf("\n");
	printf("先序遍历非递归：");
	PreOrderTraverse2(T);
	printf("\n");
	printf("中序遍历递归：");
	InOrderTraverse1(T);
	printf("\n");
	printf("中序遍历非递归：");
	InOrderTraverse2(T);
	printf("\n");
	printf("后序遍历递归：");
	PostOrderTraverse1(T);
	printf("\n");
	printf("后序遍历非递归：");
	PostOrderTraverse2(T);
	printf("\n");
	printf("层次遍历：");
	LevelOrderTraverse(T);
	printf("\n");
	return 0;
}

//测试数据：ABDG  H   CE  FJ  K  。 
