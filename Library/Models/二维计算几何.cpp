#include<bits/stdc++.h>
using namespace std;

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
}using namespace DEFINITION;

/*----------Consts----------*/
const double eps = 1e-8;
const double inf = 1e20;
const double pi = acos(-1.0);
/*----------Consts----------*/
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

//计算凸包
vector<Point> Convex_Hull(vector<Point> pvec){
    vector<Point> ch;
    ll n=pvec.size();SORT(pvec);
    vector<ll> stk(n+1);ll top=0;stk[++top]=0;
    vector<bool> used(n+1,false);
    FORLL(i,1,n-1){
        while(top>1
        &&(pvec[stk[top]]-pvec[stk[top-1]]).operator
        ^(pvec[i]-pvec[stk[top]])<=0) used[stk[top--]]=false;
        stk[++top]=i;
        used[i]=true;
    }
    ll tmp = top;
    FORLL_rev(i,n-2,0) if (!used[i]){
        while(top>tmp && (pvec[stk[top]]-pvec[stk[top-1]]).operator^(pvec[i]-pvec[stk[top]])<=0) used[stk[top--]]=false;
        stk[++top]=i;
        used[i]=true;
    }
    FORLL(i,1,top) ch.emplace_back(pvec[stk[i]]);
    return ch;
}

