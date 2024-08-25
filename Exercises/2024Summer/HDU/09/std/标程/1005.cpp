#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

void solve() {
    ll k,x,y;
    cin >> k >> x >> y;
    ll a = (k + x - 1) / x;
    ll b = (k + y - 1) / y;
    if(a != b) cout << "Yes" << "\n" << "Yes" << "\n";
    else
    {
        if(a % 2) cout << "Yes" << "\n" << "No" << "\n";
        else cout << "No" << "\n" << "Yes" << "\n";
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int _;
    cin >> _;
    while(_--) solve();
    return 0;
}