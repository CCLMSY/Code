#include<bits/stdc++.h>
using namespace std;
#define rep(i,a,n) for(int i=a;i<=n;i++)
#define per(i,a,n) for(int i=n;i>=a;i--)
#define pb push_back
#define SZ(v) ((int)v.size())
#define fs first
#define sc second
#define all(x) (x.begin()),(x.end())
typedef long long ll;
typedef double db;
typedef pair<int,int> pii;
ll sqr(ll x){
	ll l=0,r=1e9+10;
	while(r-l>1){
		ll mid=(r+l)/2ll;
		if(mid*mid<=x)	l=mid;
		else	r=mid;
	}return l;
}
int main(){
	std::ios::sync_with_stdio(false);
	cin.tie(0);
	ll T,n;
	cin>>T;
	while(T--){
		cin>>n;
		ll sq=floor(sqr(n));
		if(sq*sq==n){
			cout<<2*sq+1<<endl;
		}
		else{
			if(n<=sq*sq+sq){
				if((n-sq*sq)%2==sq%2)	cout<<2*sq+2<<endl;
				else	cout<<2*sq+3<<endl;
			}
			else	cout<<2*sq+3<<endl;
		}
	}	
	return 0;
}
