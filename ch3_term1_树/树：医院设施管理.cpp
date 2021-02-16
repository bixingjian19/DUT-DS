#include <iostream>
#include <string>
#include <stack>
#include <queue>
using namespace std;

class HosPartNode
{
private:
    int num;
    string name;

public:
    friend class TreeNode;
    friend class Tree;
    HosPartNode()
    {
    }
    HosPartNode(int n, string s)
    {
        num = n;
        name = s;
    }
    string Name()
    {
        return name;
    }
    int Num()
    {
        return num;
    }
};

ostream &operator<<(ostream &out, HosPartNode &node)
{
    out << node.Name() << " : " << node.Num() << "个" << endl;
    return out;
}

class TreeNode
{
private:
    HosPartNode value;
    TreeNode *child, *sibling;

public:
    friend class Tree;
    TreeNode()
    {
        child = sibling = NULL;
    }
    TreeNode(HosPartNode node)
    {
        value = node;
        child = sibling = NULL;
    }
    HosPartNode getValue()
    {
        return value;
    }
    TreeNode *getChild()
    {
        return child;
    }
    TreeNode *getSibling()
    {
        return sibling;
    }
    void setValue(HosPartNode node)
    {
        value = node;
    }
    void setchild(TreeNode *pointer)
    {
        child = pointer;
    }
    void setSibling(TreeNode *pointer)
    {
        sibling = pointer;
    }
    TreeNode *mostrightsibling(TreeNode *node)
    {
        if (node->sibling)
            return mostrightsibling(node->sibling);
        else
            return node;
    }
    TreeNode *findnode(TreeNode *pointer, string str)
    {
        stack<TreeNode *> stack;
        if (pointer)
            stack.push(pointer);
        while (1)
        {
            if (!stack.empty())
            {
                TreeNode *p = stack.top();
                stack.pop();
                if (p->value.name == str)
                    return p;
                if (p->sibling)
                    stack.push(p->sibling);
                if (p->child)
                    stack.push(p->child);
            }
            else
                return NULL;
        }
    }
};

class Tree
{
private:
    TreeNode *root;

public:
    Tree()
    {
        root = new TreeNode;
        root->value.name = "医院";
        root->value.num = 1;
        root->sibling = root->child = NULL;
    }
    TreeNode *getRoot()
    {
        return root;
    }
    TreeNode *Parent(TreeNode *root, TreeNode *current)
    {
        if (root == current || current == NULL)
            return NULL;
        queue<TreeNode *> aQueue;
        if (root)
            aQueue.push(root);
        while (!aQueue.empty())
        {
            TreeNode *pointer = aQueue.front();
            aQueue.pop();
            TreeNode *childpointer = pointer->child;
            while (childpointer)
            {
                aQueue.push(childpointer);
                if (childpointer == current)
                    return pointer;
                else
                {
                    childpointer = childpointer->sibling;
                }
            }
        }
    }
    void findchild(string str)
    {
        TreeNode *pointer = root->findnode(root, str);
        cout << pointer->value;
        RootFirstTraverse(pointer->child);
    }
    bool insert(string str, HosPartNode rootvalue)
    {
        TreeNode *newnode = new TreeNode(rootvalue);
        TreeNode *pointer = root->findnode(root, str);
        if (!pointer)
            return false;
        if (!pointer->child)
        {
            pointer->child = newnode;
        }
        else
        {
            pointer->child->mostrightsibling(pointer->child)->sibling = newnode;
        }
        return true;
    }
    TreeNode *RootFirstTraverse(TreeNode *pointer)
    {
        if (pointer)
        {
            cout << pointer->value;
            if (pointer->child)
                RootFirstTraverse(pointer->child);
            if (pointer->sibling)
                RootFirstTraverse(pointer->sibling);
        }
        else
            return NULL;
    }
    int count(Tree tree, string str1, string str2)
    {
        TreeNode *higherone = root->findnode(root, str1);
        TreeNode *lowerone = higherone->findnode(higherone, str2);
        TreeNode *temp = lowerone;
        int sum = 1;
        while (higherone->value.name != lowerone->value.name)
        {
            sum = sum * (lowerone->value.num);
            lowerone = tree.Parent(root, lowerone);
        }
        return sum;
    }
};

int main()
{
    Tree tree;
    HosPartNode node1(10, "楼层");
    HosPartNode node2(1, "中央大厅");
    HosPartNode node3(4, "配楼");
    HosPartNode node4(1, "电视");
    HosPartNode node5(2, "沙发");
    HosPartNode node6(2, "长走廊");
    HosPartNode node7(1, "走廊连接");
    HosPartNode node8(21, "病房");
    HosPartNode node9(5, "库房");
    HosPartNode node10(1, "卫生间");
    HosPartNode node11(4, "插座");
    HosPartNode node12(2, "病床");
    HosPartNode node13(1, "洗面盆");
    HosPartNode node14(1, "座便器");
    HosPartNode node15(2, "插口");
    HosPartNode node16(1, "面板");

    tree.insert("医院", node1);
    tree.insert("楼层", node2);
    tree.insert("楼层", node3);
    tree.insert("中央大厅", node4);
    tree.insert("中央大厅", node5);
    tree.insert("配楼", node6);
    tree.insert("配楼", node7);
    tree.insert("长走廊", node8);
    tree.insert("走廊连接", node9);
    tree.insert("病房", node10);
    tree.insert("病房", node11);
    tree.insert("病房", node12);
    tree.insert("卫生间", node13);
    tree.insert("卫生间", node14);
    tree.insert("插座", node15);
    tree.insert("插座", node16);

    cout << "输入任意两个结点:" << endl;
    string s1, s2;
    getline(cin, s1);
    getline(cin, s2);
    cout << s1 << "中有" << tree.count(tree, s1, s2) << "个" << s2 << endl;
    cout << "----------------------------------" << endl;
    cout << "输入任意结点:" << endl;
    string s3;
    getline(cin, s3);
    cout << "输出此结点和其子结点:" << endl;
    tree.findchild(s3);
    cout << "----------------------------------" << endl;
    cout << "前序遍历整个树的结果:" << endl;
    TreeNode *root = tree.getRoot();
    tree.RootFirstTraverse(root);

    return 0;
}
