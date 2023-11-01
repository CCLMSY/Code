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

namespace CCSTL
{
    //输出vector<int>
    int print_vec(vector<int>& vec)
    {
        for(auto i:vec) cout << i << ' ';
        cout << '\n';
        return 0;
    }

    //判断回文
    bool IsPalin(string& s)
    {
        int len=s.length();
        for(int i=0;i<len/2+1;i++)
        {
            if(s[i]!=s[len-1-i]) return false;
        }
        return true;
    }
}

//高精度正整数计算
namespace CCHA
{
    string HAintadd(const string& num1, const string& num2)
    {
        int len1 = num1.length();
        int len2 = num2.length();
        int diff = len1 - len2;
        int carry = 0;
        
        if (diff < 0)
            return HAintadd(num2, num1);
        
        string result(len1 + 1 , '0');
        
        for (int i = len1 - 1; i >= 0; i--)
        {
            int digitSum = (num1[i] - '0') + (i - diff >= 0 ? num2[i - diff] - '0' : 0) + carry;
            carry = digitSum / 10;
            result[i + 1] = (digitSum % 10) + '0';
        }
        
        if (carry)
            result[0] = carry + '0';
        else
            result.erase(result.begin());
        
        return result;
    }

    string HAintmul(const string& num1, const string& num2)
    {
        int len1 = num1.length();
        int len2 = num2.length();
        string result(len1 + len2, '0');
        
        for (int i = len1 - 1; i >= 0; i--)
        {
            int carry = 0;
            for (int j = len2 - 1; j >= 0; j--)
            {
                int digit = (num1[i] - '0') * (num2[j] - '0') + (result[i + j + 1] - '0') + carry;
                carry = digit / 10;
                result[i + j + 1] = (digit % 10) + '0';
            }
            result[i] = carry + '0';
        }
        
        size_t pos = result.find_first_not_of('0');
        if (pos != string::npos) result.erase(0, pos);
        else result = "0";
        
        return result;
    }
}

#define ONLINE_JUDGE
#define IO_OPTIMIZE
//#define MUTIPLE_JUDGE
//#define CHECK_OUT_TIME

using namespace DEFINITION;
//using namespace MOLDULE;
//using namespace CCSTL;
//using namespace CCHA;

/*----------Code Area----------*/
/*
//单调队列：维护一个双端队列使其在过程中保持单调
ll v[1000005]={0};
int solve()
{
    ll n,k;
    cin >> n >> k;
    FORLL(i,0,n-1) cin >> v[i];
    deque<ll> q;//q中元素为原数组中位置
    //单调增
    FORLL(i,0,n-1)
    {
        while(!q.empty()&&v[q.back()]>v[i]) q.pop_back();
        q.push_back(i);
        if(i>=k-1){
            while(q.front()<i-k+1) q.pop_front();
            cout << v[q.front()] << ' ';
        }
    }
    cout << endl;

    q.clear();

    //单调减
    FORLL(i,0,n-1)
    {
        while(!q.empty()&&v[q.back()]<v[i]) q.pop_back();
        q.push_back(i);
        if(i>=k-1){
            while(q.front()<i-k+1) q.pop_front();
            cout << v[q.front()] << ' ';
        }
    }
    cout << endl;

    return 0;
}*/

//Review
ll v[1000005]={0};
deque<ll> q;
int solve()
{
    ll n,k;
    cin >> n >> k;
    FORLL(i,1,n) cin >> v[i];

    //min
    FORLL(i,1,n)
    {
        while(!q.empty()&&v[q.back()]>v[i]) q.pop_back();
        q.push_back(i);
        if(i>=k)
        {
            while(!q.empty()&&q.front()<i-k+1) q.pop_front();
            cout << v[q.front()] << ' ';
        }
    }
    cout << endl;

    //max
    q.clear();
    FORLL(i,1,n)
    {
        while(!q.empty()&&v[q.back()]<v[i]) q.pop_back();
        q.push_back(i);
        if(i>=k)
        {
            while(!q.empty()&&q.front()<i-k+1) q.pop_front();
            cout << v[q.front()] << ' ';
        }
    }
    cout << endl;

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
    while(T--) solve();
#else
    solve();
#endif

#ifdef CHECK_OUT_TIME
    cout << clock() - clk << " ms\n";
#endif
    return 0;
}

/*
# 滑动窗口 /【模板】单调队列

## 题目描述

有一个长为 $n$ 的序列 $a$，以及一个大小为 $k$ 的窗口。现在这个从左边开始向右滑动，每次滑动一个单位，求出每次滑动后窗口中的最大值和最小值。

例如：

The array is $[1,3,-1,-3,5,3,6,7]$, and $k = 3$。

![](https://cdn.luogu.com.cn/upload/pic/688.png)

## 输入格式

输入一共有两行，第一行有两个正整数 $n,k$。
第二行 $n$ 个整数，表示序列 $a$

## 输出格式

输出共两行，第一行为每次窗口滑动的最小值   
第二行为每次窗口滑动的最大值

## 样例 #1

### 样例输入 #1

```
8 3
1 3 -1 -3 5 3 6 7
```

### 样例输出 #1

```
-1 -3 -3 -3 3 3
3 3 5 5 6 7
```

## 提示

【数据范围】    
对于 $50\%$ 的数据，$1 \le n \le 10^5$；  
对于 $100\%$ 的数据，$1\le k \le n \le 10^6$，$a_i \in [-2^{31},2^{31})$。
*/