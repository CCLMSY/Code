#include<bits/stdc++.h>
using namespace std;
#define N 200010
const int mod = 998244353;
int n, k;
int dp[N], fac[N], inv[N];
int sz[N];
vector<int>e[N];

int C(int n, int m) {return 1LL * fac[n] * inv[m] % mod * inv[n - m] % mod;}
int ksm(int a, int b)
{
    int ans = 1;
    while(b) {if(b & 1)ans = 1LL * ans * a % mod; b >>= 1; a = 1LL * a * a % mod;}
    return ans;
}

void dfs(int x)
{
    int m = 0; dp[x] = sz[x] = 1;
    for (int y : e[x])
    {
        dfs(y); sz[x] += sz[y];

        if (sz[y] % 2 == 0) dp[x] = 2LL * dp[x] * dp[y] % mod; 
        if (sz[y] % 2 == 1) dp[x] = 1LL * dp[x] * dp[y] % mod, m ++;
    }
    
    if (m == 0) {/*do nothing*/}
    else if (m % 2 == 0)dp[x] = 1LL * dp[x] * (C(m, m / 2) % mod + C(m, m / 2 - 1)) % mod;
    else if (m % 2 == 1)dp[x] = 1LL * dp[x] * C(m, m / 2) % mod;
}
void sol()
{
    cin >> n >> k;
    fac[0] = 1; 
    for (int i = 1; i <= n; i ++) fac[i] = 1LL * fac[i - 1] * i % mod;
    inv[0] = inv[1] = 1; 
    for (int i = 2; i <= n; i ++) inv[i] = 1LL * inv[mod % i] * (mod - mod / i) % mod;
    for (int i = 2; i <= n; i ++) inv[i] = 1LL * inv[i] * inv[i - 1] % mod;

    for(int i = 2; i <= n; i ++)
    {
        int parent; cin >> parent;
        e[parent].push_back(i);
    }

    dfs(1);

    cout << ksm(2LL * dp[1] % mod, k) << '\n';
    
    for (int i = 1; i <= n; i ++)e[i].clear();
}
int main()
{
    int T;
    cin >> T;
    while (T --) sol();
    return 0;
}