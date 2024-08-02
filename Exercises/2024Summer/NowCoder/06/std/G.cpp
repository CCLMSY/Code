#include<bits/stdc++.h>
using namespace std;
const int N = 103;
 const int mod = 1e9 + 7;
int n;
int l[N*2] , r[N*2];
int fpow(int a,int b)
{
    int ans = 1;
    while(b) {
        if(b & 1) ans = 1LL*ans*a%mod;
        a = 1LL*a*a%mod;b >>= 1;
    }
    return ans;
}
vector<int> vals;
struct poly : vector<int> {
    poly(int x) {
        resize(1) ; at(0) = x;
    }
    poly(int x1 ,int x0) {
        resize(2) ; at(0) = x0 ; at(1) = x1 ;
    }
    poly() {

    }
    void operator += (const poly &A) {
        resize(max(A.size() , size())) ;
        for(int i = 0;i < A.size();i++) at(i) = (at(i) + A[i]) % mod;
    }
};
poly operator *(const poly &A,const poly &B)
{
    poly ans(0);
    if(!A.size() || (A.size() == 1 && A[0] == 0) || !B.size() || (B.size() == 1 && B[0] == 0)) return ans ;
    ans.resize(A.size() + B.size() - 1) ;
    for(int i = 0;i < A.size();i++) {
        for(int j = 0;j < B.size();j++) {
            ans[i + j] = (ans[i + j] + 1LL*A[i]*B[j]) % mod;
        }
    }
    return ans;
}
poly operator +(const poly &A,const poly &B)
{
    poly ans ; ans.resize(max(A.size() , B.size())) ;
    for(int i = 0;i < ans.size();i++) {
        if(i < A.size()) ans[i] += A[i];
        if(i < B.size()) ans[i] = (ans[i] + B[i]) % mod;
    }
    return ans;
}
poly f[2][N*2];
int rlen[N*2];
poly gless(int i,int L,int R)
{
    if(l[i] >= R) {
        poly ans(0) ; return ans ;
    }
    if(r[i] <= L) {
        poly ans(1) ; return ans;
    }
    poly ans(rlen[i] , (-1LL*l[i]*rlen[i]%mod + mod) % mod) ;
    return ans;
}
poly glarge(int i,int L,int R)
{
    if(l[i] >= R) {
        poly ans(1) ; return ans ;
    }
    if(r[i] <= L) {
        poly ans(0) ; return ans;
    }
    poly ans(mod - rlen[i] , (1LL*r[i]*rlen[i]) % mod) ;
    return ans;
}
bool check_0(poly &A)
{
    for(auto &x : A) {
        if(x) return 0;
    }
    return 1;
}
void output(const poly&A) {
    for(auto x : A) cout << (3LL*x)%mod <<' ' ;
    cout << '\n' ;
}
int calc(int L,int R)
{
    int cur = 0;
    for(int j = 1;j <= 1 ;j++) f[cur][j] = poly(0) ;
    f[cur][0] = poly(1) ;
    poly pop ; 
    for(int i = 2;i < n*2;i += 2) {
        int lm = min(i/2 - 1 , (2*n - i) / 2) ;
        for(int j = 0;j <= lm + 1;j++) f[cur ^ 1][j] = poly(0) ;
        poly lA = gless(i , L , R) ;
        poly gA = glarge(i , L , R) ;
        poly lB = gless(i + 1 , L , R) ;
        poly gB = glarge(i + 1 , L , R) ;
        poly ad1 = gA * gB ;
        poly ad0 = gA * lB + gB * lA;
        poly mn1 = lA * lB;
        for(int j = 0;j <= lm;j++) {
            if(!f[cur][j].size() || (f[cur][j].size() == 1 && f[cur][j][0] == 0)) continue ;
            f[cur ^ 1][j + 1] += f[cur][j] * ad1 ;
            f[cur ^ 1][j] += f[cur][j] * ad0;
            if(j > 0) f[cur ^ 1][j - 1] += f[cur][j] * mn1;
            else f[cur ^ 1][0] += f[cur][j]  * mn1;
        }
        pop += f[cur][0] * mn1 ;
        cur ^= 1;
    }
    int ans = 0;
    pop[0] = (pop[0] - (n - 1) + mod) % mod;
    for(int i = 0;i < pop.size();i++) {
        ans = (ans + 1LL*pop[i]*(fpow(R , i + 1) - fpow(L , i + 1) + mod) % mod * fpow(i + 1 , mod - 2)) % mod;
    }
    ans = (mod - ans) % mod;
    return ans;
}
int main()
{
    // freopen("in.txt","r",stdin) ;
    ios::sync_with_stdio(false) ; cin.tie(0) ;
    cin >> n;
    for(int i = 1;i <= n*2;i++) {
        cin >> l[i] >> r[i] ;
        rlen[i] = fpow(r[i] - l[i] , mod - 2) ;
    }
    if(n == 1) {
        cout << 1LL*fpow(2,mod-2)*(l[1] + r[1]) % mod << '\n' ; return 0;
    }
    int ans = 1LL*fpow(2,mod-2)*(l[1] + r[1]) % mod ;
    for(int i = 2;i < n*2;i++) {
        vals.push_back(l[i]) ; vals.push_back(r[i]) ;
    }
    vals.push_back(0) ;
    sort(vals.begin() , vals.end()) ;
    vals.erase(unique(vals.begin() , vals.end()) , vals.end()) ;
    for(int i = 0;i < vals.size() - 1;i++) {
        ans = (ans + calc(vals[i] , vals[i + 1]) ) % mod;
    }
    cout << ans%mod << '\n' ; return 0;
}
