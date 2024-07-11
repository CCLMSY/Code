#include<bits/stdc++.h>
using namespace std;

typedef long long ll;

#define FORLL(i,l,r) for(ll i=l;i<=r;i++)
#define ALL(A) (A).begin(),(A).end()

string dic="0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";

string conv(ll x,ll d){
	string ret;
	while(x){
		ret+=dic[x%d];
		x/=d;
	}
	return ret;
}

int main(){
	ll x;cin >> x;
	FORLL(i,10,36){
		cout << i << ": " << conv(x,i) << endl;
	}
	return 0;
} 
