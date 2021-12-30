#include <iostream>
#include <cstdlib> 
using namespace std;

#define N 5

typedef struct
{
	unsigned int weight;
	unsigned int parent, lchild, rchild;
}hufTnode, *hufTree;

void create_hufTree(int n, hufTree &T)
{
	if(n <= 1) return ;//ֻ��һ����㣬ֱ�ӷ���
	T = (hufTnode *) malloc(2 * n * sizeof(hufTnode));//0�ŵ�Ԫ����
	if(!T) exit(0);
	int i, j;
	//��ʼ����������
	for(i=1; i<2*n; i++)
	{
		if(i < n+1)
			cin >> T[i].weight;
		T[i].parent = 0;
		T[i].lchild = 0;
		T[i].rchild = 0;
	}
	//������������
	for(i=n+1; i<2*n; i++)
	{
		//������T�У���1�ŵ�i-1����ѡȡ����parentΪ0����Ȩֵweight��С���������s1��s2
		int s1 = 0, s2 = 0, weight_min = 101;
		for(j=1; j<=i-1; j++)
		{
			if(T[j].weight < weight_min && T[j].parent == 0)
			{
				weight_min = T[j].weight;
				s1 = j;
			}
		}
		weight_min = 101;
		for(j=1; j<=i-1; j++)
		{
			if(T[j].weight < weight_min && T[j].parent == 0 && j!=s1)
			{
				weight_min = T[j].weight;
				s2 = j;
			}
		}
		T[s1].parent = T[s2].parent = i;
		T[i].lchild = s1;
		T[i].rchild = s2;
		T[i].weight = T[s1].weight + T[s2].weight;
	}
}

void print_hufTree(hufTree T)
{
	cout << "num  " << "weight  " << "parent  " << "lchild  " << "rchild  " << endl;
	for(int i=1; i<2*N; i++)
	{
		cout << i << '\t' << T[i].weight << '\t' << T[i].parent << '\t' << T[i].lchild << '\t' << T[i].rchild << endl;
	}
}

int main()
{
	hufTree T;
	create_hufTree(N, T);
	print_hufTree(T);
	return 0;
}

//�������ݣ�10 15 12 3 4�� 
