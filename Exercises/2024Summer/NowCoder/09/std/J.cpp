#include<bits/stdc++.h>
using namespace std;
const int N=(1<<20)+10;
struct edge{
	int next,to,dis;
}e[N<<1];
int first[N],len=1;
void add(int a,int b,int c)
{
	e[++len]=edge{first[a],b,c};
	first[a]=len;
}
int n,k,vis[N],p[N],h[N];
char str[N];
vector<int> v;
void dfs1(int x)
{
	vis[x]=1,v.push_back(x);
	for(int i=first[x],y;i;i=e[i].next)
		if(!vis[y=e[i].to]&&h[y]-h[x]==e[i].dis) dfs1(y);
}
void dfs2(int x)
{
	p[x]=1;
	for(int i=first[x],y;i;i=e[i].next)
		if(!p[y=e[i].to]&&h[x]-h[y]==e[i^1].dis) dfs2(y);
}
void work(int x)
{
	v.clear();
	dfs1(x);
	for(int z:v) vis[z]=0,h[z]--;
	for(int z:v)
		for(int i=first[z],y;!p[z]&&i;i=e[i].next)
			if(p[y=e[i].to]&&h[y]-h[z]==e[i].dis) dfs2(z);
}
int main()
{
	scanf("%d",&k);
	n=1<<(k-1);
	for(int i=0;i<n;i++)
	{
		int x=(i<<1)&(n-1),y=x|1;
		add(i,x,1),add(x,i,0),add(y,i,1),add(i,y,0);
	}
	for(int i=0;i<n;i++) p[i]=(i==0);
	scanf("%s",str);
	for(int i=0;i<n;i++)
	{
		int x=(i<<1)&(n-1),y=x|1;
		if(p[x]) putchar((h[x]==h[i]+1)^str[i<<1]);
		else
		{
			putchar('0');
			if(str[i<<1]=='0') work(x);
			dfs2(x);
		}
		if(p[y]) putchar((h[y]==h[i])^str[i<<1|1]);
		else
		{
			putchar('0');
			if(str[i<<1|1]=='0') work(y);
			dfs2(y);
		}
	}
	putchar('\n');
}
