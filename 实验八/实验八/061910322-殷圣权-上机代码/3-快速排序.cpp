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

int partition(sqlist &L, int low, int high)//一趟low和high之间的快排
{
	int pivot = L.list[low];//以第一个记录为枢轴 
	while(low < high)//当low不等于high时进行循环 
	{
		//从表的两端交替向中间扫描
		while(low<high && L.list[high]>=pivot) high--;
		L.list[low] = L.list[high];	
		while(low<high && L.list[low]<=pivot) low++;
		L.list[high] = L.list[low]; 
	}
	L.list[low] = pivot;
	return low;//返回枢轴位置 
}

void Qsort(sqlist &L, int low, int high)//low和high之间的全部快排 
{
	if(low < high)//当子序列只有一个元素时结束递归 
	{
		int pivot = partition(L, low, high);//一趟快排后的枢轴位置
		//分别对枢轴两边的子序列进行快排，调用递归  
		Qsort(L, low, pivot-1);
		Qsort(L, pivot+1, high); 
	}
}

void quick_sort(sqlist &L)//快排 
{
	Qsort(L, 1, L.length);
	cout << "快速排序后：";
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

//测试数据：10 48 35 66 91 74 18 22 48 57 03。
