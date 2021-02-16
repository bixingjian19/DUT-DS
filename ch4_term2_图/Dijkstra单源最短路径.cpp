// 用例1
// 答案输入：3
// 答案输出：图G的邻接矩阵:
// 0 4 6
// ∞ 0 1
// ∞ ∞ 0
// 从0顶点出发的最短路径如下:
// 从顶点0到顶点1的路径长度为: 4 路径为:0,1
// 从顶点0到顶点2的路径长度为: 5 路径为:0,1,2

#include <iostream>
using namespace std;

//图的两种存储结构
#define INF 32767 //定义∞
#define MAXV 100  //最大顶点个数
typedef char InfoType;
/*
TODO:定义一个邻接矩阵结构体,其中一个成员为int类型变量no存编号,
另一个为InfoType类型变量info存信息
*/
typedef struct
{
	int no;
	InfoType info;
} VertexType; //顶点类型
/*
TODO:定义一个完整的图邻接矩阵类型结构体,
其中一个成员为大小为MAXV*MAXV的二维int数组edges存邻接矩阵,
两个int型变量n,e存定点数边数,一个大小为MAXV的VertexType数组vexs存信息
*/
typedef struct
{
	int edges[MAXV][MAXV];
	int n;
	int e;
	VertexType vexs[MAXV];
} MatGraph; //完整的图邻接矩阵类型

//------------------------------------------------------------
//----邻接矩阵的基本运算算法----------------------------------
//------------------------------------------------------------
void CreateMat(MatGraph &g, int A[MAXV][MAXV], int n, int e) //创建图的邻接矩阵
{
	int i, j;
	g.n = n;
	g.e = e;
	for (i = 0; i < g.n; i++)
		for (j = 0; j < g.n; j++)
			g.edges[i][j] = A[i][j];
}
void DispMat(MatGraph g) //输出邻接矩阵g
{
	int i, j;
	for (i = 0; i < g.n; i++)
	{
		for (j = 0; j < g.n; j++)
			if (g.edges[i][j] != INF)
				cout << g.edges[i][j] << ' ';
			else
				cout << "∞ ";
		cout << endl;
	}
}
//dist表示路径长度
//path[i]为路径上i的前驱顶点编号
//S[i]=1表示顶点i在S中, S[i]=0表示顶点i在U中 相当于书上的Mark
void Dispath(MatGraph g, int dist[], int path[], int S[], int v)
//输出从顶点v出发的所有最短路径
{
	int i, j, k;
	int apath[MAXV], d;		  //存放一条最短路径(逆向)及其顶点个数
	for (i = 0; i < g.n; i++) //循环输出从顶点v到i的路径
		if (S[i] == 1 && i != v)
		{
			cout << "从顶点" << v << "到顶点" << i << "的路径长度为: " << dist[i] << " 路径为:";
			d = 0;
			apath[d] = i; //添加路径上的终点
			k = path[i];
			if (k == -1) //没有路径的情况
				cout << "无路径" << endl;
			else //存在路径时输出该路径
			{
				while (k != v)
				{
					d++;
					apath[d] = k;
					k = path[k];
				}
				d++;
				apath[d] = v; //添加路径上的起点
				cout << apath[d];
				for (j = d - 1; j >= 0; j--) //再输出其他顶点
					cout << "," << apath[j];
				cout << endl;
			}
		}
}
/*
TODO:完成用Dijkstra算法计算路径的功能.
函数功能:先初始化一些路径值,嵌套循环找出所有顶点最短路径,调用Dispath函数传参初始顶点输出最短路径.
参数说明:g-图的邻接矩阵,v-初始顶点.
返回值说明:无.
*/
//dist表示路径长度
//path[i]为路径上i的前驱顶点编号
//S[i]=1表示顶点i在S中, S[i]=0表示顶点i在U中 相当于书上的Mark
void Dijkstra(MatGraph g, int v) //Dijkstra算法
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
		S[nextvex] = 1; //第一次循环加入源点
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
	cout << "图G的邻接矩阵:" << endl;
	DispMat(g); //输出邻接矩阵
	int v = 0;
	cout << "从" << v << "顶点出发的最短路径如下:" << endl;
	Dijkstra(g, v);
	return 0;
}
