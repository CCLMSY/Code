#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;

#define FORLL(i,l,r) for(ll i=l;i<=r;i++)
#define ALL(A) (A).begin(),(A).end()

vector<ll> v(51);

ll cnt(){
	ll ret=0;
	FORLL(i,0,50)
		FORLL(j,i+1,50){
			if(v[i]>v[j]) ret++;
		}
	return ret;
}

int main(){
	ll c=0,t;
	ld ret=0;
	vector<ll> ori,ori1;
	FORLL(i,1,51) ori.push_back(i);
	FORLL(i,0,50){
		FORLL(j,i+1,50){
			ori1=ori;
			swap(ori1[i],ori1[j]);
			FORLL(i1,0,50){
				// FORLL(j1,i+1,50){ //我是傻逼
				FORLL(j1,i1+1,50){
					v=ori1;
					swap(v[i1],v[j1]);
					ret+=cnt();
					c++;
				}
				t=1;
			}
			t=1;
		}
	}
	cout << ret/c << endl;
	return 0;
} 
