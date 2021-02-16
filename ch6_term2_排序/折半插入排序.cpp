/*5.1  ��������

		b.	�۰��������
			void BinaryInsertionSort(T Data[], int n)
			
*/
#include <iostream>
using namespace std;

/*
TODO:�۰��������,ʹ�������Data�е����ݰ���������
 */
template <class T>
void BinaryInsertionSort(T Data[], int n) //���������������ݺʹ�����Ԫ
    //�ظ���
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

    BinaryInsertionSort<int>(a, n); //aΪ����������飬10Ϊ����Ĵ�С
    for (int i = 0; i < n; i++)
    {
        cout << a[i] << " ";
    }
}