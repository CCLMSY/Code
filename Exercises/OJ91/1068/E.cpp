#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
#define FORLL(i,l,r) for(ll i=l;i<=r;i++)

void solve(){
    ll ans = 0;
    ll n;cin >> n;
    ll ub=(n-1)/2,cur=1;
    while(ub>=cur){
        ans+=cur;
        cur*=2;
    }
    cout << ans << endl;
}

signed main(){
    ll T=1;
    cin >> T;
    while(T--){
        solve();
    }
    return 0;
}