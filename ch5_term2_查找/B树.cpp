//B-树运算算法
#include <iostream>
using namespace std;
#define MAXM 10      //定义B-树的最大的阶数
typedef int KeyType; //KeyType为关键字类型

typedef struct node
{
    int keynum;             //结点当前拥有的关键字的个数
    KeyType key[MAXM];      //key[1..keynum]存放关键字,key[0]不用 最多存放9个关键字
    struct node *parent;    //双亲结点指针
    struct node *ptr[MAXM]; //孩子结点指针数组ptr[0..keynum]
} BTNode;                   //B-树结点类型

typedef struct //B-树的查找结果类型
{
    BTNode *pt; //指向找到的结点
    int i;      //1..m,在结点中的关键字序号
    int tag;    //1:查找成功,O:查找失败
} Result;       //查找结果类型

int m;   //m阶B-树,为全局变量
int Max; //m阶B-树中每个结点的至多关键字个数,Max=m-1
int Min; //m阶B-树中非叶子结点的至少关键字个数,Min=(m-1)/2
/*
TODO:完成在p->key[1..keynum]中查找i,使得p->key[i]<=k<p->key[i+1]的功能.
函数功能:循环遍历判断关键字值是否符合.
参数说明:p-树结点指针,k-目标关键字.
返回值说明:int型查找到的位置.
*/
//在节点中查找关键字
//函数被下一个函数包含
int Search(BTNode *p, KeyType k)
{ //在p->key[1..keynum]中查找i,使得p->key[i]<=k<p->key[i+1]
    int i = 0;
    for (i = 0; i < p->keynum && p->key[i + 1] < k; i++)
    {
        ;
    }
    return i;
}

/*
TODO:完成在m阶t树t上查找关键字k,返回结果的功能.
函数功能:循环遍历调用查找函数查找,判断同时标记查找状态值,返回查找结果.
参数说明:t-树指针,k-目标关键字.
返回值说明:Result型查找到的位置值.
*/
//在整棵树中查找
// BTNode *pt; //指向找到的结点 或者父节点
// int i;      //1..m,在结点中的关键字序号
// int tag;    //1:查找成功,0:查找失败
Result SearchBTree(BTNode *t, KeyType k)
{ /*在m阶t树t上查找关键字k,返回结果(pt,i,tag)。若查找成功,则特征值
   tag=1,指针pt所指结点中第i个关键字等于k；否则特征值tag=0,等于k的
   关键字应插入在指针Pt所指结点中第i和第i+1个关键字之间*/
    Result result;
    BTNode *pt = t, *pre = NULL;//没有找到的话 就到了叶子节点 返回pre
    int tag = 0, i = 0;
    while (pt != NULL && tag == 0)
    {
        i = Search(pt, k);
        if (i > 0 && pt->key[i] == k)//找到
        {
            tag = 1;
        }
        else//没有找到,继续找子节点
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
TODO:完成将x和ap分别插入到q->key[i+1]和q->ptr[i+1]中的功能.
函数功能:循环关键字组并求改关键字和指针值空出位置然后插入元素.
参数说明:q-结点指针引用,i-位置值,x-目标关键字,ap-插入的结点指针.
返回值说明:无.
*/
//在节点中插入关键字
void Insert(BTNode *&q, int i, KeyType x, BTNode *ap)
{ //将x和ap分别插入到q->key[i+1]和q->ptr[i+1]中
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
TODO:完成将结点q分裂成两个结点,前一半保留,后一半移入新生结点ap的功能.
函数功能:将结点分成两个结点,新结点分配相应空间并存储分裂的后半部分.
参数说明:q-结点指针引用,ap-新赋值结点指针引用.
返回值说明:无.
*/
void Split(BTNode *&q, BTNode *&ap)
{ //将结点q分裂成两个结点,前一半保留,后一半移入新生结点ap
    int div = (m + 1) / 2;
    ap = new BTNode;
    ap->ptr[0] = q->ptr[div]; //中间点的后一个
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
TODO:完成生成含信息(T,x,ap)的新的根结点*t,原t和ap为子树指针的功能.
函数功能:分配空间给新结点,并用参数赋值相关成员变量.
参数说明:t-树指针引用,p-结点指针,x-关键字,ap-新赋值结点指针引用.
返回值说明:无.
*/
void NewRoot(BTNode *&t, BTNode *p, KeyType x, BTNode *ap)
{ //生成含信息(T,x,ap)的新的根结点*t,原p和ap为子树指针
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
TODO:完成在m阶t树t上结点*q的key[i]与key[i+1]之间插入关键字k的功能.
函数功能:判断结点值来调用函数生成新结点, 或者循环执行 插入或者拆分 等操作, 完成插入.
参数说明:t-树指针引用,k-关键字,q-结点指针,i-位置值.
返回值说明:无.
*/
//生成新节点
void InsertBTree(BTNode *&t, KeyType k, BTNode *q, int i)
{               /*在m阶t树t上结点*q的key[i]与key[i+1]之间插入关键字k。若引起
   结点过大,则沿双亲链进行必要的结点分裂调整,使t仍是m阶t树。*/
    BTNode *ap; //分裂出来的新节点
    int finished, needNewRoot, div;
    KeyType x;
    if (q == NULL) //如果q
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
            Insert(q, i, x, ap);  //完成将x和ap分别插入到q->key[i+1]和q->ptr[i+1]中的功能
            if (q->keynum <= Max) //不用分裂 直接结束
            {
                finished = 1;
            }
            else
            {
                div = (m + 1) / 2;
                Split(q, ap);
                x = q->key[div]; //要提到父结点的节点
                if (q->parent)
                {
                    q = q->parent;
                    i = Search(q, x); //在下一轮插入
                }
                else
                {
                    needNewRoot = 1; //要提到父结点 但没有父结点 需要新建一个父结点
                }
            }
        }
        if (needNewRoot == 1)
        {
            NewRoot(t, q, x, ap);
        }
    }
}

void DispBTree(BTNode *t) //以括号表示法输出B-树
{
    int i;
    if (t != NULL)
    {
        cout << '['; //输出当前结点关键字
        for (i = 1; i < t->keynum; i++)
            cout << t->key[i] << ' ';
        cout << t->key[i];
        cout << ']';
        if (t->keynum > 0)
        {
            if (t->ptr[0] != NULL)
                cout << '(';                //至少有一个子树时输出"("号
            for (i = 0; i < t->keynum; i++) //对每个子树进行递归调用
            {
                DispBTree(t->ptr[i]);
                if (t->ptr[i + 1] != NULL)
                    cout << ",";
            }
            DispBTree(t->ptr[t->keynum]);
            if (t->ptr[0] != 0)
                cout << ")"; //至少有一个子树时输出")"号
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
    for (j = 0; j < n; j++) //创建一棵5阶B-树t
    {
        s = SearchBTree(t, a[j]);
        InsertBTree(t, a[j], s.pt, s.i);
    }
    cin >> k;
    cout << "B-树:" << endl;
    DispBTree(t);

    s = SearchBTree(t, k);
    if (s.tag == 0)
    {
        InsertBTree(t, k, s.pt, s.i);
        cout << "\n插入后,B-树:" << endl;
        DispBTree(t);
    } //存在这个值 无法插入
    else
    {
        cout << "\n插入失败!";
    }
    return 0;
}
