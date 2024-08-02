#include <cmath>
#include <tuple>
#include <cstdio>
#include <string>
#include <cstring>
#include <algorithm>
#include <unordered_map>
using namespace std;
typedef long long LL;
#define N 100000 + 5
#define M 262144 + 5
#define LOGN 20
#define INF 0x3f3f3f3f
#define ls(x) x << 1
#define rs(x) x << 1 | 1

int len, q, B[N];
char s[N];
pair<pair<int, int>, LL> Ret[(N) << 1];
pair<int, int> Ans[N];
LL Steps[N];

struct Query
{
	int x, y, l, r, id;
	bool operator < (const Query& rhs) const
	{
		return l > rhs.l;
	}
}Q[N];

struct Node
{
	LL val[2], tag[2];
}Tree[2][M];

struct ST
{
	int n, tot, Root[N];
	LL Sum[N], SSum[N];
	Node *T;
	bool Flag[M][2];
	unordered_map<char, int> ValMap;
	pair<int, int> Go[LOGN][N][2];
	LL Step[LOGN][N][2];
	
	void apply(int x, int op, LL v)
	{
		T[x].val[op] += v;
		T[x].tag[op] += v;
	}
	
	void push(int x, int op)
	{
		if (T[x].tag[op] != 0)
		{
			apply(ls(x), op, T[x].tag[op]);
			apply(rs(x), op, T[x].tag[op]);
			T[x].tag[op] = 0;
		}
	}
	
	void update(int x, int op)
	{
		T[x].val[op] = T[rs(x)].val[op];
		Flag[x][op] = Flag[ls(x)][op] && Flag[rs(x)][op] && T[ls(x)].val[op] == T[rs(x)].val[op];
	}
	
	void Modify(int x, int l, int r, int s, int t, int op, int v, bool lim = false)
	{
		if (l == s && r == t)
		{
			if (!lim)
			{
				apply(x, op, v);
				return ;
			}
			if (Flag[x][op])
			{
				apply(x, op, op == 0 ? min(0LL, -T[x].val[op]) + v : max(0LL, -T[x].val[op]) + v);
				return ;
			}
		}
		push(x, op);
		int mid = (l + r) >> 1;
		if (t <= mid)
			Modify(ls(x), l, mid, s, t, op, v, lim);
		else if (s > mid)
			Modify(rs(x), mid + 1, r, s, t, op, v, lim);
		else
		{
			bool r_lim = lim && (op == 0 ? T[ls(x)].val[op] > 0 : T[ls(x)].val[op] < 0);
			Modify(ls(x), l, mid, s, mid, op, v, lim);
			Modify(rs(x), mid + 1, r, mid + 1, t, op, v, r_lim);
		}
		update(x, op);
	}
	
	int Find(int x, int l, int r, int op, int v)
	{
		if ((op == 0 && T[x].val[0] > v) ||
			(op == 1 && T[x].val[1] < v))
			return r + 1;
		if (l == r)
			return l;
		push(x, op);
		int mid = (l + r) >> 1;
		if ((op == 0 && T[ls(x)].val[0] <= v) ||
			(op == 1 && T[ls(x)].val[1] >= v))
			return Find(ls(x), l, mid, op, v);
		else return Find(rs(x), mid + 1, r, op, v);
	}
	
	void Build()
	{
		Sum[0] = SSum[0] = tot = 0;
		memset(Flag, true, sizeof(Flag));
		for (int i = 1; i <= len; i ++)
		{
			Sum[i] = Sum[i - 1] + ValMap.at(s[i]) * B[i];
			SSum[i] = SSum[i - 1] + abs(ValMap.at(s[i])) * B[i];
		}
		Modify(1, 1, len, 1, len, 0, INF);
		Modify(1, 1, len, 1, len, 1, -INF);
	}
	
	pair<pair<int, int>, LL> Calc(int pos, int st)
	{
		int pos_0 = Find(1, 1, len, 0, -pos);
		int pos_1 = Find(1, 1, len, 1, n - pos);
		if (pos_0 > len && pos_1 > len)
			return make_pair(make_pair(len + 1, 0), SSum[len] - SSum[st - 1]);
		else if (pos_0 <= pos_1)
			return make_pair(make_pair(pos_0 + 1, 0), SSum[pos_0] - SSum[st - 1] + pos + Sum[pos_0] - Sum[st - 1]);
		else return make_pair(make_pair(pos_1 + 1, 1), SSum[pos_1] - SSum[st - 1] + n - (pos + Sum[pos_1] - Sum[st - 1]));
	}
	
	pair<int, LL> GetPos(int pos, int l, int r, int id)
	{
		LL steps = 0;
		pair<int, int> st;
		if (pos == 0 || pos == n)
			st = make_pair(l, pos == 0 ? 0 : 1);
		else tie(st, steps) = Ret[id];
		tuple<int, int, int> ret;
		if (st.first > r)
		{
			pos += Sum[r] - Sum[l - 1];
			int over_step = pos < 0 ? pos : (pos > n ? pos - n : 0);
			steps = SSum[r] - SSum[l - 1] - abs(over_step);
			pos -= over_step;
			return make_pair(pos, steps);
		}
		for (int i = LOGN - 1; i >= 0; i --)
			if (Go[i][st.first][st.second].first <= min(r + 1, len))
				steps += Step[i][st.first][st.second], st = Go[i][st.first][st.second];
		pos = st.second == 0 ? 0 : n;
		if (st.first <= r)
		{
			pos += Sum[r] - Sum[st.first - 1];
			int over_step = pos < 0 ? pos : (pos > n ? pos - n : 0);
			steps += SSum[r] - SSum[st.first - 1] - abs(over_step);
			pos -= over_step;
		}
		return make_pair(pos, steps);
	}
}A[2];

void Prepare()
{
	A[0].ValMap = {{'L', -1}, {'R', 1}, {'U', 0}, {'D', 0}};
	A[1].ValMap = {{'L', 0}, {'R', 0}, {'U', 1}, {'D', -1}};
	for (int t = 0; t < 2; t ++)
	{
		A[t].T = Tree[t];
		A[t].Build();
	}
	for (int i = len, j = 1; i; i --)
	{
		for (int t = 0; t < 2; t ++)
		{
			int val = A[t].ValMap.at(s[i]) * B[i];
			if (val != 0)
			{
				int op = val < 0 ? 0 : 1;
				A[t].Modify(1, 1, len, i, i, op, A[t].ValMap.at(s[i]) * INF + val);
				if (i < len)
					A[t].Modify(1, 1, len, i + 1, len, op, val, true);
				A[t].Modify(1, 1, len, i, len, op ^ 1, val, true);
			}
			else
			{
				A[t].Modify(1, 1, len, i, len, 0, 0, true);
				A[t].Modify(1, 1, len, i, len, 1, 0, true);
			}
		}
		
		for (; j <= q && Q[j].l == i; j ++)
		{
			Ret[Q[j].id] = A[0].Calc(Q[j].x, i);
			Ret[Q[j].id + q] = A[1].Calc(Q[j].y, i);
		}
		
		int val_0 = A[0].ValMap.at(s[i]);
		int val_1 = A[1].ValMap.at(s[i]);
		if (val_0 == -1)
		{
			A[0].Go[0][i][0] = A[1].Go[0][i][0] = make_pair(i + 1, 0);
			A[1].Go[0][i][1] = make_pair(i + 1, 1);
			A[0].Step[0][i][0] = A[1].Step[0][i][0] = A[1].Step[0][i][1] = 0;
			tie(A[0].Go[0][i][1], A[0].Step[0][i][1]) = A[0].Calc(A[0].n, i);
		}
		else if (val_0 == 1)
		{
			A[1].Go[0][i][0] = make_pair(i + 1, 0);
			A[0].Go[0][i][1] = A[1].Go[0][i][1] = make_pair(i + 1, 1);
			A[0].Step[0][i][1] = A[1].Step[0][i][0] = A[1].Step[0][i][1] = 0;
			tie(A[0].Go[0][i][0], A[0].Step[0][i][0]) = A[0].Calc(0, i);
		}
		else if (val_1 == -1)
		{
			A[0].Go[0][i][0] = A[1].Go[0][i][0] = make_pair(i + 1, 0);
			A[0].Go[0][i][1] = make_pair(i + 1, 1);
			A[0].Step[0][i][0] = A[0].Step[0][i][1] = A[1].Step[0][i][0] = 0;
			tie(A[1].Go[0][i][1], A[1].Step[0][i][1]) = A[1].Calc(A[1].n, i);
		}
		else
		{
			A[0].Go[0][i][0] = make_pair(i + 1, 0);
			A[0].Go[0][i][1] = A[1].Go[0][i][1] = make_pair(i + 1, 1);
			A[0].Step[0][i][0] = A[0].Step[0][i][1] = A[1].Step[0][i][1] = 0;
			tie(A[1].Go[0][i][0], A[1].Step[0][i][0]) = A[1].Calc(0, i);
		}
	}
	A[0].Go[0][len + 1][0] = A[1].Go[0][len + 1][0] = make_pair(len + 1, 0);
	A[0].Go[0][len + 1][1] = A[1].Go[0][len + 1][1] = make_pair(len + 1, 1);
	A[0].Step[0][len + 1][0] = A[0].Step[0][len + 1][1] = A[1].Step[0][len + 1][0] = A[1].Step[0][len + 1][1] = 0;
	for (int w = 1; w < LOGN; w ++)
		for (int i = 1; i <= len + 1; i ++)
			for (int j = 0; j < 2; j ++)
			{
				A[0].Go[w][i][j] = A[0].Go[w - 1][A[0].Go[w - 1][i][j].first][A[0].Go[w - 1][i][j].second];
				A[1].Go[w][i][j] = A[1].Go[w - 1][A[1].Go[w - 1][i][j].first][A[1].Go[w - 1][i][j].second];
				A[0].Step[w][i][j] = A[0].Step[w - 1][i][j] + A[0].Step[w - 1][A[0].Go[w - 1][i][j].first][A[0].Go[w - 1][i][j].second];
				A[1].Step[w][i][j] = A[1].Step[w - 1][i][j] + A[1].Step[w - 1][A[1].Go[w - 1][i][j].first][A[1].Go[w - 1][i][j].second];
			}
}

int main()
{
	scanf("%d%d%d%d", &A[0].n, &A[1].n, &len, &q);
	for (int i = 1; i <= len; i ++)
	{
		char st[9];
		scanf("%s%d", st, B + i);
		s[i] = st[0];
	}
	for (int i = 1; i <= q; i ++)
	{
		scanf("%d%d%d%d", &Q[i].x, &Q[i].y, &Q[i].l, &Q[i].r);
		Q[i].id = i;
	}
	sort(Q + 1, Q + q + 1);
	Prepare();
	for (int i = 1; i <= q; i ++)
	{
		pair<int, LL> res_0 = A[0].GetPos(Q[i].x, Q[i].l, Q[i].r, Q[i].id);
		pair<int, LL> res_1 = A[1].GetPos(Q[i].y, Q[i].l, Q[i].r, Q[i].id + q);
		Ans[Q[i].id] = make_pair(res_0.first, res_1.first);
		Steps[Q[i].id] = res_0.second + res_1.second;
	}
	for (int i = 1; i <= q; i ++)
		printf("%d %d %lld\n", Ans[i].first, Ans[i].second, Steps[i]);
	return 0;
}
