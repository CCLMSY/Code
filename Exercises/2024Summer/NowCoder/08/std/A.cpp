#include<bits/stdc++.h>
using namespace std;
inline int read(){
   int s=0,w=1;
   char ch=getchar();
   while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
   while(ch>='0'&&ch<='9') s=s*10+ch-'0',ch=getchar();
   return s*w;
}
const int N=1e5;
int a[100003];
signed main()
{
	for(int T=read();T--;)
	{
		int Q=read(),ans=-Q;
		memset(a,0,sizeof(a));
		while(Q--) a[read()]=1;
		for(int i=1; i<=N; ++i)
			for(int j=2; i*j<=N; ++j)
				a[i]+=a[i*j];
		for(int i=1; i<=N; ++i) if(a[i])
		{
			bool ok=1;
			for(int j=2; i*j<=N; ++j)
				ok&=(a[i*j]!=a[i]);
			ans+=ok;
		}
		if(ans&1) puts("dXqwq");
		else puts("Haitang");
	}
	return 0;
}