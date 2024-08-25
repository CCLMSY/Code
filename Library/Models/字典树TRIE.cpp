#include<bits/stdc++.h>
using namespace std;
typedef long ll;
//字符转换为数字，以全62字符为例，根据题意修改
inline int trans(char c){
    if(c>='a'&&c<='z') return c-'a';
    else if(c>='A'&&c<='Z') return c-'A'+26;
    return c-'0'+52;
}
const ll N=3e6+6; //（本题单个数据）**字典**字符串最大总长度
const ll M=62; //字符集大小
// 字典树TRIE
// 解决的问题：统计字符串在字典中出现/以前缀形式出现的次数
//M(62)*N(3e6)->Luogu300ms/750MB
struct TRIE{
    vector<array<ll,62>> nxt; //经过字符边到达的下一状态
    vector<ll> cnt; //第i个结点出现/前缀的次数
    ll curn; //curn是当前节点数
    TRIE():nxt(N,{0}),cnt(N,0),curn(0){} 
    // 重置TRIE
    void clear(){
        for(ll i=0;i<=curn+1;i++){
            for(ll j=0;j<M;j++) nxt[i][j]=0;
            cnt[i]=0;
        }
        curn=0;
    }
    // 加入字典串s
    void insert(string s){
        ll p=0;
        for(auto c:s){
            c = trans(c);
            if(nxt[p][c]==0) nxt[p][c]=++curn;
            p=nxt[p][c];
            cnt[p]++; //统计前缀出现次数
        }
        // cnt[p]++; //统计单词出现次数
    }
    // 查询字典串s出现次数
    ll count(string s){
        ll p=0;
        for(auto c:s){
            c = trans(c);
            if(nxt[p][c]==0) return 0;
            p=nxt[p][c];
        }
        return cnt[p];
    }
} trie;

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