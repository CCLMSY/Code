#include<bits/stdc++.h>
using namespace std;
struct DSU {
    vector<int> f, sz;
    DSU(int n)
        : f(n), sz(n, 1) {
        //  构建函数
        iota(f.begin(), f.end(), 0);
    }
    int find(int x) {
        // 寻找父亲，路径压缩
        return f[x] == x ? x : f[x] = find(f[x]);
    }
    bool merge(int a, int b) {
        // 合并两个节点
        int fa = find(a), fb = find(b);
        if (fa == fb)
            return false;
        if (sz[fb] > sz[fa])
            swap(fa, fb);
        f[fb] = fa;
        sz[fa] += sz[fb];
        return true;
    }
    bool same(int a, int b) {
        // 判断两个点是否是一个集合
        return find(a) == find(b);
    }
};
 
int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	int n,m,q;
	cin >> n >> m >> q;
	DSU ds(n + 1);
	vector<int> len(n + 1);
	vector<array<int,3>> s(m + 1);
	for(int i = 1;i <= m; i ++){
		cin >> s[i][0] >> s[i][1] >> s[i][2];
		if(s[i][0] > s[i][1])swap(s[i][0],s[i][1]);
		len[s[i][0]] ++;
		len[s[i][1]] ++;
	}
	vector<vector<pair<int,int>>> node(n + 1);
	for(int i = 1;i <= m; i++){
		int a = s[i][0],b = s[i][1];
		if(len[a] > len[b])swap(a,b);
		node[a].emplace_back(b,s[i][2]);
	}
	vector<int> ok(n + 1);
	while(q--){
		int k;
		cin >> k;
		vector<int> v(k);
		for(int i = 0;i < k; i ++){
			cin >> v[i];
			assert(ok[v[i]] == 0);
			ok[v[i]] = 1;
			ds.f[v[i]] = v[i];
			ds.sz[v[i]] = 1;
		}
		vector<array<int,3>> S;
		for(int x:v){
			for(auto &[y,w]:node[x]){
			    if(ok[y] == 1)
				    S.push_back({w,x,y});
			}
		}
		sort(S.begin(),S.end());
		long long ans = 0,cnt = 1;
		for(auto [x,a,b]:S){
			if(ds.merge(a,b)){
				ans += x;
				cnt ++;
			}
			if(cnt == k)continue;
		}
		if(cnt == k){
			cout << ans <<"\n";
		}else cout <<"-1\n";
		for(int i = 0;i < k; i ++){
			assert(ok[v[i]] == 1);
			ok[v[i]] = 0;
		}
	}
	
}
