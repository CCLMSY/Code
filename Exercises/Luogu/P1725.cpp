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
ll v[N]={0};
int reach[N]={1,0};//可达性检查
ll dp[N]={0};
int solve()
{
    ll n,l,r;
    cin >> n >> l >> r;
    FORLL(i,0,n) cin >> v[i];
    ll ans=-INF;

    //单调队列优化dp
    deque<ll> q;
    q.push_back(0);
    FORLL(i,l,n)
    {
        while(!q.empty()&&(q.front()<i-r||reach[q.front()]==0)) q.pop_front();
        if(!q.empty())
        {
            dp[i]=dp[q.front()]+v[i];
            reach[i]=1;
        }
        while(!q.empty()&&(dp[q.back()]<dp[i-l+1]||reach[q.back()]==0)) q.pop_back();
        q.push_back(i-l+1);
    }
    for(ll i=n-r+1;i<=n;i++)
        if(reach[i]&&dp[i]>ans) ans=dp[i];
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
# 琪露诺

## 题目描述

在幻想乡，琪露诺是以笨蛋闻名的冰之妖精。

某一天，琪露诺又在玩速冻青蛙，就是用冰把青蛙瞬间冻起来。但是这只青蛙比以往的要聪明许多，在琪露诺来之前就已经跑到了河的对岸。于是琪露诺决定到河岸去追青蛙。

小河可以看作一列格子依次编号为 $0$ 到 $N$，琪露诺只能从编号小的格子移动到编号大的格子。而且琪露诺按照一种特殊的方式进行移动，当她在格子 $i$ 时，她只移动到区间 $[i+L,i+R]$ 中的任意一格。你问为什么她这么移动，这还不简单，因为她是笨蛋啊。

每一个格子都有一个冰冻指数 $A_i$，编号为 $0$ 的格子冰冻指数为 $0$。当琪露诺停留在那一格时就可以得到那一格的冰冻指数 $A_i$。琪露诺希望能够在到达对岸时，获取最大的冰冻指数，这样她才能狠狠地教训那只青蛙。

但是由于她实在是太笨了，所以她决定拜托你帮它决定怎样前进。

开始时，琪露诺在编号 $0$ 的格子上，只要她下一步的位置编号大于 $N$ 就算到达对岸。

## 输入格式

第一行三个正整数 $N, L, R$。

第二行共 $N+1$ 个整数，第 $i$ 个数表示编号为 $i-1$ 的格子的冰冻指数 $A_{i-1}$。

## 输出格式

一个整数，表示最大冰冻指数。

## 样例 #1

### 样例输入 #1

```
5 2 3
0 12 3 11 7 -2
```

### 样例输出 #1

```
11
```

## 提示

对于 $60\%$ 的数据，$N \le 10^4$。

对于 $100\%$ 的数据，$N \le 2\times 10^5$，$-10^3 \le  A_i\le 10^3 $，$1 \le L \le R \le N $。数据保证最终答案不超过 $2^{31}-1$。
*/