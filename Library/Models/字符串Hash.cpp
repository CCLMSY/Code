#include <bits/stdc++.h>
using namespace std;

#define N 200005
// 字符串哈希
struct strHash
{ 
    typedef long long ll;
    typedef pair<ll, ll> pll;
    const ll P1 = 57751, mod1 = 1e9 + 7, P2 = 43331, mod2 = 1e9 + 9;
    size_t length, size;
    vector<ll> hz1, hf1, pz1, pf1, hz2, hf2, pz2, pf2;
    // h:Hash;p:Pow;
    // z:正向;f:反向;
    // 1/2:双Hash;下标从1开始
    inline ll Get_Mod(ll x,ll mod){
        if(x<0) return x-x/mod*mod+mod;
        else return x-x/mod*mod;
    }
    strHash(string str)
    {
        length = size = str.length();
        str = ' ' + str;
        hz1.resize(size + 2); pz1.resize(size + 2);
        hf1.resize(size + 2); pf1.resize(size + 2);
        hz2.resize(size + 2); pz2.resize(size + 2);
        hf2.resize(size + 2); pf2.resize(size + 2);
        pz1[0] = 1;
        for (int i = 1; i <= size; i++)
        {
            hz1[i] = Get_Mod(hz1[i - 1] * P1 + str[i],mod1);
            pz1[i] = Get_Mod(pz1[i - 1] * P1,mod1);
        }
        pf1[size + 1] = 1;
        for (int i = size; i >= 1; i--)
        {
            hf1[i] = Get_Mod(hf1[i + 1] * P1 + str[i],mod1);
            pf1[i] = Get_Mod(pf1[i + 1] * P1,mod1);
        }
        pz2[0] = 1;
        for (int i = 1; i <= size; i++)
        {
            hz2[i] = Get_Mod(hz2[i - 1] * P2 + str[i],mod2);
            pz2[i] = Get_Mod(pz2[i - 1] * P2,mod2);
        }
        pf2[size + 1] = 1;
        for (int i = size; i >= 1; i--)
        {
            hf2[i] = Get_Mod(hf2[i + 1] * P2 + str[i],mod2);
            pf2[i] = Get_Mod(pf2[i + 1] * P2,mod2);
        }
    }
    pll findz(int l, int r)
    { // 返回[l,r]的正向双Hash
        return {Get_Mod(hz1[r] - hz1[l - 1] * pz1[r - l + 1],mod1), Get_Mod(hz2[r] - hz2[l - 1] * pz2[r - l + 1],mod2)};
    }
    pll findf(int l, int r)
    { // 返回[l,r]的反向双Hash
        return {Get_Mod(hf1[l] - hf1[r + 1] * pf1[length - r + l],mod1), Get_Mod(hf2[l] - hf2[r + 1] * pf2[length - r + l],mod2)};
    }
    bool isPalin(ll l, ll r)
    { // 判断[l,r]是否为回文串
        return findz(l, r) == findf(l, r);
    }
    bool contain(strHash &b, int l=-1, int r=-1)
    { // 判断[l,r]是否包含b
        l = ((l == -1) ? 1 : l);
        r = ((r == -1) ? length : r);
        size_t lenb = b.length;
        for(int i = l; i + lenb - 1 <= r; i++)
            if(findz(i, i + lenb - 1) == b.findz(1, lenb))
                return true;
        return false;
    }
    ll count(strHash &b, int l=-1, int r=-1)
    { // 统计[l,r]中包含b的个数
        l = ((l == -1) ? 1 : l);
        r = ((r == -1) ? length : r);
        size_t lenb = b.length;
        ll ret = 0;
        for(int i = l; i + lenb - 1 <= r; i++)
            if(findz(i, i + lenb - 1) == b.findz(1, lenb))
                ret++;
        return ret;
    }
};