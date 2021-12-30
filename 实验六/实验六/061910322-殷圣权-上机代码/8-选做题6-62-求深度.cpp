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

//˼·���ݹ���ǰ��������Ⱥ����ֵܵ���ȣ�ȡ�ϴ��ߡ� 
int Tree_depth(Tree T)//����� 
{
	if(!T) return 0;//��Ϊ����������0
	int depth_1, depth_2;//���嵱ǰ��������Ⱥ��ֵ���������� 
	depth_1 = Tree_depth(T->lchild) + 1;
	depth_2 = Tree_depth(T->rbrother);
	return ( depth_1 > depth_2 ? depth_1 : depth_2 );
}

int main()
{
	Tree T;
	create_Tree(T);
	printf("���������Ϊ��%d\n", Tree_depth(T));
	return 0;
}

//�������ݣ�ABE F  C DGH  I    �� 
