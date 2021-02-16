/*3.3  图的遍历

	a.	深度优先搜索（DFS）：递归及非递归
		递归    void DFSTraverse()    void DFS1(int v)
		非递归  void DFSNoReverse()
	b.	广度优先搜索（BFS）
		void BFSTraverse()     void BFS1(int v)

*/
// 用例1
// 答案输入：5
// 1 0 2
// 0 2 1
// 0 3 3
// 3 2 1
// 3 4 1
// 答案输出：图有5条边
// 图的信息为:
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
        cout << "start: " << start << " end：" << end << " weight：" << weight << endl;
    }
};

template <class T>
class Graph
{
public:
    int vertexNum; //图的顶点数目
    int edgeNum;   //图的边数目
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
            cout << "非法输入" << endl;
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
            cout << "非法输入" << endl;
    }

    void DFS1(int v)
    {
        this->Mark[v] = 1;    //标记该顶点已访问
        cout << v + 1 << " "; //访问该顶点：顶点0设为1
        for (Edge<T> e = FirstEdge(v); isEdge(e); e = NextEdge(e))
        {                               //由该点所关联的边进行深度优先搜索
            if (this->Mark[e.end] == 0) //访问V邻接到的未被访问过的顶点，并递归地进行深度优先搜索
                DFS1(e.end);
        }
    }
    /*
	TODO:a  深度优先搜索（DFS）：递归,对所有顶点的标志位初始化,检查图是否有未访问的顶点，
	如果有则从该顶点开始深度优先搜索,对未访问的顶点调用DFS1
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
TODO:BFS1算法，访问顶点V，并将其标志位置为已访问，访问该顶点： 打印cout << v + 1 << " ";
访问其它未被访问的顶点时，也打印cout << u + 1 << " ";其中，u是被访问的顶点
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
	TODO:b.	广度优先搜索（BFS）,对所有顶点的标志位初始化.
	检查图中是否有未访问的顶点，如果有则从该顶点开始调用BFS1进行广度优先搜索
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
        cout << "图有" << this->edgeNum << "条边" << endl;
        cout << "图的信息为:" << endl;
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
    AdjGraph<int> adp(count); //count为图的顶点数目
    for (size_t i = 0; i < count; i++)
    {
        cin >> start >> end >> weight;
        adp.setEdge(start, end, weight);
    }

    // adp.setEdge(1, 0, 2); //1,0,2  其中1为边的起点，0为边的终点，2为边的权重。
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
