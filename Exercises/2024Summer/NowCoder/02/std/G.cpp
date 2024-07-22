#include <bits/stdc++.h>

using namespace std;
const int INF = 1e9;
const unsigned int BIT = 11u;
const unsigned int MAX_STATE = 1u << BIT;
const int prime[] = {2, 3 , 5, 7, 11, 13, 17, 19, 23, 29, 31};
const int MOD = 1e9 + 7;

namespace chino
{
    template<int mod>
    class ModInt
    {
    private:
        const static int MD = mod;
        int x;

    public:
        ModInt(long long x = 0) : x(x % MD)
        {}

        int get()
        {
            return x;
        }

        ModInt operator+(const ModInt &that) const
        {
            int x0 = x + that.x;
            return ModInt(x0 < MD ? x0 : x0 - MD);
        }

        ModInt operator-(const ModInt &that) const
        {
            int x0 = x - that.x;
            return ModInt(x0 < MD ? x0 + MD : x0);
        }

        ModInt operator*(const ModInt &that) const
        {
            return ModInt((long long) x * that.x % MD);
        }

        ModInt operator/(const ModInt &that) const
        {
            return *this * that.inverse();
        }

        ModInt operator+=(const ModInt &that)
        {
            x += that.x;
            if (x >= MD)
                x -= MD;
            return x;
        }

        ModInt operator-=(const ModInt &that)
        {
            x -= that.x;
            if (x < 0)
                x += MD;
            return x;
        }

        ModInt operator*=(const ModInt &that)
        {
            return x = (long long) x * that.x % MD;
        }

        ModInt operator/=(const ModInt &that)
        {
            return *this = *this / that;
        }

        ModInt inverse() const
        {
            int a = x, b = MD, u = 1, v = 0;
            while (b)
            {
                int t = a / b;
                a -= t * b;
                std::swap(a, b);
                u -= t * v;
                std::swap(u, v);
            }
            if (u < 0)
                u += MD;
            return u;
        }
    };
}  // namespace chino
using Mint = chino::ModInt<MOD>;

struct Item
{
    unsigned int state{};
    int less{};
    int val{};

    Item() = default;

    explicit Item(int x)
    {
        val = 1;
        for (auto i = 0u; i < BIT; ++i)
        {
            while (x % prime[i] == 0)
            {
                if (state & (1u << i))
                {
                    val *= prime[i];
                }
                state ^= 1u << i;
                x /= prime[i];
            }
            less = x;
        }
    }
};

static int sval(unsigned int x, unsigned int y)
{
    int val = 1;
    for (auto i = 0u; i < BIT; ++i)
    {
        if ((x & y) & (1u << i))
        {
            val *= prime[i];
        }
    }
    return val;
}
int cur;
Mint dp[MAX_STATE][2][2];
vector<Item> G[MAX_STATE];

int main()
{
    int n, x;
    scanf("%d", &n);
    for (int i = 0; i < n; ++i)
    {
        scanf("%d", &x);
        auto it = Item(x);
        G[it.less].push_back(it);
    }
    dp[0][0][0] = 1;
    for (auto &it: G[1])
    {
        for (auto &st: dp)
        {
            st[0][cur ^ 1] = st[0][cur];
        }
        for (auto i = 0u; i < MAX_STATE; ++i)
        {
            dp[i ^ it.state][0][cur ^ 1] += dp[i][0][cur] * sval(i, it.state) * it.val;
        }
        cur ^= 1;
    }
    for (int num = 32; num < 1000; ++num)
    {
        if (!G[num].empty())
        {
            for (auto &st: dp)
            {
                st[1][cur] = 0;
            }
            for (auto &it: G[num])
            {
                for (auto &st: dp)
                {
                    st[0][cur ^ 1] = st[0][cur];
                    st[1][cur ^ 1] = st[1][cur];
                }
                for (auto i = 0u; i < MAX_STATE; ++i)
                {
                    dp[i ^ it.state][0][cur ^ 1] += dp[i][1][cur] * sval(i, it.state) * it.val * it.less;;
                    dp[i ^ it.state][1][cur ^ 1] += dp[i][0][cur] * sval(i, it.state) * it.val;
                }
                cur ^= 1;
            }
        }
    }
    printf("%d\n", (dp[0][0][cur] - 1).get());
    return 0;
}
/*
3
1 2 8
*/