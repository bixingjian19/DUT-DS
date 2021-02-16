#include <iostream>

using namespace std;
#define AFFINITY 100
/*
 * TODO:���帨���ṹ��Element�洢��̱߼�
 * �ýṹ�庬����������Ԫ�ش�����̱ߵ�Ȩֵlowcost���ڽӵ�adjvex
 *
 */
struct Element
{
	int lowcost; //Ȩֵ
	int adjvex;	 //�ڽӵ�
};

/*
 * TODO����С������Prim�㷨
 * ������������ G= ( V, E) ��һ��������ͨ��,��G����С��������Ӧ�����������Ե�
 *          ̰�ķ���Prim�㷨����⡣���������k�Ͷ�Ӧ��Ȩֵ�����¸�ʽ��
 *             cout<<shortEdge[k].adjvex<<"--"<<k<<endl;
 * ����˵����       arc: �洢ͼ�и��ߵĴ��۶�ά���飬int**����
 *                   w: ���㣬int����
 *                   n: �����С��int����
 * ����ֵ˵������
*/
void Prim(int **arc, int w, int n)
{
	int i, j;
	Element *shortEdge;
	int *nearest;  //������ľ���
	int *neighbor; //�������Ǹ������

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
		int v = -1; //�ҵ���һ������ĵ�
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
	//����: arc[n][n] �洢ͼ�и��ߵĴ���
	int n;
	cout << "�������άnxn�����С n:" << endl;
	cin >> n;
	int **arc;
	arc = new int *[n];
	for (int i = 0; i < n; i++)
	{
		arc[i] = new int[n];
	}
	//ͼ�и��ߵĴ���, 100����������
	cout << "������ͼ�и��ߵĴ���, 100����������:" << endl;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			cin >> arc[i][j];
		}
	}
	//���: ��С������
	cout << "��С�������Ľ�Ϊ:" << endl;
	Prim(arc, 0, n);
	//�ͷ��ڴ棺
	for (int i = 0; i < n; ++i)
		delete[] arc[i];
	delete[] arc;
	return 0;
}
