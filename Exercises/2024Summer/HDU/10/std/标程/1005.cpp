// Problem: HDOJ 套娃
// Url: https://acm.hdu.edu.cn/contest/problem?cid=1143&pid=1005
// T/M Limit: 2000ms 524288MB
// Time: 2024-08-17 10:01:33
// Author: ShaoJia

#pragma GCC optimize("Ofast")
#include<bits/stdc++.h>
using namespace std;
#define rep(Ii,Jj,Kk) for(int Ii=(Jj),Ii##_=(Kk);Ii<=Ii##_;Ii++)
#define per(Ii,Jj,Kk) for(int Ii=(Jj),Ii##_=(Kk);Ii>=Ii##_;Ii--)
typedef long long ll;
typedef unsigned long long ull;
typedef unsigned uint;
typedef long double db;
#define fir first
#define sec second
#define siz(Aa) ((int)(Aa).size())
#define all(Aa) (Aa).begin(),(Aa).end()
#define ckmx(Aa,Bb) (Aa=max(Aa,Bb))
#define ckmn(Aa,Bb) (Aa=min(Aa,Bb))
struct vec{
	int x,y;
	vec(){}
	vec(int xx,int yy):x(xx),y(yy){}
	ll dist()const{return 1ll*x*x+1ll*y*y;}
	bool operator==(const vec&v)const{return x==v.x&&y==v.y;}
	bool operator!=(const vec&v)const{return !(*this==v);}
	vec operator- ()const{ return vec(-x,-y); }
	vec&operator+=(const vec&v){x+=v.x,y+=v.y;return *this;}
	vec&operator-=(const vec&v){x-=v.x,y-=v.y;return *this;}
	vec operator+ (const vec&v)const{vec u=*this;return u+=v;}
	vec operator- (const vec&v)const{vec u=*this;return u-=v;}
	ll  operator* (const vec&v)const{return 1ll*x*v.x+1ll*y*v.y;}
	ll  operator^ (const vec&v)const{return 1ll*x*v.y-1ll*y*v.x;}
	vec&operator*=(const int k){x*=k,y*=k;return *this;}
	vec&operator/=(const int k){x/=k,y/=k;return *this;}
	vec operator* (const int k)const{vec u=*this;return u*=k;}
	vec operator/ (const int k)const{vec u=*this;return u/=k;}
	friend vec operator*(const int k,const vec&v){return v*k;}
	friend istream& operator>>(istream&is,vec&v){ return is>>v.x>>v.y; }
	friend ostream& operator<<(ostream&os,const vec&v){ return os<<"("<<v.x<<","<<v.y<<")"; }
};
struct line{
	vec p,w;
	db ang;
	line(){}
	line(const vec&x,const vec&y):p(x),w(y),ang(atan2(y.y,y.x)){}
	friend istream& operator>>(istream&is,line&l){ return is>>l.p>>l.w; }
	friend ostream& operator<<(ostream&os,const line&l){ return os<<"["<<l.p<<"->"<<l.w<<"]"; }
};
// vec operator^(const line&l){ return p+(l.w^(p-l.p))/(w^l.w)*w; }
const int N=100010,M=200010,V=1.01e9;
bool ole(const vec&x,const line&y){//点 x 在直线 y 的左侧（逆时针侧）
	return (y.w^(x-y.p))>0;
}
void show(line a){
	a.w+=a.p;
	cout<<"Segment "<<a.p.x<<" "<<a.p.y<<" "<<a.w.x<<" "<<a.w.y<<"\n";
	cout<<a.w.x<<" "<<a.w.y<<"\n";
}
using big=__int128;
bool ole(line a,line b,line c){//点 a^b 在直线 c 的左侧（逆时针侧）
	// show(a);
	// show(b);
	// show(c);
	big val=a.w^b.w,tar=val;
	big x=(a.p.x-c.p.x)*val;
	big y=(a.p.y-c.p.y)*val;
	val=b.w^(a.p-b.p);
	x+=a.w.x*val;
	y+=a.w.y*val;
	val=c.w.x*y-c.w.y*x;
	return (val>0 && tar>0) || (val<0 && tar<0);
}
int q[M],head,tail;
auto cmp=[](const line&x,const line&y){return x.ang<y.ang;};
bool HalfPlane(line *a,line *ae){
	sort(a,ae,cmp);
	int n=ae-a;
	// cout<<"tot:\n";
	// rep(i,0,n-1) show(a[i]);
	// cout<<"...\n";
	q[head=tail=0]=0;
	rep(i,1,n-1){
		while(head<tail && !ole(a[q[tail-1]],a[q[tail]],a[i])) tail--;
		while(head<tail && !ole(a[q[head]],a[q[head+1]],a[i])) head++;
		if(a[i].ang!=a[q[tail]].ang) q[++tail]=i;
		else if(ole(a[i].p,a[q[tail]])) q[tail]=i;
		// cout<<i<<":\n";
		// rep(j,head,tail) show(a[q[j]]);
		// cout<<"...\n";
	}
	while(head<tail && !ole(a[q[tail-1]],a[q[tail]],a[q[head]])) tail--;
	return head+2<=tail; 
}
line s[M];
int st=0;
bool slv(const vector<vec>&a,const vector<vec>&b){
	int n=siz(a),m=siz(b),x=0;
	st=0;
	s[++st]=line(vec(-V,V),vec(0,-1));
	s[++st]=line(vec(-V,-V),vec(1,0));
	s[++st]=line(vec(V,-V),vec(0,1));
	s[++st]=line(vec(V,V),vec(-1,0));
	rep(i,0,m-1){
		vec w=b[(i+1)%m]-b[i];
		int y;
		while(y=(x+1)%n  ,(w^a[x])>(w^a[y])) x=y;
		while(y=(x+n-1)%n,(w^a[x])>(w^a[y])) x=y;
		line li(b[i]-a[x],w);
		s[++st]=li;
	}
	return HalfPlane(s+1,s+st+1);
}
int n;
ll ar[N];
vector<vec> w[N];
int id[N];
void work(){
	cin>>n;
	rep(i,1,n){
		int x;cin>>x;
		w[i].resize(x);
		for(auto&j:w[i]){
          int y,z;cin>>y>>z;
          j.x=y,j.y=z;
        }
		ar[i]=w[i][x-1]^w[i][0];
		rep(j,0,x-2) ar[i]+=w[i][j]^w[i][j+1];
		assert(ar[i]>0);
	}
	iota(id+1,id+1+n,1);
	sort(id+1,id+1+n,[](int x,int y){return ar[x]<ar[y];});
	// rep(i,1,n) cout<<id[i]<<" \n"[i==i_];
	rep(i,1,n-1) if(!slv(w[id[i]],w[id[i+1]])){
		cout<<"No\n";
		return ;
	}
	cout<<"Yes\n";
}
signed main(){ios::sync_with_stdio(false),cin.tie(nullptr);
	int T;cin>>T;
	rep(i,1,T)work();
return 0;}
/*
*/