#include<bits/stdc++.h>
using namespace std;

/*----------Consts----------*/
const double eps=1e-6;

const double pi = acos(-1.0);
const long long INF=0x3fffffffffffffff;
/*----------Consts----------*/

typedef long long ll;
typedef long double ld;
typedef pair<ll,ll> pll;

namespace DEFINITION
{
    #define scanfll(a) scanf("%lld",&a)
    #define lowbit(x) ((x)&(-(x)))
    #define ALL(A) (A).begin(),(A).end()
    #define SORT(A) sort(ALL(A))
    #define SORT_REV(A) sort((A).rbegin(),(A).rend())
    //SORT BEFORE UNIQUE!!
    #define UNIQUE(A) A.erase(unique(ALL(A)),A.end())
    #define Presentation(i,r) " \n"[i==r]
    #define FORLL(i,l,r) for(ll i=l;i<=r;i++)
    #define FORLL_rev(i,r,l) for(ll i=r;i>=l;i--)
    #define NO cout << "NO\n"
    #define YES cout << "YES\n"
    #define endl '\n' //交互题不启用！
}

namespace CCLIB
{
    #define create_vec(v,n) vector<ll> v(n);for(auto &x:v) cin >> x;
    ostream& operator<<(ostream &out, const pair<ll,ll> &p) {out << '(' << p.first << ',' << p.second << ')';return out;}

    //扩欧返回d=gcd(a,b);x,y对应ax+by=d的解;通解为x=x0+k*b/d,y=y0-k*a/d;
    ll Exgcd(ll a,ll b,ll &x,ll &y) {if(a==0&&b==0) return -1; if(b==0) {x=1;y=0;return a;} ll d=Exgcd(b,a%b,y,x); y-=a/b*x; return d;}

    template<typename T>
    void chmax(T &a,T b){if(a<b) a=b;}
    template<typename T>
    void chmin(T &a,T b){if(a>b) a=b;}
    template<class T>
    void print_vec(const T &A){for(auto &x:A) cout << x << ' ';cout << endl;}
    template<class T>
    void print_float(T value,int digit=10){cout << fixed << setprecision(digit) << value;}

    vector<ll> snums;
    void Get_Nums(string s){ snums.clear(); ll n=s.length();ll t=0;int flag=0; FORLL(i,0,n-1) if(s[i]<='9'&&s[i]>='0'){t*=10;t+=s[i]-'0';flag++;}else if(flag){snums.emplace_back(t);t=0;flag=0;} if(flag){snums.emplace_back(t);t=0;flag=0;}}

}

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

    vector<vector<ll>> C;
    void Prepare_Combination(ll n){ C.clear(); C.resize(n+1); C[0].emplace_back(1); for(ll i=1;i<=n;i++) { C[i].emplace_back(1); for(ll j=1;j<=n-1;j++) C[i].emplace_back(add(C[i-1][j-1],C[i-1][j])); C[i].emplace_back(1); } }
}


using namespace DEFINITION;
using namespace CCLIB;
// using namespace MODULE;

#define ONLINE_JUDGE
#define FAST_IO
// #define MUTIPLE_JUDGE

/*----------Code Area----------*/
const ll N = 1000006;
void prepare(){
    // Prepare_Combination(5005);
    // MOD = 1e9+7;
}
struct ACauto{
    vector<array<int,62>> tr; //0-25:a-z,26-51:A-Z,52-61:0-9
    vector<int> cnt; // 第i个单词出现的次数
    vector<int> indeg; // 节点入度
    vector<int> rev; // 节点反向指针
    vector<ll> fail; // 失配指针
    vector<int> idx; // 以结点j结尾的单词编号
    ll n,tot; // curn(tot)是当前节点数，n是（本题单个数据）字典字符串最大总长度
    int trans(char c){ //字符转换为数字，以全62字符为例，根据题意修改
        if(c>='a'&&c<='z') return c-'a';
        else if(c>='A'&&c<='Z') return c-'A'+26;
        return c-'0'+52;
    }
    ACauto(ll n_):tr(n_+1,{0}),cnt(n_+1,0),idx(n_+1,0),indeg(n_+1,0),rev(n_+1,0),
        fail(n_+1,0),n(n_),tot(0){} // 70*N(3e6)->Luogu300ms/800MB
    void insert(string s,int index){ //构建TRIE树
        ll p=0;
        for(auto c:s){
            c=trans(c);
            if(tr[p][c]==0) tr[p][c]=++tot;
            p=tr[p][c];
        }
        if(!idx[p]) idx[p]=index;
        rev[index]=idx[p];
    }
    void build(){ //（字典树建成后、查询前）构建失配指针
        queue<ll> q;
        for(ll i=0;i<62;i++){
            if(tr[0][i]) q.push(tr[0][i]);
        }
        while(!q.empty()){
            ll p=q.front();q.pop();
            for(ll i=0;i<62;i++){
                if(tr[p][i]){
                    fail[tr[p][i]]=tr[fail[p]][i];
                    indeg[tr[fail[p]][i]]++; // 统计入度
                    q.push(tr[p][i]);
                }else{
                    tr[p][i]=tr[fail[p]][i];
                }
            }
        }
    }
    ll query_appeared(string s){ 
    //查询字符串s中出现过的单词个数（字典中每个单词只计一次）
        ll u=0,res=0;
        for(ll i=0;i<s.length();i++){
            u = tr[u][s[i]-'a'];
            for(ll j=u;j&&cnt[j]!=-1;j=fail[j]){
                res+=cnt[j];
                cnt[j]=-1;
            }
        }
        return res;
    }
    void clear(){ //最坏：70*N
        for(ll i=0;i<=tot+1;i++){
            for(ll j=0;j<=61;j++) tr[i][j]=0;
            fail[i]=0;
            cnt[i]=0;
            idx[i]=0;
            indeg[i]=0;
            rev[i]=0;
        }
        tot=0;
    }
};
void solve()
{
    ACauto ac(N);
    ll n; cin >> n;
    string s;
    FORLL(i,1,n){
        cin >> s;
        ac.insert(s,i);
    }
    ac.build();
    cin >> s;
}
/*----------Code Area----------*/

signed main(){

#ifndef ONLINE_JUDGE
    clock_t clk = clock();
    ifstream ifs("1.in");
    ofstream ofs("1.out");
    streambuf *cinbackup;
    cinbackup = cin.rdbuf(ifs.rdbuf());
    streambuf *coutbackup;
    coutbackup = cout.rdbuf(ofs.rdbuf());
#endif

#ifdef FAST_IO
#ifdef ONLINE_JUDGE
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
#endif
#endif

long long T = 1;
#ifdef MUTIPLE_JUDGE
    cin >> T;
#endif
prepare();
while(T--) solve();

#ifndef ONLINE_JUDGE
    cin.rdbuf(cinbackup);
    cout.rdbuf(coutbackup);
    cout << clock() - clk << " ms\n";
#endif
    return 0;
}