// std
// O(n)


#include<bits/stdc++.h>
using namespace std;


void solve() {
    int n;
    cin >> n;
    vector<int> cnt(n + 2);
    int fg = 0;
    for (int i = 1; i <= n; i++) {
        int x;
        cin >> x;
        cnt[x]++;
        fg |= cnt[x] == 2; 
    }
    for (int i = 1; i <= n; i++) {
        int x;
        cin >> x;
    }
    if (fg) cout << "shuishui" << '\n';
    else cout << "sha7dow" << '\n';
}



int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    // cout << fixed << setprecision(10);
    int tc = 1;
    cin >> tc;
    for (int i = 1; i <= tc; i++) {
        solve();
    }
    return 0;
}