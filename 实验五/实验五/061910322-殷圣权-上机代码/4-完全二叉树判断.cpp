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

Status PreCreateBiTree(BiTree &T)//创建二叉树 
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

Status ShowBiTree(BiTree T)//先序遍历显示 
{
	if(T != NULL)
	{
		printf("%c", T->data);
		if(T->lchild!=NULL || T->rchild!=NULL)
		{
			printf("(");
			ShowBiTree(T->lchild);
			printf(",");
			ShowBiTree(T->rchild);
			printf(")");
		}
	}
	return OK; 
}

//思路：层次遍历二叉树，逐层入队，若队列中有空指针，则说明不是完全二叉树 
bool Complete_BiTree(BiTree T)
{
	if(T == NULL) return true;//空二叉树是完全二叉树 
	BiTNode *p = T;
	BiTree Q[SIZE];//建立队列 
	int front = 0, rear = 0;
	int flag = 0;//标志遍历的状态
	Q[rear] = p;//根入队 
	rear = (rear+1)%SIZE;
	while(front != rear)
	{
		p = Q[front];
		front = (front+1)%SIZE;
		if(p == NULL) flag = 1;//遇到空指针 
		else if(flag) return false;//非完全二叉树 
		else
		{
			Q[rear] = p->lchild;
			rear = (rear+1)%SIZE;
			Q[rear] = p->rchild;
			rear = (rear+1)%SIZE;
		}
	}
	return true; 
}

int main()
{
	BiTree T;
	PreCreateBiTree(T);
	printf("该二叉树为：");
	ShowBiTree(T);
	printf("\n");
	if(Complete_BiTree(T)) printf("该二叉树是完全二叉树。\n");
	else printf("该二叉树不是完全二叉树。\n"); 
	return 0;
}

//测试数据：A  。ABDH  I  EJ   CF  G  。ABFG  H   CE  FJ  K  。 
