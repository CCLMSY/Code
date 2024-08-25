#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll mergeAndCount(vector<ll> &arr, ll l, ll m, ll r)
{
    vector<ll> temp(r - l + 1);
    ll invCount = 0;
    ll i = l, j = m + 1, k = 0;
    while (i <= m && j <= r)
    {
        if (arr[i] <= arr[j])
            temp[k++] = arr[i++];
        else
        {
            temp[k++] = arr[j++];
            invCount += m - i + 1;
        }
    }
    while (i <= m)
        temp[k++] = arr[i++];
    while (j <= r)
        temp[k++] = arr[j++];
    for (ll p = 0; p < temp.size(); p++)
        arr[l + p] = temp[p];
    return invCount;
}

ll mergeSortAndCount(vector<ll> &arr, ll l, ll r)
{
    ll invCount = 0;
    if (l < r)
    {
        ll m = l + (r - l) / 2;
        invCount += mergeSortAndCount(arr, l, m);
        invCount += mergeSortAndCount(arr, m + 1, r);
        invCount += mergeAndCount(arr, l, m, r);
    }
    return invCount;
}

int main(){
    ll n;cin >> n;
    vector<ll> arr(n);
    for(auto& i:arr)cin >> i;
    cout << mergeSortAndCount(arr, 0, n - 1) << endl;
}