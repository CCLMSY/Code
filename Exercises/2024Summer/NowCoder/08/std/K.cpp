#include<bits/stdc++.h>
using namespace std;
inline int read(){
   int s=0,w=1;
   char ch=getchar();
   while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
   while(ch>='0'&&ch<='9') s=s*10+ch-'0',ch=getchar();
   return s*w;
}
char s[1000003];
signed main()
{
	for(int T=read();T--;)
	{
		scanf("%s",s+1);
		int n=strlen(s+1);
		while(n>=3)
		{
			if(s[n]!='a'||s[n-1]!='v'||s[n-2]!='a') break;
			n-=3;
			if(n>=2&&s[n]=='v'&&s[n-1]=='a') n-=2;
		}
		if(n) puts("No");
		else puts("Yes");
	}
	return 0;
}