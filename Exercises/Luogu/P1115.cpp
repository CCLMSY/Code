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
#define N 200005
ll s[N]={0};
ll dp[N]={0};
int solve()
{
    //法1：贪心

    //法2：dp
    ll n;
    ll k=N;//限定子序长度
    cin >> n;
    FORLL(i,1,n)
    {
        cin >> s[i];
        s[i]+=s[i-1];
    }//前缀和

    ll ans=-INF;

    //传统dp：检查i左边k个s，得到max(s[i]-s[j])，O(kn)
    /*
    FORLL(i,1,n)
    {
        dp[i]=s[i];
        for(ll j=i-1;j>i-k&&j>0;j--)
            dp[i]=max({dp[i],s[i]-s[j]});
        ans=max({ans,dp[i]});
    }*/

    //单调队列优化dp：对于i左边k个s做单调队列（增），O(n)
    deque<ll> q;
    FORLL(i,1,n)
    {
        ans=max({ans,s[i]});
        while(!q.empty()&&q.front()<i-k+1) q.pop_front();
        if(!q.empty())
            ans=max({ans,s[i]-s[q.front()]});
        while(!q.empty()&&s[q.back()]>s[i]) q.pop_back();
        q.push_back(i);
    }

    cout << ans << endl;

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
# 最大子段和/最大子序和

## 题目描述

给出一个长度为 $n$ 的序列 $a$，选出其中连续且非空的一段使得这段和最大。

## 输入格式

第一行是一个整数，表示序列的长度 $n$。

第二行有 $n$ 个整数，第 $i$ 个整数表示序列的第 $i$ 个数字 $a_i$。

## 输出格式

输出一行一个整数表示答案。

## 样例 #1

### 样例输入 #1

```
7
2 -4 3 -1 2 -4 3
```

### 样例输出 #1

```
4
```

## 提示

#### 样例 1 解释

选取 $[3, 5]$ 子段 $\{3, -1, 2\}$，其和为 $4$。

#### 数据规模与约定

- 对于 $40\%$ 的数据，保证 $n \leq 2 \times 10^3$。
- 对于 $100\%$ 的数据，保证 $1 \leq n \leq 2 \times 10^5$，$-10^4 \leq a_i \leq 10^4$。
*/