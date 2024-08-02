#include <bits/stdc++.h>
#define int long long
#define mod 998244353
using namespace std;
int a[2005];
int dp[2005][2005];
int C[2005][2005],A[2005][2005],p[2005];
int ksm(int x,int y)
{
	int rtn=1;
	while(y)
	{
		if(y&1) rtn=rtn*x%mod;
		x=x*x%mod,y>>=1;
	}
	return rtn;
}
int inv(int x)
{
	return ksm(x,mod-2);
}
signed main()
{
	cout << inv(2) << '\n';
	ios::sync_with_stdio(false);
	cin.tie(0);
	int n,m,t;
	cin >> n >> m;
	t=n/m;
	for(int i=0;i<=2000;i++)
	{
		A[i][0]=C[i][i]=C[i][0]=1;
		for(int j=1;j<i;j++)
			C[i][j]=(C[i-1][j]+C[i-1][j-1])%mod;
		for(int j=1;j<=i;j++) A[i][j]=(i-j+1)*A[i][j-1]%mod;
	}
	for(int i=0;i<=n;i++)
		cin >> a[i];
	dp[0][0]=1;
	for(int i=1;i<=m;i++)
	{
		for(int j=0;j<=n;j++)
		{
			if(!dp[i-1][j]) continue;
			for(int k=0;k<=n/m;k++)
				dp[i][j+k]=(dp[i][j+k]+dp[i-1][j]*A[n/m][k]%mod*C[n/m][k])%mod;
		}
	}
	for(int i=n;i>=0;i--)
	{
		dp[m][i]=dp[m][i]*A[n-i][n-i]%mod;
		for(int j=i+1;j<=n;j++)
			dp[m][i]=(dp[m][i]-dp[m][j]*C[j][i]%mod+mod)%mod;
	}
	for(int i=0;i<=n;i++) p[i]=dp[m][i]%mod*inv(ksm(A[t][t],m))%mod*inv(C[n][i]*ksm(m-1,n-i)%mod)%mod;
	int ans=0,tot=0;
	for(int i=0;i<=n;i++) tot=(tot+a[i]*p[i])%mod,ans=(ans+a[i]*p[i]%mod*i)%mod;
	cout << ans*inv(tot)%mod;
	return 0;
}