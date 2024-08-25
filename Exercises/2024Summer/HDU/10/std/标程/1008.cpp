#include <bits/stdc++.h>

int main() {
	std::cin.tie(nullptr)->sync_with_stdio(false);
	int t;
	std::cin >> t;
	while (t--) {
		long long n, k;
		std::cin >> n >> k;
		if (k == 1) std::cout << (n & 1 ? 'A' : 'B');
		else if (k == n) std::cout << 'A';
		else std::cout << 'B';
	}
}