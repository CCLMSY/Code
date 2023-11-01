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
    #define scanfll(a) scanf("%lld",&a)
    #define lowbit(x) ((x)&(-(x)))
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
    //输出vector<ll>
    int print_vec(vector<ll>& vec)
    {
        for(auto i:vec) cout << i << ' ';
        cout << endl;
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
#define MUTIPLE_JUDGE
//#define CHECK_OUT_TIME

using namespace DEFINITION;
//using namespace MOLDULE;
//using namespace CCSTL;
//using namespace CCHA;

/*----------Code Area----------*/
#define N 100005
int solve()
{
    ll n,m,k,t;
    cin >> n >> m >> k;
    ll vx,vy;
    cin >> vx >> vy;
    ll x,y;
    int flag=1;
    FORLL(i,1,k)
    {
        cin >> x >> y;
        t=(abs(x-vx)+abs(y-vy));
        if(t%2==0) flag=0;
    }
    if(flag) cout << YES;
    else cout << NO;

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