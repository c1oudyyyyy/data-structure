#include <iostream>
#include <cstdlib>
using namespace std;

typedef struct tnode
{
	int data;
	struct tnode *firstchild, *nextbrother;	
}tnode, *t;

void create_t(t &root)
{
	char ch;
	cin.get(ch);
	if(ch == ' ') root = NULL;
	else
	{
		root = (tnode *) malloc(sizeof(tnode));
		if(!root) exit(0);
		root->data = ch;
		create_t(root->firstchild);
		create_t(root->nextbrother);
	}
}

int height(t root)
{
	if(!root) return 0;
	int cur_h = height(root->firstchild) + 1;
	int next_h = height(root->nextbrother);
	return cur_h > next_h ? cur_h : next_h;
}

int main()
{
	t root;
	create_t(root);
	cout << "¸ß¶È£º" << height(root) << endl;
}
