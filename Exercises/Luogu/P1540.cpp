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
        
    //从无重复记录的vector<int>中二分查找x。调用：Bi_find(vec,vec.begin(),vec.end(),x);
    vector<int>::iterator Bi_find(vector<int>& vec,vector<int>::iterator l,vector<int>::iterator r,int x)
    {
        if(r==vec.end()) r--;
        if(l>r) return vec.end();
        ptrdiff_t len=distance(l,r);
        vector<int>::iterator mid=l+len/2;
        vector<int>::iterator re;
        if(*mid==x) return mid;
        
        mid--;
        re=Bi_find(vec,l,mid,x);
        mid++;
        if(re==vec.end())
        {
            mid++;
            return Bi_find(vec,mid,r,x);
        }
        else return re;
    }

    //输出vector<int>
    int print_vec(vector<int>& vec)
    {
        for(auto i:vec) cout << i << ' ';
        cout << '\n';
        return 0;
    }
}

#define ONLINE_JUDGE
#define IO_OPTIMIZE
//#define MUTIPLE_JUDGE
//#define CHECK_OUT_TIME

using namespace DEFINITION;
//using namespace MOLDULE;
//using namespace CCSTL;

/*----------Code Area----------*/
/*1.STL deque 双端队列
int solve()
{
    int M,N;
    cin >> M >> N;
    deque<int> q;
    int t,cnt=0;
    for(int i=0;i<N;i++)
    {
        cin >> t;
        if(find(ALL(q),t)==q.end())
        {
            cnt++;
            q.push_back(t);
            if(q.size()>M) q.pop_front();
        }
    }
    cout << cnt << endl;
    return 0;
}
*/

/*2.STL queue 队列 + Hash*/
int solve()
{
    int hash[1005]={0};
    queue<int> q;
    int M,N;
    cin >> M >> N;
    int t,cnt=0;
    for(int i=0;i<N;i++)
    {
        cin >> t;
        if(hash[t]);
        else
        {
            cnt++;
            q.push(t);
            hash[t]=1;
            if(q.size()>M)
            {
                hash[q.front()]=0;
                q.pop();
            }
        }
    }
    cout << cnt << endl;
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