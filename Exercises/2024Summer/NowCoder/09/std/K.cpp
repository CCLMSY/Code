#include <bits/stdc++.h>
#define int long long
using namespace std;
int a[1000005];
vector<int> tag;
signed main(){
	int n,k; cin>>n>>k;
	for(int i=1;i<=n;i++) cin>>a[i];
	if(k==1){
		int maxv=0; for(int i=1;i<=n;i++) maxv=max(maxv,a[i]);
		cout<<maxv;
		return 0;
	}
	for(int i=1;i<=n;i++){
		while(a[i]){
			tag.push_back(a[i]);
			a[i]/=k;
		}
	}
	sort(tag.begin(),tag.end());
	int minv=tag.size();
	for(int i=0;i<tag.size();i++){
		minv=min(minv,(int)tag.size()-i-1+tag[i]);
	}
	cout<<minv;
	return 0;
}
