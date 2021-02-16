/*5.1  插入排序

		b.	折半插入排序
			void BinaryInsertionSort(T Data[], int n)
			
*/
#include <iostream>
using namespace std;

/*
TODO:折半插入排序,使得排序后Data中的数据按递增排序
 */
template <class T>
void BinaryInsertionSort(T Data[], int n) //参数：待排序数据和待排序元
    //素个数
{
    for (int i = 1; i < n; i++)
    {
        int left, right, mid;
        T temp = Data[i];
        left = 0;
        right = i - 1;
        while (left <= right)
        {
            mid = (left + right) / 2;
            if (temp < Data[mid])
            {
                right = mid - 1;
            }
            else
                left = mid + 1;
        }
        for (int j = i - 1; j >= left; j--)
        {
            Data[j + 1] = Data[j];
        }
        Data[left] = temp;
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

    BinaryInsertionSort<int>(a, n); //a为待排序的数组，10为数组的大小
    for (int i = 0; i < n; i++)
    {
        cout << a[i] << " ";
    }
}