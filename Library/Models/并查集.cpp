struct DSU{
    vector<ll> parents,size;

    explicit DSU(ll n):parents(n+1),size(n+1,1) {iota(ALL(parents),0);}

    ll find(ll x){ return (parents[x]==x)?x:(parents[x]=find(parents[x])); }
    
    void merge(ll a,ll b){
        a=find(a);b=find(b);
        if(a==b) return ;
        if (size[a]>size[b]) swap(a,b);
        parents[a]=b;
        size[a]+=size[b];
    }
};