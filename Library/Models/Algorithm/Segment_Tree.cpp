#include<bits/stdc++.h>

#define Max(a,b) (a>b?a:b)
#define Min(a,b) (a>b?b:a)
#define Max3(a,b,c) (Max(a,b)>c?Max(a,b):c)
#define Min3(a,b,c) (Min(a,b)>c?c:Min(a,b))
#define scanfint(a) scanf("%d",&a)
#define scanfll(a) scanf("%lld",&a)
#define scanfstr(a) scanf("%s",a)
#define printfll(a) printf("%lld\n",a)
#define Get_Rand(x) (rand()%(x+1))
#define swapnum(a,b) {a=a+b;b=a-b;a=a-b;}
#define FOR(i,l,r) for(int i=l;i<=r;i++)
#define FORLL(i,l,r) for(long long i=l;i<=r;i++)
#define Presentation(i,r) printf("%c"," \n"[i==r])
#define NO printf("Bob\n")
#define YES printf("Alice\n")

typedef long long ll;

const double pi=3.141592653589793;
const ll MOD=1e9+7;
const int INF=0x7fffffff;
const double eps=1e-8;

using namespace std;

/*----------Cpp Head----------*/

const ll MAXN = 1e5+7; // 线段树节点数的最大值
ll n; // 元素个数
ll a[MAXN]; // 原数组
ll stree[MAXN << 2]; // 线段树节点

//建线段树
void build(ll p, ll l, ll r) {
    //p 表示当前节点在线段树数组中的下标。
    //对于根节点来说，它的下标为 1，对于任意一个节点 i，它的左子节点下标为 i << 1，右子节点下标为 i << 1 | 1。
    if (l == r) { // 叶子节点
        stree[p] = a[l];
    } else {
        ll mid = (l + r) >> 1;
        ll lc = p << 1, rc = p << 1 | 1;
        build(lc, l, mid); // 左子节点
        build(rc, mid + 1, r); // 右子节点
        stree[p] = stree[lc] + stree[rc]; // 合并左右子树的结果
    }
}

//更新线段树
void update(ll p, ll l, ll r, ll x, ll k) {
    //x：需要更新的原始数组下标
    //k：更新后的值
    if (l == r) { // 叶子节点
        stree[p] = k;
        a[x]=k;
    } else {
        ll mid = (l + r) >> 1;
        ll lc = p << 1, rc = p << 1 | 1;
        if (x <= mid) update(lc, l, mid, x, k); // 更新左子树
        else update(rc, mid + 1, r, x, k); // 更新右子树
        stree[p] = stree[lc] + stree[rc]; // 合并左右子树的结果
    }
}

//查询区间
ll query(ll p, ll l, ll r, ll ql, ll qr) {
    if (ql <= l && qr >= r) { // 当前区间被查询区间包含
        return stree[p];
    }
    ll mid = (l + r) >> 1;
    ll lc = p << 1, rc = p << 1 | 1;
    ll sum = 0;
    if (ql <= mid) sum += query(lc, l, mid, ql, qr); // 查询左子树
    if (qr > mid) sum += query(rc, mid + 1, r, ql, qr); // 查询右子树
    return sum;
}

int main() {
    cin >> n;
    for (ll i = 1; i <= n; i++) {
        cin >> a[i];
    }
    build(1, 1, n); // 建树
    ll q;
    cin >> q;
    while (q--) {
        ll op, x, k;
        cin >> op >> x >> k;
        if (op == 1) { // 更新操作：将原始数组中下标为x的元素的值更新为k
            update(1, 1, n, x, k);
        } else if (op == 2) { // 查询操作：输出原始数组中下标为[x,k]的元素之和
            cout << query(1, 1, n, x, k) << endl;
        }
    }
    return 0;
}

