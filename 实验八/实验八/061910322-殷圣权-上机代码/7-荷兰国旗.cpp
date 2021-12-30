#include <iostream>
#include <cstdlib>
using namespace std;

//思路：先排两端的红和蓝条块，最后再加上白条块 
void color_sort(int *arr1, int *arr2, int n)
{
	int low = 1, high = n;//序列两端
	int i;
	for(i=1; i<=n; i++)
	{
		if(arr1[i] == 1) arr2[low++] = 1;
		if(arr1[i] == 3) arr2[high--] = 3;
	}
	high++;
	while(low != high)//最后将中间的位置设为白色 
		arr2[low++] = 2;
}

int main()
{
	int n;//条块数量
	cout << "n = "; 
	cin >> n;
	int arr1[256];//存储初始状态的条块
	int i;
	//1表示红，2表示白，3表示蓝，初始化条块序列 
	for(i=1; i<=n; i++)
		cin >> arr1[i];
	int arr2[256];//存储排序后的条块 
	color_sort(arr1, arr2, n);
	//输出排序后的条块序列 
	for(i=1; i<=n; i++) 
		cout << arr2[i];
	cout << endl;
	return 0;
}

//测试数据：10 1 2 3 3 2 1 1 2 2 3。 
