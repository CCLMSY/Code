#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

struct MinHeap{
    vector<ll> data;

    MinHeap(){}

    ll& operator[](ll index){
        if(index>=data.size()||index<0) throw out_of_range("Index out of range.");
        return data[index];
    }

    ll push(ll x){
        data.emplace_back(x);
        ll cur=data.size()-1;
        while(cur>0&&data[cur]<data[(cur-1)/2]){//(cur+1)/2-1=(cur-1)/2
            swap(data[(cur-1)/2],data[cur]);
            cur=(cur-1)/2;
        }return cur;
    }//插入x，返回元素最终位置

    void heapify(ll index){
        if(data.size()<=0) return ;
        if(index<0) throw out_of_range("Index out of range.");
        ll l=index*2+1,r=index*2+2;
        ll mn=index;//最小值下标

        if(l<data.size()&&data[l]<data[mn]) mn=l;
        if(r<data.size()&&data[r]<data[mn]) mn=r;

        if(mn!=index){
            swap(data[index],data[mn]);
            heapify(mn);
        }
    }//调整堆

    void pop(){
        if(data.size()<=0) return ;
        swap(data[0],data[data.size()-1]);
        data.pop_back();
        heapify(0);
    }//弹出堆顶

    ll query(){ 
        return data[0];
    }//查询最小值

    ll size(){
        return data.size();
    }
};

struct MaxHeap{
    vector<ll> data;

    MaxHeap(){}

    ll& operator[](ll index){
        if(index>=data.size()||index<0) throw out_of_range("Index out of range.");
        return data[index];
    }

    ll push(ll x){
        data.emplace_back(x);
        ll cur=data.size()-1;
        while(cur>0&&data[cur]>data[(cur-1)/2]){//(cur+1)/2-1=(cur-1)/2
            swap(data[(cur-1)/2],data[cur]);
            cur=(cur-1)/2;
        }return cur;
    }//插入x，返回元素最终位置

    void heapify(ll index){
        if(data.size()<=0) return ;
        if(index<0) throw out_of_range("Index out of range.");
        ll l=index*2+1,r=index*2+2;
        ll mx=index;//最大值下标

        if(l<data.size()&&data[l]>data[mx]) mx=l;
        if(r<data.size()&&data[r]>data[mx]) mx=r;

        if(mx!=index){
            swap(data[index],data[mx]);
            heapify(mx);
        }
    }//调整堆

    void pop(){
        if(data.size()<=0) return ;
        swap(data[0],data[data.size()-1]);
        data.pop_back();
        heapify(0);
    }//弹出堆顶

    ll query(){ 
        return data[0];
    }//查询最小值

    ll size(){
        return data.size();
    }
};

void solve(){
    MinHeap mnh;
    ll n,t;cin >> n;
    int op;
    while(n--){
        cin >> op;
        if(op==1){
            cin >> t;
            mnh.push(t);
        }else if(op==2){
            cout << mnh.query() << endl;
        }else if(op==3){
            mnh.pop();
        }
    }
}