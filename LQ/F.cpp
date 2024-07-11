#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;

#define FORLL(i,l,r) for(ll i=l;i<=r;i++)
#define ALL(A) (A).begin(),(A).end()
#define endl '\n'

const ll INF = 0x3fffffffffffffff;
const ll MAXN=1e3;
const ll MAXM=1e5;

void printvec(vector<ll>v){
	ll n=v.size();
	FORLL(i,0,n-1) cout << v[i] << " \n"[i==n-1];
} 

vector<ll> c; //c[i]:i的组号 
map<ll,ll> sz; //sz[i]:组i的成员数 
map<ll,vector<ll>> mem; //mem[i]:组i的成员
map<ll,set<ll>> G; // G[i]:第i组连接到的组 
set<ll>::iterator it;

int main(){
	ll n,m;
	cin >> n >> m;
	c.resize(n+1);
	ll mxci=0; 
	FORLL(i,1,n){
		cin >> c[i];
		sz[c[i]]++;
		mem[c[i]].push_back(i);
		mxci=max(mxci,c[i]);
	} 
	ll u,v;
	FORLL(i,1,n-1){
		cin >> u >> v;
		u=c[u];
		v=c[v];
		G[u].insert(v);
		G[v].insert(u);
	} 
	deque<ll> dq;
	vector<ll> vis(mxci+1,0);
	while(m--){
		cin >> u >> v;
		u=c[u];
		v=c[v];
		if(u==v){
			cout << 0 <<endl;
			continue;
		}
		deque<ll> dq,dq1;
		vector<int> vis(n+1,0);
		dq.push_back(u);
		ll cur=0; //当前距离 
		int fl=0;
		while(!dq.empty()){
			cur++;
			ll dn=dq.size(),t,Gti;
			while(dn--){
				t=dq.front();
				vis[t]=1;
				for(it=G[t].begin();it!=G[t].end();it++){
					Gti=*it;
					if(Gti==v) fl=1;
					if(fl) break;
					if(!vis[Gti]) dq1.push_back(Gti);
				}
//				ll gn=G[t].size();
//				FORLL(i,0,gn-1){
//					if(G[t][i]==v) fl=1;
//					if(fl) break;
//					if(!vis[G[t][i]]) dq1.push_back(G[t][i]);
//				}
				if(fl) break;
				dq.pop_front();
			}
			if(fl) break;
			dq=dq1;
			dq1.clear();
		}
		cout << cur << endl; 
	}
	return 0;
} 
















