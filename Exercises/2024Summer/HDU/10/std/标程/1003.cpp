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
//#define mod 998244353
#define mod 1000000007
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

namespace io {
    const int __SIZE = (1 << 22) + 1;
    char ibuf[__SIZE], *iS, *iT, obuf[__SIZE], *oS = obuf, *oT = oS + __SIZE - 1, __c, qu[55]; int __f, qr, _eof;
    #define Gc() (iS == iT ? (iT = (iS = ibuf) + fread (ibuf, 1, __SIZE, stdin), (iS == iT ? EOF : *iS ++)) : *iS ++)
    inline void flush () { fwrite (obuf, 1, oS - obuf, stdout), oS = obuf; }
    inline void gc (char &x) { x = Gc(); }
    inline void pc (char x) { *oS ++ = x; if (oS == oT) flush (); }
    inline void pstr (const char *s) { int __len = strlen(s); for (__f = 0; __f < __len; ++__f) pc (s[__f]); }
    inline void gstr (char *s) { for(__c = Gc(); __c < 32 || __c > 126 || __c == ' ';)  __c = Gc();
        for(; __c > 31 && __c < 127 && __c != ' '; ++s, __c = Gc()) *s = __c; *s = 0; }
    template <class I> inline bool read (I &x) { _eof = 0;
        for (__f = 1, __c = Gc(); (__c < '0' || __c > '9') && !_eof; __c = Gc()) { if (__c == '-') __f = -1; _eof |= __c == EOF; }
        for (x = 0; __c <= '9' && __c >= '0' && !_eof; __c = Gc()) x = x * 10 + (__c & 15), _eof |= __c == EOF; x *= __f; return !_eof; }
    template <class I> inline void write (I x) { if (!x) pc ('0'); if (x < 0) pc ('-'), x = -x;
        while (x) qu[++ qr] = x % 10 + '0',  x /= 10; while (qr) pc (qu[qr --]); }
    struct Flusher_ {~Flusher_(){flush();}}io_flusher_;
} using io::pc; using io::gc; using io::pstr; using io::gstr; using io::read; using io::write;

int T,n,m,q;
int msk[20],vis[20],ord[21];
char str[21];

Z dp[21][1 << 20],inv[21];
Z calc(int S,int k){
    if(!S) return Z(1);
    Z answer = 0,prd = 1;
    rep(i,1,min(n,k)){
        prd = prd * (k + 1 - i) * inv[i];
        answer += prd * dp[i][S];
    }
    return answer;
}

void solve(){
    read(n);read(m);read(q);
//    cerr << n << endl;
    rep(i,1,n) inv[i] = Z(1) / i;
    fill(msk,msk + n,0);
    fill(vis,vis + n,0);
    rep(i,1,m){
        int u,v;
        read(u);read(v);
        u--;v--;
        msk[v] |= 1 << u;
    }
    int cur = (1 << n) - 1;
    rep(p,1,n){
        int u = -1;
        rep(i,0,n - 1) if(!vis[i] && (msk[i] & cur) == 0) u = i;
        assert(u != -1);
        ord[p] = u;
        vis[u] = 1;
        cur ^= 1 << u;
    }
//    rep(i,1,n) printf("%d ",ord[i]);
//    printf("\n");

    dp[0][0] = 1;
    rep(p,1,n){
        copy(dp[p - 1],dp[p - 1] + (1 << n),dp[p]);
        rep(i,1,n){
            int u = ord[i];
            rep(S,0,(1 << n) - 1) if(((S >> u) & 1) && (msk[u] & S) == 0) dp[p][S] += dp[p][S - (1 << u)];
        }
        rep(S,0,(1 << n) - 1) dp[p][S] -= dp[p - 1][S];
/*        printf("p=%d\n",p);
        rep(S,0,(1 << n) - 1){
            if(!dp[p][S].val()) continue;
            rep(i,0,n - 1) printf("%d",(S >> i) & 1);
            printf("->%d\n",dp[p][S].val());
        }*/
    }
    int k;
    rep(i,1,q){
        read(k);
        gstr(str);
        cur = 0;
        rep(u,0,n - 1) if(str[u] == '1') cur |= 1 << u;
        write(calc(cur,k).val());
        pc('\n');
    }    
}

int main(){
//    freopen("test1.in","r",stdin);
//    freopen("test1.out","w",stdout);
    read(T);
    while(T--) solve();
//    cerr << clock() << endl;
	return 0;
}