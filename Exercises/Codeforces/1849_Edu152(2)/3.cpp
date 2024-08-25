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
    #define Get_Mod(a) ((a+MOD)%MOD)
    ll qcpow(ll x, ll b){
        ll ret = 1;
        for(; b; b >>= 1, x = 1ll * x * x % MOD) if(b & 1) ret = 1ll * ret * x % MOD;
        return ret;
    }
    ll inv(ll x){
        return qcpow(x, MOD - 2);
    }
    ll MO(ll x){
        if(x >= MOD) return x - MOD;
        if(x < 0) return x + MOD;
        return x;
    }
    ll add(ll x, ll y){
        return MO(x + y);
    }
    ll addto(ll &x, ll y){
        return x = add(x, y);
    }
    ll sub(ll x, ll y){
        return MO(x - y);
    }
    ll subto(ll &x, ll y){
        return x = sub(x, y);
    }
    ll mul(ll x, ll y){
        return 1ll * x * y % MOD;
    }
    ll multo(ll &x, ll y){
        return x = mul(x, y);
    }
}

namespace CCSTL
{
    int print_vec(vector<ll>& vec)
    {
        for(auto i:vec) cout << i << ' ';
        cout << endl;
        return 0;
    }

    bool IsPalin(string& s)
    {
        int len=s.length();
        for(int i=0;i<len/2+1;i++)
        {
            if(s[i]!=s[len-1-i]) return false;
        }
        return true;
    }

    ll C[1005][1005]={0};
    void Prepare_Combination(int n){
        C[0][0]=1;
        for(int i=1;i<=n;i++)
            for(int j=0;j<=i;j++){
                if(j==0||j==i) C[i][j]=1;
                else C[i][j]=(C[i-1][j-1]+C[i-1][j]);
            }
    }

    void print_float(double value,int digit){
        cout << fixed << setprecision(digit) << value;
    }
}
#define ONLINE_JUDGE
#define IO_OPTIMIZE
#define MUTIPLE_JUDGE
//#define CHECK_OUT_TIME

using namespace DEFINITION;
//using namespace MOLDULE;
using namespace CCSTL;

/*----------Code Area----------*/
#define N 100005
void solve()
{
    ll n,m;
    cin >> n >> m;
    string s;
    cin >> s;
    vector<ll> pos;
    pos.emplace_back(1);
    FORLL(i,1,n-1) if(s[i]!=s[i-1]) pos.emplace_back(i+1);
    vector<pll> trans;
    ll u,v,ui,vi,a,b;vector<ll>::iterator it;
    int front1=(s[0]=='1');ll cnt=0;
    //print_vec(pos);
    FORLL(i,1,m){
        cin >> u >> v;
        it=upper_bound(ALL(pos),v);vi=it-pos.begin();b=*(--it);
        it=upper_bound(ALL(pos),u);ui=it-pos.begin();a=*(--it);
        if((ui+front1)&1){//0
            if(vi==ui||vi==ui+1) {if(cnt==0) cnt=1;}
            else if((vi+front1)&1) trans.emplace_back(*(++it),v);//0
            else trans.emplace_back(*(++it),b-1);
        }else{//1
            if(vi==ui) {if(cnt==0) cnt=1;}
            else if((vi+front1)&1) trans.emplace_back(u,v);//0
            else trans.emplace_back(u,b-1);
        }
    }
    n=trans.size();
    if(n){
        SORT(trans);cnt++;
        FORLL(i,1,n-1) if(trans[i]!=trans[i-1]) cnt++;
    }
    cout << cnt << endl;
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