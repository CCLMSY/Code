#include <cstdio>
#include <string>
#include <cstring>
#include <algorithm>
#include <unordered_map>
using namespace std;

int n, m, rk, ans = 0x7fffffff;
char s[100];
const string lzr010506 = "lzr010506";
unordered_map<string, pair<int, int>> nMap, mMap;

int main()
{
	scanf("%d", &n);
	for (int i = 1, p, t; i <= n; i ++)
	{
		scanf("%s%d%d", s, &p, &t);
		nMap.emplace(s, make_pair(p, -t));
	}
	int common_cnt = 0;
	scanf("%d", &m);
	for (int i = 1, p, t; i <= m; i ++)
	{
		scanf("%s%d%d", s, &p, &t);
		mMap.emplace(s, make_pair(p, -t));
		common_cnt += nMap.count(s);
	}
	rk = 1;
	for (auto it = nMap.cbegin(); it != nMap.cend(); it ++)
		if (mMap.count(it->first) == 0 && it->second > nMap.at(lzr010506))
			rk ++;
	ans = min(ans, rk);
	rk = 1;
	for (auto it = mMap.cbegin(); it != mMap.cend(); it ++)
		if (nMap.count(it->first) == 0 && it->second > mMap.at(lzr010506))
			rk ++;
	ans = min(ans, rk);
	fprintf(stderr, "common_cnt = %d\n", common_cnt);
	printf("%d\n", ans);
	return 0;
}
