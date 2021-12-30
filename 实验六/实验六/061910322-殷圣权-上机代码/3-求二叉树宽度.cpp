#include <stdio.h>
#include <stdlib.h>

#define SIZE 256

typedef struct biTnode 
{
	char data;
	struct biTnode *lchild;
	struct biTnode *rchild;
}biTnode, *biTree;

void create_biTree(biTree &T)//���������� 
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

//˼·����α�����������ÿ������һ��֮����ԭ�еĿ��ֵ�Աȣ���������¿��ֵ 
void biTree_width(biTree T, int &width)
{
	biTree Q[SIZE];//�������� 
	int front = 0, rear = 0;
	int last = 1;//ĳ�������� 
	int num = 0;//ĳ������ 
	biTnode *p = T;//����ָ�� 
	Q[rear++] = p;//����� 
	while(rear != front)
	{
		p = Q[front];//���� 
		front = (front+1) % SIZE;
		num++;//�����+1 
		//����
		if(p->lchild)//������� 
		{
			Q[rear] = p->lchild;
			rear = (rear+1) % SIZE;
		} 
		if(p->rchild)//�Һ������ 
		{
			Q[rear] = p->rchild;
			rear = (rear+1) % SIZE;
		}
		if(front == last)//����ȫ������ 
		{
			last = rear;//��һ�������� 
			if(num > width) width = num;
			num = 0;//��һ�㣬��������� 
		} 
	}
} 

int main()
{
	biTree T;
	create_biTree(T);
	int width = 0;
	biTree_width(T, width);
	printf("�ö��������Ϊ��%d\n", width);
	return 0;
}

//�������ݣ�ABD H  E  CF  GIK    J  �� 
