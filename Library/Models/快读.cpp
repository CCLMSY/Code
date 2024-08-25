#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

// 快速读入
// Luogu 读入1e8个1e8->1.4s
static char buf[1000000],*p1=buf,*p2=buf;
#define gc() p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 1000000, stdin), p1 == p2) ? EOF : *p1++
static inline ll read()
{
    ll x = 0; int fl=1;
    char ch = gc();
    while ((ch < '0' || '9' < ch) && ch!='-')
        ch = gc();
    if(ch=='-') fl=-1,ch=gc();
    while ('0' <= ch && ch <= '9')
    {
        x = x * 10 + (ch - '0');
        ch = gc();
    }
    return x*fl;
}

int main(){
    ll n=read();
    ll ans=0,t;
    for(ll i=0;i<n;i++){
        t=read();
        ans+=t;
    }
    cout << ans << endl;
    return 0;
}