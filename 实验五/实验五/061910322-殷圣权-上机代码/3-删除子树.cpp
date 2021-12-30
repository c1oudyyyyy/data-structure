#include <stdio.h>
#include <stdlib.h>

#define OK 1
#define ERROR 0

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

Status DeleteChild(BiTree &T)//ɾ�������� 
{
	if(T != NULL)
	{
		DeleteChild(T->lchild);
		DeleteChild(T->rchild);
		free(T);
		T = NULL;
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


//˼·����������ҵ�xֵ�Ľ�㣬Ȼ��ɾ���Ըý��Ϊ�������� 
Status Delete_xChild(BiTree &T, char x)
{
	if(T != NULL)
	{
		if(T->data == x)
		{
			DeleteChild(T);//ɾ������ 
		}
		else
		{
			Delete_xChild(T->lchild, x);//������� 
			Delete_xChild(T->rchild, x);
		}
	}
	return OK;
}

int main()
{
	BiTree T;
	PreCreateBiTree(T);
	printf("��ʼ������Ϊ��");
	ShowBiTree(T);
	printf("\n");
	char x = 'F';
	Delete_xChild(T, x);
	printf("ɾ����%cΪֵ�Ľ��Ϊ����������", x);
	ShowBiTree(T);
	printf("\n");
	return 0;
}

//�������ݣ�ABFG  H   CE  FJ  K  �� 
