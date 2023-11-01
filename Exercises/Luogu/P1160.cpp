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
int solve()
{
    int l[100005],r[100005];
    r[0]=1;
    int M,N,a,p,t;
    cin >> N;
    for(int i=2;i<=N;i++)
    {
        cin >> a >> p;
        if(p)
        {
            t=r[a];
            l[t]=i;
            r[i]=t;
            r[a]=i;
            l[i]=a;
        }
        else
        {
            t=l[a];
            r[t]=i;
            l[i]=t;
            l[a]=i;
            r[i]=a;
        }
    }
    cin >> M;
    for(int i=0;i<M;i++)
    {
        cin >> a;
        if(l[a]==r[a]) continue;
        r[l[a]]=r[a];
        l[r[a]]=l[a];
        l[a]=r[a]=0;
    }
    t=0;
    while(r[t])
    {
        cout << r[t] << Presentation(r[r[t]],0);
        t=r[t];
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
# 队列安排

## 题目描述

一个学校里老师要将班上 $N$ 个同学排成一列，同学被编号为 $1\sim N$，他采取如下的方法：

1. 先将 $1$ 号同学安排进队列，这时队列中只有他一个人；

2. $2\sim N$ 号同学依次入列，编号为 $i$ 的同学入列方式为：老师指定编号为 $i$ 的同学站在编号为 $1\sim(i-1)$ 中某位同学（即之前已经入列的同学）的左边或右边；

3. 从队列中去掉 $M$ 个同学，其他同学位置顺序不变。

在所有同学按照上述方法队列排列完毕后，老师想知道从左到右所有同学的编号。

## 输入格式

第一行一个整数 $N$，表示了有 $N$ 个同学。

第 $2\sim N$ 行，第 $i$ 行包含两个整数 $k,p$，其中 $k$ 为小于 $i$ 的正整数，$p$ 为 $0$ 或者 $1$。若 $p$ 为 $0$，则表示将 $i$ 号同学插入到 $k$ 号同学的左边，$p$ 为 $1$ 则表示插入到右边。

第 $N+1$ 行为一个整数 $M$，表示去掉的同学数目。

接下来 $M$ 行，每行一个正整数 $x$，表示将 $x$ 号同学从队列中移去，如果 $x$ 号同学已经不在队列中则忽略这一条指令。

## 输出格式

一行，包含最多 $N$ 个空格隔开的整数，表示了队列从左到右所有同学的编号。

## 样例 #1

### 样例输入 #1

```
4
1 0
2 1
1 0
2
3
3
```

### 样例输出 #1

```
2 4 1
```

## 提示

**【样例解释】**

将同学 $2$ 插入至同学 $1$ 左边，此时队列为：

`2 1`

将同学 $3$ 插入至同学 $2$ 右边，此时队列为：

`2 3 1`  

将同学 $4$ 插入至同学 $1$ 左边，此时队列为：

`2 3 4 1`  

将同学 $3$ 从队列中移出，此时队列为：

`2 4 1`  

同学 $3$ 已经不在队列中，忽略最后一条指令

最终队列：

`2 4 1`  

**【数据范围】**

对于 $20\%$ 的数据，$1\leq N\leq 10$。

对于 $40\%$ 的数据，$1\leq N\leq 1000$。

对于 $100\%$ 的数据，$1<M\leq N\leq 10^5$。
*/