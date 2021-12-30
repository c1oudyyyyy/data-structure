#include <stdio.h>
#include <windows.h>
typedef int Status;
 
typedef struct BusInfo 
{
    int No;        //该公交车的编号
    int passStationNum;     //该公交车经过的站点数量
    int line[80]; //该公交车的路线
} Bus;
typedef struct StationInfo 
{
    short int bus[35]; //经过该站点的公交车的编号
    int passBusNum;         //经过该站点的公交车数量
    char name[60];     //站点名称
} Station;
typedef struct Map
{
    Bus bus[1000];          //该城市的公交车
    Station station[10000]; //该城市的站点
    int busNum;           //公交车数量
    int stationNum;       //站点数量
} Map;
typedef struct element//队列元素 
{
    int bus;
    int before;
    int cur;
} element;
typedef struct QNode
{
    element data;
    QNode *next;
} QNode, *QueuePtr;
typedef struct
{
    QueuePtr front;
    QueuePtr rear;
} LinkQueue;
 
Status InitQueue(LinkQueue &Q);
Status EnQueue(LinkQueue &Q, element e);
element DeQueue(LinkQueue &Q); 
Status GetMap(Map &M);
Status InitMap(Map &M);
int locate_station(Map &M, char name[30]);
int locate_bus(Map &M, int No);
Status GetBusStation(Map &M, char temp[60]);

Status LeastTransfers(Map &M, char name_1[60], char name_2[60]);//最少转车 
Status TraversalSite_CD(Map &M, int v1, int v2);

Status LeastSite(Map &M, char name_1[60], char name_2[60]);//最少站点 
Status TraversalSite_AD(Map &M, int v1, int v2);

void Print(Map M);
int visited[10000] = {0};
int main()
{
    Map M;
    InitMap(M);
    GetMap(M);
    while (1)
    {
        system("cls");
        char name_1[60], name_2[60];
        printf("欢迎使用南京公交线路查询系统(如要退出系统,请输入退出)\n");
        printf("请输入起点:");
        scanf("%s", name_1);
        if (strcmp(name_1, "退出") == 0)
            break;
        if (!locate_station(M, name_1))
        {
            printf("未找到该站点!\n");
            system("pause");
            continue;
        }
        printf("请输入终点:");
        scanf("%s", name_2);
        if (strcmp(name_2, "退出") == 0)
            break;
        if (!locate_station(M, name_2))
        {
            printf("未找到该站点!\n");
            system("pause");
            continue;
        }
        printf("\n最少站数路线\n");
        LeastSite(M, name_1, name_2);
        printf("\n最少转车路线\n");
        LeastTransfers(M, name_1, name_2);
        system("pause");
    }
    system("pause");
    return 0;
}
//求经过站数最少 采用广度优先遍历算法，判断起点所涉及的每辆公交车经过的起点前后的站点，
//如果是终点，则经过站数最少。
//若无终点，则让起点所涉及的每辆公交车经过的起点前后的站点进入队列，
//通过Visited数组判断该站点是否已经访问过。
//队列元素出队，继续判断该点所涉及的每辆公交车经过的该点前后的站点，
//重复以上步骤，直至找到所需终点。 
Status LeastSite(Map &M, char name_1[60], char name_2[60])
{
    int v1 = locate_station(M, name_1);
    for (int i = 1; i < 10000; i++)
    {
        visited[i] = 0;
    }
    int v2 = locate_station(M, name_2);
    TraversalSite_AD(M, v2, v1);
}
Status TraversalSite_AD(Map &M, int v1, int v2)
{
    element e[8000];
    for (int i = 1; i < 8000; i++)
    {
        e[i].cur = i;
        e[i].bus = 0;
    }
    element e0;
    int count = 1;//统计站点数 
    LinkQueue Q;
    InitQueue(Q);
    EnQueue(Q, e[v1]);
    visited[v1] = 1;
    while (1)
    {
        int k = 1;
        count++;
        e0.cur = -1;
        EnQueue(Q, e0);
        while (Q.front != Q.rear)
        {
            v1 = DeQueue(Q).cur;
            if (v1 == -1)
                break;
            //判断该站点前后的所有站点是否有终点，若有则得出最少站点路线 
            for (int i = 1; i <= M.station[v1].passBusNum; i++)
            {
                int bus1 = locate_bus(M, M.station[v1].bus[i]);//v1经过的站点的公交车编号 
                for (int j = 1; j <= M.bus[bus1].passStationNum; j++)
                {
                    if (M.bus[bus1].line[j] == v1)//该公交车路线上有v1 
                    {
                        if (M.bus[bus1].line[j + 1] == v2 || M.bus[bus1].line[j - 1] == v2)//找到路线 
                        {
                            int bus = e[v1].bus;
                            printf("最少经过%d个站点\n", count);
                            printf("%s(起点,乘坐%d路公交车)-->", M.station[v2].name, M.bus[bus1].No);
                            count--;
                            while (count--)
                            {
                                if (count == 0)
                                    printf("%s(终点)\n\n", M.station[v1].name);
                                else
                                    printf("%s(乘坐%d路公交车)-->", M.station[v1].name, bus);
                                v1 = e[v1].before;
                                bus = e[v1].bus;
                            }
                            return 1;
                        }
 
                        if (!visited[M.bus[bus1].line[j - 1]] && j - 1 > 0)
                        {
                            e[M.bus[bus1].line[j - 1]].bus = M.bus[bus1].No;
                            e[M.bus[bus1].line[j - 1]].before = v1;
                            EnQueue(Q, e[M.bus[bus1].line[j - 1]]);
                            visited[M.bus[bus1].line[j - 1]] = 1;
                        }
                        if (!visited[M.bus[bus1].line[j + 1]] && j + 1 <= M.bus[bus1].passStationNum)
                        {
                            e[M.bus[bus1].line[j + 1]].bus = M.bus[bus1].No;
                            e[M.bus[bus1].line[j + 1]].before = v1;
                            EnQueue(Q, e[M.bus[bus1].line[j + 1]]);
                            visited[M.bus[bus1].line[j + 1]] = 1;
                        }
                        break;
                    }
                }
            }
        }
    }
}
//求转车次数最少 采用广度优先遍历算法，判断起点所涉及的每辆公交车经过的所有站点，如果有终点，则无需转车。
//若无终点，则让起点所涉及的每辆公交车经过的所有站点进入队列，通过Visited数组判断该站点是否已经访问过。
//队列元素出队，继续判断该点所涉及的每辆公交车经过的所有站点，
//重复以上步骤，直至找到所需终点。 
Status LeastTransfers(Map &M, char name_1[60], char name_2[60])
{
    int v1 = locate_station(M, name_1);
    for (int i = 1; i < 10000; i++)
    {
        visited[i] = 0;
    }
    int v2 = locate_station(M, name_2);
    TraversalSite_CD(M, v2, v1);
}
Status TraversalSite_CD(Map &M, int v1, int v2)
{
    element e[8000];
    for (int i = 1; i < 8000; i++)
    {
        e[i].cur = i;
        e[i].bus = 0;
    }
    element e0;
    int count = 1;
    LinkQueue Q;
    InitQueue(Q);
    EnQueue(Q, e[v1]);
    visited[v1] = 1;
    while (1)
    {
        int k = 1;
        count++;
        e0.cur = -1;
        EnQueue(Q, e0);
        while (Q.front != Q.rear)
        {
            v1 = DeQueue(Q).cur;
            if (v1 == -1)
                break;
            //判断当前路线中是否有终点 
            for (int i = 1; i <= M.station[v1].passBusNum; i++)
            {
                int bus1 = locate_bus(M, M.station[v1].bus[i]);
                for (int j = 1; j <= M.bus[bus1].passStationNum; j++)
                {
                    if (M.bus[bus1].line[j] == v2)//找到路线 
                    {
                        int bus2;
                        bus2 = locate_bus(M, e[v1].bus);
                        printf("最少转%d次车\n", count - 1);
                        printf("%s(起点,乘坐%d路公交车)-->", M.station[v2].name, M.station[v1].bus[i]);
                        --count;
                        while (count--)
                        {
                            if (count == 0)
                                printf("%s(终点)\n\n", M.station[v1].name);
                            else
                                printf("%s(换乘%d路公交车)-->", M.station[v1].name, M.bus[bus2].No);
                            v1 = e[v1].before;
                            bus2 = locate_bus(M, e[v1].bus);
                        }
                        return 1;
                    }
                    if (!visited[M.bus[bus1].line[j]])
                    {
                        e[M.bus[bus1].line[j]].bus = M.bus[bus1].No;
                        e[M.bus[bus1].line[j]].before = v1;
                        EnQueue(Q, e[M.bus[bus1].line[j]]);
                        visited[M.bus[bus1].line[j]] = 1;
                    }
                }
            }
        }
    }
}
Status GetBusStation(Map &M, char temp[60])
{
    int index = locate_station(M, temp);
    if (!index)
    {
        strcpy(M.station[++M.stationNum].name, temp);
        index = M.stationNum;
    }
    M.bus[M.busNum].line[M.bus[M.busNum].passStationNum] = index;
    M.station[index].bus[++M.station[index].passBusNum] = M.bus[M.busNum].No;//经过该站点的公交车编号 
    for (int i = 0; i < 60; i++)//清空字符串 
    {
        temp[i] = '\0';
    }
    return index;
}
int locate_station(Map &M, char name[60])//获取站点编号 
{
    for (int i = 1; i <= M.stationNum; i++)
    {
        if (strcmp(M.station[i].name, name) == 0)
            return i;
    }
    return 0;
}
int locate_bus(Map &M, int No)//获取公交车编号 
{
    for (int i = 1; i <= M.busNum; i++)
    {
        if (M.bus[i].No == No)
            return i;
    }
    return 0;
}
void Print(Map M)
{
    for (int i = 1; i <= M.busNum; i++)
    {
        printf("%d路\t", M.bus[i].No);
        for (int j = 1; j <= M.bus[i].passStationNum; j++)
        {
            printf("%s ", M.station[M.bus[i].line[j]].name);
        }
        printf("\n");
    }
}
Status InitMap(Map &M)
{
    M.busNum = 0;
    M.stationNum = 0;
    return 1;
    for (int i = 0; i < 1000; i++)
    {
        M.bus[i].passStationNum = 1;
    }
    for (int i = 0; i < 15000; i++)
    {
        M.station[i].passBusNum = 0;
    }
}
Status GetMap(Map &M)
{
    int k = 0;
    char temp[60];//存储上一个字符 
    char ch;
    FILE *fp;
    if ((fp = fopen("南京公交线路.txt", "r")) == NULL)
    {
        printf("无法代开文件！\n");
        exit(0);
    }
    for (int i = 1; i <= 1000; i++)
    {
        M.bus[i].passStationNum = 1;
    }
    fscanf(fp, "%d", &M.bus[++M.busNum].No);
    while (ch != ' ')
        ch = fgetc(fp);
    while (1)
    {
        ch = fgetc(fp);
        if (feof(fp))//读取到最后一条路线 
        {
            GetBusStation(M, temp);
            break;
        }
        if (ch == '\n')
        {
            GetBusStation(M, temp);
            k = 0;
            char ch2;
            ch2 = fgetc(fp);
            if (feof(fp))
                break;
            fseek(fp, -1L, 1);
            fscanf(fp, "%d", &M.bus[++M.busNum].No);
            while (ch != ' ')
                ch = fgetc(fp);
            continue;
        }
        if (ch == ' ')
            continue;
        if (ch == ',')
        {
            GetBusStation(M, temp);
            k = 0;
            M.bus[M.busNum].passStationNum++;
            continue;
        }
        temp[k++] = ch;
    }
    fclose(fp);
}
Status InitQueue(LinkQueue &Q)
{
    Q.front = (QueuePtr)malloc(sizeof(QNode));
    if (!Q.front)
        exit(-2);
    Q.front->next = NULL;
    Q.rear = Q.front;
    return true;
}
Status EnQueue(LinkQueue &Q, element e)
{
    QueuePtr p = (QueuePtr)malloc(sizeof(QNode)); //开辟新结点
    if (!p)
        exit(-2);
    p->data = e;
    p->next = NULL;
    Q.rear->next = p;
    Q.rear = p;
    return true;
}
element DeQueue(LinkQueue &Q)
{
    element e;
    if (Q.front == Q.rear)
    {
        printf("栈空");
        system("pause");
        exit(0);
    }
    QueuePtr p = Q.front->next;
    e = p->data;
    Q.front->next = p->next;
    if (Q.rear == p)
        Q.rear = Q.front;
    free(p);
    return e;
}
