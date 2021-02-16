// ����1
// �����룺3
// �������ͼG���ڽӾ���:
// 0 4 6
// �� 0 1
// �� �� 0
// ��0������������·������:
// �Ӷ���0������1��·������Ϊ: 4 ·��Ϊ:0,1
// �Ӷ���0������2��·������Ϊ: 5 ·��Ϊ:0,1,2

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
//dist��ʾ·������
//path[i]Ϊ·����i��ǰ��������
//S[i]=1��ʾ����i��S��, S[i]=0��ʾ����i��U�� �൱�����ϵ�Mark
void Dispath(MatGraph g, int dist[], int path[], int S[], int v)
//����Ӷ���v�������������·��
{
	int i, j, k;
	int apath[MAXV], d;		  //���һ�����·��(����)���䶥�����
	for (i = 0; i < g.n; i++) //ѭ������Ӷ���v��i��·��
		if (S[i] == 1 && i != v)
		{
			cout << "�Ӷ���" << v << "������" << i << "��·������Ϊ: " << dist[i] << " ·��Ϊ:";
			d = 0;
			apath[d] = i; //���·���ϵ��յ�
			k = path[i];
			if (k == -1) //û��·�������
				cout << "��·��" << endl;
			else //����·��ʱ�����·��
			{
				while (k != v)
				{
					d++;
					apath[d] = k;
					k = path[k];
				}
				d++;
				apath[d] = v; //���·���ϵ����
				cout << apath[d];
				for (j = d - 1; j >= 0; j--) //�������������
					cout << "," << apath[j];
				cout << endl;
			}
		}
}
/*
TODO:�����Dijkstra�㷨����·���Ĺ���.
��������:�ȳ�ʼ��һЩ·��ֵ,Ƕ��ѭ���ҳ����ж������·��,����Dispath�������γ�ʼ����������·��.
����˵��:g-ͼ���ڽӾ���,v-��ʼ����.
����ֵ˵��:��.
*/
//dist��ʾ·������
//path[i]Ϊ·����i��ǰ��������
//S[i]=1��ʾ����i��S��, S[i]=0��ʾ����i��U�� �൱�����ϵ�Mark
void Dijkstra(MatGraph g, int v) //Dijkstra�㷨
{
	int vexnum = g.n;
	int *S = new int[vexnum];
	int *path = new int[vexnum];
	int *dist = new int[vexnum];
	for (int i = 0; i < vexnum; i++)
	{
		S[i] = 0;
		dist[i] = INF;
		path[i] = v;
	}
	dist[v] = 0;
	for (int i = 0; i < vexnum; i++)
	{
		int min = INF;
		int nextvex;
		for (int j = 0; j < vexnum; j++)
		{
			if (S[j] == 0 && dist[j] < min)
			{
				nextvex = j;
				min = dist[j];
			}
		}
		S[nextvex] = 1; //��һ��ѭ������Դ��
		for (int next_update_vex = 0; next_update_vex < vexnum; next_update_vex++)
		{
			if (S[next_update_vex] == 0 && (dist[nextvex] + g.edges[nextvex][next_update_vex] < dist[next_update_vex]))
			{
				dist[next_update_vex] = dist[nextvex] + g.edges[nextvex][next_update_vex];
				path[next_update_vex] = nextvex;
			}
		}
	}
	Dispath(g, dist, path, S, v);
}

int main()
{
	MatGraph g;
	int A[MAXV][MAXV] = {
		{0, 4, 6, 6, INF, INF, INF},
		{INF, 0, 1, INF, 7, INF, INF},
		{INF, INF, 0, INF, 6, 4, INF},
		{INF, INF, 2, 0, INF, 5, INF},
		{INF, INF, INF, INF, 0, INF, 6},
		{INF, INF, INF, INF, 1, 0, 8},
		{INF, INF, INF, INF, INF, INF, 0}};
	int n = 7, e = 12;
	cin >> n;
	CreateMat(g, A, n, e);
	cout << "ͼG���ڽӾ���:" << endl;
	DispMat(g); //����ڽӾ���
	int v = 0;
	cout << "��" << v << "������������·������:" << endl;
	Dijkstra(g, v);
	return 0;
}
