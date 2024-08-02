#include <bits/stdc++.h>
constexpr int mod = 998244353;
int main() {
	std::ios::sync_with_stdio(false), std::cin.tie(0);
	int T;
	for(std::cin >> T; T; T --) {
		int n;
		std::cin >> n;
		std::vector<int> a(n);
		for(auto &x : a) std::cin >> x;
		while(!std::is_sorted(a.rbegin(), a.rend())) {
			for(int i = 0; i + 1 < n; i ++) {
				if(a[i] < a[i + 1]) {
					int sum = a[i] + a[i + 1];
					a[i] = (sum + 1) / 2;
					a[i + 1] = sum / 2;
				}
			}
		}
		int ans = 1;
		for(auto &x : a) ans = 1ll * ans * x % mod;
		std::cout << ans << '\n';
	}
	return 0;
}