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

//������дӸ���Ҷ�ӵ�·��,����Ҷ�ӵ�����·��������������鼴�� 
char path[256];
char longest_path[256];
int longest_len = -1;
void root_leaf(bt t, char *path, int len)
{
	if(!t) return ;
	if(!t->lchild && !t->rchild)
	{
		path[len] = t->data;
		
		
		//�������Ҷ�ӵ�·��
		for(int i=0; i<=len; i++)
			cout << path[i];
		cout << '\t' << "����Ϊ��" << len;
		cout << endl;
		
		
		//�жϸ�·���Ƿ��ǵ�ǰ�·��,��������µ�ǰ�·�� 
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
	cout << "�·��Ϊ��";
	for(int i=0; i<=longest_len; i++)
		cout << longest_path[i];
	cout << endl;
	cout << "��·������Ϊ��" << longest_len << endl;
	return 0;
}

//�������ݣ�ABD G   CE  F  �� 
