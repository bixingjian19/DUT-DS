//Kruskal�㷨
#include <iostream>
using namespace std;

//ͼ�����ִ洢�ṹ
#define INF 32767 //�����
#define MAXV 100  //��󶥵����
typedef char InfoType;

/*
TODO:����һ���ڽӾ���ṹ��,����һ����ԱΪint���ͱ���no����,
��һ��ΪInfoType���ͱ���info����Ϣ
*/
typedef struct
{
    int no;
    InfoType info;
} VertexType; //��������
/*
TODO:����һ��������ͼ�ڽӾ������ͽṹ��,
����һ����ԱΪ��СΪMAXV*MAXV�Ķ�άint����edges���ڽӾ���,
����int�ͱ���n,e�涨��������,һ����СΪMAXV��VertexType����vexs����Ϣ
*/
typedef struct
{
    int edges[MAXV][MAXV];
    int n;
    int e;
    VertexType vexs[MAXV];
} MatGraph; //������ͼ�ڽӾ�������

//------------------------------------------------------------
//----�ڽӾ���Ļ��������㷨----------------------------------
//------------------------------------------------------------
void CreateMat(MatGraph &g, int A[MAXV][MAXV], int n, int e) //����ͼ���ڽӾ���
{
    int i, j;
    g.n = n;
    g.e = e;
    for (i = 0; i < g.n; i++)
        for (j = 0; j < g.n; j++)
            g.edges[i][j] = A[i][j];
}
void DispMat(MatGraph g) //����ڽӾ���g
{
    int i, j;
    for (i = 0; i < g.n; i++)
    {
        for (j = 0; j < g.n; j++)
            if (g.edges[i][j] != INF)
                cout << g.edges[i][j] << ' ';
            else
                cout << "�� ";
        cout << endl;
    }
}

#define MaxSize 100
typedef struct
{
    int u; //�ߵ���ʼ����
    int v; //�ߵ���ֹ����
    int w; //�ߵ�Ȩֵ
} Edge;

void InsertSort(Edge E[], int n) //��E[0..n-1]�������������ֱ�Ӳ�������
{
    int i, j;
    Edge temp;
    for (i = 1; i < n; i++)
    {
        temp = E[i];
        j = i - 1; //����������������E[0..i-1]����E[i]�Ĳ���λ��
        while (j >= 0 && temp.w < E[j].w)
        {
            E[j + 1] = E[j]; //���ؼ��ִ���E[i].w�ļ�¼����
            j--;
        }
        E[j + 1] = temp; //��j+1������E[i]
    }
}

/*
TODO:�����Kruskal�㷨������С�������Ĺ���.
����˵��:g-ͼ���ڽӾ���.
����ֵ˵��:��.
���˵����cout << "(" << u1 << ',' << v1 << "):" << E[j].w << endl;      
         u1Ϊ�ϴ󶥵�ţ�v1Ϊ��С����ţ�E[j].wΪ�ߵ�Ȩֵ��
*/
void Kruskal(MatGraph g)
{
    int num = g.e;
    Edge *E = new Edge[num];
    int index = 0;
    for (int i = 0; i < num; i++)
    {
        E[i].w = INF;
    }
    for (int i = 0; i < num; i++)
    {
        for (int j = i + 1; j < num; j++)
        {
            if (g.edges[i][j] != INF && g.edges[i][j] != 0)
            {
                E[index].u = i;
                E[index].v = j;
                E[index].w = g.edges[i][j];
                index++;
            }
        }
    }
    InsertSort(E, num);
    int Edgenum = 0;
    int j = 0;
    int vexnum = g.n;
    int root[vexnum];
    for (int i = 0; i < vexnum; i++)
    {
        root[i] = i; //�ȼ����root
    }
    while (Edgenum < g.n - 1)
    {
        if (root[E[j].u] != root[E[j].v]) //��ǰ��С�ıߵ� ��β�ڵ㲻����һ����ͨ����
        {
            int current_root_value = root[E[j].v]; //rootֵ
            for (int i = 0; i < vexnum; i++)
            {
                if (root[i] == current_root_value)
                {
                    root[i] = root[E[j].u];
                }
            }
            int u1 = E[j].v;
            int v1 = E[j].u;
            cout << "(" << u1 << ',' << v1 << "):" << E[j].w << endl;
            Edgenum++;
        }
        j++;
    }
}
int main()
{
    MatGraph g;
    int A[MAXV][MAXV] = {
        {0, 28, INF, INF, INF, 10, INF},
        {28, 0, 16, INF, INF, INF, 14},
        {INF, 16, 0, 12, INF, INF, INF},
        {INF, INF, 12, 0, 22, INF, 18},
        {INF, INF, INF, 22, 0, 25, 24},
        {10, INF, INF, INF, 25, 0, INF},
        {INF, 14, INF, 18, 24, INF, 0}};
    int n = 7, e = 9;

    cin >> A[0][1] >> A[1][0];

    CreateMat(g, A, n, e);
    cout << "ͼG���ڽӾ���:" << endl;
    DispMat(g); //����ڽӾ���
    cout << "Kruskal�㷨���" << endl;
    Kruskal(g);
    return 0;
}
