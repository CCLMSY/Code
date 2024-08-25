#include <bits/stdc++.h>
typedef long long ll;
typedef unsigned long long ull;
using namespace std;
#define N 100010

int n, m;
int p[N], q[N], fa[N], Q[N];
int dep[N], dfn[N], sz[N], son[N], top[N];
int Ti;
vector<int>e[N];
void clear()
{
    for (int i = 1; i <= n; i ++)e[i].clear();
    for (int i = 1; i <= n; i ++)dfn[i] = sz[i] = son[i] = top[i] = fa[i] = Q[i] = 0;
    Ti = 0;
}
void dfs1(int u, int f)
{
    dep[u] = dep[f] + 1; sz[u] = 1; fa[u] = f; son[u] = 0;
    for (int v : e[u]) if (v != f)
    {
        dfs1(v, u); sz[u] += sz[v];
        if (sz[v] > sz[son[u]]) son[u] = v;
    }
}
void dfs2(int u, int topu, int f)
{
    top[u] = topu; dfn[u] = ++ Ti; Q[Ti] = u;
    if (son[u]) dfs2(son[u], topu, u);
    for (int v : e[u]) if (v != f && v != son[u])
    {
        dfs2(v, v, u);
    }
}
int lca(int u, int v)
{
    // cout << "EE:" << u << ' ' << v << ' ' << top[u] << ' ' << top[v];
    int tu = top[u], tv = top[v];
    while (tu != tv)
    {
        if (dep[tu] < dep[tv]) swap(u, v), swap(tu, tv);
        u = fa[tu]; tu = top[u];
    }
    if (dep[u] < dep[v]) swap(u, v);
    // cout << v << endl;
    return v;
}
int dis(int u, int v) {return dep[u] + dep[v] - 2 * dep[lca(u, v)];}

#define ls (x << 1)
#define rs (x << 1 | 1)
#define mid ((l + r) >> 1)

namespace Seg1
{
    int mn[N << 2], mx[N << 2];   
    void pushup(int x)
    {
        mx[x] = max(mx[ls], mx[rs]); 
        mn[x] = min(mn[ls], mn[rs]);
    }
    void upd(int l, int r, int x, int pos)
    {
        if (l == r) {mx[x] = mn[x] = p[Q[l]]; return ;}
        if (pos <= mid)upd(l, mid, ls, pos); 
        else upd(mid + 1, r, rs, pos);
        pushup(x);
    }
    void build(int l, int r, int x)
    {
        if (l == r) {mx[x] = mn[x] = p[Q[l]]; return ;}
        build(l, mid, ls); build(mid + 1, r, rs);
        pushup(x);
    }
    int qmax(int l, int r, int x, int ql, int qr)
    {
        if (l == ql && r == qr)return mx[x];
        if (qr <= mid) return qmax(l, mid, ls, ql, qr);
        else if (ql > mid) return qmax(mid + 1, r, rs, ql, qr);
        else return max(qmax(l, mid, ls, ql, mid), qmax(mid + 1, r, rs, mid + 1, qr));
    }
    int qmin(int l, int r, int x, int ql, int qr)
    {
        if (l == ql && r == qr)return mn[x];
        if (qr <= mid) return qmin(l, mid, ls, ql, qr);
        else if (ql > mid) return qmin(mid + 1, r, rs, ql, qr);
        else return min(qmin(l, mid, ls, ql, mid), qmin(mid + 1, r, rs, mid + 1, qr));
    }
}
namespace Seg2
{
    int tu[N << 2], tv[N << 2], td[N << 2];
    void pushup(int x)
    {
        int u1 = tu[ls], v1 = tv[ls], u2 = tu[rs], v2 = tv[rs];
        td[x] = -1; int val = 0;
        if ((val = td[ls]) > td[x]) td[x] = val, tu[x] = u1, tv[x] = v1;
        if ((val = td[rs]) > td[x]) td[x] = val, tu[x] = u2, tv[x] = v2;
        if ((val = dis(u1, u2)) > td[x]) td[x] = val, tu[x] = u1, tv[x] = u2;
        if ((val = dis(u1, v2)) > td[x]) td[x] = val, tu[x] = u1, tv[x] = v2;
        if ((val = dis(v1, u2)) > td[x]) td[x] = val, tu[x] = v1, tv[x] = u2;
        if ((val = dis(v1, v2)) > td[x]) td[x] = val, tu[x] = v1, tv[x] = v2;
    }
    void upd(int l, int r, int x, int pos)
    {
        if (l == r) {tu[x] = tv[x] = q[l]; td[x] = 0; return ;}
        if (pos <= mid)upd(l, mid, ls, pos); 
        else upd(mid + 1, r, rs, pos);
        pushup(x);
    }
    void build(int l, int r, int x)
    {
        if (l == r) {tu[x] = tv[x] = q[l]; td[x] = 0; return ;}
        build(l, mid, ls); build(mid + 1, r, rs);
        pushup(x);
    }
    void qryUV(int l, int r, int x, int ql, int qr, vector<int>&V)
    {
        if (l == ql && r == qr) {V.push_back(x); return ;}
        if (qr <= mid) qryUV(l, mid, ls, ql, qr, V);
        else if (ql > mid) qryUV(mid + 1, r, rs, ql, qr, V);
        else qryUV(l, mid, ls, ql, mid, V), qryUV(mid + 1, r, rs, mid + 1, qr, V);
    }
}
int qmax(int u, int v)
{
    int tu = top[u], tv = top[v];
    int ans = 0;
    while (tu != tv)
    {
        if (dep[tu] < dep[tv])swap(tu, tv), swap(u, v);
        ans = max(ans, Seg1::qmax(1, n, 1, dfn[tu], dfn[u]));
        u = fa[tu]; tu = top[u];
    }
    if (dep[u] < dep[v]) swap(u, v);
    ans = max(ans, Seg1::qmax(1, n, 1, dfn[v], dfn[u]));
    return ans;
}
int qmin(int u, int v)
{
    int tu = top[u], tv = top[v];
    int ans = n + 1;
    while (tu != tv)
    {
        if (dep[tu] < dep[tv])swap(tu, tv), swap(u, v);
        ans = min(ans, Seg1::qmin(1, n, 1, dfn[tu], dfn[u]));
        u = fa[tu]; tu = top[u];
    }
    if (dep[u] < dep[v]) swap(u, v);
    ans = min(ans, Seg1::qmin(1, n, 1, dfn[v], dfn[u]));
    return ans;
}
bool qry(int l, int r)
{
    vector<int>V;
    Seg2::qryUV(1, n, 1, l, r, V);
    int u = 0, v = 0, d = -1;
    for (int x : V)
    {
        int val = 0, tu = 0, tv = 0, td = 0;
        if (d == -1) {u = Seg2::tu[x], v = Seg2::tv[x], d = Seg2::td[x]; continue;}
        int U = Seg2::tu[x], V = Seg2::tv[x], D = Seg2::td[x];

        if ((val = d) > td)td = val, tu = u, tv = v;
        if ((val = D) > td)td = val, tu = U, tv = V;
        if ((val = dis(u, U)) > td)td = val, tu = u, tv = U;
        if ((val = dis(u, V)) > td)td = val, tu = u, tv = V;
        if ((val = dis(v, U)) > td)td = val, tu = v, tv = U;
        if ((val = dis(v, V)) > td)td = val, tu = v, tv = V;

        u = tu, v = tv, d = td;
    }
    if (dis(u, v) != r - l) return 0;
    if (qmax(u, v) != r || qmin(u, v) != l) return 0;
    return 1;
}
void testCases()
{
    cin >> n;
    for (int i = 1; i <= n; i ++) cin >> p[i];
    for (int i = 1; i <= n; i ++) q[p[i]] = i;
    for (int i = 1; i < n; i ++)
    {
        int u, v;
        cin >> u >> v;
        e[u].push_back(v);
        e[v].push_back(u);
    }
    dfs1(1, 0); dfs2(1, 1, 0);

    // cout << "GG:" << endl;

    Seg1::build(1, n, 1);
    Seg2::build(1, n, 1);
    cin >> m;
    for (int i = 1; i <= m; i ++)
    {
        int op; cin >> op;
        if (op == 1)
        {
            int x, y;
            cin >> x >> y;
            int a = p[x], b = p[y];
            swap(p[x], p[y]); swap(q[a], q[b]);
            Seg2::upd(1, n, 1, a); Seg2::upd(1, n, 1, b);
            Seg1::upd(1, n, 1, dfn[x]); Seg1::upd(1, n, 1, dfn[y]);
            // Seg1::build(1, n, 1); Seg2::build(1, n, 1);
        }
        if (op == 2)
        {
            int l, r;
            cin >> l >> r;
            if (qry(l, r)) cout << "Yes\n";
            else cout << "No\n";
        }
    }
    clear();
}

int main(signed argc, char* argv[])
{
	// freopen("in.in","r",stdin);
	// freopen("std.out","w",stdout);
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int T;
    cin >> T;

    while (T --)testCases();
	return 0;
}
/*
1
10
9 2 10 3 1 6 8 4 5 7 
1 2
2 3
3 4
2 5
3 6
1 7
6 8
4 9
8 10
10
1 2 7
1 5 6
2 3 8
1 1 8
2 2 9
1 6 10
1 2 2
1 1 4
2 3 8
1 6 8

*/