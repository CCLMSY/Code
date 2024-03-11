#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
//字典树
struct TRIE{
    vector<array<int,62>> nxt;
    vector<int> cnt;
    ll n,curn;
    TRIE(ll n_):nxt(n_+1,{0}),cnt(n_+1,0),n(n_),curn(0){} //n是字符串总长度
    void insert(string s){
        ll p=0;
        for(auto c:s){
            if(c>='a'&&c<='z') c-='a';else if(c>='A'&&c<='Z') c-='A'-26; else c-='0'-52;
            if(nxt[p][c]==0) nxt[p][c]=++curn;
            p=nxt[p][c];
            cnt[p]++; //统计前缀出现次数
        }
        // cnt[p]++; //统计单词出现次数
    }
    ll count(string s){
        ll p=0;
        for(auto c:s){
            if(c>='a'&&c<='z') c-='a';else if(c>='A'&&c<='Z') c-='A'-26; else c-='0'-52;
            if(nxt[p][c]==0) return 0;
            p=nxt[p][c];
        }
        return cnt[p];
    }
    void clear(){
        FORLL(i,0,curn+1){
            FORLL(j,0,61) nxt[i][j]=0;
            cnt[i]=0;
        }
        curn=0;
    }
};
const ll N=3e6+6;
TRIE trie(N);