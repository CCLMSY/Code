#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;

// 高效求阶乘模大质数的值，模数要求能够NTT
// 用法：预处理NTT_init(1<<18)，Getfac(n,P)返回n!%P
// 时间复杂度：O(√n·logn)
#define IMP(lim,act) for(ll qwq=(lim),i=0;i^qwq;++i)act
const ld Pi=acos(-1);
const ll M=3e5+5;
ll n,P,F[M],ifac[M];
struct Barrett{
	typedef unsigned long long ull;
	typedef __uint128_t LL;
	ull m,B;
	Barrett(const ull&m=2):m(m),B((LL(1)<<64)/m){}
	friend inline ull operator%(const ull&a,const Barrett&mod){
		ull r=a-mod.m*(LL(mod.B)*a>>64);return r>=mod.m?r-mod.m:r;
	}
}mod;
struct complex{
	ld x,y;
	complex(const ld&x=0,const ld&y=0):x(x),y(y){}
	inline complex operator+(const complex&it)const{
		return complex(x+it.x,y+it.y);
	}
	inline complex operator-(const complex&it)const{
		return complex(x-it.x,y-it.y);
	}
	inline complex operator*(const complex&it)const{
		return complex(x*it.x-y*it.y,x*it.y+y*it.x);
	}
}buf[M],*w[20];
inline ll Getlen(const ll&n){//
	ll len(0);while((1<<len)<n)++len;return len;
}
int swap(::complex&a,::complex&b){//
	::complex c=a;a=b;b=c;
    return 0;
}
inline ll Get(const ld&x){//
	return((long long)(x+.5))%mod;
}
inline ll qpow(ll a,ll b=P-2){//
	ll ans(1);for(;b;b>>=1,a=1ll*a*a%mod)if(b&1)ans=1ll*ans*a%mod;return ans;
}
inline void NTT_init(const ll&n){//
	const ll&m=Getlen(n)-1;::complex*now=buf;w[m]=now;now+=1<<m;
	IMP(1<<m,w[m][i]=::complex(std::cos(i*Pi/(1<<m)),std::sin(i*Pi/(1<<m))));
	for(ll k=m-1;k>=0&&(w[k]=now,now+=1<<k);--k)IMP(1<<k,w[k][i]=w[k+1][i<<1]);
}
inline void DFT(::complex*f,const ll&M){//
	const ll&n=1<<M;
	for(ll len=n>>1,d=M-1;d>=0;--d,len>>=1)for(ll k=0;k^n;k+=len<<1){
		::complex*W=w[d],*L=f+(k),*R=f+(k|len),x,y;IMP(len,(x=*L,y=*R)),*L++=(x+y),*R++=*W++*(x-y);
	}
}
inline void IDFT(::complex*f,const ll&M){//
	const ll&n=1<<M;
	for(ll len=1,d=0;d^M;++d,len<<=1)for(ll k=0;k^n;k+=len<<1){
		::complex*W=w[d],*L=f+(k),*R=f+(k|len),x,y;IMP(len,(x=*L,y=*W++**R)),*L++=(x+y),*R++=(x-y);
	}
	IMP(n,(f[i].x/=n,f[i].y/=n));for(ll i=1;(i<<1)<n;++i)swap(f[i],f[n-i]);
}
inline void MTT(ll*f,ll*g,ll*h,const ll&n,const ll&m,const ll&t,const ll&Len=-1){//
	static ::complex Q[M],P[M],T[M];const ll&len=Getlen(!~Len?n+m-1:Len);
	IMP(n,(Q[i].x=f[i]&32767,P[i].x=f[i]>>15));IMP(m,T[i]=::complex(g[i]&32767,g[i]>>15));
	DFT(Q,len);DFT(P,len);DFT(T,len);IMP(1<<len,(Q[i]=Q[i]*T[i],P[i]=P[i]*T[i]));IDFT(Q,len);IDFT(P,len);
	IMP(t,h[i]=(Get(Q[i].x)+(1ll*Get(Q[i].y+P[i].x)<<15)+(1ll*Get(P[i].y)<<30))%mod);IMP(1<<len,Q[i]=P[i]=T[i]=0);
}
inline void Getinv(ll*f,const ll&n){//
	static ll pre[M];pre[0]=f[0];for(ll i=1;i<n;++i)pre[i]=1ll*pre[i-1]*f[i]%mod;
	ll t,c=qpow(pre[n-1]);for(ll i=n-1;i>=1;--i)t=f[i],f[i]=1ll*pre[i-1]*c%mod,c=1ll*c*t%mod;f[0]=c;
}
inline void PT(ll*f,ll*g,const ll&n,const ll&m){//
	static ll F[M],G[M],H[M];H[0]=1;IMP(n,H[0]=1ll*H[0]*(m-i)%mod);IMP(n+n,G[i]=m+i-n);G[0]=1;Getinv(G,n+n);
	IMP(n,F[i]=1ll*ifac[i]*(n-i-1&1?P-ifac[n-i-1]:ifac[n-i-1])%mod*f[i]%mod);
	const ll&len=Getlen(n+n);for(ll i=1;i<n;++i)H[i]=1ll*(m+i)*G[i]%mod*H[i-1]%mod;MTT(F,G,F,n,n+n,n+n,n+n);
	IMP(n,g[i]=1ll*F[n+i]*H[i]%mod);IMP(1<<len,F[i]=G[i]=H[i]=0);
}
inline ll Getfac(const ll&n,const ll&p){//
	static ll F[M],G[M];const ll&B=sqrt(n),m=Getlen(B)-1;
	mod=Barrett(P=p);ifac[0]=ifac[1]=1;for(ll i=2;i<=B;++i)ifac[i]=1ll*(P-P/i)*ifac[P%i]%mod;
	for(ll i=1;i<=B;++i)ifac[i]=1ll*ifac[i-1]*ifac[i]%mod;F[0]=1;F[1]=B+1;
	for(ll i=m;i>=0;--i){
		const ll&q=B>>i+1,p=B>>i;if(!q)continue;
		PT(F,G,q+1,q+1);IMP(q,F[i+q+1]=G[i]),G[i]=0;G[q]=0;
		PT(F,G,q*2+1,1ll*q*qpow(B)%mod);IMP(q*2+1,F[i]=1ll*F[i]*G[i]%mod),G[i]=0;
		if(q*2+1==p){
			IMP(q*2+1,F[i]=1ll*F[i]*(i*B+p)%mod);F[p]=1;IMP(p,F[p]=1ll*F[p]*(p*B+i+1)%mod);
		}
	}
	ll ans(1);IMP(B,ans=1ll*ans*F[i]%mod),F[i]=0;F[B]=0;for(ll i=B*B+1;i<=n;++i)ans=1ll*ans*i%mod;return ans;
}

int main(){
	NTT_init(1<<18);
	ll T;cin >> T;
	while(T--){
		cin >> n >> P;
		cout << Getfac(n,P) << endl;
	}
	return 0;
}