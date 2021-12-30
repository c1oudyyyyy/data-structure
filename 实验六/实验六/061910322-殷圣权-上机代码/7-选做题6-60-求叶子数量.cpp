#include <stdio.h>
#include <stdlib.h>

typedef struct Tnode
{
	struct Tnode *lchild;
	struct Tnode *rbrother;
	char data;
}Tnode, *Tree;

void create_Tree(Tree &T)//创建一棵以左孩子-右兄弟链表表示的树 
{
	char ch;
	scanf("%c", &ch);
	if(ch == ' ') T = NULL;
	else
	{
		T = (Tnode *) malloc(sizeof(Tnode));
		if(T == NULL) exit(0);
		T->data = ch;
		create_Tree(T->lchild);
		create_Tree(T->rbrother);
	}
}

/*
思路：没有左孩子的结点就是叶子。 
	如果根为空，返回0；
	如果没有左孩子且没有右兄弟，返回1；
	如果没有左孩子但是有右兄弟，返回右兄弟的叶子结点数+1； 
	否则返回左孩子和右兄弟的叶子结点数。 
*/ 
int leaf_num(Tree T)//求叶子数 
{
	if(!T) return 0;
	if(!T->lchild && !T->rbrother) return 1;
	else if(!T->lchild && T->rbrother) return ( leaf_num(T->rbrother) + 1 );
	return ( leaf_num(T->lchild) + leaf_num(T->rbrother) );
}

int main()
{
	Tree T;
	create_Tree(T);
	printf("叶子数量为：%d\n", leaf_num(T));
	return 0;
}

//测试数据：ABE F  C DGH     。ABE F  C DGH  I    。 
