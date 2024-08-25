#include <bits/stdc++.h>
using namespace std;

const int N = 1e6 + 5;

char a[N], b[N];
int nxt[N];
int T, n, m;

int solve(char *a, char *b, int n, int m) {
	for (int i = 2; i <= n; i++) {
		int k = nxt[i - 1];
		while (k && a[i] != a[k + 1]) k = nxt[k];
		if (a[i] == a[k + 1]) ++k;
		nxt[i] = k;
	}
	int match = 0, k = 0;
	for (int i = 1; i <= m; i++) {
		if (k == n) k = nxt[k];
		while (k && b[i] != a[k + 1]) k = nxt[k];
		if (b[i] == a[k + 1]) ++k;
		if (k == n) ++match;
	}
	if (match >= 2) return -1;
	if (match == 1) return m;
	return n + m - k;
}

int main() {
	scanf("%d", &T);
	while (T--) {
		scanf("%s%s", a + 1, b + 1);
		n = strlen(a + 1); m = strlen(b + 1);
		int ans = min(solve(a, b, n, m), solve(b, a, m, n));
		printf("%d\n", ans);
	}
	return 0;
}