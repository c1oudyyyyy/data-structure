#include <iostream>
#include <cstdlib>
using namespace std;

//˼·���������˵ĺ�������飬����ټ��ϰ����� 
void color_sort(int *arr1, int *arr2, int n)
{
	int low = 1, high = n;//��������
	int i;
	for(i=1; i<=n; i++)
	{
		if(arr1[i] == 1) arr2[low++] = 1;
		if(arr1[i] == 3) arr2[high--] = 3;
	}
	high++;
	while(low != high)//����м��λ����Ϊ��ɫ 
		arr2[low++] = 2;
}

int main()
{
	int n;//��������
	cout << "n = "; 
	cin >> n;
	int arr1[256];//�洢��ʼ״̬������
	int i;
	//1��ʾ�죬2��ʾ�ף�3��ʾ������ʼ���������� 
	for(i=1; i<=n; i++)
		cin >> arr1[i];
	int arr2[256];//�洢���������� 
	color_sort(arr1, arr2, n);
	//����������������� 
	for(i=1; i<=n; i++) 
		cout << arr2[i];
	cout << endl;
	return 0;
}

//�������ݣ�10 1 2 3 3 2 1 1 2 2 3�� 
