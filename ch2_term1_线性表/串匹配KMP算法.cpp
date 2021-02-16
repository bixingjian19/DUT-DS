#include <iostream>
#include <string.h>

using namespace std;

/*
 * TODO����ģʽT��nextֵ
 * ����������ʹ����������ģʽT��nextֵ
 * ����˵����T[]: ģʽT
 *          next[]: ������������
 * ����ֵ˵������
*/
void GetNext(char T[], int next[])
{
    int len = strlen(T);
    next[0] = 0;
    for (int i = 1; i < len; i++)
    {
        int k = next[i - 1];
        if (T[i] == T[k])
        {
            next[i] = k + 1;
        }
        else
        {
            next[i] = 0;
        }
    }
}

/*
 * TODO����ƥ��KMP�㷨
 * ������������������S���Լ�ģʽT������T��S�е�λ��, ʹ�ô�ƥ��KMP�㷨�������⡣
            ����GetNext�������ʱ�ٶ�ģʽ�Ϊ80���ַ���
 * ����˵����S[]: ����S
 *           T[]: ģʽT
 * ����ֵ˵��������ƥ��Ŀ�ʼλ�ã��±�+1��
 * ����˵��������ģʽT��abcacc������S��abcabcabcaccb�е�λ���ǣ�7
*/
int KMP(char S[], char T[])
{
    int N[80];
    GetNext(T, N);
    int i = 0, j = 0;
    int lens = strlen(S);
    int lent = strlen(T);
    for (i = 0; i < lens; i++)
    {
        while (T[j] != S[i] && j > 0)
        {
            j = N[j - 1];
        }
        if (T[j] == S[i])
        {
            j++;
        }
        if (j == lent)
        {
            return (i - j + 1 + 1);
        }
    }
    return 0;
}

int main()
{

    const int size = 20;
    char S[size];
    char T[size];
    //��ƥ��BF�㷨
    //���룺 ����S, ģʽT
    cout << "����������S:" << endl;
    cin >> S;
    cin.get();
    cout << "���������ģʽT:" << endl;
    cin >> T;
    cin.get();
    //��ƥ��KMP�㷨
    //���룺 ����S, ģʽT
    int index = KMP(S, T);
    //����� T��S�е�λ��
    for (int i = 1; i < index; i++)
        cout << " ";
    cout << T << "��" << endl;
    cout << S << "�е�λ���ǣ�" << index << endl;
    return 0;
}
