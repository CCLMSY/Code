#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define ull unsigned long long
#define i128 __int128
#define mem(x) memset(x,0,sizeof(x))
#define endl "\n"
#define printYes cout << "Yes\n"
#define printYES cout << "YES\n"
#define printNo cout << "No\n"
#define printNO cout << "NO\n"
#define lowbit(x) ((x)&(-(x)))
#define pb push_back
#define mkp make_pair
#define pii pair<int,int>
#define fi first
#define se second
#define SZ(x) ((int)(x).size())
#define rep(i,j,k) for (int i=(j);i<=(k);i++)
#define per(i,j,k) for (int i=(j);i>=(k);i--)
#define pcnt(x) __builtin_popcount(x)
mt19937 rnd(time(0));
template<class T>void chkmin(T&x,T y){x=min(x,y);}
template<class T>void chkmax(T&x,T y){x=max(x,y);}

const ll inf=1000000000000000000; 
//const ll inf=1000000000;
//const ll mod=998244353;
//const ll mod=1000000007;

const int N=1000005;
int n,m,k,sn; 
int a[N];


void work()
{
	cin >> n >> m >> k;
	assert(k<=m&&k>=1);
	sn+=n;
	ll sum=0;
	rep(i,1,n)
	{
		int x;
		cin >> x;
		assert(x<=m&&x>=1);
		sum+=x-1;
	}
	rep(i,1,n)
	{
		int x;
		cin >> x;
		assert(x<=1e9&&x>=1);
	}
	sum=min(sum,1ll*m-1);
	if (sum<=k-1) printYES;
	else printNO;
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	int T;
	cin >> T;
	while (T--) work();
	return 0;
}
