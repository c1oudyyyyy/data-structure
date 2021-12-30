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
思路：递归，若以左孩子进入递归，则层数+1；若以右兄弟进入，则层数不变。 
若根为空，返回空；若不为空且层数等于i，则输出该元素及所有右兄弟。
*/ 
void printf_i_level(Tree T, int i, int n)
{
	if(!T) return ;
	if(n == i) 
		printf("%c ", T->data);
	else
		printf_i_level(T->lchild, i, n+1);
	printf_i_level(T->rbrother, i, n);
	
}

int main()
{
	Tree T;
	create_Tree(T);
	int i;
	printf("i = ");
	scanf("%d", &i);
	printf("第%d层元素依次为：", i);
	printf_i_level(T, i, 1);
	return 0;
}

//测试数据：ABE F  C DGH     。 
