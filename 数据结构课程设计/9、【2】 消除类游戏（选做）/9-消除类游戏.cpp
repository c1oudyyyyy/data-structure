/*
���ж�ÿһ���Ƿ��п��������ģ���������Ϊ����(����ֵ����)��
���ж�ÿһ���Ƿ��п��������ģ���������Ϊ������
������Щ����ȫ����Ϊ0������ʾ������ɡ�
*/ 

#include <iostream>
#include <cmath>
 
using namespace std;
 
const int N = 30;
 
int grid[N][N], n, m;
 
int main()
{
    // ��ʼ������ 
    cin >> n >> m;
    for(int i=0; i<n; i++)
        for(int j=0; j<m; j++)
		{
            cin >> grid[i][j];
        }
 
    //�б�ǣ�������������Ϊ����
    for(int i=0; i<n; i++)
        for(int j=0; j<m-2; j++)
		{
            if(abs(grid[i][j]) == abs(grid[i][j+1]) && abs(grid[i][j+1]) == abs(grid[i][j+2]))
			{
                if(grid[i][j] > 0)
                    grid[i][j] = - grid[i][j];
                if(grid[i][j+1] > 0)
                    grid[i][j+1] = - grid[i][j+1];
                if(grid[i][j+2] > 0)
                    grid[i][j+2] = - grid[i][j+2];
            }
        }
 
    //�б�ǣ�������������Ϊ����
    for(int j=0; j<m; j++)
        for(int i=0; i<n-2; i++)
		{
            if(abs(grid[i][j]) == abs(grid[i+1][j]) && abs(grid[i+1][j]) == abs(grid[i+2][j]))
			{
                if(grid[i][j] > 0)
                    grid[i][j] = - grid[i][j];
                if(grid[i+1][j] > 0)
                    grid[i+1][j] = - grid[i+1][j];
                if(grid[i+2][j] > 0)
                    grid[i+2][j] = - grid[i+2][j];
            }
        }
 
    // �����������������Ϊ0������������
    cout << "�����" << endl;
    for(int i=0; i<n; i++) {
        for(int j=0; j<m; j++)
		{
            if(grid[i][j] < 0)
                grid[i][j] = 0;
            if(j != 0)
                cout << " ";
            cout << grid[i][j];
        }
        cout << endl;
    }
 
    return 0;
}
