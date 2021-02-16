/*3.3  ͼ�ı���

	a.	�������������DFS�����ݹ鼰�ǵݹ�
		�ݹ�    void DFSTraverse()    void DFS1(int v)
		�ǵݹ�  void DFSNoReverse()
	b.	�������������BFS��
		void BFSTraverse()     void BFS1(int v)

*/
// ����1
// �����룺5
// 1 0 2
// 0 2 1
// 0 3 3
// 3 2 1
// 3 4 1
// �������ͼ��5����
// ͼ����ϢΪ:
// 0 0 1 3 0
// 2 0 0 0 0
// 0 0 0 0 0
// 0 0 1 0 1
// 0 0 0 0 0
// DFSTraverse: 1 3 4 5 2
// DFSNoReverse: 1 3 4 5 2
// BFSTraverse: 1 3 4 5 2

#include <iostream>
#include <queue>
#include <stack>

using namespace std;

template <class T>
class Edge
{
public:
    int start, end, weight;
    Edge()
    {
        start = 0;
        end = 0;
        weight = 0;
    }
    Edge(int st, int en, int w)
    {
        start = st;
        end = en;
        weight = w;
    }
    void showEdge()
    {
        cout << "start: " << start << " end��" << end << " weight��" << weight << endl;
    }
};

template <class T>
class Graph
{
public:
    int vertexNum; //ͼ�Ķ�����Ŀ
    int edgeNum;   //ͼ�ı���Ŀ
    int *Mark;
    Graph()
    {
        vertexNum = 0;
        edgeNum = 0;
        Mark = NULL;
    }
    Graph(int verticesNum)
    {
        vertexNum = verticesNum;
        edgeNum = 0;
        Mark = new int[vertexNum];
        for (int i = 0; i < vertexNum; i++)
            Mark[i] = 0;
    }
    ~Graph()
    {
        delete[] Mark;
    }
    virtual Edge<T> FirstEdge(int oneVertex) = 0;
    virtual Edge<T> NextEdge(Edge<T> oneEdge) = 0;
    int VerticesNum() { return vertexNum; }
    int EdgesNum() { return edgeNum; }
    int StartVertex(Edge<T> oneEdge) { return oneEdge.start; }
    int EndVertex(Edge<T> oneEdge) { return oneEdge.end; }
    int Weight(Edge<T> oneEdge) { return oneEdge.weight; }
    virtual void setEdge(int start, int end, int weight) = 0;
    virtual void delEdge(int start, int end) = 0;
};

template <class T>
class AdjGraph : public Graph<T>
{
private:
    int **matrix;

public:
    AdjGraph(int verticesNum)
    {
        int i, j;
        this->vertexNum = verticesNum;
        this->edgeNum = 0;
        this->Mark = new int[verticesNum];
        for (int i = 0; i < verticesNum; i++)
            this->Mark[i] = 0;
        matrix = (int **)new int *[this->vertexNum];
        for (i = 0; i < this->vertexNum; i++)
            matrix[i] = new int[this->vertexNum];
        for (i = 0; i < this->vertexNum; i++)
            for (j = 0; j < this->vertexNum; j++)
                matrix[i][j] = 0;
    }
    ~AdjGraph()
    {
        for (int i = 0; i < this->vertexNum; i++)
            delete[] matrix[i];
        delete[] matrix;
    }

    bool isEdge(Edge<T> oneEdge)
    {
        if (oneEdge.weight > 0 && oneEdge.end >= 0)
            return true;
        else
            return false;
    }

    Edge<T> FirstEdge(int oneVertex)
    {
        Edge<T> tempEdge;
        tempEdge.start = oneVertex;
        for (int i = 0; i < this->vertexNum; i++)
        {
            if (matrix[oneVertex][i] != 0)
            {
                tempEdge.end = i;
                tempEdge.weight = matrix[oneVertex][i];
                break;
            }
        }
        return tempEdge;
    }

    Edge<T> NextEdge(Edge<T> oneEdge)
    {
        Edge<T> tempEdge;
        tempEdge.start = oneEdge.start;
        for (int i = oneEdge.end + 1; i < this->vertexNum; i++)
        {
            if (matrix[oneEdge.start][i] != 0)
            {
                tempEdge.end = i;
                tempEdge.weight = matrix[oneEdge.start][i];
                break;
            }
        }
        return tempEdge;
    }

    void setEdge(int start, int end, int weight)
    {
        if (start < this->vertexNum && end < this->vertexNum && weight >= 0)
        {
            if (matrix[start][end] == 0)
            {
                this->edgeNum++;
            }
            matrix[start][end] = weight;
        }
        else
            cout << "�Ƿ�����" << endl;
    }
    void delEdge(int start, int end)
    {
        if (start < this->vertexNum && end < this->vertexNum)
        {
            if (matrix[start][end] != 0)
                this->edgeNum--;
            matrix[start][end] = 0;
        }
        else
            cout << "�Ƿ�����" << endl;
    }

    void DFS1(int v)
    {
        this->Mark[v] = 1;    //��Ǹö����ѷ���
        cout << v + 1 << " "; //���ʸö��㣺����0��Ϊ1
        for (Edge<T> e = FirstEdge(v); isEdge(e); e = NextEdge(e))
        {                               //�ɸõ��������ı߽��������������
            if (this->Mark[e.end] == 0) //����V�ڽӵ���δ�����ʹ��Ķ��㣬���ݹ�ؽ��������������
                DFS1(e.end);
        }
    }
    /*
	TODO:a  �������������DFS�����ݹ�,�����ж���ı�־λ��ʼ��,���ͼ�Ƿ���δ���ʵĶ��㣬
	�������Ӹö��㿪ʼ�����������,��δ���ʵĶ������DFS1
	*/
    void DFSTraverse()
    {
        int i;
        for (i = 0; i < this->VerticesNum(); i++)
            this->Mark[i] = 0;
        for (i = 0; i < this->VerticesNum(); i++)
        {
            if (this->Mark[i] == 0)
                DFS1(i);
        }
    }
    void DFSNoReverse()
    {
        int i, v, u;
        stack<int> s;
        for (i = 0; i < this->vertexNum; i++)
            this->Mark[i] = 0;
        for (i = 0; i < this->vertexNum; i++)
        {
            if (this->Mark[i] == 0)
            {
                s.push(i);
                cout << i + 1 << " ";
                this->Mark[i] = 1;
                while (!s.empty())
                {
                    v = s.top();
                    Edge<T> e;
                    for (e = FirstEdge(v); isEdge(e); e = NextEdge(e))
                    {
                        u = e.end;
                        if (this->Mark[u] == 0)
                        {
                            s.push(u);
                            cout << u + 1 << " ";
                            this->Mark[u] = 1;
                            break;
                        }
                    }
                    if (!isEdge(e))
                        s.pop();
                }
            }
        }
    }
    /*
TODO:BFS1�㷨�����ʶ���V���������־λ��Ϊ�ѷ��ʣ����ʸö��㣺 ��ӡcout << v + 1 << " ";
��������δ�����ʵĶ���ʱ��Ҳ��ӡcout << u + 1 << " ";���У�u�Ǳ����ʵĶ���
 */

    void BFS1(int v)
    {
        queue<int> Q;
        this->Mark[v] = 1;
        cout << v + 1 << " ";
        Q.push(v);
        while (!Q.empty())
        {
            v = Q.front();
            Q.pop();
            for (Edge<T> e = FirstEdge(v); isEdge(e); e = NextEdge(e))
            {
                int u = this->Mark[e.end];
                int m = e.end;
                if (u == 0)
                {
                    cout << m + 1 << " ";
                    this->Mark[m] = 1;
                    Q.push(m);
                }
            }
        }
    }
    /*
	TODO:b.	�������������BFS��,�����ж���ı�־λ��ʼ��.
	���ͼ���Ƿ���δ���ʵĶ��㣬�������Ӹö��㿪ʼ����BFS1���й����������
	*/
    void BFSTraverse()
    {
        int v;
        for (v = 0; v < this->vertexNum; v++)
            this->Mark[v] = 0;
        for (v = 0; v < this->vertexNum; v++)
        {
            if (this->Mark[v] == 0)
                BFS1(v);
        }
    }
    void showGraph()
    {
        cout << "ͼ��" << this->edgeNum << "����" << endl;
        cout << "ͼ����ϢΪ:" << endl;
        for (int i = 0; i < this->vertexNum; i++)
        {
            for (int j = 0; j < this->vertexNum; j++)
                cout << matrix[i][j] << " ";
            cout << endl;
        }
    }
};

int main()
{
    Edge<int> tempEdge;
    int count, start, end, weight;
    cin >> count;
    AdjGraph<int> adp(count); //countΪͼ�Ķ�����Ŀ
    for (size_t i = 0; i < count; i++)
    {
        cin >> start >> end >> weight;
        adp.setEdge(start, end, weight);
    }

    // adp.setEdge(1, 0, 2); //1,0,2  ����1Ϊ�ߵ���㣬0Ϊ�ߵ��յ㣬2Ϊ�ߵ�Ȩ�ء�
    // adp.setEdge(0, 2, 1);
    // adp.setEdge(0, 3, 3);
    // adp.setEdge(3, 2, 1);
    // adp.setEdge(3, 4, 1);
    adp.showGraph();
    cout << "DFSTraverse: ";
    adp.DFSTraverse();
    cout << endl;
    cout << "DFSNoReverse: ";
    adp.DFSNoReverse();
    cout << endl;
    cout << "BFSTraverse: ";
    adp.BFSTraverse();
    cout << endl;
    return 0;
}
