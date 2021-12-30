/*
使用孩子兄弟二叉树，存储每个人的信息 
在孩子兄弟二叉树的基础上在每个树结点增加一个指向父亲的指针，用于寻找该孩子的父亲。
*/ 

#include<iostream>
#include<string.h> 
#include<stdlib.h>
#include<stdio.h>
#include<fstream>
#include<cstring>
#include <iomanip>
#define MAXSIZE 10
#define INFINITY 65535
#define LOCAL

using namespace std;
fstream fp;
typedef struct TNode//树结点信息 
{
	struct TNode *child;//孩子 
	struct TNode *brother;//兄弟 
	struct TNode *parent;//父亲 
	
	char Name[20];
	int Year,Month,Day;
	int Marry;
	char Located[100];
	int Death;
	int DYear,DMonth,DDay;
	int Level; 
} TNode,*Tree;
void InitTree( Tree &T)
{
	T=(TNode *)malloc (sizeof (TNode));
	T->child=NULL;
	T->brother=NULL;
	T->Level=1;
}
void CreateTree( Tree &T)//建立家谱树（先序创建） 
{
	char name[20];
	char b[20]={"#"};
	fp>>name;
	if(strcmp(name,b)==0) 
	{
		T=NULL;
	}
	else
	{
		if(!T) exit(1);
		strcpy(T->Name,name);
		int year,month,day;
		fp>>year>>month>>day;
		T->Year=year;
		T->Month=month;
		T->Day=day;
		int marry;
		fp>>marry; 
		T->Marry=marry;
		char locate[100];
		fp>>locate;
		strcpy(T->Located,locate);
		int death;
		fp>>death;
		T->Death=death;
		if(death)
		{	
			fp>>year>>month>>day;
			T->DYear=year;
			T->DMonth=month;
			T->DDay=day;
		}
		InitTree(T->brother);
		T->brother->Level=T->Level;
		T->brother->parent=T->parent;
		CreateTree(T->brother);
		InitTree(T->child);
		T->child->parent=T;
		T->child->Level=T->Level+1;
		CreateTree(T->child);
		}
}
TNode *FindNodeName(Tree T,char name[20])//寻找对应名字的结点 
{
	TNode *p = NULL;
	if(T == NULL)
	{
		return NULL;
	}
	else if(strcmp(name,T->Name)==0)
	{
		return T;
	}
	else 
	{
		p=FindNodeName(T->child,name);
		if(p==NULL)
		{
			return (FindNodeName(T->brother,name));
		}
		else return p;
	}
}
void Imformation(Tree T)//输出信息 
{
	cout<<T->Name<<'\t'<<T->Year<<" "<<T->Month<<" "<<T->Day<<'\t'<<T->Marry<<'\t'<<T->Located<<'\t'<<T->Death<<'\t';
	if(T->Death==1)
	cout<<T->DYear<<'\t'<<T->DMonth<<'\t'<<T->DDay<<endl;
	else cout<<endl;
}
void FindNodeBirth(Tree T,int year,int month,int day)//寻找对应生日结点 
{
	if(T!=NULL)
	{	
		if(T->Year==year and T->Month==month and T->Day==day)
		Imformation(T);
		FindNodeBirth(T->brother,year,month,day);
		FindNodeBirth(T->child,year,month,day);
	}
}
void OutPut(Tree T,int i)//显示家谱树 
{
	if(T!=NULL)
	{
		for(int n=0;n<i;n++)
		cout<<'\t';
		cout<<T->Name;
		if(T->child!=NULL)
		cout<<endl;
		OutPut(T->child,i+1);
		if(T->brother!=NULL)
		cout<<endl;
		OutPut(T->brother,i);
	}
}
void OutNum(Tree T,int n)//输出第n代人； 
{
	if(T!=NULL)
	{	
		if(T->Level==n)
		Imformation(T);
		OutNum(T->brother,n);
		OutNum(T->child,n);
	}	
}
void RelationShip(TNode *p,TNode *q)//判断关系 
{
	if(p->Level<q->Level)
		cout<<p->Name<<"是"<<q->Name<<"的长辈"<<endl;
	else if(p->Level==q->Level)
		cout<<p->Name<<"和"<<q->Name<<"是一辈人"<<endl;
	else if(p->Level>q->Level)
		cout<<p->Name<<"是"<<q->Name<<"的晚辈"<<endl;
}
void CreateChild(Tree &C)//新添加孩子的信息 
{
	InitTree(C);
	cout<<"请输入孩子的姓名，出生日期:"<<endl;
	char name[20];
	char a[20];
	scanf("%c%[^\n]",&a,name);
	strcpy(C->Name,name);
	int year,month,day;
	cin>>year>>month>>day;
	C->Year=year;
	C->Month=month;
	C->Day=day;
	
}
void AddNumber(Tree &T,TNode *p)//添加成员 
{
	TNode *q;
	q=p;
	Tree C;
	CreateChild(C);
	if(p->child==NULL)
	{	
		p->child=C;
		C->parent=p;
		C->Level=p->Level+1;
		strcpy(C->Located,p->Located);
	}
	else 
	{
		p=p->child;
		while(p->brother!=NULL)
		{
			p=p->brother;
		}
		p->brother=C;
		C->parent=q;
		C->Level=p->Level;
		strcpy(C->Located,q->Located);
	}
	cout<<"已完成"<<endl;
}
Tree DestoryTree(Tree &T)
{
	if(T)
	{
		T->child =DestoryTree(T->child);
		T->brother=DestoryTree(T->brother);
		T=NULL;
	}
}
void Alter(Tree &T,TNode *p)//修改成员信息 
{
	cout<<"请输入修改信息:"<<endl;
	cout<<"姓名:" ;
	char name[20];
	char a[20];
	scanf("%c%[^\n]",&a,name);
	strcpy(p->Name,name);
	cout<<"出生日期:";
	int year,month,day;
	cin>>year>>month>>day;
	p->Year=year;
	p->Month=month;
	p->Day=day;
	cout<<"婚姻情况:";
	int marry;
	cin>>marry;
	p->Marry=marry;
	cout<<"住址:";
	char locate[20];
	scanf("%c%[^\n]",&a,locate);
	strcpy(T->Located,locate);
	int death;
	cout<<"是否去世:";
	cin>>death;
	T->Death=death;
	if(death==1)
	{
		cout<<"死亡日期:";
		cin>>year>>month>>day;
		T->DYear=year;
		T->DMonth=month;
		T->DDay=day;
	}
	
}
int main()
{
	Tree T;
	int i=INFINITY;
	cout<<"请选择需要的操作："<<endl;
	cout<<"1：创建家谱。"<<endl;
	cout<<"2：显示家谱。"<<endl;
	cout<<"3：显示第n代人的信息"<<endl;
	cout<<"4：按照姓名查询，输出成员信息。"<<endl;
	cout<<"5：按照出生日期查询成员名单。"<<endl;
	cout<<"6：输入两人姓名，确定其关系。"<<endl;
	cout<<"7：某成员添加孩子。"<<endl;
	cout<<"8：删除某成员。"<<endl;
	cout<<"9：修改某成员信息。"<<endl;
	cout<<"0：退出程序"<<endl;
	while(i)
	{
		cin>>i;
		switch(i)
		{
			case 1:
				fp.open("family.txt");
				InitTree (T);
				T->parent=NULL;
				CreateTree(T);
				fp.close();
				cout<<"家谱已创建完成"<<endl;
				break;
			case 2:
				OutPut(T,1);
				cout<<endl;
				break;
			case 3:
				int n;
				cout<<"请选择需要输出第几代人:";
				cin>>n;
				cout<<"姓名"<<'\t'<<"生日"<<'\t'<<"   婚姻情况"<<'\t'<<"住址"<<'\t'<<"是否去世"<<'\t'<<"死亡日期"<<endl; 
				OutNum(T,n);
				cout<<"该代人的信息已输出"<<endl; 
				break;
			case 4:
				cout<<"请输入查找的人名";
				char name[20];
				char a[20];
				scanf("%c%[^\n]",&a,name);
				TNode *p,*q;
				p=new TNode;
				q=new TNode;
				p=FindNodeName(T,name);
				cout<<"姓名"<<'\t'<<"生日"<<'\t'<<"   婚姻情况"<<'\t'<<"住址"<<'\t'<<"是否去世"<<'\t'<<"死亡日期"<<endl;
				Imformation(p);
				q=p->child;
				cout<<"孩子信息为："<<endl;
				while(q!=NULL)
				{	
					Imformation(q);
					q=q->brother;
				}
				q=p->parent;
				cout<<"父亲信息为:"<<endl;
				Imformation(q);
				break;
			case 5:
				cout<<"请输入需要查找的人的生日:"<<endl;
				int y,m,d;
				cin>>y>>m>>d;
				cout<<"姓名"<<'\t'<<"生日"<<'\t'<<"   婚姻情况"<<'\t'<<"住址"<<'\t'<<"是否去世"<<'\t'<<"死亡日期"<<endl;
				FindNodeBirth(T,y,m,d);
				break;
			case 6:
				cout<<"请输入需查找的两个人的姓名："<<endl;
				char N1[20];
				char N2[20];
				scanf("%c%[^\n]",&a,N1);
				scanf("%c%[^\n]",&a,N2);
				p=FindNodeName(T,N1);
				q=FindNodeName(T,N2);
				RelationShip(p,q);
				break;
			case 7:
				cout<<"请选择新增加孩子的成员:"<<endl;
				scanf("%c%[^\n]",&a,name);
				p=FindNodeName(T,name);
				AddNumber(T,p);
				break;
			case 8:
				cout<<"请选择需删除的成员:"<<endl;
				scanf("%c%[^\n]",&a,name);
				p=FindNodeName(T,name);
				q=p->parent;
				if(q->child==p)
				{
				DestoryTree(p->child);
				p->parent->child=p->brother;
				free(p);	
				}
				else 
				{
					TNode *x;
					x=new TNode;
					x=q->child;
					while(x->brother!=p)
					{
						
						x=x->brother;
					}
					x->brother=p->brother;
					DestoryTree(p->child);
					free(p);
				}
					
				break;
			case 9:
				cout<<"请选择需要修改信息的成员:"<<endl;
				scanf("%c%[^\n]",&a,name);
				p=FindNodeName(T,name);
				Alter(T,p);
				break;
			case 0:
				break;
		}
		
	}
 } 
