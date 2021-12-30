#include <stdio.h>
#include <windows.h>
typedef int Status;
 
typedef struct BusInfo 
{
    int No;        //�ù������ı��
    int passStationNum;     //�ù�����������վ������
    int line[80]; //�ù�������·��
} Bus;
typedef struct StationInfo 
{
    short int bus[35]; //������վ��Ĺ������ı��
    int passBusNum;         //������վ��Ĺ���������
    char name[60];     //վ������
} Station;
typedef struct Map
{
    Bus bus[1000];          //�ó��еĹ�����
    Station station[10000]; //�ó��е�վ��
    int busNum;           //����������
    int stationNum;       //վ������
} Map;
typedef struct element//����Ԫ�� 
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

Status LeastTransfers(Map &M, char name_1[60], char name_2[60]);//����ת�� 
Status TraversalSite_CD(Map &M, int v1, int v2);

Status LeastSite(Map &M, char name_1[60], char name_2[60]);//����վ�� 
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
        printf("��ӭʹ���Ͼ�������·��ѯϵͳ(��Ҫ�˳�ϵͳ,�������˳�)\n");
        printf("���������:");
        scanf("%s", name_1);
        if (strcmp(name_1, "�˳�") == 0)
            break;
        if (!locate_station(M, name_1))
        {
            printf("δ�ҵ���վ��!\n");
            system("pause");
            continue;
        }
        printf("�������յ�:");
        scanf("%s", name_2);
        if (strcmp(name_2, "�˳�") == 0)
            break;
        if (!locate_station(M, name_2))
        {
            printf("δ�ҵ���վ��!\n");
            system("pause");
            continue;
        }
        printf("\n����վ��·��\n");
        LeastSite(M, name_1, name_2);
        printf("\n����ת��·��\n");
        LeastTransfers(M, name_1, name_2);
        system("pause");
    }
    system("pause");
    return 0;
}
//�󾭹�վ������ ���ù�����ȱ����㷨���ж�������漰��ÿ�����������������ǰ���վ�㣬
//������յ㣬�򾭹�վ�����١�
//�����յ㣬����������漰��ÿ�����������������ǰ���վ�������У�
//ͨ��Visited�����жϸ�վ���Ƿ��Ѿ����ʹ���
//����Ԫ�س��ӣ������жϸõ����漰��ÿ�������������ĸõ�ǰ���վ�㣬
//�ظ����ϲ��裬ֱ���ҵ������յ㡣 
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
    int count = 1;//ͳ��վ���� 
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
            //�жϸ�վ��ǰ�������վ���Ƿ����յ㣬������ó�����վ��·�� 
            for (int i = 1; i <= M.station[v1].passBusNum; i++)
            {
                int bus1 = locate_bus(M, M.station[v1].bus[i]);//v1������վ��Ĺ�������� 
                for (int j = 1; j <= M.bus[bus1].passStationNum; j++)
                {
                    if (M.bus[bus1].line[j] == v1)//�ù�����·������v1 
                    {
                        if (M.bus[bus1].line[j + 1] == v2 || M.bus[bus1].line[j - 1] == v2)//�ҵ�·�� 
                        {
                            int bus = e[v1].bus;
                            printf("���پ���%d��վ��\n", count);
                            printf("%s(���,����%d·������)-->", M.station[v2].name, M.bus[bus1].No);
                            count--;
                            while (count--)
                            {
                                if (count == 0)
                                    printf("%s(�յ�)\n\n", M.station[v1].name);
                                else
                                    printf("%s(����%d·������)-->", M.station[v1].name, bus);
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
//��ת���������� ���ù�����ȱ����㷨���ж�������漰��ÿ������������������վ�㣬������յ㣬������ת����
//�����յ㣬����������漰��ÿ������������������վ�������У�ͨ��Visited�����жϸ�վ���Ƿ��Ѿ����ʹ���
//����Ԫ�س��ӣ������жϸõ����漰��ÿ������������������վ�㣬
//�ظ����ϲ��裬ֱ���ҵ������յ㡣 
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
            //�жϵ�ǰ·�����Ƿ����յ� 
            for (int i = 1; i <= M.station[v1].passBusNum; i++)
            {
                int bus1 = locate_bus(M, M.station[v1].bus[i]);
                for (int j = 1; j <= M.bus[bus1].passStationNum; j++)
                {
                    if (M.bus[bus1].line[j] == v2)//�ҵ�·�� 
                    {
                        int bus2;
                        bus2 = locate_bus(M, e[v1].bus);
                        printf("����ת%d�γ�\n", count - 1);
                        printf("%s(���,����%d·������)-->", M.station[v2].name, M.station[v1].bus[i]);
                        --count;
                        while (count--)
                        {
                            if (count == 0)
                                printf("%s(�յ�)\n\n", M.station[v1].name);
                            else
                                printf("%s(����%d·������)-->", M.station[v1].name, M.bus[bus2].No);
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
    M.station[index].bus[++M.station[index].passBusNum] = M.bus[M.busNum].No;//������վ��Ĺ�������� 
    for (int i = 0; i < 60; i++)//����ַ��� 
    {
        temp[i] = '\0';
    }
    return index;
}
int locate_station(Map &M, char name[60])//��ȡվ���� 
{
    for (int i = 1; i <= M.stationNum; i++)
    {
        if (strcmp(M.station[i].name, name) == 0)
            return i;
    }
    return 0;
}
int locate_bus(Map &M, int No)//��ȡ��������� 
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
        printf("%d·\t", M.bus[i].No);
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
    char temp[60];//�洢��һ���ַ� 
    char ch;
    FILE *fp;
    if ((fp = fopen("�Ͼ�������·.txt", "r")) == NULL)
    {
        printf("�޷������ļ���\n");
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
        if (feof(fp))//��ȡ�����һ��·�� 
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
    QueuePtr p = (QueuePtr)malloc(sizeof(QNode)); //�����½��
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
        printf("ջ��");
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
