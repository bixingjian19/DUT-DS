/*5.4  归并排序

		a.	归并排序
			void MergeSort(T Data[], int start, int end)
			void Merge(T Data[], int start, int mid, int end)
*/

#include <iostream>
using namespace std;

template <class T>
/*
TODO:函数Merge，参数Data是待归并数组，其中对Data[start,mid]和Data[mid+1, end]
  之间的数据进行归并
*/
void Merge(T Data[], int start, int mid, int end)
{
    int len1 = mid - start + 1, len2 = end - mid; //分别表示两个归并区间的长度
    int i, j, k;
    T *left = new int[len1];   //临时数组用来存放Data[start,mid]数据
    T *right = new int[len2];  //临时数组用来存放Data[mid+1,end]
    for (i = 0; i < len1; i++) //执行数据复制操作
    {
        left[i] = Data[i + start];
    }
    for (i = 0; i < len2; i++) //执行数据复制操作
    {
        right[i] = Data[i + mid + 1];
    }
    i = 0, j = 0;
    for (k = start; k < end; k++) //执行归并
    {
        if (i == len1 || j == len2)
        {
            break;
        }
        if (left[i] <= right[j])
        {
            Data[k] = left[i++];
        }
        else
        {
            Data[k] = right[j++];
        }
    }
    while (i < len1) //若Data[start,mid]还有待归并数据，则放到Data后面
    {
        Data[k++] = left[i++];
    }
    while (j < len2) //对Data[mid+1,end]间的数据执行同样的操作
    {
        Data[k++] = right[j++];
    }
    delete[] left; //释放内存
    delete[] right;
}

/*
TODO:对Data[start]-Data[end]之间的序列进行归并排序,排序后使得Data中元素升序排列
 */
template <class T>
void MergeSort(T Data[], int start, int end)
{ //对Data[start]-Data[end]之间的序列进行归并排序
    if (start < end)
    {
        T mid = (start + end) / 2;     //计算中间位置
        MergeSort(Data, start, mid);   //对左边子序列归并排序
        MergeSort(Data, mid + 1, end); //对右边子序列归并排序
        Merge(Data, start, mid, end);  //归并左、右两边的有序序列
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
    MergeSort<int>(a, 0, n - 1); //a为待排序的数组，0为数组的第一个位置，n-1为数组的最后一个位置
    for (int i = 0; i < n; i++)
    {
        cout << a[i] << " ";
    }
    return 0;
}