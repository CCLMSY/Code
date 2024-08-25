#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

namespace MODULE
{
    ll MOD = 1e9+7;
    inline ll Get_Mod(ll x,ll mod=MOD){
        if(x<0) return x-x/mod*mod+mod;
        else return x-x/mod*mod;
    }
    ll qcpow(ll a,ll b,ll p=MOD){ll ret=1;a=Get_Mod(a);for (;b;b>>=1,a=a*a%p) if(b&1) ret=ret*a%p;return ret;}
    ll inv(ll a,ll p=MOD){return qcpow(a,p-2,p);}

    inline ll add(ll a,ll b){return Get_Mod(a+b);}
    inline ll sub(ll a,ll b){return Get_Mod(a-b);}
    inline ll mul(ll a,ll b){return Get_Mod(a*b);}

    void addto(ll &a,ll b){a=Get_Mod(a+b);}
    void subto(ll &a,ll b){a=Get_Mod(a-b);}
    void multo(ll &a,ll b){a=Get_Mod(a*b);}

    vector<ll> Fac;
    void Prepare_Factorial(ll n){Fac.resize(n+1);Fac[0]=1;for(ll i=1;i<=n;i++) Fac[i]=mul(Fac[i-1],i);}
    inline ll C(ll n,ll m){return n<m?0:mul(Fac[n],inv(mul(Fac[m],Fac[n-m])));}
} using namespace MODULE;

// 线段树
// 实现的功能：（取模）区间加、区间乘、区间直接修改、区间和查询
// 时间复杂度：单次操作O(logn)
class SegTree{
    vector<ll> tree, lazyadd, lazymul, lazyset;
    //lazy标记：打上Lazy标记的节点，值已经被更新，只是还没有更新到子节点
    vector<ll> *arr;
    int n, root, n4, end;

    // 维护当前节点的信息和Lazy，O(1)
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
    // [l, r] 为查询区间, [cl, cr] 为当前节点包含的区间, p 为当前节点的编号

    // 区间乘法，O(logn)
    void range_mul(int l, int r, ll val, int cl, int cr, int p) {
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
    // 区间增量，O(logn)
    void range_add(int l, int r, ll val, int cl, int cr, int p) {
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
    // 区间直接修改，O(logn)
    void range_set(int l, int r, ll val, int cl, int cr, int p) {
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
    // 查询区间和，O(logn)
    ll range_sum(int l, int r, int cl, int cr, int p) {
        if (l <= cl && cr <= r) return tree[p];
        int m = cl + (cr - cl) / 2;
        ll sum = 0;
        maintain(cl, cr, p);
        if (l <= m) //sum += range_sum(l, r, cl, m, p * 2);
            sum = add(sum,range_sum(l, r, cl, m, p * 2));
        if (r > m) //sum += range_sum(l, r, m + 1, cr, p * 2 + 1);
            sum = add(sum,range_sum(l, r, m + 1, cr, p * 2 + 1));
        return sum;
    }
    // 建树，O(n)
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
    explicit SegTree(vector<ll> v) {
        n = v.size();
        n4 = n * 4;
        tree = vector<ll>(n4, 0);
        lazyadd = vector<ll>(n4, 0);
        lazymul = vector<ll>(n4, 1);
        lazyset = vector<ll>(n4, 0);
        arr = &v;
        end = n - 1;
        root = 1;
        build(0, end, 1);
        arr = nullptr;
    }

    // 查询区间和，O(logn)
    ll range_sum(int l, int r) { return range_sum(l, r, 0, end, root); }
    // 区间乘法，O(logn)
    void range_mul(int l, int r, ll val) { range_mul(l, r, val, 0, end, root); }
    // 区间增量，O(logn)
    void range_add(int l, int r, ll val) { range_add(l, r, val, 0, end, root); }
    // 区间直接修改，O(logn)
    void range_set(int l, int r, ll val) { range_set(l, r, val, 0, end, root); }
};

int main(){
    // ios::sync_with_stdio(false);
    // cin.tie(0); cout.tie(0);
    ll n,q,t;cin >> n >> q;
    vector<ll> v(n);
    for(auto& i:v) cin >> i;
    SegTree st(v);
    ll op,x,y,k;
    while(q--){
        cin >> op;
        if(op==1){
            cin >> x >> y >> k;
            st.range_mul(x-1,y-1,k);
        }else if(op==2){
            cin >> x >> y >> k;
            st.range_add(x-1,y-1,k);
        }else if(op==3){
            cin >> x >> y >> k;
            st.range_set(x-1,y-1,k);
        }else{
            cin >> x >> y;
            cout << st.range_sum(x-1,y-1) << '\n';
        }
    }
}