#include <bits/stdc++.h>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;
    std::vector<std::string> a(2);
    for (auto &s : a) {
        std::cin >> s;
    }

    std::vector dp(2, std::vector(n, std::vector(2, 0)));
    for (int j = 0; j < n; j++) {
        for (int i = 0; i < 2; i++) {
            if (a[i][j] == 'R') {
                dp[i][j][0] = 1;
            }
        }
    }

    for (int j = 0; j < n; j++) {
        for (int i = 0; i < 2; i++) {
            if (a[i][j] == 'R' && j > 0) {
                dp[i][j][0] += std::max(dp[i][j - 1][0], dp[i][j - 1][1]);
            }
        }
        for (int i = 0; i < 2; i++) {
            if (a[i][j] == 'R') {
                dp[i][j][1] = dp[i ^ 1][j][0] + 1;
            }
        }
    }

    int ans = 0;
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < 2; k++) {
                ans = std::max(ans, dp[i][j][k]);
            }
        }
    }

    std::cout << std::max(0 ,ans - 1) << '\n';

    return 0;
}