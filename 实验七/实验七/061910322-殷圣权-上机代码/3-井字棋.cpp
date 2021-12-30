#include<iostream>
#include<cstdio>
using namespace std;

int score[256], m = 0;//����÷����
 
int who_win(int board[][4])
{
	if(board[1][1]==board[1][2] && board[1][2]==board[1][3] && board[1][1]==1 
	|| board[2][1]==board[2][2] && board[2][2]==board[2][3] && board[2][1]==1
	|| board[3][1]==board[3][2] && board[3][2]==board[3][3] && board[3][1]==1
	|| board[1][1]==board[2][1] && board[2][1]==board[3][1] && board[1][1]==1
	|| board[2][1]==board[2][2] && board[2][2]==board[2][3] && board[2][1]==1
	|| board[3][1]==board[3][2] && board[3][2]==board[3][3] && board[3][1]==1
	|| board[1][1]==board[2][2] && board[2][2]==board[3][3] && board[1][1]==1
	|| board[1][3]==board[2][2] && board[2][2]==board[3][1] && board[1][3]==1)//a��ʤ���������-8�� 
	return 1;
	
	else if(board[1][1]==board[1][2] && board[1][2]==board[1][3] && board[1][1]==2 
	|| board[2][1]==board[2][2] && board[2][2]==board[2][3] && board[2][1]==2
	|| board[3][1]==board[3][2] && board[3][2]==board[3][3] && board[3][1]==2
	|| board[1][1]==board[2][1] && board[2][1]==board[3][1] && board[1][1]==2
	|| board[2][1]==board[2][2] && board[2][2]==board[2][3] && board[2][1]==2
	|| board[3][1]==board[3][2] && board[3][2]==board[3][3] && board[3][1]==2
	|| board[1][1]==board[2][2] && board[2][2]==board[3][3] && board[1][1]==2
	|| board[1][3]==board[2][2] && board[2][2]==board[3][1] && board[1][3]==2)//b��ʤ���������-8�� 
	return -1;
	
	else
		return 0;//û���˻�ʤ 
}

//ͳ�ƿո����
int blank_num(int board[][4])
{
	int i, j, num = 0;//�ո���� 
	for(i=1; i<=3; i++)
		for(j=1; j<=3; j++)
			if(board[i][j] == 0) 
				num += 1;
	return num;
} 

void play(int board[][4])
{
	int blank = blank_num(board);//����ո���� 
	int win = who_win(board);//���жϵ�ǰ�ľ��� 
	if(win == 1)//��a�Ѿ�Ӯ�� 
		score[m++] = blank + 1;//����a�õ��ķ��� 
	else if(win == -1)//��b�Ѿ�Ӯ�� 
		score[m++] = -(blank + 1);//����a�۵ķ��� 
	else//��a��b����δ��ʤ����a����
	{ 
		int i, j;
		for(i=1; i<=3; i++)//�������� 
			for(j=1; j<=3; j++)
				if(board[i][j] == 0)//���ǿո�������
				{
					board[i][j] = 1;//����
					if(who_win(board) == 1)//������֮��a��ʤ 
					{
						score[m++] = blank;//���汾��a�õ��ķ��� 
						return ;//���� 
					}
					else//���򣬽������ӷŻأ�����������һ��λ�������Ƿ���ʤ 
						board[i][j] = 0;//�Ż����� 
				} 
		score[m++] = 0;//���ұ����̵Ŀո�a���ǻ�ʤ���ˣ���������Ų������彫��ƽ�� 
		return ;//���� 
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

/*�������� 
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
������� 
3 
-4 
0
*/ 
