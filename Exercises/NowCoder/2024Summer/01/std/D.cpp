#include<bits/stdc++.h>

#ifndef CPLIBRARY_BINARY_INDEXED_TREE_HPP
#define CPLIBRARY_BINARY_INDEXED_TREE_HPP

namespace data_structures {

template<typename T, bool P = true>
class BIT {
private:
    std::vector<T> c;

public:
    void init(int n) {
        std::vector<T>(n + 1, 0).swap(c);
    }
    void update(int p, const T& v) {
        if constexpr (P) {
            for(size_t i = p; i < c.size(); i += i & -i) {
                c[i] += v;
            }
        } else {
            for(size_t i = p; i > 0; i -= i & -i) {
                c[i] += v;
            }
        }
    }
    T query(int p) const {
        T res(0);
        if constexpr (P) {
            for(size_t i = p; i > 0; i -= i & -i) {
                res += c[i];
            }
        } else {
            for(size_t i = p; i < c.size(); i += i & -i) {
                res += c[i];
            }
        }
        return res;
    }
};

} // namespace data_structures

#endif // CPLIBRARY_BINARY_INDEXED_TREE_HPP

using namespace std;
typedef long long ll;
const int MAXN=500005;
const int MAXB=21;
ll p[MAXN];
data_structures::BIT<int> bit[MAXB];
int main()
{
    int n=0,q;
    scanf("%d",&q);
    for(int b=0;b<MAXB;b++)
        bit[b].init(1<<(b+1));
    auto update=[&](ll x,int v)
    {
        for(int b=0;b<MAXB;b++)
        {
            int r=-x&((1<<(b+1))-1);
            bit[b].update(r+1,v);
        }
    };
    auto query_bit=[&](int b,int l,int r)
    {
        return bit[b].query(r+1)-bit[b].query(l);
    };
    auto query=[&](ll x)
    {
        int res=0;
        for(int b=0;b<MAXB;b++)
        {
            int r=x&((1<<(b+1))-1);
            if(r<=(1<<b))res+=(query_bit(b,(1<<b)-r,(1<<(b+1))-1-r)&1)<<b;
            else res+=((n-query_bit(b,(1<<(b+1))-r,(3<<b)-1-r))&1)<<b;
        }
        return res;
    };
    while(q--)
    {
        int t,v;
        scanf("%d%d",&t,&v);
        while(t--)update(p[n-1],-1),--n;
        ++n,p[n]=p[n-1]+v;
        update(p[n-1],1);
        printf("%d\n",query(p[n]));
    }
    return 0;
}

