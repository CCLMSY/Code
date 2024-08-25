#include<bits/stdc++.h>
using namespace std;
typedef long ll;
//字符转换为数字，以全62字符为例，根据题意修改
inline int trans(char c){ 
    if(c>='a'&&c<='z') return c-'a';
    else if(c>='A'&&c<='Z') return c-'A'+26;
    return c-'0'+52;
}
const ll N = 2e5+5; //（本题单个数据）**字典**字符串最大总长度
const ll M = 26; //字符集大小
// AC自动机
// 解决的问题：统计多个模式串在主串中出现的次数
// M(26)*N(2e5)->Luogu150ms/60MB
struct ACauto{
    struct Node{
        ll  nxt[M], //经过字符边到达的下一状态
            fail, //失配指针
            flag, //flag
            ans, //临时答案
            rev, //反向flag
            indeg, //入度
            cnt; //出现的次数
        Node():nxt{0},fail(0),flag(0),ans(0),rev(0),indeg(0),cnt(0){}
        void clear(){
            memset(nxt,0,sizeof(nxt));
            fail=flag=ans=rev=indeg=cnt=0;
        }
    };
    vector<Node> trie; //trie树
    ll curn,cnts; //curn是当前节点数，cnts是模式串个数
    ACauto():trie(N),curn(0),cnts(0){}
    // 重置AC自动机
    void clear(){
        for(ll i=0;i<=curn;i++) trie[i].clear();
        for(ll i=1;i<N;i++) trie[i].cnt=0;
        curn=1; cnts=0;
    }
    // 加入模式串s，编号为num
    void insert(string s,ll num){
        ll u=1,len=s.length();
        for(ll i=0;i<len;i++){
            ll v=trans(s[i]);
            if(!trie[u].nxt[v]) trie[u].nxt[v]=++curn;
            u=trie[u].nxt[v];
        }
        if(!trie[u].flag) trie[u].flag=num;
        trie[num].rev=trie[u].flag;
        cnts++;
    }
    // 构造失配指针
    void getfail(){
        for(ll i=0;i<M;i++) trie[0].nxt[i]=1;
        queue<ll> q; q.push(1);
        trie[1].fail=0;
        while(!q.empty()){
            ll u=q.front();
            q.pop();
            ll Fail=trie[u].fail;
            for(ll i=0;i<M;i++){
                ll v=trie[u].nxt[i];
                if(!v){
                    trie[u].nxt[i]=trie[Fail].nxt[i];
                    continue;
                }
                trie[v].fail=trie[Fail].nxt[i];
                trie[trie[Fail].nxt[i]].indeg++;
                q.push(v);
            }
        }
    }
    // 拓扑排序优化建图
    void topu(){
        queue<ll> q;
        for(ll i=1;i<=curn;i++)
            if(!trie[i].indeg) q.push(i);
        while(!q.empty()){
            ll fr=q.front();
            q.pop();
            trie[trie[fr].flag].cnt=trie[fr].ans;
            ll u=trie[fr].fail;
            trie[u].ans+=trie[fr].ans;
            trie[u].indeg--;
            if(!trie[u].indeg) q.push(u);
        }
    }
    // 在主串s中匹配模式串
    void solve(string s){
        getfail();
        ll u=1,len=s.length();
        for(ll i=0;i<len;i++){
            ll v=trans(s[i]);
            u=trie[u].nxt[v];
            trie[u].ans++;
        }
        topu();
    }
    // O(1)查询编号为idx的模式串出现的次数
    ll query(ll idx){ return trie[trie[idx].rev].cnt; }
    // 查询出现过的模式串个数
    ll count(){
        ll ret=0;
        for(ll i=1;i<=curn;i++) 
            if(query(i)) ret++;
        return ret;
    }
}ac;
void solve() 
{
    ll n; cin >> n;
    ac.clear();
    vector<string> s(n+1);
    string ts;
    for(ll i=1;i<=n;i++){
        cin >> ts;
        ac.insert(ts,i);
        s[i]=ts;
    }
    cin >> ts;
    ac.solve(ts);
    // Luogu P5357
    for(ll i=1;i<=n;i++) cout << ac.query(i) << endl;
    // Luogu P3808
    // cout << ac.count() << endl;
}
/*----------Code Area----------*/

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    
    ll T=1; // cin >> T;
    while(T--) solve();

    return 0;
}