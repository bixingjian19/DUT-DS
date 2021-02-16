/*2.4最大堆
 *
 * void BuildHeap();	//2.4-a 最大堆构建
 * void SiftDown(int left);	//2.4-b SiftDown函数从left向下调整堆，使序列成为堆
 * void SiftUp(int pos);	//2.4-c SiftUp函数从position向上调整堆，使序列成为堆
 * bool Remove(int pos, T& node);	//2.4-d 删除给定下标的元素
 * bool Insert(const T& newNode);	//2.4-e 从堆中插入新元素newNode
 *
 */

#include <iostream>
#include <stdlib.h>
using namespace std;

template <class T>
class MaxHeap
{
private:
    T *heapArray;
    int CurrentSize; /* 当前堆元素个数 */
    int MaxSize;     /* 堆中能存放的最大元素个数 */
public:
    MaxHeap(T *array, int num, int max)
    {
        this->heapArray = array;
        this->CurrentSize = num;
        this->MaxSize = max;
    }

    virtual ~MaxHeap(){};
    bool isLeaf(int pos) const;
    int leftchild(int pos) const;
    int rightchild(int pos) const;
    int parent(int pos) const;
    void BuildHeap();              /* 2.4-a 最大堆构建 */
    void SiftDown(int left);       /* 2.4-b SiftDown函数从left向下调整堆，使序列成为堆 */
    void SiftUp(int pos);          /* 2.4-c SiftUp函数从position向上调整堆，使序列成为堆 */
    bool Remove(int pos, T &node); /* 2.4-d 删除给定下标的元素 */
    bool Insert(const T &newNode); /* 2.4-e 从堆中插入新元素newNode */
    T &RemoveMax();                /* 2.4-f 从堆顶删除最大值 */
    void visit();
};

/*
 * TODO:2.4-a 最大堆构建
 */
template <class T>
void MaxHeap<T>::BuildHeap()
{
    for (int i = CurrentSize / 2 - 1; i >= 0; i--) //其中i是第一个具有孩子结点的结点
        SiftDown(i);
}

template <class T>
bool MaxHeap<T>::isLeaf(int pos) const
{
    if (pos >= CurrentSize)
    {
        cout << "越界" << endl;
        return (false);
    }
    else if (pos > (CurrentSize - 1) / 2)
        return (true);
    else
        return (false);
}

template <class T>
int MaxHeap<T>::leftchild(int pos) const
{
    return (2 * pos + 1);
}

template <class T>
int MaxHeap<T>::rightchild(int pos) const
{
    return (2 * pos + 2);
}

template <class T>
int MaxHeap<T>::parent(int pos) const
{
    return ((pos - 1) / 2);
}

/*
 * TODO:2.4-d 删除给定下标的元素，并将该元素的值赋值给node变量。
 * 返回值说明：如果删除成功，则返回true，否则返回false
 * 重要说明：如果当前堆为空，则输出打印cout << "空堆" << endl;并返回false
 */
template <class T>
bool MaxHeap<T>::Remove(int pos, T &node)
{
    if (CurrentSize == 0)
    {
        cout << "空堆" << endl;
        return false;
        exit(1);
    }

    node = heapArray[pos];
    T lastElement = heapArray[CurrentSize - 1];
    heapArray[pos] = lastElement;
    CurrentSize = CurrentSize - 1; //把最后一个元素放到当前位置

    for (int i = CurrentSize / 2 - 1; i >= 0; i--) //重新排列成堆
        SiftDown(i);
    return true;
}

/*
 * TODO:2.4 - b SiftDown函数从left向下调整堆，使序列成为堆
 */
template <class T>
void MaxHeap<T>::SiftDown(int left)
{
    int i = left;          //父结点
    int j = 2 * i + 1;     //左子结点
    T temp = heapArray[i]; //把要处理的元素“挖出来”，形成一个“坑”

    while (j < CurrentSize)
    {
        if ((j < CurrentSize - 1) && (heapArray[j] < heapArray[j + 1])) //挑出子结点中最大的一个
            j++;
        if (temp < heapArray[j])
        {
            heapArray[i] = heapArray[j]; //如果父结点比子结点小 交换位置
            i = j;                       //父节点到子节点的位置 继续向下判断
            j = 2 * j + 1;               //依次递减 逐个判断以该节点为很的子树是否满足最大堆的性质
        }
        else
            break;
    }
    heapArray[i] = temp; //放到相应的我i之
}

/*
 * TODO:2.4-c SiftUp函数从pos向上调整堆，使序列成为堆
 */
template <class T>
void MaxHeap<T>::SiftUp(int pos)
{
    int i = pos;
    int j = (i - 1) / 2;

    int temp = heapArray[i]; //把要处理的元素“挖出来”，形成一个“坑”

    while (j >= 0 && i >= 1)
    {
        if (heapArray[j] < temp) //
        {
            heapArray[i] = heapArray[j]; //“坑”往上升

            i = j; //更新下标
            j = (i - 1) / 2;
        }
        else
            break;
    }

    heapArray[i] = temp; //把temp填回“坑”里去
}

/*
 * TODO:2.4-e 从堆中插入新元素newNode, 如果插入成功，返回true，否则返回false。
 * 重要说明：如果堆中元素超过堆中元素最大个数值，则输出打印cout << "堆满" << endl;并返回false
 */
template <class T>
bool MaxHeap<T>::Insert(const T &newNode)
{
    if (CurrentSize == MaxSize)
    {
        cout << "堆满" << endl;
        return false;
    }

    heapArray[CurrentSize] = newNode; //在末尾添加元素
    CurrentSize = CurrentSize + 1;
    for (int i = CurrentSize / 2 - 1; i >= 0; i--) //重新形成堆
        SiftDown(i);

    return true;
}

template <class T>
void MaxHeap<T>::visit()
{
    for (int i = 0; i < CurrentSize; i++)
        cout << heapArray[i] << " ";
    cout << endl;
}

/*
 * TODO:2.4-f 从堆顶删除最大值. 如果堆栈为空堆，则输出打印cout << "空堆" << endl;然后退出程序，退出码为1.
 * 否则，从堆顶删除最大值，并将其作为返回值进行返回。
 */
template <class T>
T &MaxHeap<T>::RemoveMax()
{
    if (CurrentSize == 0)
    {
        cout << "空堆" << endl;
        exit(1);
    }
    T lastElement = heapArray[CurrentSize - 1];
    heapArray[0] = lastElement; //把最后一个元素放到第一位
    CurrentSize = CurrentSize - 1;
    for (int i = CurrentSize / 2 - 1; i >= 0; i--) //重新排列
        SiftDown(i);
    return lastElement;
}

int main()
{
    /* int a[10] = { 20,12,35,15,10,80,30,17,2,1 }; */
    int count, maxSize; /* 初始化堆中元素个数 */
    cin >> count >> maxSize;
    int iValue;
    int *a = new int[count];
    for (int i = 0; i < count; i++)
    {
        cin >> iValue;
        a[i] = iValue;
    }

    /* MaxHeap<int> maxheap(a, 10, 20); */
    MaxHeap<int> maxheap(a, count, maxSize);
    int temp;
    maxheap.BuildHeap();
    cout << "构建堆后为:";
    maxheap.visit();
    cin >> iValue; /* 输入一个整数，判断它是否是堆上的叶子节点 */
    if (maxheap.isLeaf(iValue))
        cout << "位置" << iValue << "是叶结点" << endl;
    else
        cout << "位置" << iValue << "不是叶结点" << endl;
    maxheap.visit();
    maxheap.RemoveMax();
    cout << "移除最大值后:";
    maxheap.visit();
    cin >> iValue; /* 输入一个整数，移除该下标所在的元素 */
    maxheap.Remove(iValue, temp);
    cout << "删除下标为" << iValue << "的元素之后为:";
    maxheap.visit();
    cout << "删除下标为" << iValue << "的元素为" << temp << endl;
    cin >> iValue; /* 输入一个整数，移除该下标所在的元素 */
    maxheap.Insert(iValue);
    cout << "插入" << iValue << "后为:";
    maxheap.visit();
    return (0);
}
