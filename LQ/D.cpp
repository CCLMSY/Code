#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;

#define FORLL(i,l,r) for(ll i=l;i<=r;i++)
#define ALL(A) (A).begin(),(A).end()
#define SORT(A) sort(ALL(A))
#define endl '\n'

vector<ll> pl;
void prepl(){
	FORLL(i,0,200) pl.push_back(i);
	FORLL(i,1,200) pl[i]+=pl[i-1];
}
vector<string> v;

ll cal(ll l,ll r,ll pos,int fl){
	if(l==r) return 0;
	ll ret=0,il=l; 
	char c=v[l][pos];
	for(ll i=l+1;i<=r;i++){
		if(pos>=v[i].length()||v[i][pos]!=c){
			ret+=pl[i-il-1];
			ret+=cal(il,i-1,pos+1,fl);
			while(i<=r&&pos>=v[i].length()) i++;
			il=i;
			if(i>r) break;
			c=v[il][pos];
		}
	}if(il<=r){
		ret+=pl[r-il];
		ret+=cal(il,r,pos+1,fl);
	}
	return ret;
}

int main(){
	prepl();
	ll n;cin >> n;
	string ts;
	FORLL(i,1,n){
		cin >> ts;
		v.push_back(ts);
	}SORT(v);
	cout << cal(0,n-1,0,0) << endl;
	return 0;
} 
















