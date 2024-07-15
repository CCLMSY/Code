#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
#define FORLL(i,l,r) for(ll i=l;i<=r;i++)

ll ans,n,k;
unordered_map<ll,ll> mp;

ll query(ll cur,ll cnt){
    if(mp[cur]) return mp[cur];
    ll tmp = 0;
    if(cur>k){
        if(cur%2==0){
            tmp+=2*query(cur/2,cnt*2);
        }else{
            tmp+=query(cur/2,cnt);
            tmp+=query(cur/2+1,cnt);
        }
    }else{
        tmp = 1;
    }
    return mp[cur]=tmp;
}

void solve(){
    ans = 0;
    mp.clear();
    cin >> n >> k;
    query(n,1);
    cout << mp[n]*2-1 << endl;
}

signed main(){
    ll T=1;
    cin >> T;
    while(T--){
        solve();
    }
    return 0;
}