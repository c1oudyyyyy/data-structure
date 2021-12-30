/*
先判断每一行是否有可以消除的，若有则设为负数(绝对值不变)，
再判断每一列是否有可以消除的，若有则设为负数，
最后把这些负数全部设为0，即表示消除完成。
*/ 

#include <iostream>
#include <cmath>
 
using namespace std;
 
const int N = 30;
 
int grid[N][N], n, m;
 
int main()
{
    // 初始化数据 
    cin >> n >> m;
    for(int i=0; i<n; i++)
        for(int j=0; j<m; j++)
		{
            cin >> grid[i][j];
        }
 
    //行标记（可以消除则置为负）
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
 
    //列标记（可以消除则置为负）
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
 
    // 进行清除（消除则置为0）并且输出结果
    cout << "结果：" << endl;
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
