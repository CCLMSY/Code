#include <bits/stdc++.h>
using namespace std;

#define pb push_back
#define fi first
#define se second
#define all(x) (x).begin(), (x).end()
#define Sz(x) (int)(x).size()
#define bit(x) (1ll << (x))
using ll = long long;
using db = double;
using ull = unsigned long long;
using pii = pair<int, int>;
using vi = vector<int>;
using vii = vector<vi>;
using vl = vector<ll>;
using vll = vector<vl>;
using vs = vector<string>;
using vd = vector<db>;
mt19937 mrand(time(0));


template<typename T>
struct BIT{
    int n;
    vector<T> tr;
    BIT() {}
    BIT(int n) : n(n), tr(n + 1, 0) {}
    int lowbit(int x) {
        return x & -x;
    }
    void modify(int x, T c) {
        assert(x != 0);
        for (int i = x; i <= n; i += lowbit(i)) tr[i] += c;
    }
    T query(int x) {
        assert(x <= n);
        T res = T();
        for (int i = x; i; i -= lowbit(i)) res += tr[i];
        return res;
    }
    T query(int l, int r) {
        assert(l <= r);
        return query(r) - query(l - 1);
    }
};

void solve(void)
{
	int n, k;
	cin >> n >> k;
	vi a(n + 2), p(n + 2);
	for (int i = 1; i <= n; i++)
	{
		int x;
		cin >> x;
		a[i] = x;
	}

	int lg = 20;
	vector<vii> br(2, vii(lg + 2, vi(n + 2)));
	auto calc = [&](int tp)
	{
		for (int i = 1; i <= n; i++)
			p[a[i]] = i; 
		vi nxt(n + 2);
		set<array<int, 2>> st;
		set<int> inq;

		BIT<int> t(n + 2);
		int num = 0;
		nxt[n + 1] = n + 1;
		for (int i = n; i >= 1; i--)
		{
			inq.insert(p[i]);
			t.modify(p[i], 1);
			num++;
			while (!inq.empty())
			{
				int nl = *inq.begin(), nr = *inq.rbegin();
				if (t.query(nl, nr) <= k && t.query(nl, nr) == num)
					break;
				inq.erase(p[i + num - 1]);
				num--;
			}
			nxt[i] = i + num - 1;
		}

		br[tp][0] = nxt;
		for (int j = 1; j <= lg; j++)
			for (int i = 1; i <= n; i++)
				if (br[tp][j - 1][i] < n) br[tp][j][i] = br[tp][j - 1][br[tp][j - 1][i] + 1];
				else br[tp][j][i] = n + 1;
	};

	calc(0);
	for (int i = 1; i <= n; i++)
		a[i] = n - a[i] + 1;
	calc(1);

	int q;
	cin >> q;
	for (int i = 1; i <= q; i++)
	{
		int l, r;
		char c;
		cin >> l >> r >> c;

		int ans = 0;
		int t = 0;
		if (c == 'L') 
		{
			l = n - l + 1, r = n - r + 1;
			swap(l, r);
			t = 1;
		}

		int u = l;
		for (int j = lg; j >= 0; j--)
			if (br[t][j][u] < r)
			{
				u = br[t][j][u] + 1;
				ans += bit(j);
			}

		cout << ans + 1 << "\n";
	}
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	// cout << fixed << setprecision(10);

	int T = 1;
	cin >> T;
	for (int i = 1; i <= T; i++)
	solve();

	return 0;
}