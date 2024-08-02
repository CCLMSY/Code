#include <bits/stdc++.h>
using i64 = long long;
constexpr int N = 1e5 + 10, B = 1000, M = B + 10;
int n, m, a[N];
int k, f[M], dp[N], pre[N];
int main() {
	std::cin >> n >> k;
	for(int i = 2; i <= B; i ++) {
		f[i] = f[i - 1] + i / 2;
	}
	memset(dp, 0x3f, sizeof dp);
	dp[0] = 0;
	for(int i = 1; i <= B; i ++) {
		for(int j = f[i]; j <= k; j ++) {
			if(dp[j] > dp[j - f[i]] + i) {
				dp[j] = dp[j - f[i]] + i;
				pre[j] = i;
			}
		}
	}
	if(dp[k] <= n) {
		std::cout << "Yes\n";
		std::vector<int> vec;
		int sum = 0;
		for(int x = k; x; x -= f[pre[x]]) {
			vec.emplace_back(pre[x]);
			sum += pre[x];
		}
		while(sum < n) {
			vec.emplace_back(1);
			sum ++;
		}
		for(int i = 0; i < vec.size(); i ++) {
			int o = __builtin_parity(i + 1) - __builtin_parity(i) + 1;
			for(int j = 0; j < vec[i]; j ++) std::cout << o << ' ';
		}
		std::cout << '\n';
	} else {
		std::cout << "No\n";
	}
	return 0;
}

