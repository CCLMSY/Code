#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll,ll> pll;

const double pi=3.141592653589793;
const double eps=1e-8;
const int MOD=1e9+7;
const int INF=0x7fffffff;

namespace DEFINITION
{
    #define RESET(A) memset(A,0,sizeof(A))
    #define ALL(A) A.begin(),A.end()
    #define SORT(A) sort(ALL(A))
    #define Presentation(i,r) " \n"[i==r]
    #define FORLL(i,l,r) for(ll i=l;i<=r;i++)
    #define NO "NO\n"
    #define YES "YES\n"
}

namespace MOLDULE
{
    int qcpow(int x, int b){
        int ret = 1;
        for(; b; b >>= 1, x = 1ll * x * x % MOD) if(b & 1) ret = 1ll * ret * x % MOD;
        return ret;
    }
    int inv(int x){
        return qcpow(x, MOD - 2);
    }
    int MO(int x){
        if(x >= MOD) return x - MOD;
        if(x < 0) return x + MOD;
        return x;
    }
    int add(int x, int y){
        return MO(x + y);
    }
    int addto(int &x, int y){
        return x = add(x, y);
    }
    int sub(int x, int y){
        return MO(x - y);
    }
    int subto(int &x, int y){
        return x = sub(x, y);
    }
    int mul(int x, int y){
        return 1ll * x * y % MOD;
    }
    int multo(int &x, int y){
        return x = mul(x, y);
    }
}

#define ONLINE_JUDGE
#define IO_OPTIMIZE
//#define MUTIPLE_JUDGE
//#define CHECK_OUT_TIME

using namespace DEFINITION;
//using namespace MOLDULE;

/*----------Code Area----------*/
/*1.静态单向链表
struct node {
    int id,nextid;
}nodes[105];
int solve()
{
    int m,n;
    cin >> n >> m;
    nodes[0].nextid=1;
    for(int i=1;i<=n;i++)
    {
        nodes[i].id=i;
        nodes[i].nextid=i+1;
    }
    nodes[n].nextid=1;
    int pre,now;
    pre=now=0;
    while(n--)
    {
        for(int i=0;i<m;i++)
        {
            pre=now;
            now=nodes[pre].nextid;
        }
        cout << nodes[now].id << Presentation(n,0);
        nodes[pre].nextid=nodes[now].nextid;
    }
    return 0;
}
*/

/*2.数组实现静态单链表
int nextid[105]={0};
int solve()
{
    int m,n;
    cin >> n >> m;
    for(int i=0;i<n;i++) nextid[i]=i+1;
    nextid[n]=1;
    int pre,now;
    pre=now=0;
    while(n--)
    {
        for(int i=0;i<m;i++)
        {
            pre=now;
            now=nextid[now];
        }
        nextid[pre]=nextid[now];
        cout << now << Presentation(n,0);
    }
    return 0;
}
*/

//3.STL list 双向链表
list<int> node;
int solve()
{
    int m,n;
    cin >> n >> m;
    for(int i=0;i<n;i++) node.emplace_back(i+1);
    list<int>::iterator it,nextit=node.begin();
    while(n--)
    {
        it=nextit;
        for(int i=1;i<m;i++)
        {
            it++;
            if(it==node.end()) it=node.begin();
        }
        cout << *it << Presentation(n,0);
        nextit=++it;
        if(nextit==node.end()) nextit=node.begin();
        node.erase(--it);
    }
    return 0;
}

/*----------Code Area----------*/

int main(){
    int clk = clock();

#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif

#ifdef IO_OPTIMIZE
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
#endif

#ifdef MUTIPLE_JUDGE
    long T; cin >> T;
    while(t--) solve();
#else
    solve();
#endif

#ifdef CHECK_OUT_TIME
    cout << clock() - clk << " ms\n";
#endif
    return 0;
}

/*

# 约瑟夫问题

## 题目描述

$n$ 个人围成一圈，从第一个人开始报数,数到 $m$ 的人出列，再由下一个人重新从 $1$ 开始报数，数到 $m$ 的人再出圈，依次类推，直到所有的人都出圈，请输出依次出圈人的编号。

**注意：本题和《深入浅出-基础篇》上例题的表述稍有不同。书上表述是给出淘汰 $n-1$ 名小朋友，而该题是全部出圈。**

## 输入格式

输入两个整数 $n,m$。

## 输出格式

输出一行 $n$ 个整数，按顺序输出每个出圈人的编号。

## 样例 #1

### 样例输入 #1

```
10 3
```

### 样例输出 #1

```
3 6 9 2 7 1 8 5 10 4
```

## 提示

$1 \le m, n \le 100$

*/