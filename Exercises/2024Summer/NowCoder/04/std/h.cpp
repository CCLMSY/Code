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
ll T,n,a[100010];
int main(){
	std::ios::sync_with_stdio(false);
	cin.tie(0);
	cin>>T;
	while(T--){
		cin>>n;
		rep(i,1,n){
			cin>>a[i];
		}
		sort(a+1,a+1+n);
		ll g=0;
		rep(i,2,n){
			g=__gcd(g,a[i]-a[i-1]);
		}
		cout<<g<<"\n";
	}
	return 0;
}
