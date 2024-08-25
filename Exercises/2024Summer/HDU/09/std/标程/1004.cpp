#include<bits/stdc++.h>
/*
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
#include<queue>
#include<vector>
//*/
using namespace std;
typedef long long ll;
typedef __int128 lll;
typedef double db;
const int N=200010,M=1000010,P=1e9+7;
const int inf=0x3f3f3f3f;
const int INF=0xcfcfcfcf;
const db eps=1e-9,pi=2*asin(1);
template<typename tn> void read(tn &n);
template<typename tn1,typename tn2> bool cmax(tn1 &x,tn2 y) { return x<y?x=y,true:false; }
template<typename tn1,typename tn2> bool cmin(tn1 &x,tn2 y) { return x>y?x=y,true:false; }
#define pb push_back
#define mp make_pair
#define pii pair<int,int>
#define pil pair<int,ll>
#define pli pair<ll,int>
#define pll pair<ll,ll>
int ADD(int x,int y,int p=P) { return x+y>=p?x+y-p:x+y; }
int MINUS(int x,int y,int p=P) { return x-y<0?x-y+p:x-y; }
#define plus(a,b) a=ADD(a,b)
#define minus(a,b) a=MINUS(a,b)
#define mul(a,b) a=1ll*(a)*(b)%P
#define mem(a,b) memset(a,b,sizeof(a))

int n;
int opt[N];
lll m[N];
int x[N],k[N];
ll h[N];
bool die[N];

ostream &operator<<(ostream &os,lll x) {
    if(x==0) {
        return os<<"0";
    }
    if(x<0) {
        os<<'-';
        x=-x;
    }
    char buf[110];
    int tot=0;
    while(x) buf[++tot]=x%10+'0',x/=10;
    for(int i=tot;i;i--) os<<buf[i];
    return os;
}
void write(lll x) {
    if(x==0) {
        cout<<"0 ";
        return ;
    }
    if(x<0) {
        cout<<"-";
        x=-x;
    }
    char buf[110];
    int tot=0;
    while(x) buf[++tot]=x%10+'0',x/=10;
    for(int i=tot;i;i--) cout<<buf[i];
    cout<<" ";
}
void writeln(lll x) {
    write(x),cout<<"\n";
}

void sol()
{
    cin>>n;
    for(int i=1;i<=n;i++) {
        cin>>opt[i];
        if(opt[i]==1) {
            cin>>h[i];
        }
        if(opt[i]==2) {
            cin>>h[i]>>x[i]>>k[i];
            m[i]=1;
        }
        if(opt[i]==3) {
            cin>>h[i];
        }
    }

    for(int i=1;i<=n;i++) die[i]=false;

    int cnt=1;
    ll delta=0;
    priority_queue<pli,vector<pli>,greater<pli>> q;
    queue<int> dead;
    for(int i=2;i<=n;i++) q.push(mp(h[i],i));
    for(int i=1;i<=n;i++) cnt+=(opt[i]==3);
    dead.push(1);

    while(dead.size()) {
        int p=dead.front(); dead.pop();
        if(opt[p]==1) {
            die[p]=true,delta+=cnt;
            priority_queue<int,vector<int>,greater<int>> qq;
            while(q.size()&&q.top().first<=delta) {
                int pp=q.top().second; q.pop();
                qq.push(pp);
            }
            while(qq.size()) {
                int pp=qq.top(); qq.pop();
                dead.push(pp);
                if(opt[pp]==3) cnt--;
            }
        }
        if(opt[p]==2) {
            if(x[p]==0) die[p]=true;
            else {
                // cout<<p<<": ",writeln(m[p]);
                m[p]*=k[p],x[p]--,h[p]<<=1;
                q.push(mp(h[p]+delta,p));
                // cout<<p<<"; ",writeln(m[p]);
            }
        }
        if(opt[p]==3) {
            die[p]=true;
        }
    }

    int die_cnt=0;
    while(q.size()) {
        pli tmp=q.top(); q.pop();
        h[tmp.second]=tmp.first-delta;
    }
    for(int i=1;i<=n;i++) {
        if(opt[i]==2) {
            if(die[i]) {
                die_cnt++;
                cout<<"0 0 0\n";
            }
            else {
                cout<<m[i]<<" "<<x[i]<<" "<<h[i]<<"\n";
            }
        }
        else {
            if(die[i]) {
                die_cnt++;
                cout<<"0\n";
            }
            else {
                cout<<h[i]<<"\n";
            }
        }
    }
    // cerr<<die_cnt<<endl;
}

template<typename tn> void read(tn &n)
{
    tn s=0,flag=1;
    char ch=getchar();
    for(;ch<'0'||ch>'9';ch=getchar()) if(ch=='-') flag=-1;
    for(;'0'<=ch&&ch<='9';ch=getchar()) s=s*10+ch-'0';
    if(ch=='.')
    {
        ch=getchar();
        tn r=0,R=1;
        for(;'0'<=ch&&ch<='9';ch=getchar()) r=r*10+ch-'0',R*=10;
        s+=r/R;
    }
    n=s*flag;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    int T; cin>>T;
    // int T=1;
    while(T--) sol();
    return 0;
}
/*
3
1 1
2 1 2 2
3 7
*/
/*
5
1 1
2 1 2 3
1 1
2 1 2 3
3 7
*/
/*
5
1 1
2 1 2 3
1 1
2 1 2 3
3 1
*/