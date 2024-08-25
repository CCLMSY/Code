#include <bits/stdc++.h>
using namespace std;
#define debug(fmt, ...) \
  fprintf(stderr, "[%d] " fmt "\n", __LINE__, ##__VA_ARGS__)
template <class _Tx, class _Ty>
inline void chkmin(_Tx& x, const _Ty& y) {
  x = min<common_type_t<_Tx, _Ty>>(x, y);
}
template <class _Tx, class _Ty>
inline void chkmax(_Tx& x, const _Ty& y) {
  x = max<common_type_t<_Tx, _Ty>>(x, y);
}
using ll = long long;
using ull = unsigned long long;
using i128 = __int128_t;
using u128 = __uint128_t;
bool Mbe;
int n, k;
void print(const vector<vector<int>>& out) {
  cout << out.size() << '\n';
  for (auto it : out) {
    cout << it.size() << ' ';
    for (int i = 0; i < (int)it.size(); ++i)
      cout << n - it[i] + 1 << " \n"[i == (int)it.size() - 1];
  }
}
void push() {
  vector<vector<int>> ret(n + (n - 1) / k);
  int ptr = 0;
  for (int i = k; i < n; i += k, ++ptr)
    for (int j = i; j >= 1; --j)
      ret[ptr + i - j].emplace_back(j);
  for (int i = n; i >= 1; --i)
    ret[ptr + n - i].emplace_back(i);
  print(ret);
}
void pull() {
  vector<vector<int>> ret(n * 2 - 1);
  for (int i = 1; i <= n; ++i)
    for (int j = i; j >= 1; --j)
      ret[i + i - j - 1].emplace_back(j);
  print(ret);
}
void mian() {
  cin >> n >> k;
  push(), pull();
}
bool Med;
int main() {
  // debug("Mem: %.4lfMB.", fabs(&Med - &Mbe) / 1048576);
  cin.tie(0)->sync_with_stdio(0);
  int cas;
  cin >> cas;
  while (cas--) mian();
  return 0;
}
/*
g++ -std=c++14 -O2 -o piston piston.cpp -Wall -Wextra
-Wshadow -fsanitize=address,undefined -g
*/