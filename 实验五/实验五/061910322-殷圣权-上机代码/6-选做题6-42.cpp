#include <stdio.h>
#include <stdlib.h>

typedef struct biTnode
{
	char data;
	struct biTnode *lchild;
	struct biTnode *rchild;
}biTnode, *biTree;

void create_biTree(biTree &T)//���������� 
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

void leaf_num(biTree T, int &num)//Ҷ�ӽ����Ŀ 
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
	printf("����������������У�");
	create_biTree(T);
	leaf_num(T, num);
	printf("�ö�����Ҷ�ӽ����ĿΪ��%d\n", num);
	return 0;
}

//�������ݣ�ABDG  H   CE  FJ  K  ��
