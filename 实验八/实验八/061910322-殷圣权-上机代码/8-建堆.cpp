#include <iostream>
#include <cstdlib>
using namespace std;

#define SIZE 256

typedef struct sqlist
{
	int length;
	int size;
	int list[SIZE];
}sqlist;

void create_sqlist(sqlist &L)
{
	int n;//˳�����
	cout << "n = "; 
	cin >> n;
	for(int i=1; i<=n; i++)
		cin >> L.list[i];
	L.length = n;
	L.size = SIZE;
}

void create_heap(sqlist &L)//���ѣ��ӵ�2��Ԫ�ؿ�ʼ����������ɸѡ���ϴ��������ơ� 
{
	int i, j, k;
	for(i=2; i<=L.length; i++)
	{
		j = i;
		while(j != 1)
		{
			k = j / 2;//kΪj�ĸ���� 
			if(L.list[j] > L.list[k])
			{
				//���� 
				int t = L.list[j];
				L.list[j] = L.list[k];
				L.list[k] = t;
			}
			j = k;
		}
	}
	
	for(i=1; i<=L.length; i++)
		cout << L.list[i] << '\t';
	cout << endl;
}

void heap_adjust(sqlist &L, int low, int high)//lowλ�õ���������������С���ѵĶ��� 
{
	int t = L.list[low]; 
	int i = low;
	int j = 2 * i;
	while(j <= high)
	{
		if(j+1<=high && L.list[j]>L.list[j+1]) j++;//������������ѡ��С�� 
		if(t <= L.list[j]) break;//�Ѿ���С����
		//����ɸѡ 
		L.list[i] = L.list[j];
		i = j;
		j = 2 * i;
	}
	L.list[i] = t;//��������λ�� 
}

void heap_sort(sqlist &L)//������ 
{
	int i, t;
	create_heap(L); 
	for(i=L.length; i>1; i--)
	{
		//�Ѷ���¼�����һ����¼����
		t = L.list[1]; L.list[1] = L.list[i]; L.list[i] = t;
		heap_adjust(L, 1, i-1);//������¼����жѵ��� 
	}
	cout << "�������";
	for(int i=L.length; i>=1; i--)
		cout << L.list[i] << '\t';
	cout << endl;
}

int main()
{
	sqlist L;
	create_sqlist(L);
	heap_sort(L);
	return 0;
}

//�������ݣ�8 48 35 66 91 74 18 22 48��
