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

//思路：递归求当前子树的深度和右兄弟的深度，取较大者。 
int Tree_depth(Tree T)//求深度 
{
	if(!T) return 0;//若为空树，返回0
	int depth_1, depth_2;//定义当前子树的深度和兄弟子树的深度 
	depth_1 = Tree_depth(T->lchild) + 1;
	depth_2 = Tree_depth(T->rbrother);
	return ( depth_1 > depth_2 ? depth_1 : depth_2 );
}

int main()
{
	Tree T;
	create_Tree(T);
	printf("该树的深度为：%d\n", Tree_depth(T));
	return 0;
}

//测试数据：ABE F  C DGH  I    。 
