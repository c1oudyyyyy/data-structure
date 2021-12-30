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

//输出所有从根到叶子的路径,若求叶子到根的路径，逆序输出数组即可 
char path[256];
char longest_path[256];
int longest_len = -1;
void root_leaf(bt t, char *path, int len)
{
	if(!t) return ;
	if(!t->lchild && !t->rchild)
	{
		path[len] = t->data;
		
		
		//输出根到叶子的路径
		for(int i=0; i<=len; i++)
			cout << path[i];
		cout << '\t' << "长度为：" << len;
		cout << endl;
		
		
		//判断该路径是否是当前最长路径,若是则更新当前最长路径 
		if(len > longest_len)
		{
			longest_len = len;
			for(int j=0; j<=len; j++)
				longest_path[j] = path[j];
		}
	}
	else
	{
		path[len] = t->data;
		
		root_leaf(t->lchild, path, len+1);
		root_leaf(t->rchild, path, len+1);
	}
}

int main()
{
	bt t;
	create_bt(t);
	root_leaf(t, path, 0);
	cout << "最长路径为：";
	for(int i=0; i<=longest_len; i++)
		cout << longest_path[i];
	cout << endl;
	cout << "该路径长度为：" << longest_len << endl;
	return 0;
}

//测试数据：ABD G   CE  F  。 
