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

int partition(sqlist &L, int low, int high)//һ��low��high֮��Ŀ���
{
	int pivot = L.list[low];//�Ե�һ����¼Ϊ���� 
	while(low < high)//��low������highʱ����ѭ�� 
	{
		//�ӱ�����˽������м�ɨ��
		while(low<high && L.list[high]>=pivot) high--;
		L.list[low] = L.list[high];	
		while(low<high && L.list[low]<=pivot) low++;
		L.list[high] = L.list[low]; 
	}
	L.list[low] = pivot;
	return low;//��������λ�� 
}

void Qsort(sqlist &L, int low, int high)//low��high֮���ȫ������ 
{
	if(low < high)//��������ֻ��һ��Ԫ��ʱ�����ݹ� 
	{
		int pivot = partition(L, low, high);//һ�˿��ź������λ��
		//�ֱ���������ߵ������н��п��ţ����õݹ�  
		Qsort(L, low, pivot-1);
		Qsort(L, pivot+1, high); 
	}
}

void quick_sort(sqlist &L)//���� 
{
	Qsort(L, 1, L.length);
	cout << "���������";
	for(int i=1; i<=L.length; i++)
		cout << L.list[i] << '\t';
	cout << endl;
}

int main()
{
	sqlist L;
	create_sqlist(L);
	quick_sort(L);
	return 0;
}

//�������ݣ�10 48 35 66 91 74 18 22 48 57 03��
