#include<bits/stdc++.h>
using namespace std;

#define N 100000
typedef long long ll;

#define lowbit(x) ((x)&(-(x)))//取最后一个1所在位置的权值
struct BITree{//树状数组，下标i从1开始
    vector<ll> Data;

    explicit BITree(ll n):Data(n*2+5,0) {}

    void update(ll i,ll dif)
    {//给予i增量dif,维护树状数组，O(logn)
        while(i<Data.size()){
            Data[i]+=dif;
            i+=lowbit(i);
        }
    }

    ll presum(ll i)
    {//查询前缀和sum[i]，O(logn)
        ll sum=0;
        while(i){
            sum+=Data[i];
            i-=lowbit(i);
        }
        return sum;
    }

    ll query(ll l,ll r){//查询区间和
        return presum(r)-presum(l-1);
    }

    ll operator[](ll index){//下标调用前缀和
        //if(index>(Data.size()-5/2)||index<0) throw out_of_range("Index out of range.");
        return presum(index);
    }
};

int main()
{
    ll n,t,tt=0;
    cin >> n;
    BITree bt(n);
    for(ll i=1;i<=n;i++){
        cin >> t;
        bt.update(i,t);//维护原数组，实现单点修改，区间查询
        /*
        bt.update(i,t-tt);tt=t;
        维护差分数组，实现区间修改，单点查询
        对区间[l,r]的修改变为update(l,dif);update(r+1,-dif);
        对元素a[i]的查询变为presum(i);
        */
    }//建树O(nlogn)
    ll l,r;
    cin >> l >> r;
    cout << bt.query(l,r) << endl;
    ll i,x;
    cin >> i >> x;
    bt.update(i,x);
    cin >> l >> r;
    cout << bt.query(l,r) << endl;
    return 0;
}