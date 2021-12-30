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
	PreCreateBiTree(T);
	LevelOrderTraverse(T);
	return 0;
}

//�������ݣ�ABDG  H   CE  FJ  K  ��
