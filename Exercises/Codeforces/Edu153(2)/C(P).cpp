#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll INF=0x3ffffff;
void solve(){
    ll mn,mnn;mn=mnn=INF;
    ll t,n;ll cnt=0;
    cin >> n;
    for(ll i=0;i<n;i++){
        cin >> t;
        if(t<mn){
            mn=t;
        }else if(t<mnn){
            mnn=t;
            cnt++;
        }
    }cout << cnt << endl;
    return;
}
int main(){
    ll T;
    cin >> T;
    while(T--){
        solve();
    }return 0;
}