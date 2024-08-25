#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

#define N 210
int n, m, P;
int dp[2][N][N][N][2];// dp[i][j][t][s][0/1] è¡¨ç¤º k - a[k] = i, æœ‰ j ä¸ªè¿™æ ·çš„ k, å…±ç”¨äº† s ä¸ªäººï¼Œt ä¸ªå®ç®±ï¼Œå½“å‰æœ‰æ— æ»¡è¶³æ¡ä»¶çš„å®ç®±
int Binom[N][N];
int temp[N][N][N][2][2];
void add (int &x, int y) {x = (x + y >= P ? x + y - P : x + y);}
void sol()
{
    cin >> n >> m >> P;
    Binom[0][0] = 1;
    for (int i = 1; i <= max(n, m); i ++)
    {
        Binom[i][0] = 1;
        for (int j = 1; j <= i; j ++)
        {
            Binom[i][j] = (Binom[i - 1][j] + Binom[i - 1][j - 1]) % P;
        }
    }

    int p = 0, q = 1;
    memset(dp, 0, sizeof(dp)); memset(temp, 0, sizeof(temp));

    dp[p][0][0][0][0] = 1;
    for (int i = m; i >= 0; i --)
    {
        for (int j = 0; j * (j - 1) / 2 <= m && j <= m + 1; j ++)
        {
            int vj = j * (j - 1) / 2;
            for (int t = 0; t * (i + 2) + vj <= m && t <= n; t ++)
            {
                int vt = t * (i + 2) + vj;
                for (int s = vt; s <= m; s ++)
                {
                    for (int C = 0; C <= 1; C ++) if (dp[p][j][t][s][C])
                    {
                        int val = dp[p][j][t][s][C];
                        for (int tj = 0; tj <= j && tj + s <= m; tj ++)
                        {
                            add(temp[tj + 1][t][s + tj][C][(tj < j)], 1LL * val * Binom[j][tj] % P);
                        }
                        dp[p][j][t][s][C] = 0;
                    }
                }
            }
        }

        for (int j = 0; j * (j - 1) / 2 <= m && j <= m + 1; j ++)
        {
            int vj = j * (j - 1) / 2;
            for (int t = 0; t * (i + 2) + vj <= m && t <= n; t ++)
            {
                int vt = t * (i + 2) + vj;
                for (int s = vt; s <= m; s ++)
                {
                    for (int C = 0; C <= 1; C ++) for (int D = 0; D <= 1; D ++) if (temp[j][t][s][C][D])
                    {
                        int val = temp[j][t][s][C][D];
                        for (int tt = t; tt <= n && (tt - t) * (i + 1) + s <= m; tt ++)
                        {
                            if (tt == t + 1 && D == 1 && C == 1)continue;
                            int tC = C;
                            if (tt == t + 1 && D == 1)tC = 1;
                            add(dp[q][j][tt][s + (tt - t) * (i + 1)][tC], 1LL * val * Binom[n - t][tt - t] % P);
                        }
                        temp[j][t][s][C][D] = 0;
                    }
                }
            }
        }
        
        swap(p, q);

        // cout << "EE:" << i << endl;
        // for (int j = 0; j * (j - 1) / 2 <= m && j <= m + 1; j ++)
        // {
        //     int vj = j * (j - 1) / 2;
        //     for (int t = 0; t * (i + 1) + vj <= m && t <= n; t ++)
        //     {
        //         int vt = t * (i + 1) + vj;
        //         for (int s = vt; s <= m; s ++)
        //         {
        //             for (int C = 0; C <= 1; C ++) if (dp[p][j][t][s][C])
        //             {
        //                 cout << "??:" << j << ' ' << t << ' ' << s << ' ' << C << ' ' << dp[p][j][t][s][C] << endl;
        //             }
        //         }
        //     }
        // }
        
    }

    int ans = 0;
    for (int j = 1; j <= m + 1; j ++)
    {
        // cout << "??:" << j << endl;
        // for (int s = 0; s <= m; s ++) cout << dp[p][j][n][s][1] << ' '; cout << '\n';
        // for (int s = 0; s <= m; s ++) cout << dp[p][j][n - 1][s][0] << ' '; cout << '\n';
        if (j == 1)
        {
            add(ans, (dp[p][j][n][m][1] + dp[p][j][n - 1][m][0]) % P);
            for (int t = 1; t <= n - 2; t ++)add(ans, dp[p][j][t][m][1]);
        }
        else 
        {
            for (int s = 0; s <= m; s ++)
            {
                add(ans, 1LL * dp[p][j][n][s][1] * Binom[m - s + (j - 1) - 1][(j - 1) - 1] % P);
                add(ans, 1LL * dp[p][j][n - 1][s][0] * Binom[m - s + (j - 1) - 1][(j - 1) - 1] % P); 
                for (int t = 1; t <= n - 2; t ++)add(ans, 1LL * dp[p][j][t][s][1] * Binom[m - s + (j - 1) - 1][(j - 1) - 1] % P);
            }
        }
    }

    cout << ans << '\n';
}

int main()
{
    // freopen("r.in", "r", stdin);
    // freopen("std.out", "w", stdout);
    int T; cin >> T;
    while (T --) sol();
}
/*
1
150 200 998244353
*/