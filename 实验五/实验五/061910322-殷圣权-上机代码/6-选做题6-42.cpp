#include <stdio.h>
#include <stdlib.h>

typedef struct biTnode
{
	char data;
	struct biTnode *lchild;
	struct biTnode *rchild;
}biTnode, *biTree;

void create_biTree(biTree &T)//创建二叉树 
{
	char ch;
	scanf("%c", &ch);
	if(ch == ' ') T = NULL;
	else
	{
		T = (biTnode *) malloc(sizeof(biTnode));
		if(!T) exit(0);
		T->data = ch;
		create_biTree(T->lchild);
		create_biTree(T->rchild);
	}
}

void leaf_num(biTree T, int &num)//叶子结点数目 
{
	if(T)
	{
		if(!T->lchild && !T->rchild) num++;
		leaf_num(T->lchild, num);
		leaf_num(T->rchild, num);
	}
}

int main()
{
	int num = 0;
	biTree T;
	printf("先序输入二叉树序列：");
	create_biTree(T);
	leaf_num(T, num);
	printf("该二叉树叶子结点数目为：%d\n", num);
	return 0;
}

//测试数据：ABDG  H   CE  FJ  K  。
