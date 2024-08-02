#include <bits/stdc++.h>

using LL = long long;
using ld = long double;
using Pair = std::pair<int, int>;
#define inf 1'000'000'000
std::mt19937_64 rnd(std::chrono::steady_clock::now().time_since_epoch().count());

void solve(const int &Case) {
    int n, m;
    std::cin >> n >> m;
    std::vector<std::vector<int>> A(n + 1);
    std::vector<int> L(n + 1);
    for (int i = 1; i <= m; i++) {
        int u, v;
        std::cin >> u >> v;
        A[v].push_back(u);
    }
    for (int i = 1; i <= n; i++) {
        std::sort(A[i].begin(), A[i].end(), std::greater<>());
        int now = i - 1;
        for (const auto &x: A[i]) {
            if (x == now)now--;
            else break;
        }
        L[i] = now + 1;
    }
    LL ans = 0;
    for (int i = 1, p = 1; i <= n; i++) {
        p = std::max(p, i);
        while (p < n && L[p + 1] <= i)p++;
        ans += p - i + 1;
    }
    std::cout << ans << '\n';
}

int main() {
//    freopen("1.in", "r", stdin);
//    freopen("2.out", "w", stdout);
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    int T = 1;
//    std::cin >> T;
    for (int Case = 1; Case <= T; Case++)solve(Case);
    return 0;
}
