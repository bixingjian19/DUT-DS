//B-�������㷨
#include <iostream>
using namespace std;
#define MAXM 10      //����B-�������Ľ���
typedef int KeyType; //KeyTypeΪ�ؼ�������

typedef struct node
{
    int keynum;             //��㵱ǰӵ�еĹؼ��ֵĸ���
    KeyType key[MAXM];      //key[1..keynum]��Źؼ���,key[0]���� �����9���ؼ���
    struct node *parent;    //˫�׽��ָ��
    struct node *ptr[MAXM]; //���ӽ��ָ������ptr[0..keynum]
} BTNode;                   //B-���������

typedef struct //B-���Ĳ��ҽ������
{
    BTNode *pt; //ָ���ҵ��Ľ��
    int i;      //1..m,�ڽ���еĹؼ������
    int tag;    //1:���ҳɹ�,O:����ʧ��
} Result;       //���ҽ������

int m;   //m��B-��,Ϊȫ�ֱ���
int Max; //m��B-����ÿ����������ؼ��ָ���,Max=m-1
int Min; //m��B-���з�Ҷ�ӽ������ٹؼ��ָ���,Min=(m-1)/2
/*
TODO:�����p->key[1..keynum]�в���i,ʹ��p->key[i]<=k<p->key[i+1]�Ĺ���.
��������:ѭ�������жϹؼ���ֵ�Ƿ����.
����˵��:p-�����ָ��,k-Ŀ��ؼ���.
����ֵ˵��:int�Ͳ��ҵ���λ��.
*/
//�ڽڵ��в��ҹؼ���
//��������һ����������
int Search(BTNode *p, KeyType k)
{ //��p->key[1..keynum]�в���i,ʹ��p->key[i]<=k<p->key[i+1]
    int i = 0;
    for (i = 0; i < p->keynum && p->key[i + 1] < k; i++)
    {
        ;
    }
    return i;
}

/*
TODO:�����m��t��t�ϲ��ҹؼ���k,���ؽ���Ĺ���.
��������:ѭ���������ò��Һ�������,�ж�ͬʱ��ǲ���״ֵ̬,���ز��ҽ��.
����˵��:t-��ָ��,k-Ŀ��ؼ���.
����ֵ˵��:Result�Ͳ��ҵ���λ��ֵ.
*/
//���������в���
// BTNode *pt; //ָ���ҵ��Ľ�� ���߸��ڵ�
// int i;      //1..m,�ڽ���еĹؼ������
// int tag;    //1:���ҳɹ�,0:����ʧ��
Result SearchBTree(BTNode *t, KeyType k)
{ /*��m��t��t�ϲ��ҹؼ���k,���ؽ��(pt,i,tag)�������ҳɹ�,������ֵ
   tag=1,ָ��pt��ָ����е�i���ؼ��ֵ���k����������ֵtag=0,����k��
   �ؼ���Ӧ������ָ��Pt��ָ����е�i�͵�i+1���ؼ���֮��*/
    Result result;
    BTNode *pt = t, *pre = NULL;//û���ҵ��Ļ� �͵���Ҷ�ӽڵ� ����pre
    int tag = 0, i = 0;
    while (pt != NULL && tag == 0)
    {
        i = Search(pt, k);
        if (i > 0 && pt->key[i] == k)//�ҵ�
        {
            tag = 1;
        }
        else//û���ҵ�,�������ӽڵ�
        {
            pre = pt;
            pt = pt->ptr[i];
        }
    }
    result.i = i;
    if (tag == 1)
    {
        result.pt = pt;
        result.tag = 1;
    }
    else
    {
        result.pt = pre;
        result.tag = 0;
    }
    return result;
}

/*
TODO:��ɽ�x��ap�ֱ���뵽q->key[i+1]��q->ptr[i+1]�еĹ���.
��������:ѭ���ؼ����鲢��Ĺؼ��ֺ�ָ��ֵ�ճ�λ��Ȼ�����Ԫ��.
����˵��:q-���ָ������,i-λ��ֵ,x-Ŀ��ؼ���,ap-����Ľ��ָ��.
����ֵ˵��:��.
*/
//�ڽڵ��в���ؼ���
void Insert(BTNode *&q, int i, KeyType x, BTNode *ap)
{ //��x��ap�ֱ���뵽q->key[i+1]��q->ptr[i+1]��
    for (int j = q->keynum; j > i; j--)
    {
        q->key[j + 1] = q->key[j];
        q->ptr[j + 1] = q->ptr[j];
    }
    q->key[i + 1] = x;
    q->ptr[i + 1] = ap;
    if (ap != NULL)
    {
        ap->parent = q;
    }
    q->keynum++;
}

/*
TODO:��ɽ����q���ѳ��������,ǰһ�뱣��,��һ�������������ap�Ĺ���.
��������:�����ֳ��������,�½�������Ӧ�ռ䲢�洢���ѵĺ�벿��.
����˵��:q-���ָ������,ap-�¸�ֵ���ָ������.
����ֵ˵��:��.
*/
void Split(BTNode *&q, BTNode *&ap)
{ //�����q���ѳ��������,ǰһ�뱣��,��һ�������������ap
    int div = (m + 1) / 2;
    ap = new BTNode;
    ap->ptr[0] = q->ptr[div]; //�м��ĺ�һ��
    for (int i = div + 1; i <= m; i++)
    {
        ap->key[i - div] = q->key[i];
        ap->ptr[i - div] = q->ptr[i];
        if (ap->ptr[i - div] != NULL)
        {
            ap->ptr[i - div]->parent = ap;
        }
    }
    ap->keynum = q->keynum - div;
    ap->parent = q->parent;
    q->keynum = div - 1;
}

/*
TODO:������ɺ���Ϣ(T,x,ap)���µĸ����*t,ԭt��apΪ����ָ��Ĺ���.
��������:����ռ���½��,���ò�����ֵ��س�Ա����.
����˵��:t-��ָ������,p-���ָ��,x-�ؼ���,ap-�¸�ֵ���ָ������.
����ֵ˵��:��.
*/
void NewRoot(BTNode *&t, BTNode *p, KeyType x, BTNode *ap)
{ //���ɺ���Ϣ(T,x,ap)���µĸ����*t,ԭp��apΪ����ָ��
    t = new BTNode;
    t->keynum = 1;
    t->ptr[0] = p;
    t->ptr[1] = ap;
    t->key[1] = x;
    if (p != NULL)
    {
        p->parent = t;
    }
    if (ap != NULL)
    {
        ap->parent = t;
    }
    t->parent = NULL;
}

/*
TODO:�����m��t��t�Ͻ��*q��key[i]��key[i+1]֮�����ؼ���k�Ĺ���.
��������:�жϽ��ֵ�����ú��������½��, ����ѭ��ִ�� ������߲�� �Ȳ���, ��ɲ���.
����˵��:t-��ָ������,k-�ؼ���,q-���ָ��,i-λ��ֵ.
����ֵ˵��:��.
*/
//�����½ڵ�
void InsertBTree(BTNode *&t, KeyType k, BTNode *q, int i)
{               /*��m��t��t�Ͻ��*q��key[i]��key[i+1]֮�����ؼ���k��������
   ������,����˫�������б�Ҫ�Ľ����ѵ���,ʹt����m��t����*/
    BTNode *ap; //���ѳ������½ڵ�
    int finished, needNewRoot, div;
    KeyType x;
    if (q == NULL) //���q
    {
        NewRoot(t, NULL, k, NULL); //void NewRoot(BTNode *&t, BTNode *p, KeyType x, BTNode *ap)
    }
    else
    {
        x = k;
        ap = NULL;
        finished = needNewRoot = 0;
        while (needNewRoot == 0 && finished == 0)
        {
            Insert(q, i, x, ap);  //��ɽ�x��ap�ֱ���뵽q->key[i+1]��q->ptr[i+1]�еĹ���
            if (q->keynum <= Max) //���÷��� ֱ�ӽ���
            {
                finished = 1;
            }
            else
            {
                div = (m + 1) / 2;
                Split(q, ap);
                x = q->key[div]; //Ҫ�ᵽ�����Ľڵ�
                if (q->parent)
                {
                    q = q->parent;
                    i = Search(q, x); //����һ�ֲ���
                }
                else
                {
                    needNewRoot = 1; //Ҫ�ᵽ����� ��û�и���� ��Ҫ�½�һ�������
                }
            }
        }
        if (needNewRoot == 1)
        {
            NewRoot(t, q, x, ap);
        }
    }
}

void DispBTree(BTNode *t) //�����ű�ʾ�����B-��
{
    int i;
    if (t != NULL)
    {
        cout << '['; //�����ǰ���ؼ���
        for (i = 1; i < t->keynum; i++)
            cout << t->key[i] << ' ';
        cout << t->key[i];
        cout << ']';
        if (t->keynum > 0)
        {
            if (t->ptr[0] != NULL)
                cout << '(';                //������һ������ʱ���"("��
            for (i = 0; i < t->keynum; i++) //��ÿ���������еݹ����
            {
                DispBTree(t->ptr[i]);
                if (t->ptr[i + 1] != NULL)
                    cout << ",";
            }
            DispBTree(t->ptr[t->keynum]);
            if (t->ptr[0] != 0)
                cout << ")"; //������һ������ʱ���")"��
        }
    }
}

int main()
{
    BTNode *t = NULL;
    Result s;
    int j, n = 20;
    KeyType a[] = {1, 2, 6, 7, 11, 4, 8, 13, 10, 5, 17, 9, 16, 20, 3, 12, 14, 18, 19, 15}, k;
    m = 5;
    Max = m - 1;
    Min = (m - 1) / 2;
    for (j = 0; j < n; j++) //����һ��5��B-��t
    {
        s = SearchBTree(t, a[j]);
        InsertBTree(t, a[j], s.pt, s.i);
    }
    cin >> k;
    cout << "B-��:" << endl;
    DispBTree(t);

    s = SearchBTree(t, k);
    if (s.tag == 0)
    {
        InsertBTree(t, k, s.pt, s.i);
        cout << "\n�����,B-��:" << endl;
        DispBTree(t);
    } //�������ֵ �޷�����
    else
    {
        cout << "\n����ʧ��!";
    }
    return 0;
}
