#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const ll N = 1000;
bool check[N + 10]; // check=1表示合数，被筛除
ll phi[N + 10]; // 欧拉函数，phi[i]表示小于等于i的数中与i互质的数的个数
ll prime[N + 10]; // prime[i]表示第i个素数
ll tot; // 素数的个数
void Phi_and_Prime_Table(ll N)
{
    memset(check, false, sizeof(check));
    phi[1] = 1;
    tot = 0;
    for (ll i = 2; i <= N; i++)
    {
        if (!check[i])
        {
            prime[tot++] = i;
            phi[i] = i - 1;
        }
        for (ll j = 0; j < tot; j++)
        {
            if (i * prime[j] > N)
                break;
            check[i * prime[j]] = true;
            if (i % prime[j] == 0)
            {
                phi[i * prime[j]] = phi[i] * prime[j];
                break;
            }
            else
            {
                phi[i * prime[j]] = phi[i] * (prime[j] - 1);
            }
        }
    }
}