#include <iostream>
#include <cstdlib>

using namespace std;

typedef struct bstnode
{
	int data;
	bstnode *left, *right;
}bstnode, *bst;

//查找
bstnode *Search(bst t, int key)
{
	if(!t) return NULL;
	else if(t->data == key) return t;
	else if(t->data < key) return Search(t->right, key);
	else return Search(t->left, key);
}
 
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
 
//删除
bstnode *Delete(bst t, int key)
{
	bstnode *p = t, *pa = NULL;//p指向待删结点，pa指向p的父结点
	bstnode *q, *qa;//q指向p的左分支的最大结点，qa指向q的父结点
	//1、查找key所在结点（待删结点）
	while(p)
	{
		if(p->data == key) break;//找到
		else if(p->data < key)
		{
			pa = p;
			p = p->right;
		}
		else
		{
			pa = p;
			p = p->left;
		}
	}
	if(!p) return t;//查找不成功
	//2、删除结点p
	
	//情况一：p为叶子结点
	if(!p->left && !p->right)
	{
		if(pa)//若待删结点非根结点 
		{
			if(pa->data < key)//若待删结点是pa的右孩子 
				pa->right = NULL;
			else//若是左孩子 
				pa->left = NULL;
			free(p);
			return t;
		}
		else//待删结点是根结点 
		{
			free(p);
			return NULL;
		}
	}
	//情况二：待删结点只有右孩子
	else if(!p->left && p->right)
	{
		if(pa)//若非根结点
		{
			if(pa->data < key)
			{
				pa->right = p->right;
			}
			else
			{
				pa->left = p->right;
			}
			free(p);
			return t;
		}
		else
		{
			t = p->right;
			free(p);
			return t;
		}
	}
	//情况三：待删结点只有左孩子
	else if(p->left && !p->right)
	{
		if(pa)
		{
			if(pa->data < key)
				pa->right = p->left;
			else
				pa->left = p->left;
			free(p);
			return t;
		}
		else
		{
			t = p->left;
			free(p);
			return t;
		}
	 }
	 //情况四：待删结点既有左孩子又有右孩子
	 else
	 {
	 	//寻找待删结点左子树中的最大值
		qa = p;
		q = p->left;
		while(q->right)
		{
			qa = q;
			q = q->right;
		}
		p->data = q->data;//将左子树最大值覆盖待删结点，然后删除左子树最大值结点
		//删除最大值结点
		if(!q->left && !q->right)//若为叶子结点 
		{
			if(qa->data < q->data)
				qa->right = NULL;
			else
				qa->left = NULL;
			free(q);
		}
		else//若只有左孩子 
		{
			if(qa->data < q->data)
				qa->right = q->left;
			else
				qa->left = q->left;
			free(q);
		}
	 } 	return t;
} 

void traverse(bst t)
{
	if(!t) return ;
	else
	{
		cout << t->data << '\t';
		traverse(t->left);
		traverse(t->right);
	}
}

int main()
{
	int n;
	cin >> n;
	bst t = Create(n);
	traverse(t);
	cout << endl << "输入删除结点的值：";
	int a, b;
	cin >> a;
	Delete(t, a);
	cout << "删除结点后：" << endl;  
	traverse(t);
	cout << endl << "输入增加结点的值：";
	cin >> b;
	Insert(t, b);
	cout << "增加结点后：" << endl;
	traverse(t);
	return 0;
}

//测试数据：6 10 6 3 9 7 12。书p134 
