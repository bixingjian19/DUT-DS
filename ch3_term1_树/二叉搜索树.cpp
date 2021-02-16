/*2.3  二叉搜索树

	void createSearchTree();									//2.3-a 构建二叉搜索树
	BinarySearchTreeNode<T>* search(BinarySearchTreeNode<T>* root, T x);
																//2.3-b 二叉搜索树的查找值为x的结点，并返回此结点
	void insertNode(const T& value);							//2.3-c 二叉搜索树的插入x。
	void deleteByCopying(BinarySearchTreeNode<T>*& node);		//2.3-d 复制删除

*/

#include <iostream>
using namespace std;

template <class T>
class BinarySearchTree;

template <class T>
class BinarySearchTreeNode
{
    friend class BinarySearchTree<T>;

private:
    T element;
    BinarySearchTreeNode<T> *leftChild;
    BinarySearchTreeNode<T> *rightChild;

public:
    BinarySearchTreeNode();
    BinarySearchTreeNode(const T &ele)
    {
        element = ele;
        leftChild = NULL;
        rightChild = NULL;
    }
    BinarySearchTreeNode(const T &ele, BinarySearchTreeNode<T> *l, BinarySearchTreeNode<T> *r)
    {
        element = ele;
        leftChild = l;
        rightChild = r;
    }
    BinarySearchTreeNode<T> *getLeftChild() const
    {
        return leftChild;
    }
    BinarySearchTreeNode<T> *getRightChild() const
    {
        return rightChild;
    }
    void setLeftChild(BinarySearchTreeNode<T> *l)
    {
        leftChild = l;
    }
    void setRightChild(BinarySearchTreeNode<T> *r)
    {
        rightChild = r;
    }
    T getValue() const
    {
        return element;
    }
    void setValue(const T &val)
    {
        element = val;
    }
    bool isLeaf() const
    {
        if (leftChild == NULL && rightChild == NULL)
            return true;
        return false;
    }
};

template <class T>
class BinarySearchTree
{
private:
    BinarySearchTreeNode<T> *root;

public:
    BinarySearchTree()
    {
        root = NULL;
    }
    BinarySearchTree(BinarySearchTreeNode<T> *&r)
    {
        root = r;
    }
    void createSearchTree(); //2.3-a 构建二叉搜索树
    void visit(BinarySearchTreeNode<T> *current);
    BinarySearchTreeNode<T> *search(BinarySearchTreeNode<T> *root, T x);
    //2.3-b 二叉搜索树的查找值为x的结点，并返回此结点
    void insertNode(const T &value);                                                            //2.3-c 二叉搜索树的插入x。
    void deleteByCopying(BinarySearchTreeNode<T> *&node, BinarySearchTreeNode<T> *&tmp2parent); //2.3-d 复制删除
    void inOrder(BinarySearchTreeNode<T> *root);
    void setRoot(BinarySearchTreeNode<T> *r);
    BinarySearchTreeNode<T> *getRoot();
    BinarySearchTreeNode<T> *getParent(BinarySearchTreeNode<T> *root, BinarySearchTreeNode<T> *current) const;
};

/*
函数功能：2.3-a 构建二叉搜索树 
*/
template <class T>
void BinarySearchTree<T>::createSearchTree()
{
    int a;
    cout << "输入int型，以0为结束" << endl;
    cin >> a;
    while (a != 0)
    {
        //TODO:将变量a插入到二叉搜索树中。构建出二叉搜索树。
        insertNode(a);
        cin >> a;
    }
}

template <class T>
BinarySearchTreeNode<T> *BinarySearchTree<T>::getRoot()
{
    return root;
}

template <class T>
void BinarySearchTree<T>::setRoot(BinarySearchTreeNode<T> *r)
{
    this->root = r;
}
template <class T>
BinarySearchTreeNode<T> *BinarySearchTree<T>::getParent(BinarySearchTreeNode<T> *root, BinarySearchTreeNode<T> *current) const
{
    if (root != NULL)
    {
        if (root == current)
        {
            cout << "该节点为根结点，无父结点" << endl;
            return NULL;
        }
        else if (root->leftChild == current || root->rightChild == current)
        {
            return root;
        }
        else
        {
            getParent(root->leftChild, current);
            getParent(root->rightChild, current);
        }
    }
}

template <class T>
void BinarySearchTree<T>::visit(BinarySearchTreeNode<T> *current)
{
    cout << current->element << " ";
}

/*
TODO:2.3-b 二叉搜索树的查找值为x的结点，并返回此结点
 */
template <class T>
BinarySearchTreeNode<T> *BinarySearchTree<T>::search(BinarySearchTreeNode<T> *root, T x)
{
    BinarySearchTreeNode<T> *current = root;
    while (current)
    {
        if (current->element == x)
            return current;
        else if (x < current->element)
            current = current->leftChild;
        else
            current = current->rightChild;
    }
    return NULL;
}

/*
TODO:2.3-c 二叉搜索树的插入,将value插入进去
 */
template <class T>
void BinarySearchTree<T>::insertNode(const T &value)
{
    BinarySearchTreeNode<T> *p = root, *prev = NULL;
    while (p != 0)
    {
        prev = p;
        if (p->getValue() < value)
            p = p->rightChild;
        else
            p = p->leftChild;
    }
    if (root == NULL)
        root = new BinarySearchTreeNode<T>(value);
    else if (prev->getValue() > value)
        prev->leftChild = new BinarySearchTreeNode<T>(value);
    else
        prev->rightChild = new BinarySearchTreeNode<T>(value);
}

/*
TODO:2.3-d 复制删除
*/
template <class T>
void BinarySearchTree<T>::deleteByCopying(BinarySearchTreeNode<T> *&node, BinarySearchTreeNode<T> *&tmp2parent)
{
    BinarySearchTreeNode<T> *previous = NULL, *tmp = node;
    if (node->rightChild == NULL)
        tmp2parent->leftChild = node->leftChild;
    else if (node->leftChild == NULL)
        tmp2parent->rightChild = node->rightChild;
    else
    {
        tmp = node->leftChild;
        previous = node;
        while (tmp->rightChild != NULL)
        {
            previous = tmp;
            tmp = tmp->rightChild;
        }
        node->element = tmp->element;
        if (previous == node) //结点的孩子没有右子树
            previous->leftChild = tmp->leftChild;
        else
            previous->rightChild = tmp->leftChild;
    }
    delete tmp;
}

template <class T>
void BinarySearchTree<T>::inOrder(BinarySearchTreeNode<T> *root)
{
    if (root != NULL)
    {
        inOrder(root->leftChild);
        visit(root);
        inOrder(root->rightChild);
    }
}

int main()
{
    BinarySearchTreeNode<int> *tmp1, *tmp2, *tmp2parent;
    BinarySearchTree<int> st;
    st.createSearchTree();
    tmp1 = st.getRoot();
    st.inOrder(tmp1);
    cout << endl;
    int temp;
    cin >> temp;
    st.insertNode(temp);
    st.inOrder(tmp1);
    cout << endl;

    cout << "输入一个需要查找的值" << endl;
    cin >> temp;                  // 输入一个需要查找的值
    tmp2 = st.search(tmp1, temp); //找到值temp 返回结点，找不到返回NULL
    tmp2parent = st.getParent(st.getRoot(), tmp2);
    if (tmp2 != NULL)
    {
        cout << "查找的值为: " << tmp2->getValue() << endl;
        st.deleteByCopying(tmp2, tmp2parent);
        st.inOrder(tmp1);
    }
    else
        cout << "不存在值" << temp;
    return 0;
}
