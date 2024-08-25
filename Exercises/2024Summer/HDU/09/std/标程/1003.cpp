#include<bits/stdc++.h>
#define ll long long
#define mdd 998244353
using namespace std;
ll t,n,m,x,ans,sum;
int main()
{
	//freopen("data.txt","r",stdin);
	//freopen("ans.txt","w",stdout);
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>t;
	for(int ii=1;ii<=t;ii++)
	{
		cin>>n;ans=0;sum=0;
		for(int i=1;i<=n;i++)
		{
			cin>>x;
			sum=sum+x;
			ans=(ans+x*x%mdd*x)%mdd;
		}
		sum=sum%mdd;
		sum=sum*sum%mdd*sum%mdd;
		ans=(sum-ans+mdd)%mdd*332748118%mdd;
		cout<<ans<<'\n';
	}
	return 0;
}