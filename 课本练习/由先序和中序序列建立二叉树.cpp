#include <iostream>
#include <cstdlib>
using namespace std;

typedef struct btnode
{
	char data;
	struct btnode *lchild, *rchild;
}btnode, *bt;

//由先序和中序序列构建二叉树
bt build_tree(char *pre, char *in, int pre_left, int pre_right, int in_left, int in_right, int n)
{
	if(pre_left > pre_right)
		return NULL;
	// 前序遍历中的第一个节点就是根节点
	int pre_root = pre_left;
	// 在中序遍历中定位根节点
	int in_root, i;
	for(i=0; i<n; i++)
	{
		if(pre[pre_root] == in[i])
		{
			in_root = i;
			break;
		}
	}
	// 先把根节点建立出来
	btnode *t = (btnode *) malloc(sizeof(btnode));
	if(!t) exit(0);
	t->data = pre[pre_root];
	// 得到左子树中的节点数目
	int size_left = in_root - in_left;
	// 递归地构造左子树，并连接到根节点
    // 先序遍历中「从 左边界+1 开始的 size_left」个元素就对应了中序遍历中「从 左边界 开始到 根节点定位-1」的元素
    t->lchild = build_tree(pre, in, pre_left + 1, pre_left + size_left, in_left, in_root - 1, n);
    // 递归地构造右子树，并连接到根节点
    // 先序遍历中「从 左边界+1+左子树节点数目 开始到 右边界」的元素就对应了中序遍历中「从 根节点定位+1 到 右边界」的元素
    t->rchild = build_tree(pre, in, pre_left + size_left + 1, pre_right, in_root + 1, in_right, n);
    return t;
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
	int n;
	cin >> n;
	int i;
	char pre[256], in[256];
	for(i=0; i<n; i++)
		cin >> pre[i];
	for(i=0; i<n; i++)
		cin >> in[i];
	bt t = build_tree(pre, in, 0, n-1, 0, n-1, n);
	level_traverse(t);
	return 0;
}

//测试数据：ABDGCEFDGBAECF。
