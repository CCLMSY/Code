#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

class DSU{
private:
    vector<ll> parents, size;
public:
    explicit DSU(ll n) : parents(n + 1), size(n + 1, 1) { iota(parents.begin(), parents.end(), 0); }
    ll find(ll x) { return (parents[x] == x) ? x : (parents[x] = find(parents[x])); }
    void merge(ll a, ll b)
    { // merge a and b
        a = find(a);
        b = find(b);
        if (a == b) return;
        if (size[a] > size[b]) swap(a, b); //定向merge去掉本行：merge a into b
        parents[a] = b;
        size[b] += size[a];
    }
};