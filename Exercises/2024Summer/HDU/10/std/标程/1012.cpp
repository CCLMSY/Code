#include <bits/stdc++.h>
#define rep(i,j,k) for(int i=(j);i<=(k);i++)
#define per(i,j,k) for(int i=(j);i>=(k);i--)
#define uint unsigned int
#define ll long long
#define ull unsigned long long
#define db double
#define ldb long double
#define pii pair<int,int>
#define pll pair<ll,ll>
#define mkp make_pair
#define eb emplace_back
#define SZ(S) (int)S.size()
#define mod 998244353
//#define mod 1000000007
#define inf 0x3f3f3f3f
#define linf 0x3f3f3f3f3f3f3f3f
using namespace std;

template <class T>
void chkmax(T &x,T y){
    if(x < y) x = y;
}

template <class T>
void chkmin(T &x,T y){
    if(x > y) x = y;
}

inline int popcnt(int x){
    return __builtin_popcount(x);
}

inline int ctz(int x){
    return __builtin_ctz(x);
}

template <int P>
class mod_int
{
    using Z = mod_int;

private:
    static int mo(int x) { return x < 0 ? x + P : x; }

public:
    int x;
    int val() const { return x; }
    mod_int() : x(0) {}
    template <class T>
    mod_int(const T &x_) : x(x_ >= 0 && x_ < P ? static_cast<int>(x_) : mo(static_cast<int>(x_ % P))) {}
    bool operator==(const Z &rhs) const { return x == rhs.x; }
    bool operator!=(const Z &rhs) const { return x != rhs.x; }
    Z operator-() const { return Z(x ? P - x : 0); }
    Z pow(long long k) const
    {
        Z res = 1, t = *this;
        while (k)
        {
            if (k & 1)
                res *= t;
            if (k >>= 1)
                t *= t;
        }
        return res;
    }
    Z &operator++()
    {
        x < P - 1 ? ++x : x = 0;
        return *this;
    }
    Z &operator--()
    {
        x ? --x : x = P - 1;
        return *this;
    }
    Z operator++(int)
    {
        Z ret = x;
        x < P - 1 ? ++x : x = 0;
        return ret;
    }
    Z operator--(int)
    {
        Z ret = x;
        x ? --x : x = P - 1;
        return ret;
    }
    Z inv() const { return pow(P - 2); }
    Z &operator+=(const Z &rhs)
    {
        (x += rhs.x) >= P && (x -= P);
        return *this;
    }
    Z &operator-=(const Z &rhs)
    {
        (x -= rhs.x) < 0 && (x += P);
        return *this;
    }
    Z operator-()
    {
        return -x;
    }
    Z &operator*=(const Z &rhs)
    {
        x = 1ULL * x * rhs.x % P;
        return *this;
    }
    Z &operator/=(const Z &rhs) { return *this *= rhs.inv(); }
#define setO(T, o)                                  \
    friend T operator o(const Z &lhs, const Z &rhs) \
    {                                               \
        Z res = lhs;                                \
        return res o## = rhs;                       \
    }
    setO(Z, +) setO(Z, -) setO(Z, *) setO(Z, /)
#undef setO
    
    friend istream& operator>>(istream& is, mod_int& x)
    {
        long long tmp;
        is >> tmp;
        x = tmp;
        return is;
    }
    friend ostream& operator<<(ostream& os, const mod_int& x)
    {
        os << x.val();
        return os;
    }
};

using Z = mod_int<mod>;
Z power(Z p,ll k){
    Z ans = 1;
    while(k){
        if(k % 2 == 1) ans *= p;
        p *= p;
        k /= 2;
    }
    return ans;
}
int TEST,n,k;
int p[100005],a[100005],b[100005],buc[100005],vis[100005];
Z fact[16],C[16][16];

bitset <100005> col[15];
bitset <100005> sum[1 << 15];
int bas[100005];
vector <int> SS[100005];
void init(){
    fill(vis,vis + n + 1,0);
//    rep(i,1,n) printf("%d ",buc[i]);
//    printf("\n");
    int cur = 0;
    rep(i,1,n){
        if(buc[i]) continue;
        int u = i;
        col[cur].reset();
        while(u){
            col[cur].set(a[u]);
            vis[u] = 1;
            u = p[u];
        }
        cur++;
    }
    assert(cur == k);  
    fill(buc,buc + n + 1,0); 
    rep(i,1,n){
        bas[i] = 0;
        SS[i].clear();
    }
    rep(i,1,n){
        if(vis[i]) continue;
        int u = i,val = 0;
        while(!vis[u]){
            if(!buc[a[u]]) val++;
            buc[a[u]]++;
            vis[u] = 1;
            u = p[u];
        }
        u = p[i];
        buc[a[i]] = 0;
        while(u != i){
            buc[a[u]] = 0;
            u = p[u];
        }
        bas[val]++;
    }
/*    printf("bas info:\n");
    rep(i,1,n) printf("%d ",bas[i]);
    printf("\n");*/

    rep(S,1,(1 << k) - 1){
        int u = ctz(S);
        sum[S] = sum[S - (1 << u)] | col[u];
        SS[sum[S].count()].eb(S);
    } 
/*    rep(i,1,n){
        for(int S:SS[i]) printf("subset %d col %d\n",S,i);
    }*/
    fact[0] = 1;
    rep(i,1,k) fact[i] = fact[i - 1] * i;
    rep(i,0,k){
        C[i][0] = 1;
        rep(j,1,i) C[i][j] = C[i - 1][j - 1] + C[i - 1][j];
    }
}

Z dp[1 << 15][16],ans[16];
int A[1 << 15];
void clr(int S,int cur){
    if(A[S] == cur) return;
    fill(dp[S],dp[S] + k + 1,0);
    A[S] = cur;
}

void add(int S,int cur,int up){
//    printf("add %d %d\n",S,cur);
    int R = (1 << k) - 1 - S;
    Z cof = fact[popcnt(S) - 1];
    for(int T = R;;T = (T - 1) & R){
        clr(S + T,cur);
        if(A[T] != cur) continue;
        rep(i,1,up){
            dp[S + T][i] += dp[T][i - 1] * cof;
            ans[i] += dp[T][i - 1] * cof * fact[k - popcnt(S + T)];
        }
        if(!T) break;
    }
}

Z calc(int para,int up){
//    rep(i,0,k) printf("%d ",ans[i].val());
//    printf("\n");
    per(i,up,0){
        rep(j,0,i - 1) ans[j] -= ans[i] * C[i][j];
    }
//    rep(i,0,k) printf("%d ",ans[i].val());
//    printf("\n");
    Z ret = 0;
    rep(i,0,min(up,n - para)) ret += ans[i] * b[para + i];
    return ret;
}

void solve(){
    scanf("%d%d",&n,&k);
    fill(buc,buc + n + 1,0);
    rep(i,1,n){
        scanf("%d",&p[i]);
        if(!p[i]) continue;
        if(buc[p[i]]){
            printf("0\n");
            return;
        }
        buc[p[i]] = 1;
    }
    rep(i,1,n) scanf("%d",&a[i]);
    rep(i,1,n) scanf("%d",&b[i]);
    init();

    fill(A,A + (1 << k),-1);
    Z answer = 0;
    int up;
    rep(i,1,n){
        clr(0,i);
        fill(ans,ans + k + 1,0);
        dp[0][0] = 1;
        ans[0] = fact[k];
        up = 0;
        for(int S:SS[i]){
            up = min(up + 1,k);
            add(S,i,up);
        }
        answer += calc(bas[i],up);
    }
    printf("%d\n",answer.val());
}

int main(){
//    freopen("test.in","r",stdin);
//    freopen("test.out","w",stdout);
    scanf("%d",&TEST);
    while(TEST--) solve();
//    cerr << clock() << endl;
    return 0;
}