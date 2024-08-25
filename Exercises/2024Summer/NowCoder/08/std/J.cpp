#include<bits/stdc++.h>
using namespace std;
inline int read(){
   int s=0,w=1;
   char ch=getchar();
   while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
   while(ch>='0'&&ch<='9') s=s*10+ch-'0',ch=getchar();
   return s*w;
}
signed main()
{
	for(int T=read();T--;)
	{
		int n=read(),m=read();
		if(m==n-2)
		{
			puts("-1");
			continue;
		}
		int d=n-m;
		if(d==4) printf("3 1 2 4 ");
		else if(d%3==0)
		{
			for(int i=d/3; i>=1; --i)
				printf("%d %d %d ",i,d/3+i,d/3*2+i);
		}
		else if(d%3==1)
		{
			for(int i=1; i<=d/3; ++i)
				printf("%d %d %d ",d/3*2+i,d/3+i,i);
			printf("%d ",d);
		}
		else
		{
			printf("%d ",d-1);
			for(int i=d/3; i>=1; --i)
				printf("%d %d %d ",i,d/3+i,d/3*2+i);
			printf("%d ",d);
		}
		assert(n-d==m);
		for(int i=d+1; i<=n; ++i) printf("%d ",i);
		puts("");
	}
	return 0;
}