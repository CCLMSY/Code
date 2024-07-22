#include <bits/stdc++.h>
using namespace std;

using i64 = long long;
using u64 = unsigned long long;

#ifdef EMOFUNC
#include <debug.h>
#else
#define LOG(...)
#endif

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0);

    const i64 inf = 1e12;

    int n, x, y;
    cin >> n >> x >> y;

    vector<i64> a(n);
    for (auto& v: a) {
        cin >> v;
    }

    sort(a.begin(), a.end());

    int s = x + y;

    vector<pair<int, i64>> f{{0, 0}, {s + 1, inf}};

    for (int i = 0; i < n; i++) {
        vector<pair<int, i64>> g;

        auto add = [&g](int p, i64 v) {
            if (g.empty() || g.back().first < p) {
                g.emplace_back(p, v);
                return;
            }
            g.back().second = v;
        };

        int sz = f.size();
        for (int j = 0, k = 0; j < sz - 1 || k < sz - 1; ) {
            int p = (f[j].first + f[k].first) / 2;
            if (f[j].second <= f[k].second + a[i]) {    
                add(p, f[j].second);
                j++;
            } else {
                add(p, f[k].second + a[i]);
                k++;
            }
        }

        g.emplace_back(s + 1, inf);

        LOG(i, a[i], g);

        f.swap(g);
    }

    i64 ans = 0;
    for (auto& [p, v]: f) {
        if (p <= x) {
            ans = v;
        }
    }
    cout << ans << "\n";
    return 0;
}