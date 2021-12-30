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
	cin.get(ch);//使ch能接收空格 
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

//最近的公共祖先
btnode *LCA(bt t, char p, char q)
{
	if(!t || t->data == p || t->data == q)
		return t;
		
	btnode *left = LCA(t->lchild, p, q);
	btnode *right = LCA(t->rchild, p, q);
	
	if(left && right)
		return t;
		
	return left? left : right;
}

int main()
{
	bt t;
	create_bt(t); 
	btnode *ans = LCA(t, 'D', 'E');
	cout << ans->data;
	return 0;
}
