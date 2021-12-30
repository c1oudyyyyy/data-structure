/*
ʹ����map��������������ȡ��ĳ���ַ�����ʱ���Ӧ�����Ҫ������ݡ�
���ı��ı����в�������ȡ�ı��е������Լ���Ӧ��ֵ����map�С� 
*/ 

#include <iostream>
#include <stdio.h>
#include <string>
#include <string.h>
#include <map>
 
using namespace std;
 
int n, m;
string s, key;
char *s1 = new char[1024], *key1;
map<string, string> json;
int state;

void handle(string &s)
{
    for(int i = 0; s[i]; i++)
	{
        if(s[i] == '{')
		{
            if(state == 0)//��һ�� 
			{
                key = "";
            }
			else//����Ϊ���� 
			{
                json[key] = "OBJECT";
            }
            state = 1;//��� 
        }
		else if(s[i] == '}')
		{
            key = "";
        }
		if(s[i] == ':')
		{
            state = 2;//��� 
        }
		if(s[i] == ',')
		{
            state = 1;//��� 
        }
		if(s[i] == '"')// ˫����
		{  
            string tmp;//��ʱ�ַ��� 
            for(i++; s[i]; i++)
			{
                if(s[i] == '\\')
                    tmp += s[++i];
                else if(s[i] == '"')
                    break;
                else
                    tmp += s[i];
            }
            if(state == 1)//��һ���ַ��Ƕ��� 
			{
                if(key == "")
                    key = tmp;
                else//������Ԫ�� 
                    key += '.' + tmp;
                state = 2;
            }
			else if(state == 2)//��һ���ַ���ð�� 
			{
                json[key] = "STRING " + tmp;
                int j;
                for(j = (int)key.size() - 1; j >= 0; j--)
				{
                    if(key[j] == '.')
                        break;
                }
                if(j >= 0)
                    key = key.substr(0, j);
                else
                    key = "";
                state = 1;
            }
        }
    }
}
 
int main()
{
	FILE *fp = fopen("13.txt", "r");
	if(!fp)
	{
		cout << "�ļ���ʧ�ܣ�" << endl;
		exit(0);
	}
    fscanf(fp, "%d %d", &n, &m);
 	fgets(s1, 1024, fp);	
 	int i = strlen(s1);
	s1[strlen(s1) - 1] = '\0';
	s = s1;
    state = 0;
    while(n--)//��ȡ���� 
	{
 		fgets(s1, 1024, fp);	
 		int i = strlen(s1);
		s1[strlen(s1) - 1] = '\0';
		s = s1;
        handle(s);
    }
 
    while(m--)//��ȡ���� 
	{
        fgets(s1, 1024, fp);
        if(m == 0)
        {
        	s = s1;
        	cout << (json[s] == "" ? "NOTEXIST" : json[s]) << endl;
        	continue;
		}
 		int i = strlen(s1);
		s1[strlen(s1) - 1] = '\0';
		s = s1;
        cout << (json[s] == "" ? "NOTEXIST" : json[s]) << endl;
    }
 
    return 0;
}
 
