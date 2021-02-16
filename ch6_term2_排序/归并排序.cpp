/*5.4  �鲢����

		a.	�鲢����
			void MergeSort(T Data[], int start, int end)
			void Merge(T Data[], int start, int mid, int end)
*/

#include <iostream>
using namespace std;

template <class T>
/*
TODO:����Merge������Data�Ǵ��鲢���飬���ж�Data[start,mid]��Data[mid+1, end]
  ֮������ݽ��й鲢
*/
void Merge(T Data[], int start, int mid, int end)
{
    int len1 = mid - start + 1, len2 = end - mid; //�ֱ��ʾ�����鲢����ĳ���
    int i, j, k;
    T *left = new int[len1];   //��ʱ�����������Data[start,mid]����
    T *right = new int[len2];  //��ʱ�����������Data[mid+1,end]
    for (i = 0; i < len1; i++) //ִ�����ݸ��Ʋ���
    {
        left[i] = Data[i + start];
    }
    for (i = 0; i < len2; i++) //ִ�����ݸ��Ʋ���
    {
        right[i] = Data[i + mid + 1];
    }
    i = 0, j = 0;
    for (k = start; k < end; k++) //ִ�й鲢
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
    while (i < len1) //��Data[start,mid]���д��鲢���ݣ���ŵ�Data����
    {
        Data[k++] = left[i++];
    }
    while (j < len2) //��Data[mid+1,end]�������ִ��ͬ���Ĳ���
    {
        Data[k++] = right[j++];
    }
    delete[] left; //�ͷ��ڴ�
    delete[] right;
}

/*
TODO:��Data[start]-Data[end]֮������н��й鲢����,�����ʹ��Data��Ԫ����������
 */
template <class T>
void MergeSort(T Data[], int start, int end)
{ //��Data[start]-Data[end]֮������н��й鲢����
    if (start < end)
    {
        T mid = (start + end) / 2;     //�����м�λ��
        MergeSort(Data, start, mid);   //����������й鲢����
        MergeSort(Data, mid + 1, end); //���ұ������й鲢����
        Merge(Data, start, mid, end);  //�鲢�������ߵ���������
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
    MergeSort<int>(a, 0, n - 1); //aΪ����������飬0Ϊ����ĵ�һ��λ�ã�n-1Ϊ��������һ��λ��
    for (int i = 0; i < n; i++)
    {
        cout << a[i] << " ";
    }
    return 0;
}