#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
using namespace std;

void Swap_SortUp(int *a,int n)//交换排序排为升序
{
    int i,j;
    int temp;
    for(i=0;i<n-1;i++)
    {
        for(j=0;j<n-1-i;j++)
        {
            if(a[j]>a[j+1])
            {
                temp=a[j];
                a[j]=a[j+1];
                a[j+1]=temp;
            }
        }
    }
}

void Swap_SortDown(int *a,int n)//交换排序排为降序
{
    int i,j;
    int temp;
    for(i=0;i<n-1;i++)
    {
        for(j=0;j<n-1-i;j++)
        {
            if(a[j]<a[j+1])
            {
                temp=a[j];
                a[j]=a[j+1];
                a[j+1]=temp;
            }
        }
    }
}

void Specimen()//生成随机数 
{
    srand(time(NULL));
    int i,j;
    int a[20000];
    for(i=1;i<=10;i++)
    {
        FILE *fp=NULL;
        switch(i)
        {
            case 1:
                fp=fopen("1.txt","w");
                break;
            case 2:
                fp=fopen("2.txt","w");
                break;
            case 3:
                fp=fopen("3.txt","w");
                break;
            case 4:
                fp=fopen("4.txt","w");
                break;
            case 5:
                fp=fopen("5.txt","w");
                break;
            case 6:
                fp=fopen("6.txt","w");
                break;
            case 7:
                fp=fopen("7.txt","w");
                break;
            case 8:
                fp=fopen("8.txt","w");
                break;
            case 9:
                fp=fopen("9.txt","w");
                break;
            case 10:
                fp=fopen("10.txt","w");
                break;
        }
        for(j=0;j<20000;j++)
        {
            a[j]=rand()%1000;
        }
        if(i==1) Swap_SortUp(a,20000);
        if(i==2) Swap_SortDown(a,20000);
        for(j=0;j<20000;j++)
        {
            fprintf(fp,"%d\n",a[j]);
        }
        fclose(fp);
    }
}

//直接插入排序
void Insert_Sort(int *a,int n)
{
    int i,j;
    for(i=1;i<n;i++)
    {
        j = i;
        while(j>0 && a[j]<a[j-1])
        {
            int temp;
            temp=a[j];
            a[j]=a[j-1];
            a[j-1]=temp;
            j--;
        }
    }
}

//希尔排序
void Shell_Sort(int *a,int len)
{
    int i,j,temp,step;
    for(step=len/2;step>0;step/=2)
    {
        for(i=step;i<len;i++)
        {
            temp=a[i];
            j=i-step;
            if(a[j]>temp)
            {
                a[j]=temp;
                a[i]=a[j];
            }
        }
    }
}

//冒泡排序
void Swap_Sort(int *a,int n)
{
    int i,j;
    int temp;
    for(i=0;i<n-1;i++)
    {
        for(j=0;j<n-1-i;j++)
        {
            if(a[j]>a[j+1])
            {
                temp=a[j];
                a[j]=a[j+1];
                a[j+1]=temp;
            }
        }
    }
}

//快速排序
void Quick_Sort(int *a,int left,int right)
{
    if(left>=right)
    {
        return;
    }
    int i=left;
    int j=right;
    int key=a[left];
    while(i<j)
    {
        while(i<j && key<=a[j])
        {
            j--;
        }
        a[i]=a[j];
        while(i<j && key>=a[i])
        {
            i++;
        }
        a[j]=a[i];
    }
    a[i]=key;
    Quick_Sort(a,left,i-1);
    Quick_Sort(a,i+1,right);
}

//选择排序
void Select_Sort(int *a,int n)
{
    int i,j,min,temp;
    for(i=0;i<n;i++)
    {
        min=i;
        for(j=i+1;j<n;j++)
        {
            if(a[j]<a[i])
                min=j;
        }
        if(min!=i)
        {
            temp=a[i];
            a[i]=a[min];
            a[min]=temp;
        }
    }
}

//堆排序
void Swap(int *a,int *b)
{
    int temp;
    temp=*a;
    *a=*b;
    *b=temp;
}

void Max_Heapify(int *a,int start,int end)
{
    int dad=start;
    int son=dad*2+1;
    while(son<=end)
    {
        if(son+1<=end && a[son]<=a[son+1])
        {
            son++;
        }
        if(a[dad]>=a[son])
        {
            return;
        }
        else
        {
            a[dad]=a[son];
            dad=son;
            son=dad*2+1;
        }
    }
}

void Heap_Sort(int *a,int len)
{
    int i;
    for(i=len/2-1;i>=0;i--)
    {
        Max_Heapify(a,i,len-1);
    }
    for(i=len-1;i>=0;i--)
    {
        Swap(&a[0],&a[i]);
        Max_Heapify(a,0,i-1);
    }
}

//归并排序
void Merge(int a[],int start,int mid,int end)
{
    int *temp=(int *)malloc((end-start+1)*(sizeof(int)));
    int i=start;
    int j=mid+1;
    int k=0;
    while (i<=mid && j<=end)
    {
        if(a[i]<=a[j])
            temp[k++]=a[i++];
        else
            temp[k++]=a[j++];
    }
    while(i<=mid)
        temp[k++]=a[i++];
    while(j<=end)
        temp[k++]=a[j++];
    for(i=0;i<k;i++)
    {
        a[start+i]=temp[i];
    }
    free(temp);
}

void Merge_Sort(int a[], int start , int end)
{
    if(a==NULL || start>=end)
        return ;
    int mid;
    mid=(start+end)/2;
    Merge_Sort(a,start,mid);
    Merge_Sort(a,mid+1,end);
    Merge(a,start,mid,end);
}

//基数排序
int Get_max(int *a,int n)
{

    int i,max=a[0];
    for(i=1;i<n;i++)
    {
        if(a[i]>max)
            max=a[i];
    }
    return max;
}

void Count_Sort(int *a,int n,int exp)
{
    int tmp[n];
    int i,bucket[10]={0};
    for(i=0;i<n;i++)
    {
        bucket[(a[i]/exp)%10]++;
    }
    for(i=1;i<10;i++)
    {
        bucket[i]+=bucket[i-1];        
    }
    for(i=n-1;i>=0;i--)
    {
        tmp[bucket[(a[i]/exp)%10]-1]=a[i];
        bucket[(a[i]/exp)%10]--;
    }
    for(i=0;i<n;i++)
    {
        a[i]=tmp[i];
    }
}

void  Radix_Sort(int *a,int n)
{
    int exp;
    int max=Get_max(a,n);
    for(exp=1;max/exp>0;exp *=10)
    {
        Count_Sort(a,n,exp);
    }
}

int main()
{
    Specimen();
    int i,j,num;
    clock_t start,end;
    int a1[20000],a2[20000],a3[20000],a4[20000],a5[20000],a6[20000],a7[20000],a8[20000];
    for(i=1;i<=10;i++)
    {
        FILE *fp=NULL;
        switch(i)
        {
            case 1:
                printf("样本1各排序算法所花时间如下：\n");
                fp = fopen("1.txt","r");
                break;
            case 2:
                printf("样本2各排序算法所花时间如下：\n");
                fp = fopen("2.txt","r");
                break;
            case 3:
                printf("样本3各排序算法所花时间如下：\n");
                fp = fopen("3.txt","r");
                break;
            case 4:
                printf("样本4各排序算法所花时间如下：\n");
                fp = fopen("4.txt","r");
                break;
            case 5:
                printf("样本5各排序算法所花时间如下：\n");
                fp = fopen("5.txt","r");
                break;
            case 6:
                printf("样本6各排序算法所花时间如下：\n");
                fp = fopen("6.txt","r");
                break;
            case 7:
                printf("样本7各排序算法所花时间如下：\n");
                fp = fopen("7.txt","r");
                break;
            case 8:
                printf("样本8各排序算法所花时间如下：\n");
                fp = fopen("8.txt","r");
                break;
            case 9:
                printf("样本9各排序算法所花时间如下：\n");
                fp = fopen("9.txt","r");
                break;
            case 10:
                printf("样本10各排序算法所花时间如下：\n");
                fp = fopen("10.txt","r");
                break;
        }
        printf("\n");
        for(j=0;j<20000;j++)
        {
            fscanf(fp,"%d",&num);
            a1[j]=num;
            a2[j]=num;
            a3[j]=num;
            a4[j]=num;
            a5[j]=num;
            a6[j]=num;
            a7[j]=num;
            a8[j]=num;
        }
        fclose(fp);
        printf("直接插入排序：");
        start=clock();//开始时间 
        Insert_Sort(a1,20000);
        end=clock();//结束时间 
        printf("%fms\n",(float)(end-start));
        printf("希尔排序：");
        start=clock();
        Shell_Sort(a2,20000);
        end=clock();
        printf("%fms\n",(float)(end-start));
        printf("冒泡排序：");
        start=clock();
        Swap_Sort(a3,20000);
        end=clock();
        printf("%fms\n",(float)(end-start));
        printf("快速排序：");
        start=clock();
        Quick_Sort(a4,0,19999);
        end=clock();
        printf("%fms\n",(float)(end-start));
        printf("选择排序：");
        start=clock();
        Select_Sort(a5,20000);
        end=clock();
        printf("%fms\n",(float)(end-start));
        printf("堆排序：");
        start=clock();
        Heap_Sort(a6,20000);
        end=clock();
        printf("%fms\n",(float)(end-start));
        printf("归并排序：");
        start=clock();
        Merge_Sort(a7,0,19999);
        end=clock();
        printf("%fms\n",(float)(end-start));
        printf("基数排序：");
        start=clock();
        Radix_Sort(a8,20000);
        end=clock();
        printf("%fms\n\n\n",(float)(end-start));
    }
    return 0;
}
