#include <bits/stdc++.h>
using namespace std;
const int M = 998244353;

template<int M>
struct Modint {
    int v;
    Modint(int x = 0) : v(x) {
        while (v < 0) {
            v += M;
        }
        while (v >= M) {
            v -= M;
        }
    }
    operator int() {
        return v;
    }
    Modint operator+=(const Modint &b) {
        if ((v += b.v) >= M) {
            v -= M;
        }
        return *this;
    }
    Modint operator-=(const Modint &b) {
        if ((v -= b.v) < 0) {
            v += M;
        }
        return *this;
    }
    Modint operator*=(const Modint &b) {
        v = 1ll * v * b.v % M;
        return *this;
    }
    friend Modint operator+(Modint a, const Modint &b) {
        return a += b;
    }
    friend Modint operator-(Modint a, const Modint &b) {
        return a -= b;
    }
    friend Modint operator*(Modint a, const Modint &b) {
        return a *= b;
    }
};

struct Expr {
    int addc, mulc;
    Modint<M> midsum, midk, prek, pred, prev, sufk, sufd, sufv;
    Expr(char c = '0') {
        addc = (c == '+' ? 1 : 0);
        mulc = (c == '*' ? 1 : 0);
        midsum = 0, midk = 1;
        if (c == '*') {
            prek = sufk = 0;
        } else {
            prek = sufk = 1;
        }
        prev = sufv = isdigit(c) ? c - '0' : 0;
        pred = sufd = isdigit(c) ? 10 : 1;
    }
    Modint<M> query() {
        if (addc == 0) {
            return prev * prek;
        } else {
            return midsum + prev * prek + sufv * sufk;
        }
    }
};
Expr operator+(const Expr &l, const Expr &r) {
    Expr res;
    res.addc = l.addc + r.addc;
    res.mulc = l.mulc + r.mulc;
    if (res.addc == 0) {
        if (l.mulc == 0) {
            res.midk = r.midk;
        } else if (r.mulc == 0) {
            res.midk = l.midk;
        } else {
            res.midk = l.midk * r.midk * (l.sufv * r.pred + r.prev);
        }
    }
    if (l.addc == 0) {
        if (l.mulc == 0) {
            res.prev = l.prev * r.pred + r.prev;
            res.pred = l.pred * r.pred;
            res.prek = r.prek;
        } else {
            res.prev = l.prev;
            res.pred = l.pred;
            res.prek = l.midk * (l.sufv * r.pred + r.prev) * r.prek;
        }
    } else {
        res.prev = l.prev;
        res.pred = l.pred;
        res.prek = l.prek;
    }
    if (r.addc == 0) {
        if (r.mulc == 0) {
            res.sufv = l.sufv * r.sufd + r.sufv;
            res.sufd = l.sufd * r.sufd;
            res.sufk = l.sufk;
        } else {
            res.sufv = r.sufv;
            res.sufd = r.sufd;
            res.sufk = r.midk * (l.sufv * r.pred + r.prev) * l.sufk;
        }
    } else {
        res.sufv = r.sufv;
        res.sufd = r.sufd;
        res.sufk = r.sufk;
    }
    res.midsum = l.midsum + r.midsum;
    if (l.addc > 0 && r.addc > 0) {
        res.midsum += l.sufk * (l.sufv * r.pred + r.prev) * r.prek;
    }
    return res;
}

struct Segt {
    const int N;
    vector<Expr> t;
    Segt(const string &s) : N(s.length()), t(N << 2 | 1) {
        build(s, 1, 0, N - 1);
    }
    void change(int loc, char c) {
        change(loc, c, 1, 0, N - 1);
    }
    int query(int ql, int qr) {
        return query(ql, qr, 1, 0, N - 1).query();
    }
    #define mid ((l + r) >> 1)
    #define ls (v << 1)
    #define rs (v << 1 | 1)
    void build(const string &s, int v, int l, int r) {
        if (l == r) {
            t[v] = Expr(s[l]);
        } else {
            build(s, ls, l, mid);
            build(s, rs, mid + 1, r);
            t[v] = t[ls] + t[rs];
        }
    }
    void change(int loc, char c, int v, int l, int r) {
        if (l == r) {
            t[v] = Expr(c);
        } else {
            if (loc <= mid) {
                change(loc, c, ls, l, mid);
            } else {
                change(loc, c, rs, mid + 1, r);
            }
            t[v] = t[ls] + t[rs];
        }
    }
    Expr query(int ql, int qr, int v, int l, int r) {
        if (ql <= l && qr >= r) {
            return t[v];
        }
        if (qr <= mid) {
            return query(ql, qr, ls, l, mid);
        }
        if (ql > mid) {
            return query(ql, qr, rs, mid + 1, r);
        }
        return query(ql, qr, ls, l, mid) + query(ql, qr, rs, mid + 1, r);
    }
    #undef rs
    #undef ls
    #undef mid
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
    int m;
    string s;
    cin >> m >> s;
    Segt tr(s);
    for (int i = 0; i < m; i++) {
        int op;
        cin >> op;
        if (op == 1) {
            int l, r;
            cin >> l >> r;
            cout << tr.query(l - 1, r - 1) << '\n';
        } else {
            int x;
            char c;
            cin >> x >> c;
            tr.change(x - 1, c);
        }
    }
    return 0;
}
