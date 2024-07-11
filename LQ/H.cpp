#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;

#define FORLL(i,l,r) for(ll i=l;i<=r;i++)
#define ALL(A) (A).begin(),(A).end()
#define SORT(A) sort(ALL(A))
#define endl '\n'

vector<ll> pris;
vector<ll>::iterator it;
vector<int> fl;


void pre(ll N=1e7){
	fl.resize(N+5,0);
	fl[0]=1;
	fl[1]=1;
	FORLL(i,0,N) {
		if(!fl[i]) pris.push_back(i);
		ll tn=pris.size();
		FORLL(j,0,tn-1){
			if(pris[j]*i>N) break;
			fl[pris[j]*i]=1;
		}
	}
}

int main(){
	pre();
	ll n,q;
	cin >> n >> q;
	vector<ll> a(n);
	FORLL(i,0,n-1) cin >> a[i];
	ll op,k,x,t,tx;
	while(q--){
		cin >> op >> k >> x;
		FORLL(i,1,n/k){
			tx=x;
			if(op==1){
				it=upper_bound(ALL(pris),a[i*k-1]);
				tx--;
				while(tx--) it++;
				a[i*k-1]=(*it);
//				cout << i*k << ' ' << *it << endl;
			}else{
				it=lower_bound(ALL(pris),a[i*k-1]);
				t=distance(pris.begin(),it);
				if(t<x){
					tx-=t;
					a[i*k-1]=-pris[tx-1];
				}else{
					while(tx--) it--;
					a[i*k-1]=(*it);
				}
			}
		}
	}
	FORLL(i,0,n-1){
		if(a[i]<0) cout << 0;
		else if(a[i]>1000000) cout << 1;
		else cout << a[i];
		cout << " \n"[i==n-1];
	}
	return 0;
} 