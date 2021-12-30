#include<iostream>
#include<cstdio>
using namespace std;

int score[256], m = 0;//储存得分情况
 
int who_win(int board[][4])
{
	if(board[1][1]==board[1][2] && board[1][2]==board[1][3] && board[1][1]==1 
	|| board[2][1]==board[2][2] && board[2][2]==board[2][3] && board[2][1]==1
	|| board[3][1]==board[3][2] && board[3][2]==board[3][3] && board[3][1]==1
	|| board[1][1]==board[2][1] && board[2][1]==board[3][1] && board[1][1]==1
	|| board[2][1]==board[2][2] && board[2][2]==board[2][3] && board[2][1]==1
	|| board[3][1]==board[3][2] && board[3][2]==board[3][3] && board[3][1]==1
	|| board[1][1]==board[2][2] && board[2][2]==board[3][3] && board[1][1]==1
	|| board[1][3]==board[2][2] && board[2][2]==board[3][1] && board[1][3]==1)//a获胜的所有情况-8种 
	return 1;
	
	else if(board[1][1]==board[1][2] && board[1][2]==board[1][3] && board[1][1]==2 
	|| board[2][1]==board[2][2] && board[2][2]==board[2][3] && board[2][1]==2
	|| board[3][1]==board[3][2] && board[3][2]==board[3][3] && board[3][1]==2
	|| board[1][1]==board[2][1] && board[2][1]==board[3][1] && board[1][1]==2
	|| board[2][1]==board[2][2] && board[2][2]==board[2][3] && board[2][1]==2
	|| board[3][1]==board[3][2] && board[3][2]==board[3][3] && board[3][1]==2
	|| board[1][1]==board[2][2] && board[2][2]==board[3][3] && board[1][1]==2
	|| board[1][3]==board[2][2] && board[2][2]==board[3][1] && board[1][3]==2)//b获胜的所有情况-8种 
	return -1;
	
	else
		return 0;//没有人获胜 
}

//统计空格个数
int blank_num(int board[][4])
{
	int i, j, num = 0;//空格个数 
	for(i=1; i<=3; i++)
		for(j=1; j<=3; j++)
			if(board[i][j] == 0) 
				num += 1;
	return num;
} 

void play(int board[][4])
{
	int blank = blank_num(board);//计算空格个数 
	int win = who_win(board);//先判断当前的局面 
	if(win == 1)//若a已经赢了 
		score[m++] = blank + 1;//储存a得到的分数 
	else if(win == -1)//若b已经赢了 
		score[m++] = -(blank + 1);//储存a扣的分数 
	else//若a、b均还未获胜，则a下棋
	{ 
		int i, j;
		for(i=1; i<=3; i++)//遍历棋盘 
			for(j=1; j<=3; j++)
				if(board[i][j] == 0)//若是空格，则下棋
				{
					board[i][j] = 1;//下棋
					if(who_win(board) == 1)//若下棋之后a获胜 
					{
						score[m++] = blank;//储存本局a得到的分数 
						return ;//返回 
					}
					else//否则，将该棋子放回，继续看在下一个位置下棋是否会获胜 
						board[i][j] = 0;//放回棋子 
				} 
		score[m++] = 0;//若找遍棋盘的空格a还是获胜不了，则根据最优策略下棋将会平局 
		return ;//返回 
	}
} 

int main()
{
	int board[4][4], i, j, k, t;
	cin >> k;
	for(t=1; t<=k; t++)
	{
		for(i=1; i<=3; i++)
			for(j=1; j<=3; j++)
				cin >> board[i][j];
		
		play(board);
	}
	for(t=0; t<k; t++)
		cout << score[t] << endl;
	return 0;
}

/*样例输入 
3 
1 2 1 
2 1 2 
0 0 0 
2 1 1 
0 2 1 
0 0 2 
0 0 0 
0 0 0 
0 0 0 
样例输出 
3 
-4 
0
*/ 
