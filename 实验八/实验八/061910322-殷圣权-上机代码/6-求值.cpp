#include <iostream>
#include <cstdlib>

using namespace std;

typedef struct bstnode
{
	int data;
	bstnode *left, *right;
}bstnode, *bst;

//插入
bstnode *Insert(bst t, int key)
{
	if(!t)
	{
		t = (bstnode *) malloc(sizeof(bstnode));
		if(!t) exit(0);
		t->data = key;
		t->left = NULL;
		t->right = NULL;
	}
	else if(t->data == key)
		;
	else if(t->data < key)
		t->right = Insert(t->right, key);
	else
		t->left = Insert(t->left, key);
	return t;
} 

//创建
bstnode *Create(int n)
{
	bstnode *t = NULL;
	int i, key;
	for(i=1; i<=n; i++)
	{
		cin >> key;
		t = Insert(t, key);
	}
	return t;
}

int last = 0;
void max_min(bst t, int x)//因为二叉排序树中序遍历后为升序序列，所以可以基于中序遍历求a和b 
{
	if(t->left) max_min(t->left, x);//递归判断左子树 
	if(last<x && t->data==x) 
		cout << "a = " << last << endl;//找到小于x的最大值 
	if(last==x && t->data>x)
		cout << "b = " << t->data << endl;//找到大于x的最小值 
	last = t->data;
	if(t->right) max_min(t->right, x);//递归判断右子树 
}

int main()
{
	int n;
	cout << "n = ";
	cin >> n;
	bst t = Create(n);
	int x;
	cout << "x = ";
	cin >> x;
	max_min(t, x);
	return 0;
}

//测试数据：n=6   10 6 12 3 9 7   x=9。书p131 
