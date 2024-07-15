#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
#define FORLL(i,l,r) for(ll i=l;i<=r;i++)
#define pll pair<ll,ll>
#define ALL(v) (v).begin(),(v).end()
#define SORT(v) sort(ALL(v))
#define endl '\n'

void solve(){
    ll n;cin >> n;
    ll t_x1,t_y1,t_x2,t_y2,t1,t2,tg,t;
    map<pll,ll> mp;
    FORLL(i,1,n){ //nlog
        cin >> t_x1 >> t_y1 >> t_x2 >> t_y2;
        t1 = t_y2-t_y1;
        t2 = t_x2-t_x1;
        if(t1==0){
            t2 = 1;
        }else if (t2==0){
            t1 = 1;
        }else{
            tg = __gcd(t1,t2);
            t1/=tg;
            t2/=tg;
        }
        mp[{t1,t2}]++;
    }
    vector<ll> v;
    for(auto i:mp){ //n
        v.push_back(i.second);
    }
    SORT(v); //nlog
    ll ub=v.back();
    auto it=v.begin();
    t1 = 1;
    FORLL(i,1,ub){ //n
        it = lower_bound(ALL(v),i); //log
        t = v.end()-it;
        while(t--){
            cout << t1-i << endl; //n
            t1++;
        }
    }
}

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    ll T=1;
    cin >> T;
    while(T--){
        solve();
    }
    return 0;
}