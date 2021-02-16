/*�κ�ϰ��1.8-b
	b.	����һ������ͷ���ĵ�����д���������õ��㷨
		Node* Reverse(Node* first)
*/
#include <iostream>
using namespace std;
struct Node
{
    Node(int x)
    {
        value = x;
        next = NULL;
    }
    int value;
    Node *next;
};

/*
TODO:�����õ��㷨
 */
Node *Reverse(Node *first)
{
    Node *previous, *current;
    previous = NULL;
    current = first;
    while (current->next != NULL)
    {
        first = first->next;
        current->next = previous;
        previous = current;
        current = first;
    }
    first->next = previous;
    return first;
}
void print(Node *node)
{
    while (NULL != node)
    {
        cout << node->value << " ";
        node = node->next;
    }
}
int main()
{
    int iNum;
    cin >> iNum;
    Node *a = NULL;
    Node *pTemp;

    for (int i = 0; i < iNum; i++)
    {
        int tmp;
        cin >> tmp;
        if (i == 0)
        {
            a = new Node(tmp);
            pTemp = a;
        }
        else
        {
            pTemp->next = new Node(tmp);
            pTemp = pTemp->next;
        }
    }

    cout << "����ǰΪ��";
    print(a);
    cout << endl;
    Node *r = Reverse(a);
    cout << "���ú�Ϊ��";
    print(r);
    cout << endl;
    return 0;
}
