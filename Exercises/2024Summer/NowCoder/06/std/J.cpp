#include<bits/stdc++.h>
using namespace std;
int n , k;
int a[100005];
int h[100005];
vector<vector<int> > ans ;
void work() {
    vector<int> a;a.push_back(1) ; a.push_back(2) ;
    ans.push_back(a) ;
    int lst = n + 1;
    for(int i = 3;i <= n;i++) {
        vector<int> a;a.push_back(lst) ; a.push_back(i) ;
        lst += 2;
        ans.push_back(a) ;
    }
    cout << ans.size() <<'\n' ;
    for(auto &v : ans) {
        cout << v.size() <<' ' ;
        for(auto x : v) cout << x <<' ';
        cout << '\n' ;
    }
    return ;
    
}
void solv() {
    cin >> n >> k;
    ans.clear() ;
    memset(h,0,(n+2) * sizeof(int)) ;
    int all_2 = 1;
    for(int i = 1;i <= n;i++) {
        cin >> a[i] ;
        if(a[i] != 2) all_2 = 0;
    }
    if(k == 2 && all_2 == 1) {
        if(n >= 3) {
            cout << -1 << '\n' ; return ;
        }
        work() ; return ;
    }
    for(int i = 1;i <= n;i++) h[a[i]] = 1;
    int x = 0;
    for(int i = 2;i <= k;i++) {
        if(!h[i]) {x = i ; break ;}
    }
    if(!x) {
        cout << -1 << '\n' ; return ;
    }
    int y = (n - 1) % (x - 1) + 1;
    vector<pair<int,int> > v;
    for(int i = 1;i <= n;i++) v.push_back({a[i] , i}) ;
    sort(v.begin() , v.end() , [&](pair<int,int> a,pair<int,int> b) {
        return (a.first == y) > (b.first == y) ;
    }) ;
    vector<int> cura;
    int L , pid;
    if(y != 1) {
        if(v[y - 1].first == y) {
            for(int i = 0;i < y;i++) cura.push_back(v[i].second) ;
            v.push_back({0 , n + 1}) ;
            ans.push_back(cura) ;
        }
        else {
            reverse(v.begin() , v.end()) ;
            for(int i = 0;i < y;i++) cura.push_back(v[i].second) ;
            v.push_back({0 , n + 2}) ;
            ans.push_back(cura) ;
        }
        L = y; pid = n + 2;
    }
    else L = 0 , pid = n ;
    while(L < v.size() - 1) {
        // puts("jj") ;
        cura.clear() ;
        // printf("%d , %d , %d\n",L , L + x , v.size()) ;
        for(int i = L ; i < L + x ; i++) {
            cura.push_back(v[i].second) ;
        }
        ans.push_back(cura) ;
        v.push_back({0 , pid + 2}) ;
        L += x;
        pid += 2;
    }
    cout << ans.size() <<'\n' ;
    for(auto &v : ans) {
        cout << v.size() <<' ' ;
        for(auto x : v) cout << x <<' ';
        cout << '\n' ;
    }
    return ;
}
int main() {
    //freopen("in.txt","r",stdin) ;
    ios::sync_with_stdio(false) ; cin.tie(0) ; cout.tie(0) ;
    int t ;cin >> t;
    while(t--) solv() ;
}
