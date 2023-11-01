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
      ll n;
      cin >> n;
      vector<ll> v;
      v.emplace_back(-60);
      vector<pll> op;
      ll t,mx=-50,mxi=0,mn=50,mni=0,cntn=0,cntp=0;
      FORLL(i,1,n){
            cin >> t;
            v.emplace_back(t);
            if(t>0) cntp++;if(t<0) cntn++;
            if(t>mx) mx=t,mxi=i;
            if(t<mn) mn=t,mni=i;
      }
      if(n==1||cntn+cntp==0) {cout << "0" << endl;return;}
      if(cntn==0) {cout << n-1 << endl;FORLL(i,2,n) cout << i << ' ' << i-1 << endl;return;}
      if(cntp==0) {cout << n-1 << endl;for(ll i=n-1;i>0;i--) cout << i << ' ' << i+1 << endl;return;}
      if(mx>=-mn){
            if(cntn<=12){
                  FORLL(i,1,n) if(v[i]<0) {v[i]+=v[mxi];op.emplace_back(i,mxi);}
                  FORLL(i,2,n) {v[i]+=v[i-1];op.emplace_back(i,i-1);}
                  cout << op.size() << endl;
                  for(auto i:op) cout << i.first << ' ' << i.second << endl;
                  return;}//12+19
            else{
                  while(-v[mni]<mx) {v[mni]*=2;op.emplace_back(mni,mni);}
                  FORLL(i,1,n) if(v[i]>0) {v[i]+=v[mni];op.emplace_back(i,mni);}
                  for(ll i=n-1;i>0;i--) {v[i]+=v[i+1];op.emplace_back(i,i+1);}
                  cout << op.size() << endl;
                  for(auto i:op) cout << i.first << ' ' << i.second << endl;
                  return;}//7+5+19
      }else if(mx<-mn){
            if(cntp<=12){
                  FORLL(i,1,n) if(v[i]>0) {v[i]+=v[mni];op.emplace_back(i,mni);}
                  for(ll i=n-1;i>0;i--) {v[i]+=v[i+1];op.emplace_back(i,i+1);}
                  cout << op.size() << endl;
                  for(auto i:op) cout << i.first << ' ' << i.second << endl;
                  return;}//12+19
            else{
                  while(v[mxi]<-mn) {v[mxi]*=2;op.emplace_back(mxi,mxi);}
                  FORLL(i,1,n) if(v[i]<0) {v[i]+=v[mxi];op.emplace_back(i,mxi);}
                  FORLL(i,2,n) {v[i]+=v[i-1];op.emplace_back(i,i-1);}
                  cout << op.size() << endl;
                  for(auto i:op) cout << i.first << ' ' << i.second << endl;
                  return;}
      }
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