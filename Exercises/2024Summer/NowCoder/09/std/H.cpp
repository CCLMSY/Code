#include<bits/stdc++.h>
#define ll long long
#define N 1000005
using namespace std;
struct point{ll x,y;}p[N];
inline point operator-(point a,point b){return (point){a.x-b.x,a.y-b.y};}
inline bool cmp(point a,point b){
	if(a.x==b.x) return a.y<b.y;
	else return a.x<b.x;
}
inline ll cross(point a,point b){return a.x*b.y-a.y*b.x;}
ll T,n,i,j,top,pos,sta[N],p3,p4,ans;
long double dis(point a){
	return sqrtl(a.x*a.x+a.y*a.y);
}
struct IO{
    static const int S=1<<21;
    char buf[S],*p1,*p2;int st[105],Top;
    ~IO(){clear();}
    inline void clear(){fwrite(buf,1,Top,stdout);Top=0;}
    inline void pc(const char c){Top==S&&(clear(),0);buf[Top++]=c;}
    inline char gc(){return p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++;}
    inline IO&operator >> (char&x){while(x=gc(),x==' '||x=='\n'||x=='\r');return *this;}
    template<typename T>inline IO&operator >> (T&x){
        x=0;bool f=0;char ch=gc();
        while(ch<'0'||ch>'9'){if(ch=='-') f^=1;ch=gc();}
        while(ch>='0'&&ch<='9') x=(x<<3)+(x<<1)+ch-'0',ch=gc();
        f?x=-x:0;return *this;
    }
    inline IO&operator << (const char c){pc(c);return *this;}
    template<typename T>inline IO&operator << (T x){
        if(x<0) pc('-'),x=-x;
        do{st[++st[0]]=x%10,x/=10;}while(x);
        while(st[0]) pc('0'+st[st[0]--]);return *this;
    }
}fin;
int main(){
	for(fin>>T;T--;){
		n=i=j=top=pos=p3=p4=ans=0;
		fin>>n;
		for(i=1;i<=n;i++) fin>>p[i].x>>p[i].y;
		long double res=0;
		for(i=1;i<=n;i++)res+=dis(p[i]-p[i%n+1]);
		fin>>n;
		for(i=1;i<=n;i++) fin>>p[i].x>>p[i].y;
		sort(p+1,p+n+1,cmp);
		for(i=1;i<=n;i++){
			while(top>=2&&cross(p[sta[top]]-p[sta[top-1]],p[i]-p[sta[top]])>=0) top--;
			sta[++top]=i;
		}
		pos=top;
		for(i=n-1;i>=1;i--){
			while(top>=pos+1&&cross(p[sta[top]]-p[sta[top-1]],p[i]-p[sta[top]])>=0) top--;
			sta[++top]=i;
		}
		ans=0;
		for(i=1,j=pos,p3=1,p4=pos;i<=pos;i++){
			while(j<=top){
				ans=max(ans,(p[sta[i]].x-p[sta[j]].x)*(p[sta[i]].x-p[sta[j]].x)+(p[sta[i]].y-p[sta[j]].y)*(p[sta[i]].y-p[sta[j]].y));
				if(j+1>top||(cross(p[sta[j]]-p[sta[j+1]],p[sta[i+1]]-p[sta[i]])>=0&&i+1<=pos)) break;
				j++;
			}
		}
		cout<<fixed<<setprecision(20)<<res+sqrtl(ans)*2*acosl(-1)<<'\n';
	}
	return 0;
}