#include <set>
#include <queue>
#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;
#define N 1000 + 5
#define M 10000000 + 5

// #define DEBUG

int Case, n, m, sz, G[N][N], Pre[2][N], H[N][N], Fa[N], Q[N], Pos[N], Stack[N], Ring[N];
int Nxt[N][N], Dp[2][N][N], Du[2][N][N];
bool Up[2][N][N], Flag[N][N];

void Read()
{
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
		G[i][0] = 0;
	for (int i = 1, u, v; i <= n; i++)
	{
		scanf("%d%d", &u, &v);
		G[u][++G[u][0]] = v;
		G[v][++G[v][0]] = u;
	}
	scanf("%d", &m);
	for (int i = 1; i <= m; i++)
		H[i][0] = 0;
	for (int i = 1, u, v; i < m; i++)
	{
		scanf("%d%d", &u, &v);
		H[u][++H[u][0]] = v;
		H[v][++H[v][0]] = u;
	}
}

bool dfs(int dep, int x, int pre)
{
	if (Pos[x] != 0)
	{
		sz = 0;
		for (int i = Pos[x]; i < dep; i++)
			Ring[++sz] = Stack[i];
		return true;
	}
	Pos[x] = dep;
	Stack[dep] = x;
	for (int i = 1; i <= G[x][0]; i++)
		if (G[x][i] != pre && dfs(dep + 1, G[x][i], x))
			return true;
	Stack[dep] = Pos[x] = 0;
	return false;
}

void dfs(int x, int pre)
{
	Q[++Q[0]] = x;
	Fa[x] = pre;
	for (int i = 1; i <= H[x][0]; i++)
		if (H[x][i] != pre)
			dfs(H[x][i], x);
}

void Prepare()
{
	for (int i = 1; i <= n; i++)
		Pos[i] = 0;
	dfs(1, 1, 0);
	Q[0] = 0;
	dfs(1, 0);
#if defined(DEBUG)
	fprintf(stderr, "Ring : ");
	for (int i = 1; i <= sz; i ++)
		fprintf(stderr, "%d%c", Ring[i], i == sz ? '\n' : ' ');
	fprintf(stderr, "Q : ");
	for (int i = 1; i <= m; i ++)
		fprintf(stderr, "%d%c", Q[i], i == m ? '\n' : ' ');
#endif
}

struct Edge
{
	int next, node, flow;
}h[M];
int S, T, tot, Head[(N) << 1], Que[(N) << 1], Dfn[(N) << 1];

inline void addedge(int u, int v, int fl)
{
	h[++tot].next = Head[u], Head[u] = tot;
	h[tot].node = v, h[tot].flow = fl;
	h[++tot].next = Head[v], Head[v] = tot;
	h[tot].node = u, h[tot].flow = 0;
}

bool BFS(int st, int ed, bool op = true)
{
	for (int i = S; i <= T; i++)
		Dfn[i] = 0;
	int l = 1, r = 0;
	Que[++r] = st, Dfn[st] = 1;
	while (l <= r)
	{
		int x = Que[l++];
		for (int i = Head[x]; i; i = h[i].next)
		{
			int d = h[i].node, p = h[i].flow;
			if ((p != 0) == op && !Dfn[d])
			{
				Dfn[d] = Dfn[x] + 1;
				Que[++r] = d;
				if (d == ed)
					return true;
			}
		}
	}
	return false;
}

int Dinic(int x, int inflow)
{
	if (x == T || !inflow)
		return inflow;
	int ret = inflow;
	for (int i = Head[x]; i; i = h[i].next)
	{
		int d = h[i].node, p = h[i].flow;
		if (p && Dfn[d] == Dfn[x] + 1)
		{
			int flow = Dinic(d, min(ret, p));
			h[i].flow -= flow;
			h[i ^ 1].flow += flow;
			ret -= flow;
			if (!ret)
				break;
		}
	}
	if (ret == inflow)
		Dfn[x] = -1;
	return inflow - ret;
}

void MakeGraph(int rcnt, int ccnt)
{
	S = 0;
	T = rcnt + ccnt + 1;
	tot = 1;
	for (int i = S; i <= T; i++)
		Head[i] = 0;
	for (int i = 1; i <= rcnt; i++)
		addedge(S, i, 1);
	for (int j = 1; j <= ccnt; j++)
		addedge(rcnt + j, T, 1);
	for (int i = 1; i <= rcnt; i++)
		for (int j = 1; j <= ccnt; j++)
			if (Flag[i][j])
				addedge(i, rcnt + j, 1);
}

int Flow(int rcnt, int ccnt, vector<int> *match = nullptr)
{
	MakeGraph(rcnt, ccnt);
	int flow = 0;
	while (BFS(S, T))
		flow += Dinic(S, 0x3f3f3f3f);
	if (match != nullptr)
	{
		*match = vector<int>(rcnt + 1, 0);
		for (int x = 1; x <= rcnt; x ++)
			for (int i = Head[x]; i; i = h[i].next)
				if (rcnt < h[i].node && h[i].node < T && !h[i].flow)
					match->at(x) = h[i].node - rcnt;
	}
	return flow;
}

bool Vis[N];
void dfs(int x, int rcnt, int ccnt, const vector<int> &CVal, const vector<int>& match, int &ret)
{
	if (Vis[x])
		return ;
	if (!match[x])
	{
		ret = min(ret, 0);
		return ;
	}
	if (CVal[match[x]] != -1)
		ret = min(ret, CVal[match[x]] + 1);
	Vis[x] = true;
	for (int i = Head[rcnt + match[x]]; i; i = h[i].next)
		if (S < h[i].node && h[i].node <= rcnt && !h[i].flow)
			dfs(h[i].node, rcnt, ccnt, CVal, match, ret);
}

int Match(int rcnt, int ccnt, const vector<int> &CVal)
{
	vector<int> match;
	if (Flow(rcnt, ccnt, &match) != ccnt)
		return -1;
	for (int i = 1; i <= rcnt; i ++)
		Vis[i] = false;
	int ret = 0x3f3f3f3f;
	dfs(rcnt, rcnt, ccnt, CVal, match, ret);
	return ret;
}

vector<bool> MultiMatch(int rcnt, int ccnt)
{
	vector<bool> ret(rcnt + 1, false);
	if (Flow(rcnt, ccnt) == ccnt)
	{
		BFS(S, T);
		for (int i = 1; i <= rcnt; i ++)
			ret[i] = (Dfn[i] != 0);
	}
	return ret;
}

vector<bool> MatchMulti(int rcnt, int ccnt, bool debug = false)
{
	vector<bool> ret(ccnt + 1, false);
	int flow = Flow(rcnt, ccnt);
	if (flow == ccnt)
	{
		for (int i = 1; i <= ccnt; i ++)
			ret[i] = true;
	}
	else if (flow == ccnt - 1)
	{
		BFS(T, S, false);
		for (int i = 1; i <= ccnt; i ++)
			ret[i] = Dfn[rcnt + i] != 0;
	}
	if (debug)
	{
		fprintf(stderr, "flow = %d, Flag : \n", flow);
		for (int i = 1; i <= rcnt; i ++)
			for (int j = 1; j <= ccnt; j ++)
				fprintf(stderr, "%d%c", Flag[i][j], j == ccnt ? '\n' : ' ');
		fprintf(stderr, "Ret : ");
		for (int j = 1; j <= ccnt; j ++)
			fprintf(stderr, "%d%c", ret[j] ? 1 : 0, j == ccnt ? '\n' : ' ');
	}
	return ret;
}

bool Reach[N];
bool dfs(int x, int rcnt, int ccnt, int val, vector<int>& ret)
{
	int _x = x - rcnt;
	if (Vis[_x])
		return Reach[_x];
	Vis[_x] = true;
	Reach[_x] = false;
	for (int i = Head[x]; i; i = h[i].next)
	{
		int d = h[i].node, p = h[i].flow;
		if (1 <= d && d <= rcnt && p != 0)
		{
			if (d == rcnt)
				return Reach[_x] = true;
			for (int j = Head[d]; j; j = h[j].next)
			{
				int _d = h[j].node, _p = h[j].flow;
				if (rcnt < _d && _d <= rcnt + ccnt && _p != 0 && dfs(_d, rcnt, ccnt, val, ret))
					return Reach[_x] = true;
			}
		}
	}
	return Reach[_x];
}

int Dis[(N) << 1];
struct Cmp
{
	bool operator()(const pair<int, int>& lhs, const pair<int, int>& rhs)
	{
		return lhs.second > rhs.second;
	}
};
void Dijkstra(int st, bool op, int rcnt, int ccnt, const vector<int>& CVal, int base_val)
{
	priority_queue<pair<int, int>, vector<pair<int, int>>, Cmp> Que;
	for (int i = S; i <= T; i ++)
		Dis[i] = -1;
	Dis[st] = 0;
	Que.push(make_pair(st, 0));
	while (!Que.empty())
	{
		pair<int, int> p = Que.top();
		Que.pop();
		if (Dis[p.first] != p.second)
			continue ;
		int x = p.first, dis = p.second;
		for (int i = Head[x]; i; i = h[i].next)
		{
			int d = h[i].node, p = h[i].flow;
			int w = (d == rcnt && rcnt < x && x <= rcnt + ccnt) ? max(0, CVal[x - rcnt] - base_val) : 0;
			if ((p != 0) == op && (Dis[d] == -1 || Dis[d] > dis + w))
			{
				Dis[d] = dis + w;
				Que.push(make_pair(d, dis + w));
			}
		}
	}
}

vector<int> MatchMulti(int rcnt, int ccnt, const vector<int>& CVal, bool debug = false)
{
	vector<int> ret(ccnt + 1, -1);
	/* // Brute
	set<int> val_set = {-1};
	for (int i = 1; i <= ccnt; i ++)
		val_set.insert(CVal[i]);
	for (int val : val_set)
	{
		for (int i = 1; i <= ccnt; i ++)
			Flag[rcnt][i] = CVal[i] != -1 && CVal[i] <= val;
		vector<bool> bool_ret = MatchMulti(rcnt, ccnt, debug);
		for (int i = 1; i <= ccnt; i ++)
			if (bool_ret[i])
				ret[i] = ret[i] == -1 ? val + 1 : min(ret[i], val + 1);
	}
	*/
	int flow = Flow(rcnt, ccnt);
	BFS(S, T);
	vector<int> ord(ccnt + 1);
	for (int i = 1; i <= ccnt; i ++)
		ord[i] = i, Vis[i] = Reach[i] = false;
	sort(ord.begin() + 1, ord.end(), [&](int u, int v) {
		return CVal[u] < CVal[v];
	});
	if (flow == ccnt)
	{
		if (Dfn[rcnt] != 0)
		{
			for (int i = 1; i <= ccnt; i ++)
				ret[i] = 0;
		}
		else
		{
			for (int i = 1; i <= ccnt; i ++)
				if (CVal[ord[i]] != -1 && dfs(rcnt + ord[i], rcnt, ccnt, CVal[ord[i]], ret))
				{
					ret[ord[i]] = 0;
					for (int j = 1; j <= ccnt; j ++)
						if (ord[i] != j)
							ret[j] = ret[j] == -1 ? CVal[ord[i]] : min(ret[j], CVal[ord[i]]);
				}
		}
	}
	else if (flow == ccnt - 1)
	{
		int dfn_rcnt = Dfn[rcnt];
		BFS(T, S, false);
		if (dfn_rcnt != 0)
		{
			for (int i = 1; i <= ccnt; i ++)
				if (Dfn[rcnt + i] != 0)
					ret[i] = 0;
		}
		else
		{
			for (int i = 1; i <= ccnt; i ++)
				Flag[rcnt][i] = false;
			Flow(rcnt, ccnt);
			for (int i = 1; i <= ccnt; i ++)
				if (CVal[i] != -1)
					addedge(rcnt, rcnt + i, 1);
			int l = 1, r = ccnt;
			while (l < r)
			{
				int mid = (l + r) >> 1;
				for (int i = Head[rcnt]; i; i = h[i].next)
					if (rcnt < h[i].node && h[i].node <= rcnt + ccnt && CVal[h[i].node - rcnt] > CVal[ord[mid]])
						h[i].flow = 0;
				if (BFS(S, T))
					r = mid;
				else l = mid + 1;
				for (int i = Head[rcnt]; i; i = h[i].next)
					if (rcnt < h[i].node && h[i].node <= rcnt + ccnt && CVal[h[i].node - rcnt] > CVal[ord[mid]])
						h[i].flow = 1;
			}
			int base_val = CVal[ord[l]];
			if (debug)
			 	fprintf(stderr, "base_val = %d, l = %d\n", base_val, l);
			for (int i = 1; i <= ccnt; i ++)
				Flag[rcnt][i] = CVal[i] != -1 && CVal[i] <= base_val;
			Flow(rcnt, ccnt);
			for (int i = 1; i <= ccnt; i ++)
				if (CVal[ord[i]] > base_val)
					addedge(rcnt, rcnt + ord[i], 1);
			Dijkstra(T, false, rcnt, ccnt, CVal, base_val);
			for (int i = 1; i <= ccnt; i ++)
				ret[i] = Dis[rcnt + i] == -1 ? -1 : Dis[rcnt + i] + base_val + 1;
		}
	}
	if (debug)
	{
		for (int i = 1; i <= ccnt; i ++)
			Flag[rcnt][i] = CVal[i] != -1;
		fprintf(stderr, "flow = %d, rcnt = %d, ccnt = %d, Flag : \n", flow, rcnt, ccnt);
		for (int i = 1; i <= rcnt; i ++)
			for (int j = 1; j <= ccnt; j ++)
				fprintf(stderr, "%d%c", Flag[i][j], j == ccnt ? '\n' : ' ');
		fprintf(stderr, "CVal : ");
		for (int j = 1; j <= ccnt; j ++)
			fprintf(stderr, "%d%c", CVal[j], j == ccnt ? '\n' : ' ');
		fprintf(stderr, "Ret : ");
		for (int j = 1; j <= ccnt; j ++)
			fprintf(stderr, "%d%c", ret[j], j == ccnt ? '\n' : ' ');
	}
	return ret;
}

void dfsDp(int t, int x, int pre)
{
	static int Sub[N];
	int cnt = 0;
	Pre[t][x] = pre;
	for (int i = 1; i <= G[x][0]; i++)
		if (G[x][i] != pre && minmax(x, G[x][i]) != minmax(Ring[1], Ring[sz]))
		{
			Nxt[x][++cnt] = G[x][i];
			if (Pos[x] != 0 && Pos[G[x][i]] != 0 && Pos[x] == Pos[G[x][i]] - 1)
				swap(Nxt[x][1], Nxt[x][cnt]);
			dfsDp(t, G[x][i], x);
		}
	reverse(Nxt[x] + 1, Nxt[x] + cnt + 1);
	for (int i = m; i; i--)
	{
		int y = Q[i], scnt = 0;
		Dp[t][x][y] = -1;
		for (int j = 1; j <= H[y][0]; j++)
			if (H[y][j] != Fa[y])
				Sub[++scnt] = H[y][j];
		if (cnt < scnt)
			continue;
		for (int u = 1; u <= cnt; u++)
			for (int v = 1; v <= scnt; v++)
				Flag[u][v] = Dp[t][Nxt[x][u]][Sub[v]] != -1;
		bool in_chain = cnt > 0 && Pos[x] != 0 && Pos[Nxt[x][cnt]] != 0 && Pos[x] == Pos[Nxt[x][cnt]] - 1;
		if (in_chain)
		{
			int chain_child = Nxt[x][cnt];
			vector<int> CVal(scnt + 1, 0);
			for (int v = 1; v <= scnt; v++)
				CVal[v] = Dp[t][chain_child][Sub[v]];
			Dp[t][x][y] = Match(cnt, scnt, CVal);
		}
		else Dp[t][x][y] = (Flow(cnt, scnt) == scnt) ? 0 : -1;
	}
}

void dfsUp(int t, int x, int pre)
{
	static int Sub[N];
	int cnt = 0;
	for (int i = 1; i <= G[x][0]; i++)
		if (G[x][i] != pre && minmax(x, G[x][i]) != minmax(Ring[1], Ring[sz]))
			Nxt[x][++cnt] = G[x][i];
	for (int j = m; j; j--)
	{
		int y = Q[j], scnt = 0;
		for (int j = 1; j <= H[y][0]; j++)
			if (H[y][j] != Fa[y])
				Sub[++scnt] = H[y][j];
		for (int u = 1; u <= cnt + 1; u++)
			for (int v = 1; v <= scnt; v++)
				Flag[u][v] = u <= cnt ? (Dp[t][Nxt[x][u]][Sub[v]] != -1) : Up[t][x][Sub[v]];
		vector<bool> ret = MultiMatch(cnt + 1, scnt);
		for (int u = 1; u <= cnt; u ++)
			Up[t][Nxt[x][u]][y] = ret[u];
	}
	for (int i = 1; i <= cnt; i++)
		dfsUp(t, Nxt[x][i], x);
}

void dfsDu(int t, int x, int pre)
{
	static int Sub[N];
	int cnt = 0;
	for (int i = 1; i <= G[x][0]; i++)
		if (G[x][i] != pre && minmax(x, G[x][i]) != minmax(Ring[1], Ring[sz]))
		{
			Nxt[x][++cnt] = G[x][i];
			if (Pos[x] != 0 && Pos[G[x][i]] != 0 && Pos[x] == Pos[G[x][i]] - 1)
				swap(Nxt[x][1], Nxt[x][cnt]);
			dfsDu(t, G[x][i], x);
		}
	reverse(Nxt[x] + 1, Nxt[x] + cnt + 1);
	Du[t][x][Q[1]] = 0;
	for (int i = 1; i <= m; i++)
	{
		int y = Q[i], scnt = 0;
		for (int j = 1; j <= H[y][0]; j++)
			Sub[++scnt] = H[y][j];
#if defined(DEBUG)
		fprintf(stderr, "Du[%d][%d][%d] = %d : cnt = %d, scnt = %d, Fa[%d] = %d, H[%d][0] = %d\n", t, x, y, Du[t][x][y], cnt, scnt, y, Fa[y], y, H[y][0]);
#endif
		for (int u = 1; u <= cnt; u++)
			for (int v = 1; v <= scnt; v++)
				Flag[u][v] = Sub[v] == Fa[y] ? (Du[t][Nxt[x][u]][y] != -1) : (Dp[t][Nxt[x][u]][Sub[v]] != -1);		
		bool in_chain = cnt > 0 && Pos[x] != 0 && Pos[Nxt[x][cnt]] != 0 && Pos[x] == Pos[Nxt[x][cnt]] - 1;
		if (in_chain)
		{
			int chain_child = Nxt[x][cnt];
			vector<int> CVal(scnt + 1, 0);
			for (int v = 1; v <= scnt; v++)
				CVal[v] = Sub[v] == Fa[y] ? Du[t][chain_child][y] : Dp[t][chain_child][Sub[v]];
			vector<int> ret = MatchMulti(cnt, scnt, CVal);
			for (int v = 1; v <= scnt; v++)
				if (Sub[v] != Fa[y])
					Du[t][x][Sub[v]] = ret[v];
		}
		else
		{
			vector<bool> ret = MatchMulti(cnt, scnt);
			for (int v = 1; v <= scnt; v++)
				if (Sub[v] != Fa[y])
					Du[t][x][Sub[v]] = ret[v] ? 0 : -1;
		}
	}
}

void Calc()
{
	for (int t = 0; t < 2; t++)
	{
		for (int i = 1; i <= n; i++)
			Pos[i] = 0;
		for (int i = 1; i <= sz; i++)
			Pos[Ring[i]] = i;

		dfsDp(t, Ring[1], 0);
		if (t == 0)
		{
			for (int j = 1; j <= m; j++)
				Up[t][Ring[1]][j] = false;
			dfsUp(t, Ring[1], 0);
		}
		dfsDu(t, Ring[1], 0);
		
#if defined(DEBUG)
		fprintf(stderr, "Dp[%d](root = %d) : \n", t, Ring[1]);
		for (int i = 1; i <= n; i ++)
			for (int j = 1; j <= m; j ++)
				fprintf(stderr, "%d%c", Dp[t][i][j], j == m ? '\n' : ' ');
		if (t == 0)
		{
			fprintf(stderr, "Up[%d](root = %d) : \n", t, Ring[1]);
			for (int i = 1; i <= n; i ++)
				for (int j = 1; j <= m; j ++)
					fprintf(stderr, "%d%c", Up[t][i][j], j == m ? '\n' : ' ');
		}
		fprintf(stderr, "Du[%d](root = %d) : \n", t, Ring[1]);
		for (int i = 1; i <= n; i ++)
			for (int j = 1; j <= m; j ++)
				fprintf(stderr, "%d%c", Du[t][i][j], j == m ? '\n' : ' ');
#endif

		reverse(Ring + 1, Ring + sz + 1);
	}
}

bool GetAns()
{
	// Dp[0] && Up[0]
	for (int x = 1; x <= n; x ++)
	{
		if (Dp[0][x][1] != -1)
			return true;
		int cnt = 0;
		for (int i = 1; i <= G[x][0]; i++)
			if (minmax(x, G[x][i]) != minmax(Ring[1], Ring[sz]))
			{
				cnt++;
				for (int j = 1; j <= H[1][0]; j++)
					Flag[cnt][j] = G[x][i] == Pre[0][x] ? Up[0][x][H[1][j]] : (Dp[0][G[x][i]][H[1][j]] != -1);
			}
		if (cnt >= H[1][0] && Flow(cnt, H[1][0]) == H[1][0])
			return true;
	}
	// Dp && Du
	for (int y = 2; y <= m; y ++)
	{
		if (Dp[0][Ring[1]][y] != -1 && Du[1][Ring[sz]][y] != -1 && Dp[0][Ring[1]][y] + Du[1][Ring[sz]][y] + 2 <= sz)
			return true;
		if (Du[0][Ring[1]][y] != -1 && Dp[1][Ring[sz]][y] != -1 && Du[0][Ring[1]][y] + Dp[1][Ring[sz]][y] + 2 <= sz)
			return true;
	}
	return false;
}

int main()
{
#if defined(DEBUG)
	freopen("input_11.txt", "r", stdin);
#endif
	for (scanf("%d", &Case); Case; Case--)
	{
		Read();
		Prepare();
		Calc();
		puts(GetAns() ? "Yes" : "No");
	}
	return 0;
}

