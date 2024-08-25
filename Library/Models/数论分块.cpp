#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

// 数论分块
// 解决的问题：快速计算一些含有 除法向下取整 的 和式

// 分块，vr_i存储\floor{x/i}相同的分块的右端点
vector<ll> vr; 
// 求取分块
void Sqrt_dec(ll x){
    vr.clear(); ll r=1;
    for(ll l=1;l<=x;l=vr.back()+1){
        r=x/(x/l);
        vr.emplace_back(r);
    }
}

// 函数f的前缀和
vector<ll> pref; 
//数论分块，求函数g(x)=\sum_{i=1}^{x} f(i)*\floor{x/i}的值
ll Get_G(ll x){ 
    ll res=0,r=1;
    for(ll l=1;l<=x;l=r+1){
        r=x/(x/l);
        res+=(pref[r]-pref[l-1])*(x/l)*(r-l+1);
    }
    return res;
}