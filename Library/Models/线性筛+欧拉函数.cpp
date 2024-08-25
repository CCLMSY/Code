#include <bits/stdc++.h>
using namespace std;
typedef long ll;

const ll N = 5e7+7;
// 线性筛法求素数/欧拉函数
// 素数筛法，时间复杂度视为O(n)
struct PrimeSieve
{
    vector<bool> check; // check=1表示合数，被筛除
    vector<ll> prime; // prime[i]表示第i个素数，i从0开始 v[0]=2
    // vector<ll> phi; // 欧拉函数，phi[i]表示小于等于i的数中与i互质的数的个数
    ll cnt; // 素数的个数
    PrimeSieve(ll n=N){
        check.resize(n+1);
        // phi.resize(n+1); phi[1] = 1;
        for (ll i = 2; i <= n; i++){
            if (!check[i]){
                prime.push_back(i);
                // phi[i] = i - 1;
            }
            for (ll j = 0; j < prime.size(); j++){
                if (i * prime[j] > n) break;
                check[i * prime[j]] = true;
                // if (i % prime[j] == 0){
                //     phi[i * prime[j]] = phi[i] * prime[j];
                //     break;
                // }else phi[i * prime[j]] = phi[i] * (prime[j] - 1);
            }
        }
        cnt = prime.size();
    }
};

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    ll n,q,t;cin >> n >> q;
    PrimeSieve ps(n);
    while(q--){
        cin >> t;
        cout << ps.prime[t-1] << '\n';
    }
    return 0;
}