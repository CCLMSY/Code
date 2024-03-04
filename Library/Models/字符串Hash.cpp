#include <bits/stdc++.h>
using namespace std;

#define N 200005
struct strHash
{ // 字符串哈希
    typedef long long ll;
    typedef pair<ll, ll> pll;
    const ll P1 = 57751, mod1 = 1e9 + 7, P2 = 43331, mod2 = 1e9 + 9;
    size_t length, size;
    vector<ll> hz1, hf1, pz1, pf1, hz2, hf2, pz2, pf2;
    // h:Hash;p:Pow;
    // z:正向;f:反向;
    // 1/2:双Hash;下标从1开始
    strHash(string str)
    {
        length = size = str.length();
        str = ' ' + str;
        hz1.resize(size + 2);
        pz1.resize(size + 2);
        hf1.resize(size + 2);
        pf1.resize(size + 2);
        hz2.resize(size + 2);
        pz2.resize(size + 2);
        hf2.resize(size + 2);
        pf2.resize(size + 2);
        pz1[0] = 1;
        for (int i = 1; i <= size; i++)
        {
            hz1[i] = (hz1[i - 1] * P1 + str[i]) % mod1;
            pz1[i] = pz1[i - 1] * P1 % mod1;
        }
        pf1[size + 1] = 1;
        for (int i = size; i >= 1; i--)
        {
            hf1[i] = (hf1[i + 1] * P1 + str[i]) % mod1;
            pf1[i] = pf1[i + 1] * P1 % mod1;
        }
        pz2[0] = 1;
        for (int i = 1; i <= size; i++)
        {
            hz2[i] = (hz2[i - 1] * P2 + str[i]) % mod2;
            pz2[i] = pz2[i - 1] * P2 % mod2;
        }
        pf2[size + 1] = 1;
        for (int i = size; i >= 1; i--)
        {
            hf2[i] = (hf2[i + 1] * P2 + str[i]) % mod2;
            pf2[i] = pf2[i + 1] * P2 % mod2;
        }
    }
    pll findz(int l, int r)
    { // 返回[l,r]的正向双Hash
        return {((hz1[r] - hz1[l - 1] * pz1[r - l + 1]) % mod1 + mod1) % mod1, ((hz2[r] - hz2[l - 1] * pz2[r - l + 1]) % mod2 + mod2) % mod2};
    }
    pll findf(int l, int r)
    { // 返回[l,r]的反向双Hash
        return {((hf1[l] - hf1[r + 1] * pf1[length - r + l]) % mod1 + mod1) % mod1, ((hf2[l] - hf2[r + 1] * pf2[length - r + l]) % mod2 + mod2) % mod2};
    }
    bool isPalin(ll l, ll r)
    { // 判断[l,r]是否为回文串
        return findz(l, r) == findf(l, r);
    }
};