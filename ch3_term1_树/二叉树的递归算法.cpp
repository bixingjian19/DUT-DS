/*2.5 �κ�ϰ��

a.	��һ�ö����������Զ��������ʾ���Ա�д�йض������ĵݹ��㷨
	int degree1(binarytreenode* p)							//2.5-a-i ͳ�ƶ�Ϊ1�Ľ��
	int degree2(binarytreenode* p)							//2.5-a-ii ͳ�ƶ������ж�Ϊ2�Ľ�����
	int degree3(binarytreenode* p)							//2.5-a-iii ͳ�ƶ������ж�Ϊ0�Ľ�����
	int get_height(binarytreenode* p)						//2.5-a-iv ͳ�ƶ������ĸ߶�
	void get_width(binarytreenode* p, int i, int wide[])	//2.5-a-v ͳ�Ƹ�������
	int get_max(binarytreenode* p)							//2.5-a-vi ����������и�����е����Ԫ�ص�ֵ
	void change_children(binarytreenode* p)					//2.5-a-vii ����ÿ����������������������
	void del_leaf(binarytreenode* p)						//2.5-a-viii �Ӷ�������ɾȥ����Ҷ���
	bool wanquan(binarytreenode* pRoot)						//2.5-b ��д�㷨�ж������������Ƿ�Ϊ��ȫ������
*/
#include <iostream>
#include <queue>
using namespace std;
class binarytreenode //���������
{
    int data;

public:
    binarytreenode *leftchild;
    binarytreenode *rightchild;
    binarytreenode(int &d)
    {
        data = d;
        leftchild = NULL;
        rightchild = NULL;
    }
    int &get_data() { return data; }
    void change_data(int &n) { data = n; }
    ~binarytreenode(){};
};

//������
class binarytree
{
    binarytreenode *root;
    static int times;
    int size;

public:
    binarytree()
    {
        size = 0;
        root = NULL;
    }
    int get_size() { return size; }
    binarytreenode *get_root() { return root; }
    void creat() //����������
    {
        binarytreenode *prev;
        cout << "����int������:(��0����)";
        int temp;
        cin >> temp;
        while (temp != 0)
        {
            if (root == NULL)
            {
                root = new binarytreenode(temp);
                size++;
                prev = root;
            }
            else
            {
                prev = root;
                size++;
                for (;;)
                {
                    if (temp < prev->get_data())
                    {
                        if (prev->leftchild == NULL)
                        {
                            prev->leftchild = new binarytreenode(temp);
                            break;
                        }
                        prev = prev->leftchild;
                    }
                    else
                    {
                        if (prev->rightchild == NULL)
                        {
                            prev->rightchild = new binarytreenode(temp);
                            break;
                        }
                        prev = prev->rightchild;
                    }
                }
            }
            cin >> temp;
        }
    }

    void levelorder() //������ȱ���
    {
        binarytreenode *p = get_root();
        queue<binarytreenode *> que;
        cout << "��ȱ������: ";
        if (p != NULL)
            que.push(p);
        else
            cout << "������Ϊ��!";
        while (!que.empty())
        {
            if (p != NULL)
            {
                cout << p->get_data() << " ";
                if (p->leftchild != NULL)
                    que.push(p->leftchild);
                if (p->rightchild != NULL)
                    que.push(p->rightchild);
                que.pop();
                if (!que.empty())
                    p = que.front();
            }
        }
        cout << endl;
    }
    /*
	TODO:ͳ�Ʋ����ض�Ϊ1�Ľ�����
	 */
    int degree1(binarytreenode *p)
    {
        if (p == NULL)
            return 0;
        if (p->leftchild == NULL && p->rightchild != NULL)
        {
            return degree1(p->rightchild) + 1;
        }
        else if (p->rightchild == NULL && p->leftchild != NULL)
        {
            return degree1(p->leftchild) + 1;
        }
        else
        {
            return degree1(p->leftchild) + degree1(p->rightchild);
        }
    }
    /*
	TODO:ͳ�Ʋ����ض�Ϊ2�Ľ�����
	 */
    int degree2(binarytreenode *p)
    {
        if (p == NULL)
            return 0;
        if (p->leftchild == NULL && p->rightchild == NULL)
            return 0;
        if (p->leftchild == NULL && p->rightchild != NULL)
        {
            return degree2(p->rightchild);
        }
        else if (p->rightchild == NULL && p->leftchild != NULL)
        {
            return degree2(p->leftchild);
        }
        else
        {
            return 1 + degree2(p->leftchild) + degree2(p->rightchild);
        }
    }
    /*
	TODO:ͳ�Ʋ����ض�Ϊ0�Ľ�����
	 */
    int degree0(binarytreenode *p)
    {
        if (p == NULL)
            return 0;
        if (p->leftchild == NULL && p->rightchild == NULL)
            return 1;
        else
        {
            return degree0(p->leftchild) + degree0(p->rightchild);
        }
    }
    /*
	TODO:ͳ�Ʋ����ظ߶�
	 */
    int get_height(binarytreenode *p)
    {
        if (p == NULL)
            return 0;
        if (p->leftchild == NULL && p->rightchild == NULL)
        { //�Ǹ���� return1
            return 1;
        }
        else
        {
            return 1 + max(get_height(p->leftchild), get_height(p->rightchild)); //����������������ֵ+1
        }
    }
    void get_width(binarytreenode *p, int i, int wide[]) //ͳ�Ƹ�������
    {
        wide[i++]++;
        if (p->leftchild != NULL)
            get_width(p->leftchild, i, wide);
        if (p->rightchild != NULL)
            get_width(p->rightchild, i, wide);
    }
    /*
	TODO:ͳ�Ʋ����ض������Ŀ��
	 */
    int get_max_width() //��ȱ���
    {
        if (root == NULL)
            return 0;

        int LastLevelWidth = 0; //��һ��Ŀ��
        int CurLevelWidth = 0;  //��һ��Ŀ��

        queue<binarytreenode *> myQueue;
        myQueue.push(root);
        int width = 1;
        LastLevelWidth = 1;
        binarytreenode *pCur = NULL;

        while (!myQueue.empty()) //������л���û���������Ϣ
        {
            while (LastLevelWidth != 0)
            { //����һ��Ԫ�ص�����ȫ����ջ
                pCur = myQueue.front();
                myQueue.pop();

                if (pCur->leftchild != NULL) //������Ԫ���������� ��ջ
                    myQueue.push(pCur->leftchild);

                if (pCur->rightchild != NULL)
                    myQueue.push(pCur->rightchild); //������Ԫ���������� ��ջ
                LastLevelWidth--;
            }

            CurLevelWidth = myQueue.size();                        //��ǰ��Ŀ��
            width = CurLevelWidth > width ? CurLevelWidth : width; //�Ƚ���һ��Ŀ�Ⱥ���һ��Ŀ��
            LastLevelWidth = CurLevelWidth;                        //������һ��
        }
        return width;
    }

    /*
	TODO: ���㲢���ض����������ֵ
	 */
    int get_max(binarytreenode *p)
    {
        while (p->rightchild != NULL)
        { //ֱ���ҵ����ұߵĽ���Ԫ��
            p = p->rightchild;
        }
        return p->get_data();
    }
    /*
	TODO:���������������Һ���
	 */
    void change_children(binarytreenode *p)
    {
        if (p->leftchild != NULL)
        {
            change_children(p->leftchild);
        }
        if (p->rightchild != NULL)
        {
            change_children(p->rightchild);
        }
        binarytreenode *pointer = root; //����
        pointer = p->leftchild;
        p->leftchild = p->rightchild;
        p->rightchild = pointer;
    }
    int find_father(binarytreenode *num, binarytreenode *&fa) //Ѱ�Ҹ��ڵ�
    {
        binarytreenode *p = root;
        int flag = 0;
        while (p != NULL)
        {
            if (p->get_data() > num->get_data())
            {
                fa = p;
                flag = 1;
                p = p->leftchild;
            }
            else if (p->get_data() <= num->get_data() && p != num)
            {
                fa = p;
                flag = 2;
                p = p->rightchild;
            }
            else
            {
                break;
            }
        }
        return flag;
    }
    /*
	TODO:ɾ��Ҷ�ڵ㣬ɾ���ɹ���ʱ�������ӡcout << xxx << "ɾ���ɹ�!" << endl;����xxxΪҶ�ӽڵ��ֵ
	 */
    binarytreenode *del_leaf(binarytreenode *p)
    {
        if (p == NULL || (p->leftchild == NULL && p->rightchild == NULL))
        { //����Ǹ��ڵ� �����ǿ��� returnNULL �����ж�һ������Ǹ��ڵ� ���ɾ���ɹ�
            if (p && p != root)
            {
                cout << p->get_data() << "ɾ���ɹ�!" << endl;
            }
            return NULL;
        }

        p->rightchild = del_leaf(p->rightchild); //�ݹ�������  ��Ϊ�����Ǵ��ұ߿�ʼɾ��
        p->leftchild = del_leaf(p->leftchild);   //�ݹ�������
        return p;
    }

    bool leaf(binarytreenode *pCur)
    {
        if (pCur->leftchild == NULL && pCur->rightchild == NULL)
            return true;
        return false;
    }

    /*
TODO:�ж��Ƿ�����ȫ�����������򷵻�true�����򷵻�false��
 */
    bool wanquan(binarytreenode *pRoot) //�Ƿ���ȫ������//��ȱ��� ���ǰһ��Ϊ�ղ�����һ�����ǿ� ����false
    {
        if (pRoot == NULL)
            return true;
        binarytreenode *p, *r;
        queue<binarytreenode *> q;
        q.push(pRoot);
        while (!q.empty())
        {
            int z = q.size();
            for (int i = 0; i < z; i++) //�Ե�ǰ������Ԫ�ر���
            {
                p = q.front();
                q.pop();
                if (p == NULL) //������κ�һ���ǿ�
                {

                    while (!q.empty()) //����������һ�����ǿյ�ʱ��
                    {
                        r = q.front();
                        q.pop();
                        if (r != NULL)
                            return false;
                    }
                    break;
                }
                q.push(p->leftchild);  //��������ջ
                q.push(p->rightchild); //��������ջ
            }
        }
        return true;
    }
};
int binarytree::times = 0;
int main()
{
    binarytree tree;
    tree.creat();
    tree.levelorder();
    cout << "��Ϊ1�Ľ�����: " << tree.degree1(tree.get_root()) << endl;
    cout << "��Ϊ2�Ľ�����: " << tree.degree2(tree.get_root()) << endl;
    cout << "��Ϊ0�Ľ�����: " << tree.degree0(tree.get_root()) << endl;
    cout << "�������߶�: " << tree.get_height(tree.get_root()) << endl;
    cout << "���������: " << tree.get_max_width() << endl;
    cout << "���ֵ:" << tree.get_max(tree.get_root()) << endl;
    cout << "ɾ��Ҷ�ڵ�:" << endl;
    tree.del_leaf(tree.get_root());
    tree.levelorder();
    cout << "�������Һ���. . ." << endl;
    tree.change_children(tree.get_root());
    tree.levelorder();
    if (tree.wanquan(tree.get_root()))
        cout << "�ö���������ȫ������" << endl;
    else
        cout << "�ö�����������ȫ������" << endl;
    return 0;
}
