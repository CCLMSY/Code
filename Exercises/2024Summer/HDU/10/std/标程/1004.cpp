#include <bits/stdc++.h>
#define rep(i,j,k) for(int i=(j);i<=(k);i++)
#define per(i,j,k) for(int i=(j);i>=(k);i--)
#define uint unsigned int
#define ll long long
#define ull unsigned long long
#define db double
#define ldb long double
#define pii pair<int,int>
#define pll pair<ll,ll>
#define mkp make_pair
#define eb emplace_back
#define SZ(S) (int)S.size()
//#define mod 998244353
//#define mod 1000000007
#define inf 0x3f3f3f3f
#define linf 0x3f3f3f3f3f3f3f3f
using namespace std;

template <class T>
void chkmax(T &x,T y){
	if(x < y) x = y;
}

template <class T>
void chkmin(T &x,T y){
	if(x > y) x = y;
}

inline int popcnt(int x){
	return __builtin_popcount(x);
}

inline int ctz(int x){
	return __builtin_ctz(x);
}


/*ll power(ll p,int k = mod - 2){
	ll ans = 1;
	while(k){
		if(k % 2 == 1) ans = ans * p % mod;
		p = p * p % mod;
		k /= 2;	
	}
	return ans;
}*/

namespace io {
	const int __SIZE = (1 << 22) + 1;
	char ibuf[__SIZE], *iS, *iT, obuf[__SIZE], *oS = obuf, *oT = oS + __SIZE - 1, __c, qu[55]; int __f, qr, _eof;
	#define Gc() (iS == iT ? (iT = (iS = ibuf) + fread (ibuf, 1, __SIZE, stdin), (iS == iT ? EOF : *iS ++)) : *iS ++)
	inline void flush () { fwrite (obuf, 1, oS - obuf, stdout), oS = obuf; }
	inline void gc (char &x) { x = Gc(); }
	inline void pc (char x) { *oS ++ = x; if (oS == oT) flush (); }
	inline void pstr (const char *s) { int __len = strlen(s); for (__f = 0; __f < __len; ++__f) pc (s[__f]); }
	inline void gstr (char *s) { for(__c = Gc(); __c < 32 || __c > 126 || __c == ' ';)  __c = Gc();
		for(; __c > 31 && __c < 127 && __c != ' '; ++s, __c = Gc()) *s = __c; *s = 0; }
	template <class I> inline bool read (I &x) { _eof = 0;
		for (__f = 1, __c = Gc(); (__c < '0' || __c > '9') && !_eof; __c = Gc()) { if (__c == '-') __f = -1; _eof |= __c == EOF; }
		for (x = 0; __c <= '9' && __c >= '0' && !_eof; __c = Gc()) x = x * 10 + (__c & 15), _eof |= __c == EOF; x *= __f; return !_eof; }
	template <class I> inline void write (I x) { if (!x) pc ('0'); if (x < 0) pc ('-'), x = -x;
		while (x) qu[++ qr] = x % 10 + '0',  x /= 10; while (qr) pc (qu[qr --]); }
	struct Flusher_ {~Flusher_(){flush();}}io_flusher_;
} using io::pc; using io::gc; using io::pstr; using io::gstr; using io::read; using io::write;

struct solver{
	int n,m;
	char str[3005][3005];
	int U[3005][3005],D[3005][3005];
	void init(){
		rep(i,1,n){
			rep(j,1,m){
				U[i][j] = U[i - 1][j] + 1;
				if(str[i][j] == '1') U[i][j] = 0;
			}
		}
		fill(D[n + 1],D[n + 1] + m + 1,0);
		per(i,n,1){
			rep(j,1,m){
				D[i][j] = D[i + 1][j] + 1;
				if(str[i][j] == '1') D[i][j] = 0;				
			}
		}
	}
	struct Que{//单调队列,查 min
		int h,t;
		struct node{
			int val,id;
		}Q[3005];
		void init(){
			h = t = 1;
		}
		void push(int val,int id){
			while(h != t){
				if(Q[t - 1].val > val) t--;
				else break;
			}
			Q[t++] = {val,id};
		}
		void pop(int id){//删掉 <= id 的
			while(h != t){
				if(Q[h].id <= id) h++;
				else return;
			}
		}
		int getval(){
			assert(h != t);
			return Q[h].val;
		}
	}Q[2];
	int a[3005][3005],b[3005][3005],answer;
	void gsum(int l,int r){
		chkmax(l,1);chkmin(r,n);
		if(l > r) return;
		answer += r - l + 1;
	}
	int solve(int p,int q){
/*		rep(i,1,n){
			rep(j,1,m) printf("%c",str[i][j]);
			printf("\n");
		}
		printf("(%d,%d)\n",p,q);*/
		for(int i = p;i <= n;i += p){
			Q[0].init();Q[1].init();
			rep(j,1,m){
				Q[0].push(U[i][j],j);
				Q[1].push(D[i][j],j);
				Q[0].pop(j - q);Q[1].pop(j - q);
				if(j >= q){
					a[i][j] = Q[0].getval();
					b[i][j] = Q[1].getval();
					if(a[i][j] + b[i][j] - 1 < p) a[i][j] = b[i][j] = 0;
				}
			}
			Q[0].init();Q[1].init();
			rep(j,1,m){
				if(j + q - 1 <= m){
					Q[0].push(-a[i][j + q - 1],j + q - 1);
					Q[1].push(-b[i][j + q - 1],j + q - 1);				
				}
				Q[0].pop(j - 1);Q[1].pop(j - 1);
				a[i][j] = -Q[0].getval();
				b[i][j] = -Q[1].getval();
			}
/*			printf("i=%d\n",i);
			rep(j,1,m) printf("%d ",c[i][j]);
			printf("\n");
			rep(j,1,m) printf("%d ",d[i][j]);
			printf("\n");*/
		}
		answer = 0;
		for(int s = 0;s <= n;s += p){
			int t = s + p;
			rep(j,1,m){
				if(t > n){
					gsum(s,s + b[s][j] - 1);
					continue;
				}
				if(t - a[t][j] + 1 <= s + b[s][j] - 1){
					gsum(s,t - 1);
				}else{
					gsum(s,s + b[s][j] - 1);
					gsum(t - a[t][j] + 1,t - 1);
				}
			}
		}
//		printf("answer=%d\n",answer);
		return answer;
	}
}S[2];

int T,n,m,k;
char s[3005][3005];

int check(int p,int q){
	int res;
	if(p > q) res = S[0].solve(p,q);
	else res = S[1].solve(q,p);
//	printf("(%d,%d) %d\n",p,q,res);
	return res >= k;
}

int _sum;
void solve(){
	read(n);read(m);read(k);
	_sum += n * m;
	cerr << n << " " << m << endl;
	rep(i,1,n) gstr(s[i] + 1);
	S[0].n = n;S[0].m = m;
	rep(i,1,n){
		rep(j,1,m) S[0].str[i][j] = s[i][j];
	}
	S[1].n = m;S[1].m = n;
	rep(i,1,m){
		rep(j,1,n) S[1].str[i][j] = s[j][i];
	}
	S[0].init();S[1].init();
//	S[1].solve(2,1);
	int j = m,answer = 0;
	rep(i,1,n){
		while(j && !check(i,j)) j--;
		answer += j;
//		cerr << j << " ";
	}
//	cerr << endl;
	write(answer);
	pc('\n');
}

int main(){
//	freopen("test.in","r",stdin);
//	freopen("1.out","w",stdout);
	scanf("%d",&T);
	while(T--) solve();
//	assert(_sum == 20542315);
//	cerr << _sum << endl;
//	cerr << clock() << endl;
//	cerr << Mxn << " " << Mxm << endl;
	return 0;
}