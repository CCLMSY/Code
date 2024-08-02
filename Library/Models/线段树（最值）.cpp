#include <bits/stdc++.h>
using namespace std;
typedef long long T;
const T INF = 0x7fffffffffffffff;

// 最值线段树 实现log^2n的区间增加、区间最值、区间查询
template<typename T>
class MxSegTree{
    struct data{
        T mx,mx2,cntmax,lazymax; //最大值，次大值，最大值个数，最大值标记
        T mn,mn2,cntmin,lazymin; //最小值，次小值，最小值个数，最小值标记
        T lazyadd,sum; // 增加标记，区间和
        data(){mx=mx2=-INF;mn=mn2=INF;cntmax=cntmin=0;lazymax=-INF;lazymin=INF;lazyadd=0;sum=0;}
    };
    vector<data> tree;
    vector<T> *arr;
    long n,n5,root,end;

    void push_add(ll cl, ll cr, ll p,T v){
        tree[p].sum += (cr - cl + 1) * v;
        tree[p].mx += v, tree[p].mn += v;
        if (tree[p].mx2 != -INF) tree[p].mx2 += v;
        if (tree[p].mn2 != INF) tree[p].mn2 += v;
        if (tree[p].lazymax != -INF) tree[p].lazymax += v;
        if (tree[p].lazymin != INF) tree[p].lazymin += v;
        tree[p].lazyadd += v;
    }
    void push_min(ll p, T tg){
        if (tree[p].mx <= tg) return;
        tree[p].sum += (tg * 1ll - tree[p].mx) * tree[p].cntmax;
        if (tree[p].mn2 == tree[p].mx) tree[p].mn2 = tg;  
        if (tree[p].mn == tree[p].mx) tree[p].mn = tg;  
        if (tree[p].lazymax > tg) tree[p].lazymax = tg; 
        tree[p].mx = tg, tree[p].lazymin = tg;
    }
    void push_max(ll p, T tg){
        if (tree[p].mn > tg) return;
        tree[p].sum += (tg * 1ll - tree[p].mn) * tree[p].cntmin;
        if (tree[p].mx2 == tree[p].mn) tree[p].mx2 = tg;
        if (tree[p].mx == tree[p].mn) tree[p].mx = tg;
        if (tree[p].lazymin < tg) tree[p].lazymin = tg;
        tree[p].mn = tg, tree[p].lazymax = tg;
    }
    void push_up(ll p) { //用子节点维护当前节点信息
        tree[p].sum = tree[p * 2].sum + tree[p * 2 + 1].sum;
        if (tree[p * 2].mx == tree[p * 2 + 1].mx) {
            tree[p].mx = tree[p * 2].mx, tree[p].cntmax = tree[p * 2].cntmax + tree[p * 2 + 1].cntmax;
            tree[p].mx2 = max(tree[p * 2].mx2, tree[p * 2 + 1].mx2);
        } else if (tree[p * 2].mx > tree[p * 2 + 1].mx) {
            tree[p].mx = tree[p * 2].mx, tree[p].cntmax = tree[p * 2].cntmax;
            tree[p].mx2 = max(tree[p * 2].mx2, tree[p * 2 + 1].mx);
        } else {
            tree[p].mx = tree[p * 2 + 1].mx, tree[p].cntmax = tree[p * 2 + 1].cntmax;
            tree[p].mx2 = max(tree[p * 2].mx, tree[p * 2 + 1].mx2);
        }
        if (tree[p * 2].mn == tree[p * 2 + 1].mn) {
            tree[p].mn = tree[p * 2].mn, tree[p].cntmin = tree[p * 2].cntmin + tree[p * 2 + 1].cntmin;
            tree[p].mn2 = min(tree[p * 2].mn2, tree[p * 2 + 1].mn2);
        } else if (tree[p * 2].mn < tree[p * 2 + 1].mn) {
            tree[p].mn = tree[p * 2].mn, tree[p].cntmin = tree[p * 2].cntmin;
            tree[p].mn2 = min(tree[p * 2].mn2, tree[p * 2 + 1].mn);
        } else {
            tree[p].mn = tree[p * 2 + 1].mn, tree[p].cntmin = tree[p * 2 + 1].cntmin;
            tree[p].mn2 = min(tree[p * 2].mn, tree[p * 2 + 1].mn2);
        }
    }
    void push_down(ll cl, ll cr, ll p) { //下放标记
        T cm = cl + (cr - cl) / 2;
        if(tree[p].lazyadd) push_add(cl, cm, p * 2, tree[p].lazyadd), push_add(cm + 1, cr, p * 2 + 1, tree[p].lazyadd);
        if(tree[p].lazymax != -INF) push_max(p * 2, tree[p].lazymax), push_max(p * 2 + 1, tree[p].lazymax);
        if(tree[p].lazymin != INF) push_min(p * 2, tree[p].lazymin), push_min(p * 2 + 1, tree[p].lazymin);
        tree[p].lazyadd = 0, tree[p].lazymax = -INF, tree[p].lazymin = INF;
    }

    void build(T s, T t, ll p) {
        tree[p].lazymax = -INF, tree[p].lazymin = INF;
        if (s == t) {
            tree[p].sum = tree[p].mx = tree[p].mn = (*arr)[s];
            tree[p].mx2 = -INF, tree[p].mn2 = INF;
            tree[p].cntmax = tree[p].cntmin = 1;
            return;
        }
        T m = s + (t - s) / 2;
        build(s, m, p * 2);
        build(m + 1, t, p * 2 + 1);
        push_up(p);
    }

    void range_add(ll l, ll r, T v, ll cl, ll cr, ll p) {
        if(cl > r || cr < l) return;
        if (l <= cl && cr <= r) return push_add(cl, cr, p, v);
        T cm = cl + (cr - cl) / 2;
        push_down(cl, cr, p);
        if (l <= cm) range_add(l, r, v, cl, cm, p * 2);
        if (r > cm) range_add(l, r, v, cm + 1, cr, p * 2 + 1);
        push_up(p);
    }
    void range_min(ll l, ll r, T v, ll cl, ll cr, ll p) {
        if(cl > r || cr < l || tree[p].mx <= v) return;
        if (l <= cl && cr <= r && tree[p].mx2 < v) return push_min(p, v);
        T cm = cl + (cr - cl) / 2;
        push_down(cl, cr, p);
        if (l <= cm) range_min(l, r, v, cl, cm, p * 2);
        if (r > cm) range_min(l, r, v, cm + 1, cr, p * 2 + 1);
        push_up(p);
    }
    void range_max(ll l, ll r, T v, ll cl, ll cr, ll p) {
        if(cl > r || cr < l || tree[p].mn >= v) return;
        if (l <= cl && cr <= r && tree[p].mn2 > v) return push_max(p, v);
        T cm = cl + (cr - cl) / 2;
        push_down(cl, cr, p);
        if (l <= cm) range_max(l, r, v, cl, cm, p * 2);
        if (r > cm) range_max(l, r, v, cm + 1, cr, p * 2 + 1);
        push_up(p);
    }
    
    T query_sum(ll l, ll r, ll cl, ll cr, ll p) {
        if(cl > r || cr < l) return 0;
        if (l <= cl && cr <= r) return tree[p].sum;
        T cm = cl + (cr - cl) / 2;
        T sum = 0;
        push_down(cl, cr, p);
        if (l <= cm) sum += query_sum(l, r, cl, cm, p * 2);
        if (r > cm) sum += query_sum(l, r, cm + 1, cr, p * 2 + 1);
        return sum;
    }
    T query_max(ll l, ll r, ll cl, ll cr, ll p) {
        if(cl > r || cr < l) return -INF;
        if (l <= cl && cr <= r) return tree[p].mx;
        T cm = cl + (cr - cl) / 2;
        T mx = -INF;
        push_down(cl, cr, p);
        if (l <= cm) mx = max(mx, query_max(l, r, cl, cm, p * 2));
        if (r > cm) mx = max(mx, query_max(l, r, cm + 1, cr, p * 2 + 1));
        return mx;
    }
    T query_min(ll l, ll r, ll cl, ll cr, ll p) {
        if(cl > r || cr < l) return INF;
        if (l <= cl && cr <= r) return tree[p].mn;
        T cm = cl + (cr - cl) / 2;
        T mn = INF;
        push_down(cl, cr, p);
        if (l <= cm) mn = min(mn, query_min(l, r, cl, cm, p * 2));
        if (r > cm) mn = min(mn, query_min(l, r, cm + 1, cr, p * 2 + 1));
        return mn;
    }

public:
    explicit MxSegTree(vector<T> v) {
        n = v.size();
        n5 = n * 5;
        end = n - 1;
        root = 1;
        arr = &v;
        tree.resize(n5);
        build(0, end, 1);
        arr = nullptr;
    }
    void range_add(ll l, ll r, T v) { range_add(l, r, v, 0, end, root); }
    void range_min(ll l, ll r, T v) { range_min(l, r, v, 0, end, root); }
    void range_max(ll l, ll r, T v) { range_max(l, r, v, 0, end, root); }
    T query_sum(ll l, ll r) { return query_sum(l, r, 0, end, root); }
    T query_max(ll l, ll r) { return query_max(l, r, 0, end, root); }
    T query_min(ll l, ll r) { return query_min(l, r, 0, end, root); }
};