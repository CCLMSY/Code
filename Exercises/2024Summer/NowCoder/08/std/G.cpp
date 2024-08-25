#include<bits/stdc++.h>
using namespace std;
inline int read(){
   int s=0,w=1;
   char ch=getchar();
   while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
   while(ch>='0'&&ch<='9') s=s*10+ch-'0',ch=getchar();
   return s*w;
}
const int p=998244353,M=2005;
int a[2003],b[2003],pw[2003];
int f[2003][3][4013];
signed main()
{
	int n=read(),ans=0;
	pw[0]=1;
	for(int i=1; i<=n; ++i) pw[i]=3ll*pw[i-1]%p;
	for(int i=1; i<=n; ++i) a[i]=read();
	f[0][0][M]=1;
	for(int i=1; i<=n; ++i) b[i]=b[i-1]+(a[i]==-1);
	for(int i=1; i<=n; ++i)
		for(int j=0; j<3; ++j)
			for(int l=0; l<3; ++l) if(a[i]==l||a[i]==-1)
			{
				int gap=(l+3-j)%3;
				if(gap==0)
				{
					for(int k=-i; k<=i; ++k)
					{
						if(k<=0) ans=(ans+
						1ll*f[i-1][j][M+k]*pw[b[n]-b[i]])%p;
						f[i][l][M+(1-k)]=
						(f[i][l][M+(1-k)]
						+f[i-1][j][M+k])%p;
					}
				}
				else if(gap==1)
				{
					for(int k=-i; k<=i; ++k)
					{
						if(k>=0) ans=(ans+
						1ll*f[i-1][j][M+k]*pw[b[n]-b[i]])%p;
						f[i][l][M+min(k+1,1)]=
						(f[i][l][M+min(k+1,1)]
						+f[i-1][j][M+k])%p;
					}
				}
				else
				{
					for(int k=-i; k<=i; ++k)
					{
						ans=(ans+1ll*f[i-1][j][M+k]*pw[b[n]-b[i]])%p;
						f[i][l][M+max(k+1,1)]=
						(f[i][l][M+max(k+1,1)]
						+f[i-1][j][M+k])%p;
					}
				}
			}
	printf("%d\n",ans);			
	return 0;
}