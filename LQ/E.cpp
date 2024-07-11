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

int main(){
	ll n,m,L;
	cin >> n >> m >> L ;
	string s,t;
	cin >> s >> t;
	map<char,int> scnt;
	map<char,vector<ll>> spos;
	FORLL(i,0,n-1){
		scnt[s[i]]++;
		spos[s[i]].push_back(i);
	}
	vector<ll>::iterator it;
	ll tl,tlpre,td,dp1,dp2,ans=1;
	vector<ll> tpospre,tpos;
	vector<vector<ll>> dp(m);
	dp[0].resize(scnt[t[0]],0);
	tpos=spos[t[0]]; tl=scnt[t[0]];
	FORLL(i,1,m-1){
		tlpre = tl; //前一位置的pos长度 
		tl = scnt[t[i]]; //当前位置的pos长度 
		tpospre = tpos; //前一位字符的可能出现的位置 
		tpos = spos[t[i]]; //当前字符可能出现的位置 
		
//		cout << tl << "   " ;
//		printvec(tpos);
		
		dp[i].resize(tl,0);
		FORLL(j,0,tl-1){
			it=lower_bound(ALL(tpospre),tpos[j]);
			if(it==tpospre.end()){
				dp[i][j]=dp[i-1][tlpre-1]+abs(tpospre[tlpre-1]-tpos[j]);
			}else if(it==tpospre.begin()){
				dp[i][j]=dp[i-1][0]+abs(tpospre[0]-tpos[j]);
			}else{
				td=(ll)distance(it,tpospre.begin());
				dp1=dp[i-1][td-1]+abs(tpospre[td-1]-tpos[j]);
				dp2=dp[i-1][td]+abs(tpospre[td]-tpos[j]);
				dp[i][j]=min(dp1,dp2);
			}
			if(dp[i][j]<=L) ans=max(ans,i+1);
		}
		if(ans!=i+1) break;
	}cout << ans <<endl;
	return 0;
} 
















