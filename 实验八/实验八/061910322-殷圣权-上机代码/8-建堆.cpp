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

void create_heap(sqlist &L)//建堆：从第2个元素开始，依次往上筛选，较大者往上移。 
{
	int i, j, k;
	for(i=2; i<=L.length; i++)
	{
		j = i;
		while(j != 1)
		{
			k = j / 2;//k为j的父结点 
			if(L.list[j] > L.list[k])
			{
				//交换 
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

void heap_adjust(sqlist &L, int low, int high)//low位置的左右子树均满足小顶堆的定义 
{
	int t = L.list[low]; 
	int i = low;
	int j = 2 * i;
	while(j <= high)
	{
		if(j+1<=high && L.list[j]>L.list[j+1]) j++;//在左右子树中选最小者 
		if(t <= L.list[j]) break;//已经是小顶堆
		//向下筛选 
		L.list[i] = L.list[j];
		i = j;
		j = 2 * i;
	}
	L.list[i] = t;//插入最终位置 
}

void heap_sort(sqlist &L)//堆排序 
{
	int i, t;
	create_heap(L); 
	for(i=L.length; i>1; i--)
	{
		//堆顶记录和最后一个记录交换
		t = L.list[1]; L.list[1] = L.list[i]; L.list[i] = t;
		heap_adjust(L, 1, i-1);//交换记录后进行堆调整 
	}
	cout << "堆排序后：";
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

//测试数据：8 48 35 66 91 74 18 22 48。
