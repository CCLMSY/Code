#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;

#define FORLL(i,l,r) for(ll i=l;i<=r;i++)
#define FORLL_rev(i,r,l) for(ll i=r;i>=l;i--) 
#define ALL(A) (A).begin(),(A).end()
#define endl '\n'

const ll INF = 0x3fffffffffffffff;
const ll MAXN=1e3;
const ll MAXM=1e5;

void printvec(vector<ll>v){
	ll n=v.size();
	FORLL(i,0,n-1) cout << v[i] << " \n"[i==n-1];
} 

int main(){
	ll n;
	cin >> n;
	vector<ll> v(n);
	FORLL(i,0,n-1) cin >> v[i];
	ll ans=2,t;
	vector<ll> st; 
	vector<ll>::iterator it;
	FORLL(i,0,n-1){
		if(n-i<=ans) break;
		st.clear();
		FORLL(j,i+1,n-1){
			if(v[j]>=v[i]) ans=max(ans,(ll)st.size()+2);
			else{
				it = upper_bound(ALL(st),v[j]);
				t=distance(st.begin(),it);
//				cout << t << endl;
				ans=max(ans,t+2);
				st.insert(it,v[j]);
			}
//			printvec(st);
		}
	}
	cout << ans << endl;
	return 0;
} 
//
//7
//7 1 6 2 5 3 4














