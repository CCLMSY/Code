#include <bits/stdc++.h>

int main() {
// 	freopen("in.txt", "r", stdin);
	std::ios::sync_with_stdio(false), std::cin.tie(0);
	int T;
	std::cin >> T;
	while(T --) {
		int n, m, a, b;
		std::cin >> n >> m >> a >> b;
		if(a && b) {
			std::cout << (n % 2 == 0 || m % 2 ==0 ? "Yes\n" : "No\n");
		} else if(a && !b) {
			std::cout << (n == 1 && m % 2 == 0 || m == 1 && n % 2 == 0 ? "Yes\n" : "No\n");
		} else if(!a && b) {
			std::cout << (n % 2 == 0 && m > 1 || m % 2 == 0 && n > 1 || n == 1 && m == 2 || n == 2 && m == 1 ? "Yes\n" : "No\n");
		} else {
			std::cout << (n == 1 && m == 2 || n == 2 && m == 1 ? "Yes\n" : "No\n");
		}
	}	
	return 0;
}