#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<string.h>
#include<malloc.h>
#include<ctype.h>

#define Max(a,b) (a>b?a:b)
#define Min(a,b) (a>b?b:a)
#define Max3(a,b,c) (Max(a,b)>c?Max(a,b):c)
#define Min3(a,b,c) (Min(a,b)>c?c:Min(a,b))
#define scanfint(a) scanf("%d",&a)
#define scanfll(a) scanf("%lld",&a)
#define scanfstr(a) scanf("%s",a)
#define printfll(a) printf("%lld\n",a)
#define swapnum(a,b) a=a+b;b=a-b;a=a-b
#define FOR(i,l,r) for(int i=l;i<=r;i++)
#define FORLL(i,l,r) for(long long i=l;i<=r;i++)
#define Get_Rand(x) (rand()%x+1)
#define Presentation(i,r) printf("%c"," \n"[i==r])
#define NO printf("NO\n")
#define YES printf("YES\n")
#define RESET(A) memset(A,0,sizeof(A))

typedef long long ll;

const double pi=3.141592653589793;
const ll MOD=1e9+7;
const int INF=0x7fffffff;
const double eps=1e-8;

/*----------C Head----------*/
int dp[10005][10005];
