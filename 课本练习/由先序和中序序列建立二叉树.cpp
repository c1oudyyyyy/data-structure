#include <iostream>
#include <cstdlib>
using namespace std;

typedef struct btnode
{
	char data;
	struct btnode *lchild, *rchild;
}btnode, *bt;

//��������������й���������
bt build_tree(char *pre, char *in, int pre_left, int pre_right, int in_left, int in_right, int n)
{
	if(pre_left > pre_right)
		return NULL;
	// ǰ������еĵ�һ���ڵ���Ǹ��ڵ�
	int pre_root = pre_left;
	// ����������ж�λ���ڵ�
	int in_root, i;
	for(i=0; i<n; i++)
	{
		if(pre[pre_root] == in[i])
		{
			in_root = i;
			break;
		}
	}
	// �ȰѸ��ڵ㽨������
	btnode *t = (btnode *) malloc(sizeof(btnode));
	if(!t) exit(0);
	t->data = pre[pre_root];
	// �õ��������еĽڵ���Ŀ
	int size_left = in_root - in_left;
	// �ݹ�ع����������������ӵ����ڵ�
    // ��������С��� ��߽�+1 ��ʼ�� size_left����Ԫ�ؾͶ�Ӧ����������С��� ��߽� ��ʼ�� ���ڵ㶨λ-1����Ԫ��
    t->lchild = build_tree(pre, in, pre_left + 1, pre_left + size_left, in_left, in_root - 1, n);
    // �ݹ�ع����������������ӵ����ڵ�
    // ��������С��� ��߽�+1+�������ڵ���Ŀ ��ʼ�� �ұ߽硹��Ԫ�ؾͶ�Ӧ����������С��� ���ڵ㶨λ+1 �� �ұ߽硹��Ԫ��
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

//�������ݣ�ABDGCEFDGBAECF��
