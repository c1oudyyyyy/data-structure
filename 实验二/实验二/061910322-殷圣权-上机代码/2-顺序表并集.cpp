#include <stdio.h>
#include <stdlib.h>


#define OK 1
#define ERROR 0

#define SIZE 256
#define INCREMENT 128

typedef int Status;

typedef struct SeqList
{
	int *pData;
	int length;
	int size;
}SeqList;

Status InitList(SeqList &L)
{
	L.pData = (int *) malloc(SIZE * sizeof(int));
	if(L.pData == NULL) exit(ERROR);
	L.length = 0;
	L.size = SIZE;
	return OK;
}

Status InputElem(SeqList &L)
{
	int n, i;
	printf("请输入元素个数：");
	scanf("%d", &n);
	L.length = n;
	for(i=0; i<n; i++)
	{
		scanf("%d", &L.pData[i]);
	}
	return OK;
}

Status ListTraverse(SeqList L)
{
	for(int i=0; i<L.length; i++)
	{
		printf("%d ", L.pData[i]);
	}
	printf("\n");
	return OK;
}


//依次将b表中的元素与a表中的比较，将b元素插入a表中合适的位置 
Status ListUnion(SeqList &La, SeqList Lb)
{
	int i, j, k;
	for(j = 0; j < Lb.length; j++)//遍历b表 
	{
		for(i = 0; i < La.length; i++)//遍历a表 
		{
			//删除a表中重复元素
			if(La.pData[i] == La.pData[i+1])
			{
				for(k=i; k<La.length-1; k++)
				{
					La.pData[k] = La.pData[k+1];
				}
				La.length -= 1;
			}
			//找到大于a表元素的位置 
			if(Lb.pData[j] > La.pData[i])
			{
				if(La.length == La.size)//若a表已满 
				{
					int *newbase = (int *) realloc(La.pData, (SIZE+INCREMENT) * sizeof(int));
					if(newbase == NULL) exit(ERROR);
					La.pData = newbase;
					La.size += INCREMENT;
				}
				//插入当前元素之前
				for(k=La.length; k>i; k--)
					La.pData[k] = La.pData[k-1];
				La.pData[i] = Lb.pData[j];
				La.length += 1;
				break;	//跳出循环，轮到下一个b表元素 
			}
			else if(Lb.pData[j] == La.pData[i])//若相等，则跳过 
			{
				j++;
				break;
			}	
		}
		//该元素比a表元素都小，则插入a表表尾
		if(Lb.pData[j] < La.pData[La.length-1])
		{
			if(La.length == La.size)//若a表已满 
			{
				int *newbase = (int *) realloc(La.pData, (SIZE+INCREMENT) * sizeof(int));
				if(newbase == NULL) exit(ERROR);
				La.pData = newbase;
				La.size += INCREMENT;
			}
			La.pData[La.length] = Lb.pData[j];//插入该元素 
			La.length += 1;
		}	
	}	
	return OK;
}

int main()
{
	SeqList La, Lb;
	InitList(La);
	InitList(Lb);
	InputElem(La);
	InputElem(Lb);
	ListUnion(La, Lb);
	printf("合并之后：\n");
	ListTraverse(La);
	return 0;
} 
