#include <stdio.h>
#include <stdlib.h>

#define OK 1
#define ERROR 0

typedef int Status;

typedef struct LNode
{
	struct LNode *next;
	int operate; 
}LNode;

typedef struct ListInfo
{
	LNode *head;
	LNode *tail;
	int operateNumber;
	int AppleNumber; //ƻ������ 
	int AppleOffTreeNum;//�Ƿ����ƻ�� 
}ListInfo;//һ��ƻ���������� 

Status CreateList(ListInfo &L)
{
	L.head = (LNode *) malloc(sizeof(LNode));
	if(L.head == NULL) exit(ERROR);
	L.head->next = NULL;
	L.tail = L.head;
	int m;
	scanf("%d", &m);
	for(int i=1; i<=m; i++)
	{
		LNode *p = (LNode *) malloc(sizeof(LNode));
		if(p == NULL) exit(ERROR);
		scanf("%d", &p->operate);
		p->next = NULL;
		L.tail->next = p;
		L.tail = p;
	}
	L.AppleNumber = 0;
	L.AppleOffTreeNum = 0;
	L.operateNumber = m;
	return OK;
}

Status Operation(ListInfo &L)//��ÿһ��ƻ�����Ĳ���
{
	LNode *p = L.head->next;
	while(p != NULL)//����ÿһ����� 
	{
		if(p->operate > 0)//������0 
		{
			if(p == L.head->next)//���ǵ�һ����� 
				L.AppleNumber += p->operate;//ֱ�Ӹ�ֵ��ƻ������ 
			else
			{
				if(p->operate < L.AppleNumber)// �����ǵ�һ����㣬�ұ�ƻ�������� 
				{
					//˵��������ƻ�������������ֵΪ1������ƻ��������ֵΪ��ǰ���� 
					L.AppleOffTreeNum = 1;
					L.AppleNumber = p->operate;
				}
			}
		}
		
		else//��С��0����ƻ���������� 
			L.AppleNumber += p->operate;
		 
		p = p->next;//��һ����� 
	}
	return OK;
}

int main()
{
	int N, T = 0, D = 0, E = 0, i;
	scanf("%d", &N);
	ListInfo L[N];//����N������ 
	for(i=1; i<=N; i++)
	{
		CreateList(L[i]);
		Operation(L[i]);
		T += L[i].AppleNumber; //ÿһ��ƻ������ƻ���������ۼ� 
		D += L[i].AppleOffTreeNum;//����ƻ����ƻ�����Ŀ����ۼ� 
	}
	
	//�����������������������
	//1��ֻ������ͷ��β��������������  
	for(i=2; i<=N-1; i++)
		if(L[i-1].AppleOffTreeNum + L[i].AppleOffTreeNum + L[i+1].AppleOffTreeNum == 3)
			E += 1;
	//2������ͷ��β������������ 
	if(L[N].AppleOffTreeNum + L[1].AppleOffTreeNum + L[2].AppleOffTreeNum == 3)
		E += 1;
	if(L[N-1].AppleOffTreeNum + L[N].AppleOffTreeNum + L[1].AppleOffTreeNum == 3)
		E += 1;
		
	printf("%d %d %d", T, D, E);
	
	return 0;
}
