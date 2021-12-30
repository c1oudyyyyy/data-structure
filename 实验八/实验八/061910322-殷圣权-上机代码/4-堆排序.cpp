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
	for(i=L.length/2; i>=1; i--)//�Ȱ����ݽ��ɶ� 
		heap_adjust(L, i, L.length);
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

//�������ݣ�10 48 35 66 91 74 18 22 48 57 03��
