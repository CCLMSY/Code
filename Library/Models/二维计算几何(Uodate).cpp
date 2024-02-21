#include<bits/stdc++.h>
using namespace std;

/*----------Consts----------*/
const long MOD=1e9+7;
const double eps=1e-80;

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
    #define RESET(A) memset(A,0,sizeof(A))
    #define ALL(A) (A).begin(),(A).end()
    #define SORT(A) sort(ALL(A))
    #define SORT_REV(A) sort((A).rbegin(),(A).rend())
    #define UNIQUE(A) unique(ALL(A))
    #define Presentation(i,r) " \n"[i==r]
    #define FORLL(i,l,r) for(ll i=l;i<=r;i++)
    #define FORLL_rev(i,r,l) for(ll i=r;i>=l;i--)
    #define Get_Mod(a) (((a)+MOD)%MOD)
    #define pb push_back
    #define NO "NO\n"
    #define YES "YES\n"
    #define endl '\n'
}

struct Point{
    ld x,y;
    Point(ld _x=0,ld _y=0):x(_x),y(_y){}
    Point operator+(const Point &b) const {return Point(x+b.x,y+b.y);}
    Point operator-(const Point &b) const {return Point(x-b.x,y-b.y);}
    Point operator*(const ld &b) const {return Point(x*b,y*b);}
    Point operator/(const ld &b) const {return Point(x/b,y/b);}
};

struct Line{
    Point st,ed;
};

