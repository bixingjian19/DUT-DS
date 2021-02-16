/*5.1  插入排序
	
	c.	希尔排序
		void ShellSort(T Data[], int n)
		
*/
#include <iostream>
using namespace std;

/*
TODO:希尔排序,排序后使得Data中元素为升序排列
 */
template <class T>
void ShellSort(T Data[], int n)
{
    int d = n / 2;
    while (d >= 1)
    {
        for (int k = 0; k < d; k++) //有d个子序列
        {
            for (int i = k + d; i < n; i += d) //循环这个子序列的每个元素
            {
                T temp = Data[i];
                int j = i - d;
                while (j >= k && temp < Data[j]) //对子序列中的每个元素向前排序
                {
                    Data[j + d] = Data[j];
                    j -= d;
                }
                Data[j + d] = temp;
            }
        }
        d = d / 2;
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

    ShellSort<int>(a, n); //a为待排序的数组，n为数组的大小
    for (int i = 0; i < n; i++)
        cout << a[i] << " ";
}
