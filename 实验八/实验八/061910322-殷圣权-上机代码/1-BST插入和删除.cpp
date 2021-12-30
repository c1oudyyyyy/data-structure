#include <iostream>
#include <cstdlib>

using namespace std;

typedef struct bstnode
{
	int data;
	bstnode *left, *right;
}bstnode, *bst;

//����
bstnode *Search(bst t, int key)
{
	if(!t) return NULL;
	else if(t->data == key) return t;
	else if(t->data < key) return Search(t->right, key);
	else return Search(t->left, key);
}
 
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
 
//ɾ��
bstnode *Delete(bst t, int key)
{
	bstnode *p = t, *pa = NULL;//pָ���ɾ��㣬paָ��p�ĸ����
	bstnode *q, *qa;//qָ��p�����֧������㣬qaָ��q�ĸ����
	//1������key���ڽ�㣨��ɾ��㣩
	while(p)
	{
		if(p->data == key) break;//�ҵ�
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
	if(!p) return t;//���Ҳ��ɹ�
	//2��ɾ�����p
	
	//���һ��pΪҶ�ӽ��
	if(!p->left && !p->right)
	{
		if(pa)//����ɾ���Ǹ���� 
		{
			if(pa->data < key)//����ɾ�����pa���Һ��� 
				pa->right = NULL;
			else//�������� 
				pa->left = NULL;
			free(p);
			return t;
		}
		else//��ɾ����Ǹ���� 
		{
			free(p);
			return NULL;
		}
	}
	//���������ɾ���ֻ���Һ���
	else if(!p->left && p->right)
	{
		if(pa)//���Ǹ����
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
	//���������ɾ���ֻ������
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
	 //����ģ���ɾ���������������Һ���
	 else
	 {
	 	//Ѱ�Ҵ�ɾ����������е����ֵ
		qa = p;
		q = p->left;
		while(q->right)
		{
			qa = q;
			q = q->right;
		}
		p->data = q->data;//�����������ֵ���Ǵ�ɾ��㣬Ȼ��ɾ�����������ֵ���
		//ɾ�����ֵ���
		if(!q->left && !q->right)//��ΪҶ�ӽ�� 
		{
			if(qa->data < q->data)
				qa->right = NULL;
			else
				qa->left = NULL;
			free(q);
		}
		else//��ֻ������ 
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
	cout << endl << "����ɾ������ֵ��";
	int a, b;
	cin >> a;
	Delete(t, a);
	cout << "ɾ������" << endl;  
	traverse(t);
	cout << endl << "�������ӽ���ֵ��";
	cin >> b;
	Insert(t, b);
	cout << "���ӽ���" << endl;
	traverse(t);
	return 0;
}

//�������ݣ�6 10 6 3 9 7 12����p134 
