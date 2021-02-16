#include <iostream>
#include <string>
#include <queue>
using namespace std;
int servetime = 2;
class user
{
public:
    int endtime;
    string priority;
    user(int a, string b)
    {
        endtime = a;
        priority = priority + b;
    }
};
class nuser : public user
{
public:
    int nid;
    nuser(int a, string b, int c) : user(a, b)
    {
        nid = c;
    }
};
class vuser : public user
{
public:
    int vid;
    vuser(int a, string b, int c) : user(a, b)
    {
        vid = c;
    }
};
class ouser : public user
{
public:
    int oid;
    ouser(int a, string b, int c) : user(a, b)
    {
        oid = c;
    }
};
class bank
{
public:
    int bankid;
    string banktype;
    int endtime;
    int userid;
    string usertype;
    bank(){};
    bank(int a, string b, int c, int d, string e)
    {
        bankid = a;
        banktype = banktype + b;
        endtime = c;
        userid = d;
        usertype = usertype + e;
    }
};
class simulator
{
public:
    queue<nuser> q1;
    queue<vuser> q2;
    queue<ouser> q3;
    bank nb1, nb2, nb3, vb, ob;
    simulator(queue<nuser> a, queue<vuser> b, queue<ouser> c, bank d, bank e, bank f, bank g, bank h)
    {
        q1 = a;
        q2 = b;
        q3 = c;
        nb1 = d;
        nb2 = e;
        nb3 = f;
        vb = g;
        ob = h;
    }
    void isservetimeend(int time)
    {
        if (nb1.endtime == time)
            nb1.endtime = 0;
        if (nb2.endtime == time)
            nb2.endtime = 0;
        if (nb3.endtime == time)
            nb3.endtime = 0;
        if (vb.endtime == time)
            vb.endtime = 0;
        if (ob.endtime == time)
            ob.endtime = 0;
    }
    void callnumber(int &nid, int &vid, int &oid, int nnum, int vnum, int onum, int time, int servetime)
    {
        for (int i = 0; i < nnum; i++)
        {
            cout << "calling normal user " << nid << endl;
            q1.push(nuser(time + servetime, "normal", nid++));
        }
        for (int i = 0; i < vnum; i++)
        {
            cout << "calling vip user " << vid << endl;
            q2.push(vuser(time + servetime, "vip", vid++));
        }
        for (int i = 0; i < onum; i++)
        {
            cout << "calling official user " << oid << endl;
            q3.push(ouser(time + servetime, "official", oid++));
        }
    }
    void getservice(int time)
    {
        if (ob.endtime == 0 && !q3.empty())
        {
            ob.endtime = time + servetime;
            ob.userid = q3.front().oid;
            ob.usertype = ob.usertype + q3.front().priority;
            q3.pop();
        }
        if (vb.endtime == 0 && !q2.empty())
        {
            vb.endtime = time + servetime;
            vb.userid = q2.front().vid;
            vb.usertype = q2.front().priority;
            q2.pop();
        }
        if (nb1.endtime == 0 && !q1.empty())
        {
            nb1.endtime = time + servetime;
            nb1.userid = q1.front().nid;
            nb1.usertype = q1.front().priority;
            q1.pop();
        }
        if (nb2.endtime == 0 && !q1.empty())
        {
            nb2.endtime = time + servetime;
            nb2.userid = q1.front().nid;
            nb2.usertype = q1.front().priority;
            q1.pop();
        }
        if (nb3.endtime == 0 && !q1.empty())
        {
            nb3.endtime = time + servetime;
            nb3.userid = q1.front().nid;
            nb3.usertype = q1.front().priority;
            q1.pop();
        }
        if (vb.endtime == 0 && !q1.empty())
        {
            vb.endtime = time + servetime;
            vb.userid = q1.front().nid;
            vb.usertype = q1.front().priority;
            q1.pop();
        }
        if (ob.endtime == 0 && !q1.empty())
        {
            ob.endtime = time + servetime;
            ob.userid = q1.front().nid;
            ob.usertype = q1.front().priority;
            q1.pop();
        }
    }
    void waitinguser()
    {
        cout << " " << endl;
        cout << q1.size() << " normal user is waiting " << endl;
        cout << q2.size() << " vip waiting " << endl;
        cout << q3.size() << " official waiting " << endl;
        cout << " " << endl;
    }
    void bankstatus()
    {
        if (!nb1.endtime == 0)
            cout << "BANK " << nb1.banktype << " " << nb1.bankid << " is serving"
                 << " USER " << nb1.usertype << " " << nb1.userid << endl;
        if (!nb2.endtime == 0)
            cout << "BANK " << nb2.banktype << " " << nb2.bankid << " is serving"
                 << " USER " << nb2.usertype << " " << nb2.userid << endl;
        if (!nb3.endtime == 0)
            cout << "BANK " << nb3.banktype << " " << nb3.bankid << " is serving"
                 << " USER " << nb3.usertype << " " << nb3.userid << endl;
        if (!vb.endtime == 0)
            cout << "BANK " << vb.banktype << " " << vb.bankid << " is serving"
                 << " USER " << vb.usertype << " " << vb.userid << endl;
        if (!ob.endtime == 0)
            cout << "BANK " << ob.banktype << " " << ob.bankid << " is serving"
                 << " USER " << ob.usertype << " " << ob.userid << endl;
        cout << "  " << endl;
    }
};
int main()
{
    int nid = 0, vid = 0, oid = 0;
    bank nb1(1, "normal", 0, 0, ""), nb2(2, "normal", 0, 0, ""), nb3(3, "normal", 0, 0, ""), vb(4, "vip", 0, 0, ""), ob(5, "official", 0, 0, "");
    queue<nuser> q1;
    queue<vuser> q2;
    queue<ouser> q3;
    simulator simulate_tool(q1, q2, q3, nb1, nb2, nb3, vb, ob);
    int USER[7][3] = {{3, 1, 1}, {5, 0, 0}, {0, 0, 0}, {5, 1, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}};
    for (int time = 0; time < 7; time++)
    {
        cout << "----------------------------------------------------------------" << endl;
        cout << "this is " << time << " s" << endl;
        cout << " " << endl;

        int nnum = USER[time][0];
        int vnum = USER[time][1];
        int onum = USER[time][2];

        simulate_tool.isservetimeend(time);

        simulate_tool.callnumber(nid, vid, oid, nnum, vnum, onum, time, servetime);

        simulate_tool.getservice(time);

        simulate_tool.waitinguser();

        simulate_tool.bankstatus();
    }
    return 0;
}
