#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
// 字典树TRIE
// 解决的问题：统计字符串在字典中出现/以前缀形式出现的次数
struct TRIE{
    vector<array<int,62>> nxt; //0-25:a-z,26-51:A-Z,52-61:0-9
    vector<int> cnt; //第i个结点出现/前缀的次数
    ll n,curn; //curn是当前节点数，n是（本题单个数据）字典字符串最大总长度
    TRIE(ll n_):nxt(n_+1,{0}),cnt(n_+1,0),n(n_),curn(0){} //70*N(3e6)->Luogu300ms/750MB
    int trans(char c){ //字符转换为数字，以全62字符为例，根据题意修改
        if(c>='a'&&c<='z') return c-'a';
        else if(c>='A'&&c<='Z') return c-'A'+26;
        return c-'0'+52;
    }
    void insert(string s){
        ll p=0;
        for(auto c:s){
            c = trans(c);
            if(nxt[p][c]==0) nxt[p][c]=++curn;
            p=nxt[p][c];
            // cnt[p]++; //统计前缀出现次数
        }
        cnt[p]++; //统计单词出现次数
    }
    ll count(string s){
        ll p=0;
        for(auto c:s){
            c = trans(c);
            if(nxt[p][c]==0) return 0;
            p=nxt[p][c];
        }
        return cnt[p];
    }
    void clear(){ //最坏：70*N
        for(ll i=0;i<=curn+1;i++){
            for(ll j=0;j<=61;j++) nxt[i][j]=0;
            cnt[i]=0;
        }
        curn=0;
    }
};
const ll N=3e6+6;
TRIE trie(N);

void solve(){
    trie.clear();
    ll n,q;cin >> n >> q;
    string s;
    for(ll i=0;i<n;i++){
        cin >> s;
        trie.insert(s);
    }
    for(ll i=0;i<q;i++){
        cin >> s;
        cout << trie.count(s) << endl;
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    
    ll T; cin >> T;
    while(T--) solve();

    return 0;
}