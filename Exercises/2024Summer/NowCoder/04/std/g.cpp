#include<bits/stdc++.h>
using namespace std;
double solve(){
    long long xg,yg;
    long long xt,yt;
    cin>>xg>>yg>>xt>>yt;
    auto sq=[](long long x){return x*x;};
    long long ans=min(
        sq(xg+xt)+sq(yg-yt),
        sq(xg-xt)+sq(yg+yt)
    );
    return sqrt(ans);
}
int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int t=1;
    cin>>t;
    while(t--) printf("%.10f\n",solve());
    return 0;
}
