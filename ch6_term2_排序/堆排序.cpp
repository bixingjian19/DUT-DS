/*5.3  选择排序

		b.	堆排序
			void HeapSort(T Data[], int n)
			void BuildHeap(T Data[], int n)
			void SiftDown(T Data[], int i, int n)

*/

#include <iostream>
using namespace std;

/*
TODO:用来保持以结点i为根的最大堆的性质，n是所有元素的个数,找到i结点的两个孩子的下标.
和左子结点进行比较;和右子结点进行比较;判断是否需要进行调整;递归对子结点进行调整
 */
template <class T>
void SiftDown(T Data[], int i, int n)
{
    int l = 2 * i + 1, r = 2 * i + 2, min = i; //找到i结点的两个孩子的下标
    if (l < n && Data[min] < Data[l])          //和左子结点进行比较
        min = l;
    if (r < n && Data[min] < Data[r]) //和右子结点进行比较
        min = r;
    if (min != i) //判断是否需要进行调整
    {
        T t = Data[min];
        Data[min] = Data[i];
        Data[i] = t;
        SiftDown(Data, min, n); //递归对子结点进行调整
    }
}
/*
TODO:建立一个最大堆，求出非叶子结点的最大下标,循环调用SiftDown函数，保持最大堆的性质
 */
template <class T>
void BuildHeap(T Data[], int n)
{
    int p = n / 2 - 1; //求出非叶子结点的最大下标
    for (int i = p; i >= 0; i--)
    {
        SiftDown(Data, i, n); //调用SiftDown函数，保持最大堆的性质
    }
}

/*
TODO: 进行堆排序，首先建立一个最大堆，进行循环，次取出最大元素后不断调整最大堆
 排序完成后，使得Data中元素按升序排列
 */
template <class T>
void HeapSort(T Data[], int n)
{
    BuildHeap(Data, n);             //首先建立一个最大堆
    for (int i = n - 1; i > 0; i--) //进行循环
    {
        T t = Data[0]; //每次取出最大元素后不断调整最大堆
        Data[0] = Data[i];
        Data[i] = t;
        BuildHeap(Data, i);
    }
}

int main()
{
    int n, num;
    cin >> n;
    int *a = new int[n];
    for (int i = 0; i < n; i++)
    {
        cin >> num;
        a[i] = num;
    }
    HeapSort<int>(a, n); //a为待排序的数组，n为数组的大小
    for (int i = 0; i < n; i++)
    {
        cout << a[i] << " ";
    }
    return 0;
}
