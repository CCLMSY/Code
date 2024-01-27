#include<bits/stdc++.h>
using namespace std;

/*----------Consts----------*/
const long MOD=1e9+7;

const double pi = acos(-1.0);
const double eps=1e-8;
const double goden_radio=1.618033988749895;
const long long INF=0x3fffffffffffffff;
/*----------Consts----------*/

typedef long long ll;
typedef pair<ll,ll> pll;

namespace DEFINITION
{
    #define scanfll(a) scanf("%lld",&a)
    #define lowbit(x) ((x)&(-(x)))
    #define RESET(A) memset(A,0,sizeof(A))
    #define ALL(A) A.begin(),A.end()
    #define SORT(A) sort(ALL(A))
    #define Presentation(i,r) " \n"[i==r]
    #define FORLL(i,l,r) for(ll i=l;i<=r;i++)
    #define FORLL_rev(i,r,l) for(ll i=r;i>=l;i--)
    #define Get_Mod(a) (((a)+MOD)%MOD)
    #define NO "NO\n"
    #define YES "YES\n"
    #define endl '\n'
}

namespace CCLIB
{
    #define create_vec(A,n) vector<ll> A(n);for(auto &x:A) cin >> x;
    #define print_vec(A) for(auto i:A) cout << i << ' ';cout << endl;
    #define print_float(value,digit) cout << fixed << setprecision(digit) << value;
    #define point_dist(x1,y1,x2,y2) (sqrt(((x1)-(x2))*((x1)-(x2))+((y1)-(y2))*((y1)-(y2))))

    //扩欧返回d=gcd(a,b);x,y对应ax+by=d的解
    ll Exgcd(ll a,ll b,ll &x,ll &y) {if(a==0&&b==0) return -1; if(b==0) {x=1;y=0;return a;} ll d=Exgcd(b,a%b,y,x); y-=a/b*x; return d;}
    ll qcpow(ll x, ll b) {ll ret = 1;x=Get_Mod(x);for(; b; b >>= 1, x = 1ll * x * x % MOD) if(b & 1) ret = Get_Mod(1ll*ret*x); return ret;}

    vector<ll> Fac,Fac_inv;
    void Prepare_Factorium(ll n) {Fac.clear();Fac.resize(n+1);Fac[0]=Fac[1]=1; Fac_inv.clear();Fac_inv.resize(n+1);Fac_inv[0]=Fac_inv[1]=1; FORLL(i,2,n) {Fac[i]=Get_Mod(Fac[i-1]*i);Fac_inv[i]=CCLIB::qcpow(Fac[i],MOD-2);}}void Prepare_Combination(ll n){Prepare_Factorium(n);}
    ll Get_Combination(ll m,ll n) {return Get_Mod(Get_Mod(Fac[m]*Fac_inv[m-n])*Fac_inv[n]);}

    vector<ll> Nums;
    void Get_Nums(string s){ Nums.clear(); ll n=s.length();ll t=0;int flag=0; FORLL(i,0,n-1) if(s[i]<='9'&&s[i]>='0'){t*=10;t+=s[i]-'0';flag++;}else if(flag){Nums.emplace_back(t);t=0;flag=0;} if(flag){Nums.emplace_back(t);t=0;flag=0;}}


}

namespace MOLDULE
{
    inline ll inv(ll x) {return CCLIB::qcpow(x,MOD-2);}
    inline ll add(ll x, ll y) {return Get_Mod(x + y);}
    inline ll addto(ll &x, ll y) {return x = add(x, y);}
    inline ll sub(ll x, ll y) {return Get_Mod(x - y);}
    inline ll subto(ll &x, ll y) {return x = sub(x, y);}
    inline ll mul(ll x, ll y) {return Get_Mod(1ll*x * y);}
    inline ll multo(ll &x, ll y) {return x = mul(x, y);}
    inline ll div(ll x, ll y) {return Get_Mod(1ll*x*inv(y));} 
    inline ll divto(ll &x, ll y) {return x = div(x, y);}
}


#define ONLINE_JUDGE
#define IO_OPTIMIZE
#define MUTIPLE_JUDGE
//#define CHECK_OUT_TIME

using namespace DEFINITION;
//using namespace MOLDULE;
using namespace CCLIB;

int sgn(double x) {if(fabs(x)<eps) return 0;if(x<0) return -1;return 1;}
inline double sqr(double x) {return x*x;}

struct Point{
    double x,y;
    Point(){}//Empty Point
    Point(double _x,double _y){x = _x;y = _y;}//Point

    void input(){cin >> x >> y;}
    #ifndef print_float
        #define print_float(value,digit) cout << fixed << setprecision(digit) << value;
    #endif
    void output(int digit){
        print_float(x,digit);
        cout << ',';
        print_float(y,digit);
        cout << '\n';
    }void output(){output(7);}

    bool operator == (Point b)const {return sgn(x-b.x) == 0 && sgn(y-b.y) == 0;}
    bool operator <  (Point b)const {return sgn(x-b.x)== 0?sgn(y-b.y)<0:x<b.x;}
    bool operator >  (Point b)const {return sgn(x-b.x)== 0?sgn(y-b.y)>0:x>b.x;}

    Point operator - (const Point &b)const{return Point(x-b.x,y-b.y);}//相减(转向量)：A-B=BA
    Point operator + (const Point &b)const{return Point(x+b.x,y+b.y);}//向量和

    double operator * (const Point &b)const{return x*b.x + y*b.y;}//点积
    double operator ^ (const Point &b)const{return x*b.y - y*b.x;}//叉积

    double len(){return hypot(x,y);}//向量长度
    double len2(){return x*x + y*y;}//向量长度平方

    double distance(Point p){return hypot(x-p.x,y-p.y);}//与另一点的距离

    Point operator *(const double &k)const{return Point(x*k,y*k);}
    Point operator /(const double &k)const{return Point(x/k,y/k);}

    //计算 pa 和 pb 的夹角，就是求这个点看 a,b 所成的夹角
    double rad(Point a,Point b) {Point p = *this;return fabs(atan2(fabs((a-p)^(b-p)),(a-p)*(b-p)));}

    Point trunto(double r){
        double l = len();if(!sgn(l))return *this;
        r /= l;return Point(x*r,y*r);}//化为长度为 r 的向量

    Point rotleft(){return Point(-y,x);}//逆时针旋转 90 度
    Point rotright(){return Point(y,-x);}//顺时针旋转 90 度

    //绕着 p 点逆时针旋转angle(弧度制)
    Point rotate(Point p,double angle){
        Point v = (*this) - p;double c = cos(angle), s = sin(angle);
        return Point(p.x + v.x*c - v.y*s,p.y + v.x*s + v.y*c);}

};
/*----------Code Area----------*/
#define N 100005
Point O;
void solve()
{
    O.x=O.y=0;
    Point P,A,B;
    P.input();A.input();B.input();
    double ans11=A.distance(B)/2;
    double ans12=max(A.distance(O),B.distance(P));
    double ans13=max(A.distance(P),B.distance(O));
    double ans1=min(max(ans11,ans12),max(ans11,ans13));
    double ans2=max(A.distance(P),A.distance(O));
    double ans3=max(B.distance(P),B.distance(O));
    print_float(min({ans1,ans2,ans3}),10);cout << endl;
}
/*----------Code Area----------*/

int main(){
    int clk = clock();

#ifndef ONLINE_JUDGE
    if(freopen("in.txt", "r", stdin)==NULL) {cout << "Fail opening in.txt!" << endl;return 0;}
    if(freopen("out.txt", "w", stdout)==NULL) {cout << "Fail opening out.txt!" << endl;return 0;}
#endif

#ifdef IO_OPTIMIZE
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
#endif

#ifdef MUTIPLE_JUDGE
    long T; cin >> T;
    while(T--) solve();
#else
    solve();
#endif

#ifdef CHECK_OUT_TIME
    cout << clock() - clk << " ms\n";
#endif
    return 0;
}