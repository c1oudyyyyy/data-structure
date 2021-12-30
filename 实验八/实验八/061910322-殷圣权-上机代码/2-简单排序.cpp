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

void bubble_sort(sqlist L)//�򵥽�������ð�ݣ� 
{
	int i, j, t;
	for(i=1; i<=L.length-1; i++)//����n-1ð�� 
	{
		for(j=1; j<=L.length-i; j++)
		{
			if(L.list[j] > L.list[j+1])
			{
				t = L.list[j];
				L.list[j] = L.list[j+1];
				L.list[j+1] = t;
			}
		}
	}
	cout << "ð������";
	for(i=1; i<=L.length; i++)
		cout << L.list[i] << '\t';
	cout << endl;
}

void select_sort(sqlist &L)//��ѡ������ 
{
	int i, j ,t;
	for(i=1; i<=L.length-1; i++)//n-1��ѡ����Сֵ 
	{
		int min = L.list[i];//������ʼ��¼Ϊ��Сֵ 
		int k = i;
		for(j=i+1; j<=L.length; j++)//Ѱ����Сֵ 
		{
			if(L.list[j] < min)
			{
				min = L.list[j];
				k = j;
			}
		}
		t = L.list[i]; L.list[i] = L.list[k]; L.list[k] = t;//����Сֵ���� 
	}
	cout << "ѡ������";
	for(i=1; i<=L.length; i++)
		cout << L.list[i] << '\t';
	cout << endl;
} 

void merge(sqlist &L, int low, int mid, int high)//�鲢���������� 
{
	sqlist T;//������ 
	int i = low, j = mid+1, k = 0;
	while(i<=mid && j<=high)//��L�е�Ԫ��������T 
	{
		if(L.list[i] <= L.list[j])
			T.list[k++] = L.list[i++];
		else
			T.list[k++] = L.list[j++];
	}
	while(i <= mid) T.list[k++] = L.list[i++];//��ʣ��Ԫ�ظ��Ƶ�T 
	while(j <= high) T.list[k++] = L.list[j++];
	for(k=0,i=low; i<=high; k++,i++)//�ϲ��Ľ���ͻ�ԭ�ռ� 
		L.list[i] = T.list[k];
}

void Msort(sqlist &L, int len)//��������Ϊlen�������й鲢
{
	int i = 1;
	while(i+2*len <= L.length)
	{
		merge(L, i, i+len-1, i+2*len-1);//�鲢������Ϊlen��������
		i = i+2*len;//��һ����鲢�������еĵ�һ��Ԫ�ص�λ�� 
	}
	if(i+len <= L.length)
		merge(L, i, i+len-1, L.length);//�鲢������������� 
} 

void merge_sort(sqlist &L)//2·�鲢����
{
	int len;
	for(len=1; len<=L.length; len=2*len)//�鲢���еĳ�������Ϊ1��2��4��8�� 
		Msort(L, len);
	cout << "�鲢����";
	for(int i=1; i<=L.length; i++)
		cout << L.list[i] << '\t';
	cout << endl; 
}


int main()
{
	sqlist L;
	create_sqlist(L);
	bubble_sort(L);
	select_sort(L);
	merge_sort(L);
	return 0;
}

//�������ݣ�10 48 35 66 91 74 18 22 48 57 03�� 
