/*
ʹ�ú����ֵܶ��������洢ÿ���˵���Ϣ 
�ں����ֵܶ������Ļ�������ÿ�����������һ��ָ���׵�ָ�룬����Ѱ�Ҹú��ӵĸ��ס�
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
typedef struct TNode//�������Ϣ 
{
	struct TNode *child;//���� 
	struct TNode *brother;//�ֵ� 
	struct TNode *parent;//���� 
	
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
void CreateTree( Tree &T)//���������������򴴽��� 
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
TNode *FindNodeName(Tree T,char name[20])//Ѱ�Ҷ�Ӧ���ֵĽ�� 
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
void Imformation(Tree T)//�����Ϣ 
{
	cout<<T->Name<<'\t'<<T->Year<<" "<<T->Month<<" "<<T->Day<<'\t'<<T->Marry<<'\t'<<T->Located<<'\t'<<T->Death<<'\t';
	if(T->Death==1)
	cout<<T->DYear<<'\t'<<T->DMonth<<'\t'<<T->DDay<<endl;
	else cout<<endl;
}
void FindNodeBirth(Tree T,int year,int month,int day)//Ѱ�Ҷ�Ӧ���ս�� 
{
	if(T!=NULL)
	{	
		if(T->Year==year and T->Month==month and T->Day==day)
		Imformation(T);
		FindNodeBirth(T->brother,year,month,day);
		FindNodeBirth(T->child,year,month,day);
	}
}
void OutPut(Tree T,int i)//��ʾ������ 
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
void OutNum(Tree T,int n)//�����n���ˣ� 
{
	if(T!=NULL)
	{	
		if(T->Level==n)
		Imformation(T);
		OutNum(T->brother,n);
		OutNum(T->child,n);
	}	
}
void RelationShip(TNode *p,TNode *q)//�жϹ�ϵ 
{
	if(p->Level<q->Level)
		cout<<p->Name<<"��"<<q->Name<<"�ĳ���"<<endl;
	else if(p->Level==q->Level)
		cout<<p->Name<<"��"<<q->Name<<"��һ����"<<endl;
	else if(p->Level>q->Level)
		cout<<p->Name<<"��"<<q->Name<<"����"<<endl;
}
void CreateChild(Tree &C)//����Ӻ��ӵ���Ϣ 
{
	InitTree(C);
	cout<<"�����뺢�ӵ���������������:"<<endl;
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
void AddNumber(Tree &T,TNode *p)//��ӳ�Ա 
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
	cout<<"�����"<<endl;
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
void Alter(Tree &T,TNode *p)//�޸ĳ�Ա��Ϣ 
{
	cout<<"�������޸���Ϣ:"<<endl;
	cout<<"����:" ;
	char name[20];
	char a[20];
	scanf("%c%[^\n]",&a,name);
	strcpy(p->Name,name);
	cout<<"��������:";
	int year,month,day;
	cin>>year>>month>>day;
	p->Year=year;
	p->Month=month;
	p->Day=day;
	cout<<"�������:";
	int marry;
	cin>>marry;
	p->Marry=marry;
	cout<<"סַ:";
	char locate[20];
	scanf("%c%[^\n]",&a,locate);
	strcpy(T->Located,locate);
	int death;
	cout<<"�Ƿ�ȥ��:";
	cin>>death;
	T->Death=death;
	if(death==1)
	{
		cout<<"��������:";
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
	cout<<"��ѡ����Ҫ�Ĳ�����"<<endl;
	cout<<"1���������ס�"<<endl;
	cout<<"2����ʾ���ס�"<<endl;
	cout<<"3����ʾ��n���˵���Ϣ"<<endl;
	cout<<"4������������ѯ�������Ա��Ϣ��"<<endl;
	cout<<"5�����ճ������ڲ�ѯ��Ա������"<<endl;
	cout<<"6����������������ȷ�����ϵ��"<<endl;
	cout<<"7��ĳ��Ա��Ӻ��ӡ�"<<endl;
	cout<<"8��ɾ��ĳ��Ա��"<<endl;
	cout<<"9���޸�ĳ��Ա��Ϣ��"<<endl;
	cout<<"0���˳�����"<<endl;
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
				cout<<"�����Ѵ������"<<endl;
				break;
			case 2:
				OutPut(T,1);
				cout<<endl;
				break;
			case 3:
				int n;
				cout<<"��ѡ����Ҫ����ڼ�����:";
				cin>>n;
				cout<<"����"<<'\t'<<"����"<<'\t'<<"   �������"<<'\t'<<"סַ"<<'\t'<<"�Ƿ�ȥ��"<<'\t'<<"��������"<<endl; 
				OutNum(T,n);
				cout<<"�ô��˵���Ϣ�����"<<endl; 
				break;
			case 4:
				cout<<"��������ҵ�����";
				char name[20];
				char a[20];
				scanf("%c%[^\n]",&a,name);
				TNode *p,*q;
				p=new TNode;
				q=new TNode;
				p=FindNodeName(T,name);
				cout<<"����"<<'\t'<<"����"<<'\t'<<"   �������"<<'\t'<<"סַ"<<'\t'<<"�Ƿ�ȥ��"<<'\t'<<"��������"<<endl;
				Imformation(p);
				q=p->child;
				cout<<"������ϢΪ��"<<endl;
				while(q!=NULL)
				{	
					Imformation(q);
					q=q->brother;
				}
				q=p->parent;
				cout<<"������ϢΪ:"<<endl;
				Imformation(q);
				break;
			case 5:
				cout<<"��������Ҫ���ҵ��˵�����:"<<endl;
				int y,m,d;
				cin>>y>>m>>d;
				cout<<"����"<<'\t'<<"����"<<'\t'<<"   �������"<<'\t'<<"סַ"<<'\t'<<"�Ƿ�ȥ��"<<'\t'<<"��������"<<endl;
				FindNodeBirth(T,y,m,d);
				break;
			case 6:
				cout<<"����������ҵ������˵�������"<<endl;
				char N1[20];
				char N2[20];
				scanf("%c%[^\n]",&a,N1);
				scanf("%c%[^\n]",&a,N2);
				p=FindNodeName(T,N1);
				q=FindNodeName(T,N2);
				RelationShip(p,q);
				break;
			case 7:
				cout<<"��ѡ�������Ӻ��ӵĳ�Ա:"<<endl;
				scanf("%c%[^\n]",&a,name);
				p=FindNodeName(T,name);
				AddNumber(T,p);
				break;
			case 8:
				cout<<"��ѡ����ɾ���ĳ�Ա:"<<endl;
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
				cout<<"��ѡ����Ҫ�޸���Ϣ�ĳ�Ա:"<<endl;
				scanf("%c%[^\n]",&a,name);
				p=FindNodeName(T,name);
				Alter(T,p);
				break;
			case 0:
				break;
		}
		
	}
 } 
