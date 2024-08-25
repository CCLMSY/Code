#include<bits/stdc++.h>
using namespace std;
constexpr int MN=505;
char a[MN][MN];
int n,m;
int main()
{
	int x1=0,y1,x2=0,y2;
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
	{
		scanf("%s",a[i]+1);
		for(int j=1;j<=m;j++)
			if(a[i][j]=='x'&&!x1)
				x1=i,y1=j;
	}
	for(int i=n;i;i--)
		for(int j=m;j;j--)
			if(a[i][j]=='x'&&!x2)
				x2=i,y2=j;
	n=x2-x1+1,m=y2-y1+1;
	int g=__gcd(n,m);
	n/=g,m/=g;
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<m;j++)
			putchar('x');
		putchar('\n');
	}
	return 0;
}