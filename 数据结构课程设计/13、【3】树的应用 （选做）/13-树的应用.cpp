/*
使用了map关联容器，当读取到某个字符串的时候对应输出所要求的内容。
对文本的标点进行操作，截取文本中的属性以及对应的值存在map中。 
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
            if(state == 0)//第一行 
			{
                key = "";
            }
			else//否则为对象 
			{
                json[key] = "OBJECT";
            }
            state = 1;//标记 
        }
		else if(s[i] == '}')
		{
            key = "";
        }
		if(s[i] == ':')
		{
            state = 2;//标记 
        }
		if(s[i] == ',')
		{
            state = 1;//标记 
        }
		if(s[i] == '"')// 双引号
		{  
            string tmp;//临时字符串 
            for(i++; s[i]; i++)
			{
                if(s[i] == '\\')
                    tmp += s[++i];
                else if(s[i] == '"')
                    break;
                else
                    tmp += s[i];
            }
            if(state == 1)//上一个字符是逗号 
			{
                if(key == "")
                    key = tmp;
                else//对象内元素 
                    key += '.' + tmp;
                state = 2;
            }
			else if(state == 2)//上一个字符是冒号 
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
		cout << "文件打开失败！" << endl;
		exit(0);
	}
    fscanf(fp, "%d %d", &n, &m);
 	fgets(s1, 1024, fp);	
 	int i = strlen(s1);
	s1[strlen(s1) - 1] = '\0';
	s = s1;
    state = 0;
    while(n--)//读取数据 
	{
 		fgets(s1, 1024, fp);	
 		int i = strlen(s1);
		s1[strlen(s1) - 1] = '\0';
		s = s1;
        handle(s);
    }
 
    while(m--)//读取问题 
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
 
