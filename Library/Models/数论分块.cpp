#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

vector<ll> vr; //数论分块，vr存储\floor{x/i}相同的分块的右端点
void Sqrt_dec(ll x){
    vr.clear(); ll r=1;
    for(ll l=1;l<=x;l=vr.back()+1){
        r=x/(x/l);
        vr.emplace_back(r);
    }
}

vector<ll> pref; //函数f前缀和
ll Get_G(ll x){ //数论分块，求函数g(x)=\sum_{i=1}^{x} f(i)*\floor{x/i}
    ll res=0,r=1;
    for(ll l=1;l<=x;l=vr.back()+1){
        r=x/(x/l);
        res+=(pref[r]-pref[l-1])*(x/l)*(r-l+1);
    }
    return res;
}