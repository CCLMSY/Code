#include <bits/stdc++.h>

using LL = long long;
using ld = long double;
using Pair = std::pair<int, int>;
#define inf 1'000'000'000
std::mt19937_64 rnd(std::chrono::steady_clock::now().time_since_epoch().count());

template<int kcz>
struct ModInt {
#define T (*this)
    int x;

    ModInt() : x(0) {}

    ModInt(int y) : x(y >= 0 ? y : y + kcz) {}

    ModInt(LL y) : x(y >= 0 ? y % kcz : (kcz - (-y) % kcz) % kcz) {}

    inline int inc(const int &v) {
        return v >= kcz ? v - kcz : v;
    }

    inline int dec(const int &v) {
        return v < 0 ? v + kcz : v;
    }

    inline ModInt &operator+=(const ModInt &p) {
        x = inc(x + p.x);
        return T;
    }

    inline ModInt &operator-=(const ModInt &p) {
        x = dec(x - p.x);
        return T;
    }

    inline ModInt &operator*=(const ModInt &p) {
        x = (int) ((LL) x * p.x % kcz);
        return T;
    }

    inline ModInt inverse() const {
        int a = x, b = kcz, u = 1, v = 0, t;
        while (b > 0)t = a / b, std::swap(a -= t * b, b), std::swap(u -= t * v, v);
        return u;
    }

    inline ModInt &operator/=(const ModInt &p) {
        T *= p.inverse();
        return T;
    }

    inline ModInt operator-() const {
        return -x;
    }

    inline friend ModInt operator+(const ModInt &lhs, const ModInt &rhs) {
        return ModInt(lhs) += rhs;
    }

    inline friend ModInt operator-(const ModInt &lhs, const ModInt &rhs) {
        return ModInt(lhs) -= rhs;
    }

    inline friend ModInt operator*(const ModInt &lhs, const ModInt &rhs) {
        return ModInt(lhs) *= rhs;
    }

    inline friend ModInt operator/(const ModInt &lhs, const ModInt &rhs) {
        return ModInt(lhs) /= rhs;
    }

    inline bool operator==(const ModInt &p) const {
        return x == p.x;
    }

    inline bool operator!=(const ModInt &p) const {
        return x != p.x;
    }

    inline ModInt qpow(LL n) const {
        ModInt ret(1), mul(x);
        while (n > 0) {
            if (n & 1)ret *= mul;
            mul *= mul, n >>= 1;
        }
        return ret;
    }

    inline friend std::ostream &operator<<(std::ostream &os, const ModInt &p) {
        return os << p.x;
    }

    inline friend std::istream &operator>>(std::istream &is, ModInt &a) {
        LL t;
        is >> t, a = ModInt<kcz>(t);
        return is;
    }

    static int get_mod() {
        return kcz;
    }

    inline bool operator<(const ModInt &A) const {
        return x < A.x;
    }

    inline bool operator>(const ModInt &A) const {
        return x > A.x;
    }

#undef T
};

const int kcz = 998244353;
using Z = ModInt<kcz>;

void solve(const int &Case) {
    int n, k;
    std::cin >> n >> k;
    std::vector<Z> fac(k + 1), inv(k + 1);
    fac[0] = 1;
    for (int i = 1; i <= k; i++)fac[i] = fac[i - 1] * i;
    inv[k] = fac[k].inverse();
    for (int i = k - 1; i >= 0; i--) {
        inv[i] = inv[i + 1] * (i + 1);
    }
    auto Comb = [&](int x, int y) {
        if (x < y)return Z{0};
        return fac[x] * inv[y] * inv[x - y];
    };
    std::string s;
    std::cin >> s;
    s.push_back('0'), n++;
    std::vector<Z> h(k + 1);
    Z f = 0, g = 0;
    h[0] = 1;
    Z ans = 0;
    for (int i = 0; i < n; i++) {
        if (s[i] == '0') {
            ans += f;
            f = g = 0;
            for (int j = 1; j <= k; j++) {
                h[j] = 0;
            }
        }
        else if (s[i] == '1') {
            Z sum = 0;
            for (int j = 0; j <= k; j++) {
                sum += Comb(k, j) * h[j];
            }
            f = f + g + sum;
            g = g + sum;
            for (int j = k; j >= 1; j--) {
                Z ret = 0;
                for (int l = 0; l <= j; l++) {
                    ret += Comb(j, l) * h[l];
                }
                h[j] = ret;
            }
        }
        else {
            ans += f / 2;
            Z sum = 0;
            for (int j = 0; j <= k; j++) {
                sum += Comb(k, j) * h[j];
            }
            f = (f + g + sum) / 2;
            g = (g + sum) / 2;
            for (int j = k; j >= 1; j--) {
                Z ret = 0;
                for (int l = 0; l <= j; l++) {
                    ret += Comb(j, l) * h[l];
                }
                h[j] = ret / 2;
            }
        }
    }
    std::cout << ans << '\n';
}

int main() {
//    freopen("1.in", "r", stdin);
//    freopen("2.out", "w", stdout);
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    int T = 1;
//    std::cin >> T;
    for (int Case = 1; Case <= T; Case++)solve(Case);
    return 0;
}
