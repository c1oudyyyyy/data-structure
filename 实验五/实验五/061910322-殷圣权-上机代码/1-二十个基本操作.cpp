#include <stdio.h>
#include <stdlib.h>

#define OK 1
#define ERROR 0

typedef int Status;

typedef struct BiTNode
{
	char data;
	struct BiTNode *lchild, *rchild;
}BiTNode, *BiTree;

Status InitBiTree(BiTree &T)//1、初始化 
{
	T = NULL;
	return OK;
}

BiTree DestroyBiTree(BiTree &T)//2、销毁
{
	if(T != NULL)
	{
		T->lchild = DestroyBiTree(T->lchild);
		T->rchild = DestroyBiTree(T->rchild);
		free(T);
		return NULL;
	}
}

Status PreCreateBiTree(BiTree &T)//3、创建二叉树 
{
	char ch;
	scanf("%c", &ch);
	if(ch == ' ')
		T = NULL;
	else
	{
		T = (BiTNode *) malloc(sizeof(BiTNode));
		if(T == NULL) exit(ERROR);
		T->data = ch;
		PreCreateBiTree(T->lchild);
		PreCreateBiTree(T->rchild);
	}
	return OK;
}

Status ClearBiTree(BiTree &T)//4、清空 
{
	T = NULL;
	return OK;
}

bool BiTreeEmpty(BiTree T)//5、判空 
{
	if(T == NULL) 
		return true;
	else
		return false;
}

int BiTreeDepth(BiTree T)//6、求深度 
{
	int leftdepth, rightdepth;
	if(T == NULL) return 0;
	else
	{
		leftdepth = BiTreeDepth(T->lchild);
		rightdepth = BiTreeDepth(T->rchild);
		return (leftdepth > rightdepth) ? (leftdepth+1) : (rightdepth+1);
	}
}

Status Root(BiTree T, char &e)//7、求二叉树根的元素值 
{
	if(T == NULL)
	{
		printf("该树为空\n");
		return ERROR;
	}
	else
	{
		e = T->data;
		return OK;
	}
}

Status Value(BiTree T, BiTNode *cur_p, char &e)//8、返回当前值
{
	if(T != NULL)
	{
		e = cur_p->data;
		return OK;
	}
	printf("该树为空\n");
	return ERROR;
} 

Status Parent(BiTree T, BiTNode *cur_p, BiTNode *&parent)//9、求双亲指针 
{
	if(T != NULL)
	{
			if(T->lchild == cur_p || T->rchild == cur_p)
			{
				parent = T;
				return OK;
			}
			Parent(T->lchild, cur_p, parent);
			Parent(T->rchild, cur_p, parent);
	}
	return OK;
}

Status LeftChild(BiTree T, BiTNode *cur_p, BiTNode *&leftChild)//10、求左孩子结点 
{
	if(T != NULL)
	{
		leftChild = cur_p->lchild;
		return OK;
	}
	printf("该树为空\n");
	return ERROR;
}

Status RightChild(BiTree T, BiTNode *cur_p, BiTNode *&rightChild)//11、求右孩子结点 
{
	if(T != NULL)
	{
			rightChild = cur_p->rchild;
			return OK;
	}
	printf("该树为空\n");
	return ERROR;
}

Status LeftBrother(BiTree T, BiTNode *cur_p, BiTNode *&leftBrother)//12、求左兄弟结点 
{
	if(T != NULL)
	{
		if(T->lchild == cur_p)
		{
			leftBrother = NULL;
			return OK;
		}
		else if(T->rchild == cur_p)
		{
			leftBrother = T->lchild;
			return OK;
		}
		LeftBrother(T->lchild, cur_p, leftBrother);
		LeftBrother(T->rchild, cur_p, leftBrother);
	}
	return OK; 
} 

Status RightBrother(BiTree T, BiTNode *cur_p, BiTNode *&rightBrother)//13、求右兄弟结点 
{
	if(T != NULL)
	{
		if(T->rchild == cur_p)
		{
			rightBrother = NULL;
			return OK;
		}
		else if(T->lchild == cur_p)
		{
			rightBrother = T->rchild;
			return OK;
		}
		RightBrother(T->lchild, cur_p, rightBrother);
		RightBrother(T->rchild, cur_p, rightBrother);
	}
	return OK; 
}

Status PreOrderTraverse(BiTree T)//14、先序遍历 
{
	if(T != NULL)
	{
		printf("%c ", T->data);
		PreOrderTraverse(T->lchild);
		PreOrderTraverse(T->rchild);
	}
	return OK;
}

Status InOrderTraverse(BiTree T)//15、中序遍历 
{
	if(T != NULL)
	{
		InOrderTraverse(T->lchild);
		printf("%c ", T->data);
		InOrderTraverse(T->rchild);
	}
	return OK;
}

Status PostOrderTraverse(BiTree T)//16、后序遍历 
{
	if(T != NULL)
	{
		PostOrderTraverse(T->lchild);
		PostOrderTraverse(T->rchild);
		printf("%c ", T->data);
	}
	return OK;
}

Status LevelOrderTraverse(BiTree T)//17、层次遍历 
{
	BiTNode *p;
	BiTree queue[256];
	int front = 0, rear = 0;
	queue[rear] = T;
	rear++;
	while(front != rear)
	{
		p = queue[front];
		front = (front+1+256)%256;
		printf("%c ", p->data);
		if(p->lchild != NULL)
		{
			queue[rear] = p->lchild;
			rear = (rear+1+256)%256;
		}
		if(p->rchild != NULL)
		{
			queue[rear] = p->rchild;
			rear = (rear+1+256)%256;
		}
	}
}

Status Assign(BiTree T, BiTNode *&cur_p, char value)//18、给结点元素赋值 
{
	if(T != NULL)
	{
		cur_p->data = value;
		return OK;
	}
	printf("该树为空\n");
	return ERROR;
}

Status InsertChild(BiTree T, BiTNode *cur_p, Status LR, BiTree c)//19、插入子树 
{
	if(T != NULL)
	{
		if(LR == 0)
		{
			c->rchild = cur_p->lchild;
			cur_p->lchild = c;
		}
		else if(LR == 1)
		{
			c->rchild = cur_p->rchild;
			cur_p->rchild = c;
		}
		return OK;
	}
	printf("该树为空\n");
	return ERROR;
}

Status DeleteChild(BiTree T, BiTNode *cur_p, Status LR)//20、删除子树 
{
	if(T != NULL)
	{
		if(LR == 0)
		{
			cur_p->lchild = NULL;
		}
		else if(LR == 1)
		{
			cur_p->rchild = NULL;
		}
		return OK;
	}
	printf("该树为空\n");
	return ERROR;
}

Status ShowBiTree(BiTree T)//先序遍历显示 
{
	if(T != NULL)
	{
		printf("%c", T->data);
		if(T->lchild!=NULL || T->rchild!=NULL)
		{
			printf("(");
			ShowBiTree(T->lchild);
			printf(",");
			ShowBiTree(T->rchild);
			printf(")");
		}
	}
	return OK; 
}

int main()
{
	BiTree T;
	InitBiTree(T);
	printf("输入二叉树T和c的元素值：");
	PreCreateBiTree(T);
	printf("二叉树T为：");
	ShowBiTree(T);
	printf("\n");
	printf("该树的深度为：%d\n", BiTreeDepth(T));
	char e;
	Root(T, e);
	printf("根的元素值为：%c\n", e);
	BiTNode *cur_p = T->rchild->rchild;
	Value(T, cur_p, e);
	printf("cur_p指向的结点的元素为：%c\n", e);
	BiTNode *parent = NULL, *leftChild, *rightChild, *leftBrother, *rightBrother; 
	Parent(T, cur_p, parent);
	LeftChild(T, cur_p, leftChild);
	RightChild(T, cur_p, rightChild);
	LeftBrother(T, cur_p, leftBrother);
	RightBrother(T, cur_p, rightBrother);
	printf("cur_p的双亲结点元素为：%c\n", parent->data);
	printf("cur_p的左孩子元素为：%c\n", leftChild->data);
	printf("cur_p的右孩子元素为：%c\n", rightChild->data);
	printf("cur_p的左兄弟元素为：%c\n", leftBrother->data);
	//printf("cur_p的右兄弟元素为：%c\n", rightBrother->data);
	printf("先序遍历输出：");
	PreOrderTraverse(T);
	printf("\n");
	printf("中序遍历输出：");
	InOrderTraverse(T);
	printf("\n");
	printf("后序遍历输出：");
	PostOrderTraverse(T);
	printf("\n");
	printf("层次遍历输出：");
	LevelOrderTraverse(T);
	printf("\n");
	char value = 'a';
	Assign(T, cur_p, value);
	printf("替换结点后的二叉树T为：");
	ShowBiTree(T);
	printf("\n");
	BiTree c;
	PreCreateBiTree(c);
	InsertChild(T, cur_p, 0, c);
	printf("c插入二叉树T当前结点左边后：");
	ShowBiTree(T);
	printf("\n");
	DeleteChild(T, cur_p, 0);
	printf("删除二叉树T当前结点的左子树后：");
	ShowBiTree(T);
	printf("\n");
	ClearBiTree(T);
	PreOrderTraverse(T);
	DestroyBiTree(T);
	return 0;
}

//测试数据：ABDG  H   CE  FJ  K  LMN O  P   。
