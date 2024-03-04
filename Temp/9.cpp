#include<bits/stdc++.h>
using namespace std;
#define int long long
unsigned main()
{
	int n,st[100010]={0};
	st[1]=st[5]=st[429]=1;//卡特兰
	cin>>n;
	for(int i=1;i<=n;i++) if(i%2==0)  st[i]=1;//偶数
	for(int i=2;i<=n;i++)
	{
		int flag=1;
		for(int j=2;j<=sqrt(i)+1;j++)
			if(i%j==0)
			{
				flag=0;
				break;
			}
		if(flag)  st[i]=1;
	}//素数
	int cnt=1;
	while(cnt*(cnt+1)/2<=n)
	{
		st[cnt*(cnt+1)/2]=1;
		cnt++;
	}//三角数
	int ans=0;
	for(int i=1;i<=n;i++)
		if(!st[i])  ans++;
	cout<<ans;
}