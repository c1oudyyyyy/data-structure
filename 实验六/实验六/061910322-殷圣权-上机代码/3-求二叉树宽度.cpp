#include <stdio.h>
#include <stdlib.h>

#define SIZE 256

typedef struct biTnode 
{
	char data;
	struct biTnode *lchild;
	struct biTnode *rchild;
}biTnode, *biTree;

void create_biTree(biTree &T)//创建二叉树 
{
	char ch;
	scanf("%c", &ch);
	if(ch == ' ') T = NULL;
	else
	{
		T = (biTnode *) malloc(sizeof(biTnode));
		if(!T) exit(0);
		T->data = ch;
		create_biTree(T->lchild);
		create_biTree(T->rchild);
	}
}

//思路：层次遍历二叉树，每遍历完一层之后与原有的宽度值对比，若大则更新宽度值 
void biTree_width(biTree T, int &width)
{
	biTree Q[SIZE];//建立队列 
	int front = 0, rear = 0;
	int last = 1;//某层最后结点号 
	int num = 0;//某层结点数 
	biTnode *p = T;//遍历指针 
	Q[rear++] = p;//根入队 
	while(rear != front)
	{
		p = Q[front];//出队 
		front = (front+1) % SIZE;
		num++;//结点数+1 
		//访问
		if(p->lchild)//左孩子入队 
		{
			Q[rear] = p->lchild;
			rear = (rear+1) % SIZE;
		} 
		if(p->rchild)//右孩子入队 
		{
			Q[rear] = p->rchild;
			rear = (rear+1) % SIZE;
		}
		if(front == last)//本层全部出队 
		{
			last = rear;//下一层最后结点号 
			if(num > width) width = num;
			num = 0;//下一层，结点数清零 
		} 
	}
} 

int main()
{
	biTree T;
	create_biTree(T);
	int width = 0;
	biTree_width(T, width);
	printf("该二叉树宽度为：%d\n", width);
	return 0;
}

//测试数据：ABD H  E  CF  GIK    J  。 
