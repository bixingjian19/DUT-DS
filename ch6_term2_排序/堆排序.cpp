/*5.3  ѡ������

		b.	������
			void HeapSort(T Data[], int n)
			void BuildHeap(T Data[], int n)
			void SiftDown(T Data[], int i, int n)

*/

#include <iostream>
using namespace std;

/*
TODO:���������Խ��iΪ�������ѵ����ʣ�n������Ԫ�صĸ���,�ҵ�i�����������ӵ��±�.
�����ӽ����бȽ�;�����ӽ����бȽ�;�ж��Ƿ���Ҫ���е���;�ݹ���ӽ����е���
 */
template <class T>
void SiftDown(T Data[], int i, int n)
{
    int l = 2 * i + 1, r = 2 * i + 2, min = i; //�ҵ�i�����������ӵ��±�
    if (l < n && Data[min] < Data[l])          //�����ӽ����бȽ�
        min = l;
    if (r < n && Data[min] < Data[r]) //�����ӽ����бȽ�
        min = r;
    if (min != i) //�ж��Ƿ���Ҫ���е���
    {
        T t = Data[min];
        Data[min] = Data[i];
        Data[i] = t;
        SiftDown(Data, min, n); //�ݹ���ӽ����е���
    }
}
/*
TODO:����һ�����ѣ������Ҷ�ӽ�������±�,ѭ������SiftDown�������������ѵ�����
 */
template <class T>
void BuildHeap(T Data[], int n)
{
    int p = n / 2 - 1; //�����Ҷ�ӽ�������±�
    for (int i = p; i >= 0; i--)
    {
        SiftDown(Data, i, n); //����SiftDown�������������ѵ�����
    }
}

/*
TODO: ���ж��������Ƚ���һ�����ѣ�����ѭ������ȡ�����Ԫ�غ󲻶ϵ�������
 ������ɺ�ʹ��Data��Ԫ�ذ���������
 */
template <class T>
void HeapSort(T Data[], int n)
{
    BuildHeap(Data, n);             //���Ƚ���һ������
    for (int i = n - 1; i > 0; i--) //����ѭ��
    {
        T t = Data[0]; //ÿ��ȡ�����Ԫ�غ󲻶ϵ�������
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
    HeapSort<int>(a, n); //aΪ����������飬nΪ����Ĵ�С
    for (int i = 0; i < n; i++)
    {
        cout << a[i] << " ";
    }
    return 0;
}
