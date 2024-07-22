#include <bits/stdc++.h>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, x, y;
    std::cin >> n >> x >> y;
    std::string s;
    std::cin >> s;

    auto next = [&](std::pair<int, int> cur, char c) {
        if (c == 'W') {
            cur.second++;
        } else if (c == 'S') {
            cur.second--;
        } else if (c == 'A') {
            cur.first--;
        } else {
            cur.first++;
        }
        return cur;
    };

    std::map<std::pair<int, int>, std::vector<int>> mp;
    std::pair cur(0, 0);
    mp[cur].push_back(0);
    for (int i = 0; i < n; i++) {
        cur = next(cur, s[i]);
        mp[cur].push_back(i + 1);
    }

    int64_t ans = 0;
    cur = std::pair(0, 0);
    for (int i = 0; i < n; i++) {
        std::pair target(x + cur.first, y + cur.second);
        if (mp.count(target)) {
            auto p = std::lower_bound(mp[target].begin(), mp[target].end(), i);
            if (p != mp[target].end()) {
                if (*p == i) {
                    ans += n - *p;
                } else {
                    ans += n - *p + 1;
                }
            }
        }
        cur = next(cur, s[i]);
    }

    std::cout << ans << "\n";

    return 0;
}