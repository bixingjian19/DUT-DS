/*5.1  ��������
		
		a.	ֱ�Ӳ�������
			void InsertionSort(T Data[], int n)
*/

#include <iostream>
using namespace std;

/*
TODO:����ֱ�Ӳ������򷨣���Data������в���������
 */
template <class T>
void InsertionSort(T Data[], int n)
{ //
    for (int i = 1; i < n; i++)
    {
        T temp = Data[i];
        int j = i - 1;
        while (j >= 0 && Data[j] > temp)
        {
            Data[j + 1] = Data[j];
            j--;
        }
        Data[j + 1] = temp;
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
    InsertionSort<int>(a, n); //aΪ����������飬10Ϊ����Ĵ�С
    for (int i = 0; i < n; i++)
    {
        cout << a[i] << " ";
    }
}
