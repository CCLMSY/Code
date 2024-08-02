#include <bits/stdc++.h>
#define rep(i,x,y) for(int i=x; i<=y; ++i)

using namespace std;

using i64 = long long;

template<int P>
struct MInt {
    int x;
    MInt() : x{} {}
    MInt(i64 x) : x{norm(x % getMod())} {}
     
    static int Mod;
    static int getMod() {
        if (P > 0) {
            return P;
        } else {
            return Mod;
        }
    }
    static void setMod(int Mod_) {
        Mod = Mod_;
    }
    int norm(int x) const {
        if (x < 0) {
            x += getMod();
        }
        if (x >= getMod()) {
            x -= getMod();
        }
        return x;
    }
    int val() const {
        return x;
    }
    explicit operator int() const {
        return x;
    }
    MInt operator-() const {
        MInt res;
        res.x = norm(getMod() - x);
        return res;
    }
    MInt inv() const {
        assert(x != 0);
        return power(*this, getMod() - 2);
    }
    MInt &operator*=(MInt rhs) & {
        x = 1LL * x * rhs.x % getMod();
        return *this;
    }
    MInt &operator+=(MInt rhs) & {
        x = norm(x + rhs.x);
        return *this;
    }
    MInt &operator-=(MInt rhs) & {
        x = norm(x - rhs.x);
        return *this;
    }
    MInt &operator/=(MInt rhs) & {
        return *this *= rhs.inv();
    }
    friend MInt operator*(MInt lhs, MInt rhs) {
        MInt res = lhs;
        res *= rhs;
        return res;
    }
    friend MInt operator+(MInt lhs, MInt rhs) {
        MInt res = lhs;
        res += rhs;
        return res;
    }
    friend MInt operator-(MInt lhs, MInt rhs) {
        MInt res = lhs;
        res -= rhs;
        return res;
    }
    friend MInt operator/(MInt lhs, MInt rhs) {
        MInt res = lhs;
        res /= rhs;
        return res;
    }
    friend std::istream &operator>>(std::istream &is, MInt &a) {
        i64 v;
        is >> v;
        a = MInt(v);
        return is;
    }
    friend std::ostream &operator<<(std::ostream &os, const MInt &a) {
        return os << a.val();
    }
    friend bool operator==(MInt lhs, MInt rhs) {
        return lhs.val() == rhs.val();
    }
    friend bool operator!=(MInt lhs, MInt rhs) {
        return lhs.val() != rhs.val();
    }
};
 
template<>
int MInt<0>::Mod = 1;
 
template<int V, int P>
MInt<P> CInv = MInt<P>(V).inv();
 
constexpr int P = 998244353;
using Z = MInt<P>;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
    int N, K;
    cin >> N >> K;

    vector<Z> pw(N + 1);
    pw[0] = 1;
    rep(i,1,N) pw[i] = pw[i - 1] * K;


    int n = 0;
    vector<bool> border(N + 1);

    auto check = [&](int x)
    {
        return x >= 2 * n || border[n * 2 - x];
    };

    auto calcLong = [&]() -> Z
    {
        Z res {pw[N - n]};
        vector<Z> f(N + 1, 0);
        f[n] = 1;
        rep(i,n+1,N)
        {
            f[i] = pw[i - n];
            rep(j,n,i-1)
            {
                if (border[n - i + j]) f[i] -= f[j];
            }
            res += f[i] * pw[N - i];
        }
        return res;
    };

    auto calcShort = [&]() -> Z
    {
        Z res {pw[N - n]}, tmp {0}, k {K};
        vector<Z> f(N + 1, 0);
        f[n] = 1, tmp = 0;
        rep(i,n+1,N)
        {
            f[i] = pw[i - n];
            rep(j,max(n,i-n+1),i-1)
            {
                if (border[n - i + j]) f[i] -= f[j];  
            }
            if (i - n >= n) tmp = tmp * k + f[i - n], f[i] -= tmp;
            res += f[i] * pw[N - i];
        }
        return res;
    };

    Z ans = pw[(N + 1) / 2];
    if (N > 1) ans += pw[N / 2] * K * 2 - K;

    auto dfs = [&](auto self, Z now) -> vector<Z>
    {
        if (n)
            ans += now * (n <= N / 2 ? calcShort() : calcLong());
        int L = n;
        vector<Z> res(N, 0);
        rep(i,L+1,N-2)
            if (check(i))
            {
                n = i, border[i] = true;
                Z nxt = now * pw[(max(0, i - 2 * L) + 1) / 2] - res[i];
                if (nxt.val())
                {
                    auto p = self(self, nxt);
                    rep(j,i,N-2) res[j] += p[j];
                }
                n = L, border[i] = false;
            }
        res[L] += now;
        return res;
    };

    dfs(dfs, 1);
    cout << ans << '\n';
    return 0;
}
