#include <bits/stdc++.h>
using namespace std;
#define endl '\n'
#define inf 1e18
typedef long long ll;
typedef pair<ll, ll> P;
#define x first
#define y second
#define pi 3.14159265358
#define int long long
int lowbit(int x) {return x & -x;}

const int p = 1e9 + 7;
const int pp = 998244353;

int dx[8] = {-1, 0, 1, 0, -1, -1, 1, 1}, dy[8] = {0, 1, 0, -1, -1, 1, -1, 1};
int ddx[8] = {1, 1, 2, 2, -1, -1, -2, -2}, ddy[8] = {2, -2, 1, -1, 2, -2, 1, -1};

ll ksm(ll a, ll b, ll p) {
    ll ans = 1;
    while(b) {
        if(b & 1) ans = (ans * a) % p;
        b >>= 1;
        a = (a * a) % p;
    }
    return ans % p;
}

std::mt19937 rng;  // 随机数生成器  
int rand(int l, int r) {
    std::uniform_int_distribution<int> distribution(l, r);
    return distribution(rng);
}

void add(int & x, int y, int p) {
	x %= p;
	y %= p;
	x = ((x + y) % p + p) % p;
}

int inv(int x, int p) {
	x %= p;
	return ksm(x, p - 2, p);
}

int n;

void solve() {
	cin >> n;
	if((n & (n - 1)) == 0) cout << -1 << endl;
	else {
		cout << n - lowbit(n) << endl;
	}
}


/*

1010
1000

*/

signed main () {
//     init(minp, primes, m); // primes
    // init();
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    int _ = 1;
  cin >> _;
    while(_ -- ) {
        solve();
    }
    return 0;
}