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
const ll N = 200005;
void prepare(){
    // Prepare_Combination(5005);
    // MOD = 1e9+7;
}
void solve()
{
    ll n,q;cin >> n >> q;
    create_vec(v,n);
    while (q--)
    {
        ll l,r;cin >> l >> r;
        l--;r--;
        if(r-l>100){
            YES;
            continue ;
        }
        vector<ll> tv;
        FORLL(i,l,r) tv.push_back(v[i]);
        SORT(tv);
        ll tn=tv.size();
        if(tn<6){ NO; continue; }

        int fl=0;
        FORLL(i,0,tn-6){ // 区间左端点
            FORLL(ai,i,i+3){ 
                FORLL(bi,ai+1,i+4){
                    FORLL(ci,bi+1,i+5){ //第一组
                        if(tv[ai]+tv[bi]>tv[ci]){
                            vector<ll> trian2;
                            FORLL(j,i,i+5){
                                if(j!=ai&&j!=bi&&j!=ci) trian2.push_back(tv[j]);
                            }
                            if(trian2[0]+trian2[1]>trian2[2]){ fl=1; break; } //第二组
                        } if(fl) break;
                    } if(fl) break;
                } if(fl) break;
            } if(fl) break;
        }
        if(fl){ YES; continue; }

        ll cnt=0;
        FORLL(i,0,tn-3){
            if(tv[i]+tv[i+1]>tv[i+2]) {cnt++;i+=2;}
            if(cnt>=2) break;
        }
        if(cnt>=2){ YES; continue; }

        vector<ll> pr; //点对
        FORLL(i,0,tn-2){
            if(tv[i]==tv[i+1]){
                pr.push_back(tv[i]);
                i++;
            }
        }
        if(pr.size()>=2){
            int fl=0;
            ll ttn = pr.size();
            ll t1 = pr[ttn-2],t2 = pr[ttn-1];
            ll ct1,ct2; ct1=ct2=0;
            int tcnt = 0;
            FORLL(i,0,tn-1){
                if(tv[i]==t1&&ct1<2) ct1++;
                else if(tv[i]==t2&&ct2<2) ct2++;
                else if(tcnt==0){
                    if(v[i]>=t1*2) {fl=-1;break;}
                    else tcnt=1;
                }else if(tcnt==1){
                    if(v[i]>=t2*2) {fl=-1;break;}
                    else {fl=1;break;}
                }
            }
            if(fl==1) {YES;continue;}
        }

        NO;
    }
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