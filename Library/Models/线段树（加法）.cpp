#include <bits/stdc++.h>
using namespace std;
typedef long ll;

// 线段树
// 实现的功能：区间加、区间和查询
// 时间复杂度：单次操作O(logn)
// 下标从0开始
class SegTree {
    vector<ll> tree, lazy; // tree: 线段树的值/ lazy: 懒标记
    vector<ll> *arr; // arr: 原始数组
    int n, root, n4, end; // n: 原始数组的大小/ root: 根节点编号/ n4: 线段树的大小/ end: 原始数组的右端点
    // cl, cr: 当前节点的左右端点/ p: 当前节点的编号
    // 维护当前节点的信息和Lazy，O(1)
    void maintain(int cl, int cr, int p) {
        int cm = cl + (cr - cl) / 2;
        if (cl != cr && lazy[p]) {
        lazy[p * 2] += lazy[p];
        lazy[p * 2 + 1] += lazy[p];
        tree[p * 2] += lazy[p] * (cm - cl + 1);
        tree[p * 2 + 1] += lazy[p] * (cr - cm);
        lazy[p] = 0;
        }
    }
    // 查询区间和，O(logn)
    ll range_sum(int l, int r, int cl, int cr, int p) {
        if (l <= cl && cr <= r) return tree[p];
        int m = cl + (cr - cl) / 2;
        ll sum = 0;
        maintain(cl, cr, p);
        if (l <= m) sum += range_sum(l, r, cl, m, p * 2);
        if (r > m) sum += range_sum(l, r, m + 1, cr, p * 2 + 1);
        return sum;
    }
    // 区间修改，O(logn)
    void range_add(int l, int r, ll val, int cl, int cr, int p) {
        if (l <= cl && cr <= r) {
        lazy[p] += val;
        tree[p] += (cr - cl + 1) * val;
        return;
        }
        int m = cl + (cr - cl) / 2;
        maintain(cl, cr, p);
        if (l <= m) range_add(l, r, val, cl, m, p * 2);
        if (r > m) range_add(l, r, val, m + 1, cr, p * 2 + 1);
        tree[p] = tree[p * 2] + tree[p * 2 + 1];
    }
    // 建树，O(n)
    void build(int s, int t, int p) {
        if (s == t) {
        tree[p] = (*arr)[s];
        return;
        }
        int m = s + (t - s) / 2;
        build(s, m, p * 2);
        build(m + 1, t, p * 2 + 1);
        tree[p] = tree[p * 2] + tree[p * 2 + 1];
    }

public:
    // v: 原始数组，下标从0开始
    explicit SegTree(vector<ll> v) {
        n = v.size();
        n4 = n * 4;
        tree = vector<ll>(n4, 0);
        lazy = vector<ll>(n4, 0);
        arr = &v;
        end = n - 1;
        root = 1;
        build(0, end, 1);
        arr = nullptr;
    }
    // 查询区间和，O(logn)
    ll range_sum(int l, int r) { return range_sum(l, r, 0, end, root); }
    // 区间修改，O(logn)
    void range_add(int l, int r, int val) { range_add(l, r, val, 0, end, root); }
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    ll n,q,t;cin >> n >> q;
    vector<ll> v(n);
    for(auto& i:v) cin >> i;
    SegTree st(v);
    ll op,x,y,k;
    while(q--){
        cin >> op;
        if(op==1){
            cin >> x >> y >> k;
            st.range_add(x-1,y-1,k);
        }else{
            cin >> x >> y;
            cout << st.range_sum(x-1,y-1) << '\n';
        }
    }
    return 0;
}