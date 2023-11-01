---
title: 动态规划-其他
date: '2023/9/22 20:00'
categories: 笔记模板
keywords: 动态规划
description: 动态规划-其他//其他类型的题目篇幅较小，故整合到一起
tags:
  - 动态规划
  - 笔记
abbrlink: 4014d4be
updated: 2023/10/22 14:50
sticky:
swiper_index:
---
# 一.子序列问题
## 1.最长公共子序列(LCS)
O(mn)
```cpp
#define N 1005
ll a[N]={0},b[N]={0},dp[N][N]={0};
void solve()
{
    ll m,n;cin >> n >> m;
    FORLL(i,1,n) cin >> a[i];
    FORLL(i,1,m) cin >> b[i];
    FORLL(i,1,n)
        FORLL(j,1,m){
            if(a[i]==b[j]) dp[i][j]=dp[i-1][j-1]+1;
            else dp[i][j]=max(dp[i-1][j],dp[i][j-1]);
        }
    cout << dp[n][m] << endl;
}
```

## 2.最长上升子序列
### 2.1.DP
$O(n^2)$ [洛谷B3637](https://www.luogu.com.cn/problem/B3637)
```cpp
/*----------Code Area----------*/
#define N 10005
ll a[N]={0},dp[N]={0};
void solve()
{
    ll n;cin >> n;
    FORLL(i,1,n) cin >> a[i];
    dp[1]=1;ll ans=0;
    FORLL(i,2,n){
        ll mx=0;
        FORLL(j,1,i-1)
            if(a[i]>a[j]) mx=max(mx,dp[j]);
        dp[i]=mx+1;
        ans=max(ans,dp[i]);
    }
    cout << ans << endl;
}
```

### 2.2.贪心
$O(n\log n)$ [洛谷B3637](https://www.luogu.com.cn/problem/B3637)
贪心：维护当前子序列d，替换序列中不小于a[i]的第一个元素
```cpp
#define N 10005
ll a[N]={0};
vector<ll> d;
void solve()
{
    ll n;cin >> n;
    FORLL(i,1,n) cin >> a[i];
    d.emplace_back(a[1]);
    FORLL(i,2,n){
        if(d.back()<a[i]) d.emplace_back(a[i]);
        else *lower_bound(ALL(d),a[i])=a[i];
    }//最长不降子序列改成upper_bound
    cout << d.size() << endl;
}
```

# 二.区间DP
分治：父问题的答案由子问题集中最优解转移
$O(n^3)$

[NOI1995/LOJ10147](https://loj.ac/p/10147)
```cpp
#define N 205
ll v[N*2]={0},S[N*2]={0};
ll dpmx[N*2][N*2]={0},dpmn[N*2][N*2]={0};
void solve(){
    ll n,t;cin >> n;
    FORLL(i,1,n){
        cin >> v[i];
        v[i+n]=v[i];
    }
    FORLL(i,1,n*2) FORLL(j,1,n*2) dpmn[i][j]=INF;
    FORLL(i,1,n*2) dpmn[i][i]=0;//Init
    FORLL(i,1,n*2) S[i]=S[i-1]+v[i];
    FORLL(len,1,n){//枚举区间长度
        FORLL(i,1,n*2-len+1){
            ll j=i+len-1;//根据长度和i算出j
            FORLL(k,i,j-1){//枚举分界点
                dpmx[i][j]=max(dpmx[i][j],dpmx[i][k]+dpmx[k+1][j]+S[j]-S[i-1]);
                dpmn[i][j]=min(dpmn[i][j],dpmn[i][k]+dpmn[k+1][j]+S[j]-S[i-1]);
            }//转移
        }
    }
    ll mx=0,mn=INF;
    FORLL(i,1,n+1) mx=max(mx,dpmx[i][i+n-1]);
    FORLL(i,1,n+1) mn=min(mn,dpmn[i][i+n-1]);
    cout << mn << endl << mx << endl;
}
```

[NOIP2006/VIJOS1312](https://vijos.org/p/1312)
```cpp
#define N 105
ll dp[N*2][N*2]={0};
void solve(){
    ll n;
    cin >> n;
    deque<ll> head(n);
    for(auto &t:head) cin >> t;
    for(auto t:head) head.emplace_back(t);
    deque<ll> tail=head;
    tail.emplace_back(tail.front());tail.pop_front();
    head.emplace_front(0);tail.emplace_front(0);
    FORLL(len,2,n)
        FORLL(i,1,n*2-len+1){
            ll j=i+len-1;
            FORLL(k,i+1,j)//k作为第二段开头
                dp[i][j]=max(dp[i][j],dp[i][k-1]+dp[k][j]+head[i]*head[k]*tail[j]);
        }
    ll re=0;
    FORLL(i,1,n) re=max(re,dp[i][i+n-1]);
    cout << re << endl;
}
```



# 三.概率/期望DP
ATC-abc323_e
某点的期望从此前的一段区间内转移
```cpp
#define N 1003
#define X 10004
ll dp[X]={1,0};//歌曲在t时刻切换的概率
ll t[N]={0};
void solve()
{
    ll n,x;cin >> n >> x;
    FORLL(i,1,n) cin >> t[i];
    ll invn=inv(n);//1/n
    FORLL(i,1,x){
        FORLL(j,1,n) if(i>=t[j])
            addto(dp[i],dp[i-t[j]]);
        multo(dp[i],invn);
    }
    ll re=0;
    FORLL(i,max(0ll,x-t[1]+1),x) addto(re,dp[i]);
    cout << multo(re,invn) << endl;
}
```

# 四.DP优化
## 1. 单调队列优化DP
O(mn) M(m) CF372C
利用单调队列将每次区间DP均摊复杂度降至O(1)
```cpp
#define N 305
#define M 150005
ll a[N]={0},b[N]={0},t[N]={0};
ll dp[2][M]={0};
ll n,m,d;int fl=1;
ll que[M]={0};
void solve()
{
    cin >> n >> m >> d;
    FORLL(i,1,m) cin >> a[i] >> b[i] >> t[i];
    fl=1;
    FORLL(i,1,m){
        ll l=1,r=0,k=1;
        FORLL(j,1,n){
            for(;k<=min(n,j+(t[i]-t[i-1])*d);k++){
                while(r>=l&&dp[fl^1][que[r]]<dp[fl^1][k]) r--;
                que[++r]=k;//单调队列优化DP：维护上一状态的有效区间内的最大值的下标
            }
            while(r>=l&&que[l]<max(1ll,j-(t[i]-t[i-1])*d)) l++;
            dp[fl][j]=dp[fl^1][que[l]]+b[i]-abs(a[i]-j);
        }fl^=1;//状态转换
    }fl^=1;//回到最终状态
    ll ans=-INF;
    FORLL(i,1,n) ans=max(ans,dp[fl][i]);
    cout << ans << endl;
}
```

Reference：[OI-Wiki](https://oi-wiki.org/dp/)