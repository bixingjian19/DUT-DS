/*5.2   ��������

		b.	��������
			void QuickSort(T Data[], int left, int right)
			int Partition1(T Data[], int left, int right)
*/
#include <iostream>
using namespace std;

/*
TODO:ʵ�ֶ�data[left]��data[right]�ķָ�����������ػ��ֺ���Ԫ�ض�Ӧ��λ��,������Ԫ�ص���λ�ã�ʵ�ַ���
*/
template <class T>
int Partition1(T Data[], int left, int right)
{
    T temp = Data[left];
    while (left < right)
    {
        while (left < right && Data[right] > temp)
        {
            right--;
        }
        Data[left] = Data[right];
        while (left < right && Data[left] <= temp)
        {
            left++;
        }
        Data[right] = Data[left];
    }
    Data[left] = temp;
    return left;
}

/*
TODO:�÷��η�ʵ�ֿ��������㷨,�����Data��Ԫ�ذ���������
 */
template <class T>
void QuickSort(T Data[], int left, int right)
{
    if (left < right)
    {
        int partition = Partition1(Data, left, right);
        QuickSort(Data, left, partition - 1);
        QuickSort(Data, partition + 1, right);
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
    QuickSort<int>(a, 0, n - 1); //aΪ����������飬0Ϊ����ĵ�һ��λ�ã�n-1Ϊ��������һ��λ��
    for (int i = 0; i < n; i++)
    {
        cout << a[i] << " ";
    }
    return 0;
}