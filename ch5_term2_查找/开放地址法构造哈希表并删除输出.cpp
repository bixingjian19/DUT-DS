//���ŵ�ַ������Ĺ�ϣ��������㷨
#include <iostream>
using namespace std;

#define MaxSize 100  //��������ϣ����
#define NULLKEY -1   //����չؼ���ֵ
#define DELKEY -2    //���屻ɾ�ؼ���ֵ
typedef int KeyType; //�ؼ�������

/*
TODO:����һ����ϣ���Žṹ��,��һ��ΪKeyType���ͱ���key��ؼ�����,
�ڶ���Ϊint�ͱ���count��̽�������
*/
typedef struct
{
    KeyType key;
    int count;

} HashTable; //��ϣ������

/*
TODO:��ɽ��ؼ���k���뵽��ϣ���еĹ���.
��������:�����ϣ����ֵ,�жϹ�ϣ��״̬���в������ѭ��̽�����.
����˵��:ha-��ϣ��,n-�ܹؼ�����,m-����,p-�����ϣ��ĸ,k-����ؼ���.
����ֵ˵��:��.
*/
void InsertHT(HashTable ha[], int &n, int m, int p, KeyType k) //���ؼ���k���뵽��ϣ����
{
    int i = 0; //̽������б��
    int pos = k % p;
    while (ha[pos].key != NULLKEY) //EMPTY��ɢ�б�ǰλ��Ϊ�յı��
    {
        i++;
        pos = (k % p + i) % p; //probe����̽�鲽��
    }
    ha[pos].key = k; //���±���λ����Ϣ
    ha[pos].count = i + 1;
}

/*
TODO:��ɴ�����ϣ��Ĺ���.
��������:ѭ����ʼ����ϣ��Ԫ��ֵȻ��ѭ�����ú�������ؼ���.
����˵��:ha-��ϣ��,n-�ܹؼ�����,m-����,p-�����ϣ��ĸ,keys-�ؼ�����,n1-��ʼ�ؼ�����.
����ֵ˵��:��.
*/
void CreateHT(HashTable ha[], int &n, int m, int p, KeyType keys[], int n1) //������ϣ��
{
    int i = 0;
    while (i < m)
    {
        ha[i].key = NULLKEY;
        ha[i].count = 0;
        i++;
    }
    i = 0;
    while (i < n1)
    {
        InsertHT(ha, n, m, p, keys[i]);
        i++;
    }
}
/*
TODO:���ɾ����ϣ���йؼ���k�Ĺ���.
��������:�����ϣ����ֵ,ѭ��̽�����,���ݲ��ҽ������ɾ�������سɹ����߷���ʧ�ܣ���ɾ����λ�õĹؼ��ָ�ֵΪDELKEY.
����˵��:ha-��ϣ��,n-�ܹؼ�����,m-����,p-�����ϣ��ĸ,k-Ŀ��ؼ���.
����ֵ˵��:����ʧ�ܷ���false,����ɾ���ɹ�����true.
*/
bool DeleteHT(HashTable ha[], int &n, int m, int p, KeyType k) //ɾ����ϣ���йؼ���k
{
    int i = 0;
    int pos = k % p;
    do
    {
        if (ha[pos].key == k)
        {
            ha[pos].key = DELKEY;
            return true;
        }
        else
        {
            i++;
            pos = (k % p + i) % p;
        }
    } while (ha[pos].key != NULLKEY);
    return false;
}

void DispHT(HashTable ha[], int n, int m, int p) //�����ϣ��
{
    int i, j;
    cout << "��ϣ��:" << endl;
    cout << "��ϣ���ַ:    ";
    for (i = 0; i < m; i++)
        cout << i << "  ";
    cout << endl;
    cout << "��ϣ��ؼ���: ";
    for (i = 0; i < m; i++)
        if (ha[i].key == NULLKEY)
            cout << "   "; //���3���ո�
        else
            cout << ha[i].key << ' ';
    cout << endl;
    cout << "̽�����:       ";
    for (i = 0; i < m; i++)
        if (ha[i].key == NULLKEY)
            cout << "   "; //���3���ո�
        else
            cout << ha[i].count << "   ";
    cout << endl;
}

int main()
{
    int keys[] = {16, 74, 60, 43, 54, 90, 46, 31, 29, 88, 77};
    int n, m = 13, p = 13, k;
    HashTable ha[MaxSize];
    cin >> k;
    CreateHT(ha, n, m, p, keys, 11);
    cout << "��ʾ��ϣ��:" << endl;
    DispHT(ha, n, m, p);
    if (DeleteHT(ha, n, m, p, k))
    {
        cout << "\nɾ��֮��:\n";
        DispHT(ha, n, m, p);
    }
    else
    {
        cout << "\nɾ��ʧ��!\n";
    }

    return 0;
}