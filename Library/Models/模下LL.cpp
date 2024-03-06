#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const ll MOD=1e9+7;

template<ll P=0>
class MLL{
private:
    constexpr ll norm(ll x) const { return x<0?x+Mod:x; }
    constexpr ll mult(ll x,ll y) const { return norm(x*y-x*y/Mod*Mod); }
    MLL qcpow(MLL a,ll b) const { MLL res = 1; for(;b;b>>=1,a*=a) if(b&1) res*=a; return res; }

public:
    ll val;
    static ll Mod;

    constexpr MLL():val(0){if(P>0) Mod = P;}
    constexpr MLL(ll x){ if(P>0) Mod = P; val=norm(x%Mod); }
    constexpr static void setMod(ll Mod_){ Mod=Mod_; }

    explicit constexpr operator ll() const { return val; }
    constexpr MLL operator-() const { MLL res; res.val = norm(Mod-val); return res; }
    constexpr MLL inv() const { return qcpow(*this,Mod-2); }
    
    constexpr MLL &operator+=(MLL rhs) & { val = norm(val+rhs.val); return *this; }
    constexpr MLL &operator-=(MLL rhs) & { val = norm(val-rhs.val); return *this; }
    constexpr MLL &operator*=(MLL rhs) & { val = mult(val,rhs.val); return *this; }
    constexpr MLL &operator/=(MLL rhs) & { val = mult(val,rhs.inv()); return *this; }
    constexpr MLL &operator%=(MLL rhs) & { val = norm(val%rhs.val); return *this; }
    
    friend constexpr MLL operator+(MLL lhs, MLL rhs) { MLL res = lhs; res += rhs; return res; }
    friend constexpr MLL operator-(MLL lhs, MLL rhs) { MLL res = lhs; res -= rhs; return res; }
    friend constexpr MLL operator*(MLL lhs, MLL rhs) { MLL res = lhs; res *= rhs; return res; }
    friend constexpr MLL operator/(MLL lhs, MLL rhs) { MLL res = lhs; res /= rhs; return res; }
    friend constexpr MLL operator%(MLL lhs, MLL rhs) { MLL res = lhs; res %= rhs; return res; }

    friend ostream &operator<<(ostream &out, const MLL &a) { out << a.val; return out; }
    friend istream &operator>>(istream &in, MLL &a) { in >> a.val; return in; }

    friend bool operator==(MLL a, MLL b) { return a.val == b.val; }
    friend bool operator!=(MLL a, MLL b) { return a.val != b.val; }
    friend bool operator<(MLL a, MLL b)  { return a.val <  b.val; }
    friend bool operator>(MLL a, MLL b)  { return a.val >  b.val; }
}; template<> ll MLL<>::Mod = MOD;