#include <bits/stdc++.h>
using namespace std;

// 线段树 实现logn的区间修改和查询，下标从0开始
// 使用前确认采用的运算方法
template <typename T>
class SegTree{
    vector<T> tree, lazyadd, lazymul, lazyset;
    //lazy标记：打上Lazy标记的节点，值已经被更新，只是还没有更新到子节点
    vector<T> *arr;
    int n, root, n4, end;

    void maintain(int cl, int cr, int p) {
        int cm = cl + (cr - cl) / 2;
        if (cl != cr) {//cl==cr：叶子节点
            
            if(lazymul[p]!=1){ //区间乘法
                multo(lazymul[p * 2],lazymul[p]); //lazymul[p * 2] *= lazymul[p];
                multo(lazymul[p * 2 + 1],lazymul[p]); //lazymul[p * 2 + 1] *= lazymul[p];
                multo(lazyadd[p * 2],lazymul[p]); //lazyadd[p * 2] *= lazymul[p];
                multo(lazyadd[p * 2 + 1],lazymul[p]); //lazyadd[p * 2 + 1] *= lazymul[p];
                multo(tree[p * 2],lazymul[p]); //tree[p * 2] *= lazymul[p];
                multo(tree[p * 2 + 1],lazymul[p]); //tree[p * 2 + 1] *= lazymul[p];
                lazymul[p] = 1;
            }
            
            if(lazyadd[p]){ //区间增量
                addto(lazyadd[p * 2],lazyadd[p]); //lazyadd[p * 2] += lazyadd[p];
                addto(lazyadd[p * 2 + 1],lazyadd[p]); //lazyadd[p * 2 + 1] += lazyadd[p];
                addto(tree[p * 2],lazyadd[p] * (cm - cl + 1)); //tree[p * 2] += lazyadd[p] * (cm - cl + 1);
                addto(tree[p * 2 + 1],lazyadd[p] * (cr - cm)); //tree[p * 2 + 1] += lazyadd[p] * (cr - cm);
                lazyadd[p] = 0;
            }
            
            if(lazyset[p]){ //区间直接修改
                lazyset[p * 2] = Get_Mod(lazyset[p]); //lazyset[p * 2] = lazyset[p];
                lazyset[p * 2 + 1] = Get_Mod(lazyset[p]); //lazyset[p * 2 + 1] = lazyset[p];
                tree[p * 2] = Get_Mod(lazyset[p] * (cm - cl + 1)); //tree[p * 2] = lazyset[p] * (cm - cl + 1);
                tree[p * 2 + 1] = Get_Mod(lazyset[p] * (cr - cm)); //tree[p * 2 + 1] = lazyset[p] * (cr - cm);
                lazyset[p] = 0;
            }
        }
    }
    void range_mul(int l, int r, T val, int cl, int cr, int p) {
    // [l, r] 为查询区间, [cl, cr] 为当前节点包含的区间, p 为当前节点的编号
        if (l <= cl && cr <= r) {
            multo(lazyadd[p],val); //lazyadd[p] *= val;
            multo(tree[p],val); //tree[p] *= val;
            multo(lazymul[p],val); //lazymul[p] *= val;
            return;
        }
        int m = cl + (cr - cl) / 2;
        maintain(cl, cr, p);
        if (l <= m) range_mul(l, r, val, cl, m, p * 2);
        if (r > m) range_mul(l, r, val, m + 1, cr, p * 2 + 1);
        tree[p] = add(tree[p * 2],tree[p * 2 + 1]); //tree[p] = tree[p * 2] + tree[p * 2 + 1];
    }
    void range_add(int l, int r, T val, int cl, int cr, int p) {
        if (l <= cl && cr <= r) {
            addto(lazyadd[p],val); //lazyadd[p] += val;
            addto(tree[p],(cr - cl + 1) * val); //tree[p] += (cr - cl + 1) * val;
            return;
        }
        int m = cl + (cr - cl) / 2;
        maintain(cl, cr, p);
        if (l <= m) range_add(l, r, val, cl, m, p * 2);
        if (r > m) range_add(l, r, val, m + 1, cr, p * 2 + 1);
        tree[p] = add(tree[p * 2],tree[p * 2 + 1]); //tree[p] = tree[p * 2] + tree[p * 2 + 1];
    }
    void range_set(int l, int r, T val, int cl, int cr, int p) {
        if (l <= cl && cr <= r) {
            lazyset[p] = Get_Mod(val); //lazyset[p] = val;
            tree[p] = Get_Mod(val * (cr - cl + 1)); //tree[p] = val * (cr - cl + 1);
            return;
        }
        int m = cl + (cr - cl) / 2;
        maintain(cl, cr, p);
        if (l <= m) range_set(l, r, val, cl, m, p * 2);
        if (r > m) range_set(l, r, val, m + 1, cr, p * 2 + 1);
        tree[p] = add(tree[p * 2],tree[p * 2 + 1]); //tree[p] = tree[p * 2] + tree[p * 2 + 1];
    }

    T range_sum(int l, int r, int cl, int cr, int p) {
        if (l <= cl && cr <= r) return tree[p];
        int m = cl + (cr - cl) / 2;
        T sum = 0;
        maintain(cl, cr, p);
        if (l <= m) //sum += range_sum(l, r, cl, m, p * 2);
            sum = add(sum,range_sum(l, r, cl, m, p * 2));
        if (r > m) //sum += range_sum(l, r, m + 1, cr, p * 2 + 1);
            sum = add(sum,range_sum(l, r, m + 1, cr, p * 2 + 1));
        return sum;
    }

    void build(int s, int t, int p) {
        if (s == t) {
            tree[p] = Get_Mod((*arr)[s]);
            return;
        }
        int m = s + (t - s) / 2;
        build(s, m, p * 2);
        build(m + 1, t, p * 2 + 1);
        tree[p] = add(tree[p * 2],tree[p * 2 + 1]); //tree[p] = tree[p * 2] + tree[p * 2 + 1];
    }

public:
    explicit SegTree<T>(vector<T> v) {
        n = v.size();
        n4 = n * 4;
        tree = vector<T>(n4, 0);
        lazyadd = vector<T>(n4, 0);
        lazymul = vector<T>(n4, 1);
        lazyset = vector<T>(n4, 0);
        arr = &v;
        end = n - 1;
        root = 1;
        build(0, end, 1);
        arr = nullptr;
    }

    void show(int p, int depth = 0) {
        if (p > n4 || tree[p] == 0) return;
        show(p * 2, depth + 1);
        for (int i = 0; i < depth; ++i) putchar('\t');
        printf("%d:%d\n", tree[p], lazyadd[p]);
        show(p * 2 + 1, depth + 1);
    }

    T range_sum(int l, int r) { return range_sum(l, r, 0, end, root); }

    void range_mul(int l, int r, T val) { range_mul(l, r, val, 0, end, root); }
    void range_add(int l, int r, T val) { range_add(l, r, val, 0, end, root); }
    void range_set(int l, int r, T val) { range_set(l, r, val, 0, end, root); }
};