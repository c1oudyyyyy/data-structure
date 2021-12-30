#include <stdio.h>
#include <stdlib.h> 

#define MAX 32 

void Fibonacci(int k, int n)
{
	if(k < 1) exit(0);
	int queue[k], front = 0, rear = 0;//ѭ������ 
	int e, i = 0, j;
	while(i <= n)
	{
		int x = 0;
		if(i < k-1)//ǰk-1��Ϊ0 
		{
			queue[rear] = 0;
			rear = (rear + 1 + k) % k;
		}
		if(i == k-1)//��k��Ϊ1 
		{
			queue[rear] = 1;
			rear = (rear + 1 + k) % k;
		}
			
		else//�Ժ��ÿһ��Ϊǰ���Ԫ��֮�� 
		{
			// �������
			j = front;
			do
			{
				x += queue[j];
				j = (j + 1 + k) % k;
			}while(j != rear);
			
			if(x < MAX)//��Ԫ��С��Լ���ĳ���MAX=14������� 
			{
				//���� 
				front = (front + 1 + k) % k;
				//��� 
				queue[rear] = x;
				rear = (rear + 1 + k) % k;
			}
			
			else//�������ѭ�� 
				break;
		}
		
		i++;
	}
	//��������ڵ�Ԫ��
	i = front;
	do
	{
		printf("%d ", queue[i]);
		i = (i + 1 + k) % k;
	}while(i != rear);
}

int main()
{
	int k, n;
	printf("����k��n��ֵ��");
	scanf("%d %d", &k, &n);
	Fibonacci(k, n);
	return 0;
}

//���ԣ�2 10000 
