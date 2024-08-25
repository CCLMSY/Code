#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define ull unsigned long long
#define uint unsigned int
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
int n,m,sn; 
uint a[N],b[N],c[N];
void work()
{
	cin >> n;
	sn+=n;
	rep(i,0,n-1) cin >> a[i] >> b[i];
	rep(i,0,n-1) c[i]=(a[i]^b[i])&1;
	rep(k,1,31)
	{
		rep(i,0,n-1)
		{
			uint bas=c[(i+n-1)%n]&((1u<<k)-1);
			uint d=(a[i]^bas)+(b[i]^bas);
			c[i]^=d&(1u<<k);
		}
	}
	rep(i,0,n-1) cout << c[i] << endl;
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