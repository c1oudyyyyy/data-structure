#include <stdio.h>
#include <stdlib.h>

#define OK 1
#define ERROR 0

#define ROWS 5
#define COLS 5

typedef int Status;

/*˼·�� 
�ӵ�һ�п�ʼ���ҳ�ÿ�е���Сֵ��Ȼ���ҳ���Сֵ�����е����ֵ��
�����ֵ��Ȼ�������Сֵ���������Ԫ�ص�λ�á� 
*/ 
int main()
{
	//�������� 
	int i, j;
	int M[ROWS][COLS];
	printf("�������Ԫ�أ�\n");
	for(i=0; i<ROWS; i++)
	{
		for(j=0; j<COLS; j++)
		{
			scanf("%d", &M[i][j]); 
		}
	}
	//Ѱ�Ұ���
	for(i=0; i<ROWS; i++)
	{
		int min = M[i][0];//��ʼ����СֵΪÿ�е�һ�� 
		int min_j = 0, max_i = i;;//��¼��Сֵ���ڵ��к����ֵ���ڵ��У���ʼ��Ϊ��һ�к͵�i�� 
		for(j=1; j<COLS; j++)
		{
			if(M[i][j] < min)
			{
				min = M[i][j];
				min_j = j;
			}
		}//�ҵ����е���Сֵ
		//���Ƿ��ж����Сֵ
		int min_j_arr[COLS], k = 0;//������Сֵ���ڵ�����
		for(j=0; j<COLS; j++)
		{
			if(M[i][j] == min)
			{
				min_j_arr[k++] = j; 
			}
		}
		int j_num = k;//������Сֵ��������������Сֵ�ĸ����� 
		//�ж�����Сֵ�������Ƿ��бȸ���Сֵ���ֵ���������ǰ��� 
		int max = min;//�������ֵ
		int sp = 1;//�ж��Ƿ�Ϊ���㣬0Ϊ���ǣ�1Ϊ��
		for(int o=0; o<j_num; o++)//������Сֵ���ڵ��� 
		{ 
			for(int k = 0; k<ROWS; k++)
			{
				if(M[k][min_j_arr[o]] > max)
				{
					sp = 0;//���ǰ��� 
					break;//�õ㲻�ǰ��㣬ֱ������ѭ�� 
				}
			} 
			if(sp == 1)//�ǰ��㣬���ֵ��λ�� 
			{
				printf("����Ԫ��ֵΪ��%d���ڵ�%d�У���%d��\n", max, max_i+1, min_j_arr[o]+1);
			}
		}
	} 
	return 0;
}

/*��������
3 2 1 1 5
9 2 7 5 11
6 5 7 2 9
7 6 8 6 10
5 3 2 0 6 
*/ 
