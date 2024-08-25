#include<bits/stdc++.h>
#define ll long long
using namespace std;

const int maxn = 210000;

vector< pair<int,int> >V[maxn];
int n;
int p[maxn][2],dep[maxn];
//ans= max( 0/(0+1) )
double f[maxn];
void dfs(const int x,const int fa)
{
	if(x!=1)
	{
		f[x]= max(f[x], (double)p[x][0]/(p[x][0]+p[x][1]) );
	}
	else f[x]=0;
	for(auto [y,c]:V[x]) if(y!=fa)
	{
		p[y][0]=p[x][0],p[y][1]=p[x][1];
		p[y][c]++;
		dep[y]=dep[x]+1;
		
		f[y]=f[x];
		dfs(y,x);
	}
}
double g[maxn];
void dp(const int x,const int fa)
{
	int sz=0;
	if(dep[x]&1) g[x]=1;
	else g[x]=0;
	
	for(auto [y,c]:V[x]) if(y!=fa)
	{
		dp(y,x);
		sz++;
		if(dep[x]&1) //Alice
		{
			g[x]= min(g[x],g[y]);
		}
		else //Bob
		{
			g[x]= max(g[x],g[y]);
		}
	}
	if(sz==0)
	{
		g[x]=f[x];
	}
}

int main()
{
	ios_base::sync_with_stdio(false);
	
	int Tcase; cin>>Tcase;
	while(Tcase--)
	{
		cin>>n;
		for(int i=1;i<=n;i++)
		{
			{
				vector< pair<int,int> >_;
				V[i].swap(_);
			}
		}
		for(int i=2;i<=n;i++)
		{
			int x,y,c; cin>>x>>y>>c;
			V[x].emplace_back(y,c);
			V[y].emplace_back(x,c);
		}
		dep[1]=1; p[1][0]=p[1][1]=0;
		f[1]=0; dfs(1,0);
		for(int i=1;i<=n;i++) cout << f[i] << " \n"[i==n];
		dp(1,0);
		// for(int i=1;i<=n;i++) cout << g[i] << " \n"[i==n];
		cout<<fixed<<setprecision(12)<<1-g[1]<<endl;
		
	}
	return 0;
}
