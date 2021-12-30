/*
在树结点分配一个整型变量记录每个结点的平衡度，
创建平衡二叉树以及插入或删除某元素的时候先找到每个结点在树上的位置，
然后再根据平衡度是否满足平衡二叉树的定义来进行相应的左旋和右旋的操作。
*/ 

#include<stdio.h>
#include<stdlib.h>
#define LH +1
#define EH 0
#define RH -1
#define NO 0
 
typedef struct BSTNode
{
    int data;
    int bf;//结点的平衡因子 
    struct BSTNode *lchild,*rchild;
}BSTNode,*BSTree;
 
void CreatBST(BSTree &T);//创建二叉排序树
bool InsertAVL(BSTree &T,int e,bool &taller);//平衡化插入 

void R_Rotate (BSTree &p);//对以*p为根的二叉排序树作右旋处理 
void L_Rotate(BSTree &p);//对以*p为根的二叉排序树作左旋处理 
void LeftBalance(BSTree &T);//对以指针Ｔ所指结点为根的二叉树作左平衡旋转处理
void RightBalance(BSTree &T);//对以指针Ｔ所指结点为根的二叉树作右平衡旋转处理

bool SearchBST(BSTree &T,int key);//查找 

void LeftBalance_div(BSTree &p,int &shorter);//删除结点时左平衡旋转处理
void RightBalance_div(BSTree &p,int &shorter);//删除结点时右平衡旋转处理
void Delete(BSTree q,BSTree  &r,int &shorter);//删除结点 
int DeleteAVL(BSTree &p,int x,int &shorter);//平衡二叉树删除操作 

void PrintBST(BSTree T,int depth);//打印树状图 
 
int main()
{
    BSTree T;
    int sear,cmd,depth;
    int ch;
    int shorter=0;
    bool taller=false;
    T=(BSTree)malloc(sizeof(BSTNode));
    T=NULL;
    printf("***********************菜单*****************************\n");
    printf("*                    1--创建                           *\n");
    printf("*                    2--查找                           *\n");
    printf("*                    3--插入                           *\n");
    printf("*                    4--删除                           *\n");
    printf("*                    0--退出                           *\n");
    printf("********************************************************\n");
    do
    {
        printf("\n请选择操作的编号：");
        scanf("%d",&cmd);
        getchar();
        switch(cmd)
        {
        case 1:
            CreatBST(T);break;
        case 2:
            printf("请输入您要查找的关键字：");
                scanf("%d",&sear);
                getchar();
            if(SearchBST(T,sear))
            {
                printf("关键字%d存在，查找成功!\n",sear);
            }
            else printf("查找失败!\n");
            break;
        case 3:
            printf("请输入您要插入的关键字：");
            scanf("%d",&sear);
            getchar();
            InsertAVL(T,sear,taller);depth=0;
            PrintBST(T,depth);
            break;
        case 4:
            depth=0;
            printf("请输入你要删除的关键字: ");
            scanf("%d",&sear);
            getchar();
            DeleteAVL(T,sear,shorter);
            PrintBST(T,depth);
            break;
        case 0:
            printf("结束!\n");
            return 0;
        default:
            printf("输入错误!\n");
        }
    }while(true);
}
 
void CreatBST(BSTree &T)
{
	FILE *fp = fopen("7.txt", "r");
	if(!fp)
	{
		printf("文件打开失败！\n");
		exit(0);
	}
    int depth;
    int e;
    bool taller = false;
    T = NULL;
    fscanf(fp, "%d", &e);
    while(!feof(fp))
    {
        InsertAVL(T,e,taller);
        fscanf(fp, "%d", &e);
        taller = false;
    }
    depth = 0;
    printf("您创建的二叉树为\n");
    if(T)
        PrintBST(T,depth);
    else
        printf("这是一棵空树!\n");
}
 
void R_Rotate (BSTree &p)
{
    BSTree lc;
    lc=p->lchild;
    p->lchild=lc->rchild;
    lc->rchild=p;
    p=lc;
}
 
void L_Rotate(BSTree &p)
{
    BSTree rc;
    rc=p->rchild;
    p->rchild=rc->lchild;
    rc->lchild=p;
    p=rc;
}
 
void LeftBalance(BSTree &T)
{
    BSTree lc,rd;
    lc=T->lchild;
    switch(lc->bf)
    {
    case LH://原本左子树高于右子树 
        T->bf=lc->bf=EH;//现在设为等高 
        R_Rotate(T);//右旋 
        break;
    case RH://原本右子树高于左子树 
        rd=lc->rchild;//右子树 
        switch(rd->bf)
        {
        case LH://原本右子树的平衡度为1 
                T->bf=RH;
                lc->bf=EH;
                break;
        case EH://原本右子树的平衡度为0 
                T->bf=lc->bf=EH;
                break;
        case RH://原本右子树的平衡度为-1 
                T->bf=EH;
                lc->bf=LH;break;
        }
        rd->bf=EH;//将右子树平衡度设为0 
        L_Rotate(T->lchild);//左旋左子树 
        R_Rotate(T);//右旋
    }
}

void RightBalance(BSTree &T)
{
    BSTree rc,ld;
    rc=T->rchild;
    switch(rc->bf)
    {
    case RH:
        T->bf=rc->bf=EH;
        L_Rotate(T);
        break;
    case LH:
        ld=rc->lchild;
        switch(ld->bf)
        {
        case RH:
                T->bf=LH;
                rc->bf=EH;
                break;
        case EH:
                T->bf=rc->bf=EH;
                break;
        case LH:
                T->bf=EH;
                rc->bf=RH;
                break;
        }
        ld->bf=EH;
        R_Rotate(T->rchild);
        L_Rotate(T);
    }
}
 
bool InsertAVL(BSTree &T,int e,bool &taller) 
{
    if(!T)//若为空则直接插入，树长高，把taller设置为true 
    {
        T=(BSTree)malloc(sizeof(BSTNode));
        T->data=e;
        T->lchild=T->rchild=NULL;
        T->bf=EH;
        taller=true;
    }
    else//否则 
	{
        if(e==T->data)//若已存在该关键字，则不再插入
        {
            taller=false;
            printf("已存在相同关键字的结点!\n");
            return false;
        }
        if(e<T->data)//若值较小则继续在T的左子树中进行搜索
        {
            if(!InsertAVL(T->lchild,e,taller))//递归调用，在左子树中未插入 
                return false;//没有长高 
            if(taller)//已插入左子树并且左子树长高
            switch(T->bf)//根据平衡度判断是否旋转 
            {
                case LH://原本左子树比右子树高，需要作左平衡处理
                    LeftBalance(T);
                    taller=false;
                    break;
                case EH: //原本左、右子树等高，现因左子树增高而使树增高，树依然在平衡状态 
                    T->bf=LH;
                    taller=true;
                    break;
                case RH://原本右子树比左子树高，现左、右子树等高，树依然在平衡状态 
                    T->bf=EH;
                    taller=false;
                    break;
            }
        }
        else//否则继续在T的右子树中进行搜索
		{
            if(!InsertAVL(T->rchild,e,taller))
                return 0;
            if(taller)
            switch(T->bf)
            {
                case LH:
                    T->bf=EH;
                    taller=false;
                    break;
                case EH:
                    T->bf=RH;
                    taller=true;
                    break;
                case RH://原本右子树比左子树高，需要平衡化处理 
                    RightBalance(T);
                    taller=false;
                    break;
            }
        }
    }
    return true;
}
 
bool SearchBST(BSTree &T,int key)
{
    if(!T)
        return false;
    else if(key==T->data)
        return true;
    else if(key<T->data)
        return SearchBST(T->lchild,key);
    else
        return SearchBST(T->rchild,key);
}
 
void LeftBalance_div(BSTree &p,int &shorter)
{
    BSTree  p1,p2;
    if(p->bf==1)
    {
        p->bf=0;
        shorter=1;
    }
    else if(p->bf==0)
    {
        p->bf=-1;
        shorter=0;
    }
    else
    {
        p1=p->rchild;
        if(p1->bf==0)
        {
            L_Rotate(p);
            p1->bf=1;
            p->bf=-1;
            shorter=0;
        }
        else if(p1->bf==-1)
        {
            L_Rotate(p);
            p1->bf=p->bf=0;
            shorter=1;
        }
        else
        {
            p2=p1->lchild;
            p1->lchild=p2->rchild;
            p2->rchild=p1;
            p->rchild=p2->lchild;
            p2->lchild=p;
            if(p2->bf==0)
            {
                p->bf=0;
                p1->bf=0;
            }
            else if(p2->bf==-1)
            {
                p->bf=1;
                p1->bf=0;
            }
            else
            {
                p->bf=0;
                p1->bf=-1;
            }
            p2->bf=0;
            p=p2;
            shorter=1;
        }
    }
}
 
void RightBalance_div(BSTree &p,int &shorter)
{
    BSTree  p1,p2;
    if(p->bf==-1)
    {
        p->bf=0;
        shorter=1;
    }
    else if(p->bf==0)
    {
        p->bf=1;
        shorter=0;
    }
    else
    {
        p1=p->lchild;
        if(p1->bf==0)
        {
            R_Rotate(p);
            p1->bf=-1;
            p->bf=1;
            shorter=0;
        }
        else if(p1->bf==1)
        {
            R_Rotate(p);
            p1->bf=p->bf=0;
            shorter=1;
        }
        else
        {
            p2=p1->rchild;
            p1->rchild=p2->lchild;
            p2->lchild=p1;
            p->lchild=p2->rchild;
            p2->rchild=p;
            if(p2->bf==0)
            {
                p->bf=0;
                p1->bf=0;
            }
            else if(p2->bf==1)
            {
                p->bf=-1;
                p1->bf=0;
            }
            else
            {
                p->bf=0;
                p1->bf=1;
            }
            p2->bf=0;
            p=p2;
            shorter=1;
        }
    }
}
 
void Delete(BSTree q,BSTree  &r,int &shorter)
{
    if(r->rchild==NULL)
    {
        q->data=r->data;
        q=r;
        r=r->lchild;
        free(q);
        shorter=1;
    }
    else
    {
        Delete(q,r->rchild,shorter);
        if(shorter==1)
            RightBalance_div(r,shorter);
    }
}
 
int DeleteAVL(BSTree &p,int x,int &shorter)
{
    int k;
    BSTree q;
    if(p==NULL)
    {
        printf("不存在要删除的关键字!\n");
        return 0;
    }
    else if(x<p->data)
    {
        k=DeleteAVL(p->lchild,x,shorter);
        if(shorter==1)//树变矮 
            LeftBalance_div(p,shorter);
        return k;
    }
    else if(x>p->data)
    {
        k=DeleteAVL(p->rchild,x,shorter);
        if(shorter==1)
            RightBalance_div(p,shorter);
        return k;
    }
    else
    {
        q=p;
        if(p->rchild==NULL)
        {
            p=p->lchild;
            free(q);
            shorter=1;
        }
        else if(p->lchild==NULL)
        {
            p=p->rchild;
            free(q);
            shorter=1;
        }
        else
        {
            Delete(q,q->lchild,shorter);
            if(shorter==1)
                LeftBalance_div(p,shorter);
            p=q;
        }
       return 1;
    }
}
 
void PrintBST(BSTree T,int depth)
{
    int i;
        if(T->rchild)
            PrintBST(T->rchild,depth+1);
        for(i=1;i<=depth;i++)
            printf("     ");
        printf("%d\n",T->data);
        if(T->lchild)
            PrintBST(T->lchild,depth+1);
}
