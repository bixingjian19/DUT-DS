/*5.1  ��������
	
	c.	ϣ������
		void ShellSort(T Data[], int n)
		
*/
#include <iostream>
using namespace std;

/*
TODO:ϣ������,�����ʹ��Data��Ԫ��Ϊ��������
 */
template <class T>
void ShellSort(T Data[], int n)
{
    int d = n / 2;
    while (d >= 1)
    {
        for (int k = 0; k < d; k++) //��d��������
        {
            for (int i = k + d; i < n; i += d) //ѭ����������е�ÿ��Ԫ��
            {
                T temp = Data[i];
                int j = i - d;
                while (j >= k && temp < Data[j]) //���������е�ÿ��Ԫ����ǰ����
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

    ShellSort<int>(a, n); //aΪ����������飬nΪ����Ĵ�С
    for (int i = 0; i < n; i++)
        cout << a[i] << " ";
}
