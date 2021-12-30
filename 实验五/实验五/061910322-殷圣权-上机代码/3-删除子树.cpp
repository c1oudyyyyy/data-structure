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

Status DeleteChild(BiTree &T)//删除二叉树 
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


//思路：先序遍历找到x值的结点，然后删除以该结点为根的子树 
Status Delete_xChild(BiTree &T, char x)
{
	if(T != NULL)
	{
		if(T->data == x)
		{
			DeleteChild(T);//删除子树 
		}
		else
		{
			Delete_xChild(T->lchild, x);//先序遍历 
			Delete_xChild(T->rchild, x);
		}
	}
	return OK;
}

int main()
{
	BiTree T;
	PreCreateBiTree(T);
	printf("初始二叉树为：");
	ShowBiTree(T);
	printf("\n");
	char x = 'F';
	Delete_xChild(T, x);
	printf("删除以%c为值的结点为根的子树后：", x);
	ShowBiTree(T);
	printf("\n");
	return 0;
}

//测试数据：ABFG  H   CE  FJ  K  。 
