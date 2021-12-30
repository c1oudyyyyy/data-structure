#include <stdio.h>
#include <stdlib.h>

typedef struct Tnode
{
	struct Tnode *lchild;
	struct Tnode *rbrother;
	char data;
}Tnode, *Tree;

void create_Tree(Tree &T)//����һ��������-���ֵ������ʾ���� 
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
˼·���ݹ飬�������ӽ���ݹ飬�����+1���������ֵܽ��룬��������䡣 
����Ϊ�գ����ؿգ�����Ϊ���Ҳ�������i���������Ԫ�ؼ��������ֵܡ�
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
	printf("��%d��Ԫ������Ϊ��", i);
	printf_i_level(T, i, 1);
	return 0;
}

//�������ݣ�ABE F  C DGH     �� 
