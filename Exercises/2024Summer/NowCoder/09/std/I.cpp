#include<bits/stdc++.h>
using namespace std;
#define M 1005
struct hh{
	int a[M],sz;
	void clear(){
		memset(a,0,sizeof(a));sz=0;
	}
	void jw(){
		for(int i=1;i<=sz;++i)a[i+1]+=a[i]/10,a[i]%=10;
		while(a[sz+1])++sz;
	}
	hh operator*(hh x){
		hh s;s.clear();
		s.sz=sz+x.sz-1;
		for(int i=1;i<=sz;++i)
			for(int j=1;j<=x.sz;++j)s.a[i+j-1]+=a[i]*x.a[j];
		s.jw();
		return s;
	}
	hh operator-(hh x){
		hh s;s.clear();s.sz=sz;
		for(int i=1;i<=sz;++i)s.a[i]=a[i]-x.a[i];
		for(int i=1;i<=sz;++i)if(s.a[i]<0)s.a[i]+=10,s.a[i+1]--;
		while(s.sz&&s.a[s.sz]==0)--s.sz;
		return s;
	}
	hh operator+(hh x){
		hh s;s.clear();s.sz=max(sz,x.sz);
		for(int i=1;i<=s.sz;++i)s.a[i]=a[i]+x.a[i];
		s.jw();
		return s;
	}
	bool operator<=(hh x)const{
		if(sz>x.sz)return 0;
		if(sz<x.sz)return 1;
		for(int i=sz;i>=1;--i){
			if(a[i]>x.a[i])return 0;
			if(a[i]<x.a[i])return 1;
		}
		return 1;
	}
	hh operator/(int x){
		hh s;s.clear();
		for(int i=sz,tp=0;i>=1;--i){
			tp=tp*10+a[i];
			s.a[i]=tp/x;
			if(s.a[i])s.sz=max(s.sz,i);
			tp%=x;
		}
		return s;
	}
	void out(){
		for(int i=sz;i>=1;--i)printf("%d",a[i]);
		puts("");
	}
}a,L,R,ls;
hh sqrt(hh x){
	hh l,r;l.clear();r.clear();
	l.sz=1;l.a[1]=1;r=x;
	while(l<=r){
		hh mid=(l+r)/2;
		if(mid*mid<=x)l=mid+ls;
		else r=mid-ls;
	}
	return l-ls;
}
int n;
hh solve(hh a){
	if(a.sz<n)return a.clear(),a;
	hh p1,p2;p1.clear();p2.clear();
	p1.sz=p2.sz=n/2;
	for(int i=n/2;i>=1;--i)p1.a[i]=a.a[i+n/2];
	for(int i=n/2;i>=1;--i)p2.a[i]=a.a[i];
	while(p2.sz&&!p2.a[p2.sz])p2.sz--;
	hh ans,gd,ac;ans.clear();gd.clear();ac.clear();
	gd.sz=n/2-1;ac.sz=n/2;
	for(int i=1;i<n/2;++i)gd.a[i]=9;
	for(int i=1;i<=n/2;++i)ac.a[i]=9;
	ans=(sqrt(p1-ls)-sqrt(gd))*(sqrt(ac)+ls);
	if(p1<=sqrt(p1)*sqrt(p1))ans=ans+sqrt(p2)+ls;
	return ans;
}
int main(){
//	freopen("data10.in","r",stdin);
//	freopen("data10.ans","w",stdout);
	scanf("%d",&n);
	L.sz=R.sz=n;
	for(int i=n;i>=1;--i)scanf("%01d",&L.a[i]);
	for(int i=n;i>=1;--i)scanf("%01d",&R.a[i]);
	ls.sz=1;ls.a[1]=1;
	L=L-ls;
	a=solve(R)-solve(L);
	a.out();
}
