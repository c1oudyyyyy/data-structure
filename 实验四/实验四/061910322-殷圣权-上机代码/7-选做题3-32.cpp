#include <stdio.h>
#include <stdlib.h> 

#define MAX 32 

void Fibonacci(int k, int n)
{
	if(k < 1) exit(0);
	int queue[k], front = 0, rear = 0;//循环队列 
	int e, i = 0, j;
	while(i <= n)
	{
		int x = 0;
		if(i < k-1)//前k-1项为0 
		{
			queue[rear] = 0;
			rear = (rear + 1 + k) % k;
		}
		if(i == k-1)//第k项为1 
		{
			queue[rear] = 1;
			rear = (rear + 1 + k) % k;
		}
			
		else//以后的每一项为前面的元素之和 
		{
			// 队列求和
			j = front;
			do
			{
				x += queue[j];
				j = (j + 1 + k) % k;
			}while(j != rear);
			
			if(x < MAX)//若元素小于约定的常数MAX=14，则入队 
			{
				//出队 
				front = (front + 1 + k) % k;
				//入队 
				queue[rear] = x;
				rear = (rear + 1 + k) % k;
			}
			
			else//否则结束循环 
				break;
		}
		
		i++;
	}
	//输出队列内的元素
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
	printf("输入k和n的值：");
	scanf("%d %d", &k, &n);
	Fibonacci(k, n);
	return 0;
}

//测试：2 10000 
