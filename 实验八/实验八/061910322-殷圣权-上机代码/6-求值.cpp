#include <iostream>
#include <cstdlib>

using namespace std;

typedef struct bstnode
{
	int data;
	bstnode *left, *right;
}bstnode, *bst;

//����
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

//����
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
void max_min(bst t, int x)//��Ϊ�������������������Ϊ�������У����Կ��Ի������������a��b 
{
	if(t->left) max_min(t->left, x);//�ݹ��ж������� 
	if(last<x && t->data==x) 
		cout << "a = " << last << endl;//�ҵ�С��x�����ֵ 
	if(last==x && t->data>x)
		cout << "b = " << t->data << endl;//�ҵ�����x����Сֵ 
	last = t->data;
	if(t->right) max_min(t->right, x);//�ݹ��ж������� 
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

//�������ݣ�n=6   10 6 12 3 9 7   x=9����p131 
