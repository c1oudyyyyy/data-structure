#include <iostream>
#include <cstdlib>

using namespace std;

typedef struct btnode
{
	char data;
	struct btnode *lchild, *rchild;
}btnode, *bt;

void create_bt(bt &t)
{
	char ch;
	cin.get(ch);//ʹch�ܽ��տո� 
	if(ch == ' ') t = NULL;
	else
	{
		t = (btnode *) malloc(sizeof(btnode));
		if(!t) exit(0);
		t->data = ch;
		create_bt(t->lchild);
		create_bt(t->rchild); 
	}
}

int height(bt t)
{
	if(!t) return 0;
	int left = height(t->lchild) + 1;
	int right = height(t->rchild) + 1;
	return left > right ? left : right;
}

int main()
{
	bt t;
	create_bt(t);
	cout << "�߶ȣ�" << height(t) << endl;
	return 0;
}

//�������ݣ�ABD G   CE  F  ��
