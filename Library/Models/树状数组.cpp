#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

#define lowbit(x) ((x) & (-(x))) // 取最后一个1所在位置的权值

const ll N=5e5+5; //（本题单个数据）数组最大长度
// 树状数组（下标i从1开始）
// 解决的问题：单点修改，区间查询/区间修改，单点查询
// 单次时间复杂度：O(logn)
// fl=0: 维护原数组，实现单点修改，区间查询
// fl=1: 维护差分数组，实现区间修改，单点查询
struct BiTree{
    vector<ll> data; // 树状数组
    int fl;
    ll n; // 当前数组长度
    BiTree(int fl=0):data(N*2+5,0),fl(fl),n(0){}
    // 重置树状数组
    void clear(){ for(ll i=0;i<=n*2+1;i++) data[i]=0; }
    // 给予v[i]增量dif,维护树状数组，O(logn)
    void update(ll i,ll dif){
        while(i<data.size()){
            data[i]+=dif;
            i+=lowbit(i);
        }
    }
    // 给予区间[l,r]增量dif,维护树状数组，O(logn)
    void update(ll l,ll r,ll dif){
        assert(fl==1);
        update(l,dif);
        update(r+1,-dif);
    }
    // 建立树状数组，v下标从1开始，v[0]=0
    void build(vector<ll>& v,int fl=0){
        clear(); this->fl=fl; n=v.size()-1;
        if(fl){ for(ll i=1;i<=n;i++) update(i,v[i]-v[i-1]); }
        else { for(ll i=1;i<=n;i++) update(i,v[i]); }
    }
    // 查询前缀和sum[i]，O(logn)
    ll presum(ll i){
        ll sum=0;
        while(i){
            sum+=data[i];
            i-=lowbit(i);
        }
        return sum;
    }
    // 区间查询[l,r]
    ll query(ll l,ll r){
        assert(fl==0);
        return presum(r)-presum(l-1);
    }
    // 单点查询v[i]
    ll query(ll i){
        assert(fl==1);
        return presum(i);
    }
} bt;
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    ll n,q;cin >> n >> q;
    vector<ll> v(n+1,0);
    for(ll i=1;i<=n;i++) cin >> v[i];
    ll op,x,y,k;
    // P3374
    bt.build(v,0);
    for(ll i=0;i<q;i++){
        cin >> op;
        if(op==1){
            cin >> x >> k;
            bt.update(x,k);
        }else{
            cin >> x >> y;
            cout << bt.query(x,y) << endl;
        }
    }
    // P3368
    // bt.build(v,1);
    // for(ll i=0;i<q;i++){
    //     cin >> op;
    //     if(op==1){
    //         cin >> x >> y >> k;
    //         bt.update(x,y,k);
    //     }else{
    //         cin >> x;
    //         cout << bt.query(x) << endl;
    //     }
    // }
}