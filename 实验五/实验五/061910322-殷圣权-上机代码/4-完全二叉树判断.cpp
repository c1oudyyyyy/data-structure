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

Status PreCreateBiTree(BiTree &T)//���������� 
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

Status ShowBiTree(BiTree T)//���������ʾ 
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

//˼·����α����������������ӣ����������п�ָ�룬��˵��������ȫ������ 
bool Complete_BiTree(BiTree T)
{
	if(T == NULL) return true;//�ն���������ȫ������ 
	BiTNode *p = T;
	BiTree Q[SIZE];//�������� 
	int front = 0, rear = 0;
	int flag = 0;//��־������״̬
	Q[rear] = p;//����� 
	rear = (rear+1)%SIZE;
	while(front != rear)
	{
		p = Q[front];
		front = (front+1)%SIZE;
		if(p == NULL) flag = 1;//������ָ�� 
		else if(flag) return false;//����ȫ������ 
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
	printf("�ö�����Ϊ��");
	ShowBiTree(T);
	printf("\n");
	if(Complete_BiTree(T)) printf("�ö���������ȫ��������\n");
	else printf("�ö�����������ȫ��������\n"); 
	return 0;
}

//�������ݣ�A  ��ABDH  I  EJ   CF  G  ��ABFG  H   CE  FJ  K  �� 
