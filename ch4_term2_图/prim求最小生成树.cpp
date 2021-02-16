#include <iostream>

using namespace std;
#define AFFINITY 100
/*
 * TODO:定义辅助结构体Element存储最短边集
 * 该结构体含有两个整型元素代表最短边的权值lowcost和邻接点adjvex
 *
 */
struct Element
{
	int lowcost; //权值
	int adjvex;	 //邻接点
};

/*
 * TODO：最小生成树Prim算法
 * 功能描述：设 G= ( V, E) 是一个无向连通网,求G的最小生成树。应用最近顶点策略的
 *          贪心法（Prim算法）求解。在输出顶点k和对应的权值按以下格式：
 *             cout<<shortEdge[k].adjvex<<"--"<<k<<endl;
 * 参数说明：       arc: 存储图中各边的代价二维数组，int**类型
 *                   w: 顶点，int类型
 *                   n: 数组大小，int类型
 * 返回值说明：空
*/
void Prim(int **arc, int w, int n)
{
	int i, j;
	Element *shortEdge;
	int *nearest;  //离里面的距离
	int *neighbor; //离里面那个点最近

	shortEdge = new Element[n - 1];
	nearest = new int[n];
	neighbor = new int[n];
	for (i = 0; i < n; i++)
	{
		neighbor[i] = w;
		nearest[i] = AFFINITY;
	}
	for (i = 0; i < n; i++)
	{
		if (arc[0][i] > 0 && arc[0][i] < 100)
			nearest[i] = arc[0][i];
	}
	neighbor[w] = -1;

	for (i = 1; i < n; i++)
	{
		int min = AFFINITY;
		int v = -1; //找到下一个加入的点
		for (j = 0; j < n; j++)
		{
			if (nearest[j] < min && neighbor[j] > -1)
			{
				min = nearest[j];
				v = j;
			}
		}
		shortEdge[v].adjvex = neighbor[v];
		shortEdge[v].lowcost = nearest[v];
		cout << shortEdge[v].adjvex << "--" << v << endl;
		neighbor[v] = -1;
		for (int u = 0; u < n; u++)
		{
			if (arc[v][u] > 0 && arc[v][u] < 100)
			{
				if (neighbor[u] != -1 && nearest[u] > arc[v][u])
				{
					neighbor[u] = v;
					nearest[u] = arc[v][u];
				}
			}
		}
	}
}

int main()
{
	//输入: arc[n][n] 存储图中各边的代价
	int n;
	cout << "请输入二维nxn数组大小 n:" << endl;
	cin >> n;
	int **arc;
	arc = new int *[n];
	for (int i = 0; i < n; i++)
	{
		arc[i] = new int[n];
	}
	//图中各边的代价, 100代表最大代价
	cout << "请输入图中各边的代价, 100代表最大代价:" << endl;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			cin >> arc[i][j];
		}
	}
	//输出: 最小生成树
	cout << "最小生成树的解为:" << endl;
	Prim(arc, 0, n);
	//释放内存：
	for (int i = 0; i < n; ++i)
		delete[] arc[i];
	delete[] arc;
	return 0;
}
