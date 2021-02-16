/*课后习题1.8-h

	h.	假设表达式中允许包含3中括号：圆括号、方括号和大括号。
		设计一个算法采用顺序栈判断表达式中的括号是否正确配对。
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
TODO:计一个算法采用顺序栈判断表达式c中的括号是否正确配对。
返回值说明:返回长度为3个字符的字符串，
第1个字符表示()的匹配情况。
第2个字符表示[]的匹配情况
第3个字符表示{}的匹配情况。
如果匹配，则对应的字符设置为'1'，否则设置为'0'。
比如：返回值为"110",表示：()匹配，[]匹配，{}不匹配
 */
char *Bracketmatch(const char *c) //括号匹配
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
            cout << "()匹配" << endl;
        }
        else
        {
            cout << "()不匹配" << endl;
        }

        if (p[1] == '1')
        {
            cout << "[]匹配" << endl;
        }
        else
        {
            cout << "[]不匹配" << endl;
        }

        if (p[2] == '1')
        {
            cout << "{}匹配" << endl;
        }
        else
        {
            cout << "{}不匹配" << endl;
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
