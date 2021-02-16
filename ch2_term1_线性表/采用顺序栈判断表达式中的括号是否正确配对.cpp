/*�κ�ϰ��1.8-h

	h.	������ʽ���������3�����ţ�Բ���š������źʹ����š�
		���һ���㷨����˳��ջ�жϱ��ʽ�е������Ƿ���ȷ��ԡ�
		void Bracketmatch(const char* c)

*/
#include <cstring>
#include <iostream>
#include <string>

using namespace std;
class stack
{
private:
    int maxsize;
    int top;
    char *st;

public:
    stack(int size)
    {
        maxsize = size;
        top = -1;
        st = new char[maxsize];
    }

    void push(char item)
    {
        st[++top] = item;
    }

    void pop()
    {
        top--;
    }

    bool empty()
    {
        return top == -1;
    }
    char gettop()
    {
        if (top == -1)
        {
            return ' ';
        }
        return st[top];
    }
};
/*
TODO:��һ���㷨����˳��ջ�жϱ��ʽc�е������Ƿ���ȷ��ԡ�
����ֵ˵��:���س���Ϊ3���ַ����ַ�����
��1���ַ���ʾ()��ƥ�������
��2���ַ���ʾ[]��ƥ�����
��3���ַ���ʾ{}��ƥ�������
���ƥ�䣬���Ӧ���ַ�����Ϊ'1'����������Ϊ'0'��
���磺����ֵΪ"110",��ʾ��()ƥ�䣬[]ƥ�䣬{}��ƥ��
 */
char *Bracketmatch(const char *c) //����ƥ��
{
    char *res = new char[3];
    res[0] = '1';
    res[1] = '1';
    res[2] = '1';
    int len = strlen(c);

    stack s1(100);
    stack s2(100);
    stack s3(100);

    for (int i = 0; i < len; i++)
    {
        if (c[i] != '(' && c[i] != '[' && c[i] != '{' && c[i] != ')' && c[i] != ']' && c[i] != '}')
        {
            continue;
        }
        if (s1.empty() && c[i] == '(')
        {
            s1.push(c[i]);
            continue;
        }
        if (s2.empty() && c[i] == '[')
        {
            s2.push(c[i]);
            continue;
        }
        if (s3.empty() && c[i] == '{')
        {
            s3.push(c[i]);
            continue;
        }
        if (s1.gettop() == '(' && c[i] == ')')
        {
            s1.pop();
            continue;
        }
        if (s2.gettop() == '[' && c[i] == ']')
        {
            s2.pop();
            continue;
        }
        if (s3.gettop() == '{' && c[i] == '}')
        {
            s3.pop();
            continue;
        }
        if (c[i] == '(' || c[i] == ')')
        {
            s1.push(c[i]);
            continue;
        }
        if (c[i] == '[' || c[i] == ']')
        {
            s2.push(c[i]);
            continue;
        }
        if (c[i] == '{' || c[i] == '}')
        {
            s3.push(c[i]);
            continue;
        }
    }
    res[0] = s1.empty() ? '1' : '0';
    res[1] = s2.empty() ? '1' : '0';
    res[2] = s3.empty() ? '1' : '0';

    return res;
}
void printResult(char *p)
{
    if (NULL != p)
    {
        if (p[0] == '1')
        {
            cout << "()ƥ��" << endl;
        }
        else
        {
            cout << "()��ƥ��" << endl;
        }

        if (p[1] == '1')
        {
            cout << "[]ƥ��" << endl;
        }
        else
        {
            cout << "[]��ƥ��" << endl;
        }

        if (p[2] == '1')
        {
            cout << "{}ƥ��" << endl;
        }
        else
        {
            cout << "{}��ƥ��" << endl;
        }
    }
}
int main()
{

    string s;
    getline(cin, s);
    cout << s << endl;
    char *result = Bracketmatch(s.c_str());
    printResult(result);
    delete result;
    return 0;
}
