#include<bits/stdc++.h>
using namespace std;
int main()
{
	ios_base::sync_with_stdio(false);
	int n,m;
	cin>>n>>m;
	vector<vector<int>> G(n+5);
	vector<pair<int,int>> lun,qie;
	for(int i=1;i<=m;i++)
	{
		int u,v;
		string w;
		cin>>u>>v>>w;
		if(w=="Lun")
		{
			G[u].push_back(v);
			G[v].push_back(u);
			lun.emplace_back(u,v);
		}
		else
		{
			qie.emplace_back(u,v);
		}
	}
	vector<int> dfn(n+5),low(n+5),ins(n+5),bel(n+5);
	int bccnt=0,ind=0;
	stack<int> s;
	function<void(int,int)> dfs=[&](int u,int pa)
	{
		dfn[u]=low[u]=++ind;
		s.push(u);
		ins[u]=1;
		for(auto v:G[u])
		{
			if(v==pa)continue;
			if(not ins[v])
			{
				dfs(v,u);
				low[u]=min(low[u],low[v]);
			}
			else if(ins[v]==1)
			{
				low[u]=min(low[u],dfn[v]);
			}
		}
		if(dfn[u]==low[u])
		{
			int vv;
			++bccnt;
			do
			{
				vv=s.top();s.pop();
				ins[vv]=2;
				bel[vv]=bccnt;
			}
			while(vv!=u);
		}
	};
	for(int i=1;i<=n;i++)
	{
		if(not ins[i])
		{
			dfs(i,0);
		}
	}
	vector<pair<int,int>> ans;
	for(auto [u,v]:lun)
	{
		if(bel[u]==bel[v])ans.emplace_back(u,v);
	}
	vector<int> pa(bccnt+5);
	function<int(int)> find=[&](int x){return pa[x]?pa[x]=find(pa[x]):x;};
	int tot=bccnt;
	for(auto [u,v]:qie)
	{
		int pu=find(bel[u]),pv=find(bel[v]);
		if(pu!=pv)
		{
			ans.emplace_back(u,v);
			pa[pv]=pu;
			tot--;
		}
	}
	if(tot==1)
	{
		cout<<"YES\n";
		cout<<ans.size()<<endl;
		for(auto [u,v]:ans)
		{
			cout<<u<<' '<<v<<"\n";
		}
	}
	else
	{
		cout<<"NO\n";
	}
	return 0;
}
/*
7 11
1 2 Qie
1 3 Qie/Lun
1 4 Lun
2 3 Lun
2 4 Lun
2 5 Qie
3 4 Qie
4 7 Qie
5 6 Lun
5 7 Lun
6 7 Lun
*/
