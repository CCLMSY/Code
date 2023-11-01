#include<bits/stdc++.h>
//Pollard_rho 大数因子分解快速随机算法
//Miller-Rabin 素数性测试算法
using namespace std;
ll qcpow_p(ll a,ll b,ll p){
	ll ret=1;
	for(;b;b>>=1,a=(__int128)a*a%p)
		if(b&1)ret=(__int128)ret*a%p;
	return ret;
}
bool Miller_Rabin(ll p){
	if(p<2)return 0;
	if(p==2||p==3)return 1;
	ll d=p-1,r=0;
	while(!(d&1))++r,d>>=1;
	for(ll k=0;k<10;++k){
		ll a=rand()%(p-2)+2;
		ll x=qcpow_p(a,d,p);
		if(x==1||x==p-1)continue;
		for(int i=0;i<r-1;++i){
			x=(__int128)x*x%p;
			if(x==p-1)break;
		}
		if(x!=p-1)return 0;
	}
	return 1;
}
ll Pollard_Rho(ll x){
	ll s=0,t=0;
	ll c=(ll)rand()%(x-1)+1;
	int step=0,goal=1;
	ll val=1;
	for(goal=1;;goal<<=1,s=t,val=1){
		for(step=1;step<=goal;step++){
			t=((__int128)t*t+c)%x;
			val=(__int128)val*abs(t-s)%x;
			if(step%127==0){
				ll d=__gcd(val,x);
				if(d>1)return d;
			}
		}
		ll d=__gcd(val,x);
		if(d>1)return d;
	}
}
int main(){
	ll t,n;
	cin >> t;
	while(t--){
		cin >> n;
		cout << Pollard_Rho(n) << endl;
	}
	return 0;
}