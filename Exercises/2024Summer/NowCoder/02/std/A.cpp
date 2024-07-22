
#include <bits/stdc++.h>

using namespace std;
int get_max_cnt(int n, int m, int type)
{
    int temp = n + m;
    n--;
    m--;
    if ((n & 1) && (m & 1) && type == 0)
    {
        return (n * m + 1) / 2 + temp;
    }
    else
    {
        return n * m / 2 + temp;
    }
}
int get_min_cnt(int n, int m)
{
    return n + m;
}

int main(int argc, char* argv[])
{
    int T;
    scanf("%d", &T);
    while (T--)
    {
        int n, m, k;
        char ts[5];
        int x, y, t;
        scanf("%d %d %d", &n, &m, &k);
        scanf("%d %d %s", &x, &y, ts);
        t = ts[0] == 'B';
        if ((x + y) & 1)
            t ^= 1;
        bool flag = get_min_cnt(n, m) <= k && k <= get_max_cnt(n, m, t);
        if (!flag)
        {
            printf("No\n");
            continue;
        }
        printf("Yes\n");
        vector<vector<char>> a;
        a.resize(n);
        for (int i = 0; i < n; ++i)
        {
            a[i].resize(m + 1);
        }
        a[0][0] = 'A' + t;
        for (int i = 0; i < n; ++i)
        {
            if (i)
            {
                a[i][0] = a[i - 1][0] == 'A' ? 'B' : 'A';
            }
            for (int j = 0; j < m; ++j)
            {
                if (j)
                {
                    a[i][j] = a[i][j - 1] == 'A' ? 'B' : 'A';
                }
            }
        }
        int now = get_max_cnt(n, m, t);
        for (int i = 0; i < n - 1 && now > k; ++i)
        {
            for (int j = m - 2; j >= 0 && now > k; --j)
            {
                if (a[i][j] == 'A')
                {
                    if (i == x - 1 && j == y - 1)
                    {
                        a[i][j + 1] = 'A';
                    }
                    else
                    {
                        a[i][j] = 'B';
                    }
                    --now;
                }
            }
        }
        assert(now == k);
        for (int i = 0; i < n; ++i)
        {
            printf("%s\n", a[i].data());
        }
    }
    return 0;
}