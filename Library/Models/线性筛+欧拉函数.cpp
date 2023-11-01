#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const ll MAXN = 1000;
bool check[MAXN+10];//check=1表示合数，被筛除
ll phi[MAXN+10];
ll prime[MAXN+10];
ll tot;//素数的个数
void Phi_and_Prime_Table(ll N){
    memset(check,false,sizeof(check)); phi[1] = 1; tot = 0;
    for(ll i = 2; i <= N; i++) {if( !check[i] ) {prime[tot++] = i; phi[i] = i-1; }
        for(ll j = 0; j < tot; j++) {if(i * prime[j] > N)break; check[i * prime[j]] = true;
            if( i % prime[j] == 0) {phi[i * prime[j]] = phi[i] * prime[j]; break; }
            else {phi[i * prime[j]] = phi[i] * (prime[j] - 1);}}}}