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
˼·��û�����ӵĽ�����Ҷ�ӡ� 
	�����Ϊ�գ�����0��
	���û��������û�����ֵܣ�����1��
	���û�����ӵ��������ֵܣ��������ֵܵ�Ҷ�ӽ����+1�� 
	���򷵻����Ӻ����ֵܵ�Ҷ�ӽ������ 
*/ 
int leaf_num(Tree T)//��Ҷ���� 
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
	printf("Ҷ������Ϊ��%d\n", leaf_num(T));
	return 0;
}

//�������ݣ�ABE F  C DGH     ��ABE F  C DGH  I    �� 
