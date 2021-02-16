#include <iostream>
#include <string>
#include <queue>
#include <stack>
using namespace std;

template <class T>

class BinaryTree;

template <class T>

class BinaryTreeNode
{
private:
    T element;                     //����������
    BinaryTreeNode<T> *leftChild;  //�������ӽ��
    BinaryTreeNode<T> *rightChild; //�����Һ��ӽ��
public:
    friend class BinaryTree<T>; //������������Ϊ��������Ԫ�࣬�Ա����˽�����ݳ�Ա
    BinaryTreeNode()            //Ĭ�Ϲ��캯��
    {
        element = 0;
        leftChild = NULL;
        rightChild = NULL;
    }
    BinaryTreeNode(const T &ele) //�������ݵĹ��캯��
    {
        element = ele;
        leftChild = NULL;
        rightChild = NULL;
    }
    BinaryTreeNode(const T &ele, BinaryTreeNode<T> *l, BinaryTreeNode<T> *r) //��������ֵ�����Һ��ӽ��Ĺ��캯��
    {
        element = ele;
        leftChild = l;
        rightChild = r;
    }
    BinaryTreeNode<T> *getLeftChild() const //���ظý������ӽ��
    {
        return leftChild;
    }
    BinaryTreeNode<T> *getrightChild() const //���ظý����Һ��ӽ��
    {
        return rightChild;
    }
    void setleftChild(BinaryTreeNode<T> *l) //���øý������ӽ��
    {
        leftChild = l;
    }
    void setrightChild(BinaryTreeNode<T> *r) //���øý����Һ��ӽ��
    {
        rightChild = r;
    }
    T getValue(const T &val) //���ظý�������ֵ
    {
        val = element;
        return val;
    }
    void setValue(const T &val) //���øý����������ֵ
    {
        element = val;
    }
    bool isLeaf() const //�жϸý���Ƿ���Ҷ�ӽ�㣬���ǣ��򷵻�true
    {
        if (rightChild == NULL && leftChild == NULL)
            return true;
        else
            return false;
    }
    void showEle()
    {
        cout << element << ' ';
    }
};

template <class T>

class BinaryTree
{
public:
    BinaryTreeNode<T> *root; //�����������
    BinaryTree()             //Ĭ�Ϲ��캯��
    {
        root = NULL;
    }
    ~BinaryTree() //��������
    {
        deleteBinaryTree(root);
    }
    bool isEmpty() const //�ж��������Ƿ�Ϊ����
    {
        if (root == NULL)
            return true;
        else
            return false;
    }
    BinaryTreeNode<T> *Root() //���ض������ĸ����
    {
        return root;
    }

    BinaryTreeNode<T> *buildPreAndIn(string prestr, string instr);   //2.1-a ʵ���������������й�����������㷨
    BinaryTreeNode<T> *buildPostAndIn(string poststr, string instr); //2.1-b ʵ���ɺ����������й�����������㷨
    void levelOrder(BinaryTreeNode<T> *root);                        //2.1-c ������ȱ�����rootΪ����������
    void inOrder(BinaryTreeNode<T> *root);                           //2.1-d ���������rootΪ����������
    void InOrderWithoutRecusion(BinaryTreeNode<T> *root);            //2.1-e �ǵݹ����������������������
    void deleteBinaryTree(BinaryTreeNode<T> *root);                  //ɾ����rootΪ����������

    void visit(BinaryTreeNode<T> *p) //����һ����ʵ��
    {
        p->showEle();
    }
    BinaryTreeNode<T> *setTree()
    {
        T ch;
        cin >> ch;
        BinaryTreeNode<T> *treeroot = NULL;
        if (ch == 0 || ch == '0')
            return NULL;
        else
        {
            treeroot = new BinaryTreeNode<T>;
            treeroot->element = ch;
            treeroot->leftChild = setTree();
            treeroot->rightChild = setTree();
            return treeroot;
        }
    }
};

/*
TODO��2.1-a ʵ���������������й�����������㷨
	  return ���ĸ����root
 */
template <class T>
BinaryTreeNode<T> *BinaryTree<T>::buildPreAndIn(string prestr, string instr)
{
    BinaryTreeNode<char> *root = new BinaryTreeNode<char>();
    if (prestr.length() == 0)
    {
        return NULL;
    }
    char rootch = prestr[0];

    int index = instr.find(rootch);
    string lchild_instr = instr.substr(0, index);
    string rchild_instr = instr.substr(index + 1);
    int lchild_length = lchild_instr.length();
    int rchild_length = rchild_instr.length();
    string lchild_prestr = prestr.substr(1, lchild_length);
    string rchild_prestr = prestr.substr(1 + lchild_length);

    if (root != NULL)
    {
        root->setValue(rootch);
        root->setleftChild(buildPreAndIn(lchild_prestr, lchild_instr));
        root->setrightChild(buildPreAndIn(rchild_prestr, rchild_instr));
    }

    return root;
}

/*
TODO��2.1-b ʵ���ɺ����������й�����������㷨
	  return ���ĸ����root
 */
template <class T>
BinaryTreeNode<T> *BinaryTree<T>::buildPostAndIn(string poststr, string instr)
{
    BinaryTreeNode<char> *root = new BinaryTreeNode<char>();
    if (poststr.length() == 0)
    {
        return NULL;
    }
    char rootch = poststr[poststr.size() - 1];

    int index = instr.find(rootch);
    string lchild_instr = instr.substr(0, index);
    string rchild_instr = instr.substr(index + 1);
    int lchild_length = lchild_instr.length();
    int rchild_length = rchild_instr.length();
    string lchild_poststr = poststr.substr(0, lchild_length);
    string rchild_poststr = poststr.substr(lchild_length, poststr.size() - 1 - lchild_length);

    if (root != NULL)
    {
        root->setValue(rootch);
        root->setleftChild(buildPostAndIn(lchild_poststr, lchild_instr));
        root->setrightChild(buildPostAndIn(rchild_poststr, rchild_instr));
    }

    return root;
}

/*
TODO��2.1-c ������ȱ�����rootΪ����������
 */
template <class T>
void BinaryTree<T>::levelOrder(BinaryTreeNode<T> *root)
{
    queue<BinaryTreeNode<T> *> q;
    BinaryTreeNode<T> *tempnode = root;
    q.push(root);
    while (q.size() != 0)
    {
        tempnode = q.front();
        visit(tempnode);
        if (tempnode->leftChild)
        {
            q.push(tempnode->leftChild);
        }
        if (tempnode->rightChild)
        {
            q.push(tempnode->rightChild);
        }
        q.pop();
    }
}

/*
TODO��2.1-d �ݹ����������rootΪ����������
 */
template <class T>
void BinaryTree<T>::inOrder(BinaryTreeNode<T> *root)
{
    if (root != NULL)
    {
        inOrder(root->leftChild);
        visit(root);
        inOrder(root->rightChild);
    }
}

/*
TODO��2.1-e �ǵݹ����������������������
 */
template <class T>
void BinaryTree<T>::InOrderWithoutRecusion(BinaryTreeNode<T> *root)
{
    stack<BinaryTreeNode<T> *> nodestack;
    BinaryTreeNode<T> *pointer = root;
    while (!nodestack.empty() || pointer)
    {
        if (pointer)
        {
            nodestack.push(pointer);
            pointer = pointer->leftChild;
        }
        else
        {
            pointer = nodestack.top();
            visit(pointer);
            pointer = pointer->rightChild;
            nodestack.pop();
        }
    }
}

template <class T>

void BinaryTree<T>::deleteBinaryTree(BinaryTreeNode<T> *root)
{
    if (root == NULL)
        return;
    BinaryTreeNode<T> *temp = NULL;
    queue<BinaryTreeNode<T> *> node_queue;
    if (root->leftChild)
        node_queue.push(root->leftChild);
    if (root->rightChild)
        node_queue.push(root->rightChild);
    delete root;
    while (!node_queue.empty())
    {
        temp = node_queue.front();
        node_queue.pop();
        if (temp->leftChild != NULL)
            node_queue.push(temp->leftChild);
        if (temp->rightChild != NULL)
            node_queue.push(temp->rightChild);
        delete temp;
    }
    root = NULL;
}

int main()
{
    BinaryTree<char> test;
    BinaryTreeNode<char> *root = NULL, *root2 = NULL;
    string prestr, instr, poststr;
    getline(cin, prestr);
    getline(cin, instr);
    getline(cin, poststr);
    root = test.buildPreAndIn(prestr, instr);    //2.1-a ʵ���������������й�����������㷨
    root2 = test.buildPostAndIn(poststr, instr); //2.1-b ʵ���ɺ����������й�����������㷨

    cout << "PreAndIn:" << endl;
    cout << "inOrder: ";
    test.inOrder(root);
    cout << endl;

    cout << "levelOrder: ";
    test.levelOrder(root);
    cout << endl;

    cout << "InOrderWithoutRecusion: ";
    test.InOrderWithoutRecusion(root);
    cout << endl;

    cout << "PostAndIn:" << endl;
    cout << "inOrder: ";
    test.inOrder(root2);
    cout << endl;

    cout << "levelOrder: ";
    test.levelOrder(root2);
    cout << endl;

    cout << "InOrderWithoutRecusion: ";
    test.InOrderWithoutRecusion(root2);
    cout << endl;
    return 0;
}
