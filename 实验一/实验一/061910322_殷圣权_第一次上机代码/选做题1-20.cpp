#include<stdio.h>
#include<stdlib.h>

#define N 10

double polynomail(int a[],int i,double x,int n)
{
	if(i > 0)
		return (a[n-i] + polynomail(a,i-1,x,n) * x);
	else 
		return a[n];
}

int main()
{
    double x;
	int n, i;
	int a[N];
	printf("x = ");
	scanf("%lf", &x);
	printf("n = ");
	scanf("%d", &n);
	if(n > N-1) exit(0);
	for(i=0; i<=n; i++)
		scanf("%d", &a[i]);
	printf("%f", polynomail(a,n,x,n));
	return 0;
}

