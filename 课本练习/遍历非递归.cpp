#include <iostream>
#include <cstdlib>

using namespace std;

typedef struct btnode
{
	char data;
	struct btnode *lchild, *rchild;
}btnode, *bt;

typedef struct stacknode
{
	char tag;
	btnode *ptr;
}stacknode, *st;

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

//先序遍历非递归 
void pre_unrecursive(bt t)
{
	btnode *p = t;
	bt stack[256];
	int top = -1;
	while(top >= 0 || p)
	{
		while(p)
		{
			cout << p->data;
			stack[++top] = p;
			p = p->lchild;
		}
		if(top >= 0)
		{
			p = stack[top--];
			p = p->rchild;
		}
	}
	cout << endl;
}

//中序遍历非递归
void in_unrecursive(bt t)
{
	bt stack[256];
	int top = -1;
	btnode *p = t;
	while(p || top >=  0)
	{
		while(p)
		{
			stack[++top] = p;
			p = p->lchild;
		}
		if(top >= 0)
		{
			p = stack[top--];
			cout << p->data;
			p = p->rchild;
		}
	}
	cout << endl;
}

void post_unrecursive(bt t)
{
	st stack[256];
	int top = -1;
	stacknode *x;
	btnode *p = t;
	do
	{
		while(p)//遍历左子树 
		{
			x->ptr = p;
			x->tag = 'L';
			stack[++top] = x;
			p = p->lchild;
		}
		while(top >= 0 && stack[top]->tag == 'R')
		{
			x = stack[top--];
			p = x->ptr;
			cout << p->data;
		}
		if(top >= 0)
		{
			stack[top]->tag = 'R';
			p = stack[top]->ptr->rchild;
		}
	}while(top >= 0);
	cout << endl; 
}

void level_traverse(bt t)
{
	bt queue[256];
	int front = 0, rear = 0;
	btnode *p;
	queue[rear] = t;
	rear = (rear + 1) % 256;
	while(front != rear)
	{
		p = queue[front];
		front = (front + 1) % 256;
		cout << p->data;
		if(p->lchild)
		{
			queue[rear] = p->lchild;
			rear = (rear + 1) % 256;
		}
		if(p->rchild)
		{
			queue[rear] = p->rchild;
			rear = (rear + 1) % 256;
		}
	}
}

int main()
{
	bt t;
	create_bt(t);
	pre_unrecursive(t);
	in_unrecursive(t);
	post_unrecursive(t);
	level_traverse(t);
	return 0;
}

//测试数据：ABD G   CE  F  。 
