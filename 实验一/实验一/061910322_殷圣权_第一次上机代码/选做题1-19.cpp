#include<stdio.h>
#include<stdlib.h>
#define MAXINT 65535
#define arrsize 256

int main()
{
	int i, k;
	int a[arrsize];
	printf("k = ");
	scanf("%d", &k);
	if(k > arrsize-1) exit(0);
	for(i=0; i<=k; i++)
	{
		if(i == 0)
			a[i] = 1;
		else
		{
			if(2 * i * a[i-1] > MAXINT) exit(0);
			else a[i] = 2 * i * a[i-1];
		}
	}
	for(i=0; i<=k; i++)
	{
		printf("%d ", a[i]);
	}
	return 0;
}

