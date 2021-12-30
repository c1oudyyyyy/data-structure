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
	int n;//顺序表长度
	cout << "n = "; 
	cin >> n;
	for(int i=1; i<=n; i++)
		cin >> L.list[i];
	L.length = n;
	L.size = SIZE;
} 

void bubble_sort(sqlist L)//简单交换排序（冒泡） 
{
	int i, j, t;
	for(i=1; i<=L.length-1; i++)//进行n-1冒泡 
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
	cout << "冒泡排序：";
	for(i=1; i<=L.length; i++)
		cout << L.list[i] << '\t';
	cout << endl;
}

void select_sort(sqlist &L)//简单选择排序 
{
	int i, j ,t;
	for(i=1; i<=L.length-1; i++)//n-1趟选择最小值 
	{
		int min = L.list[i];//假设起始记录为最小值 
		int k = i;
		for(j=i+1; j<=L.length; j++)//寻找最小值 
		{
			if(L.list[j] < min)
			{
				min = L.list[j];
				k = j;
			}
		}
		t = L.list[i]; L.list[i] = L.list[k]; L.list[k] = t;//与最小值交换 
	}
	cout << "选择排序：";
	for(i=1; i<=L.length; i++)
		cout << L.list[i] << '\t';
	cout << endl;
} 

void merge(sqlist &L, int low, int mid, int high)//归并两个子序列 
{
	sqlist T;//辅助表 
	int i = low, j = mid+1, k = 0;
	while(i<=mid && j<=high)//将L中的元素有序并入T 
	{
		if(L.list[i] <= L.list[j])
			T.list[k++] = L.list[i++];
		else
			T.list[k++] = L.list[j++];
	}
	while(i <= mid) T.list[k++] = L.list[i++];//将剩余元素复制到T 
	while(j <= high) T.list[k++] = L.list[j++];
	for(k=0,i=low; i<=high; k++,i++)//合并的结果送回原空间 
		L.list[i] = T.list[k];
}

void Msort(sqlist &L, int len)//将两两长为len的子序列归并
{
	int i = 1;
	while(i+2*len <= L.length)
	{
		merge(L, i, i+len-1, i+2*len-1);//归并两个长为len的子序列
		i = i+2*len;//下一组待归并的子序列的第一个元素的位置 
	}
	if(i+len <= L.length)
		merge(L, i, i+len-1, L.length);//归并最后两个子序列 
} 

void merge_sort(sqlist &L)//2路归并排序
{
	int len;
	for(len=1; len<=L.length; len=2*len)//归并序列的长度依次为1、2、4、8等 
		Msort(L, len);
	cout << "归并排序：";
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

//测试数据：10 48 35 66 91 74 18 22 48 57 03。 
