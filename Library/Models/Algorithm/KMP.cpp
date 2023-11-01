#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
vector<ll> prefix_function(string s) {
ll n = (ll)s.length();
vector<ll> pi(n);
for (ll i = 1; i < n; i++) {
        ll j = pi[i - 1];
        while (j > 0 && s[i] != s[j]) j = pi[j - 1];
        if (s[i] == s[j]) j++;
        pi[i] = j;
    }
    return pi;
}
vector<ll> KMP(string text, string pattern) {
    string cur = pattern + '#' + text;
    ll sz1 = text.size(), sz2 = pattern.size();
    vector<ll> v;
    vector<ll> lps = prefix_function(cur);
    for (ll i = sz2 + 1; i <= sz1 + sz2; i++) {
        if (lps[i] == sz2)
        v.push_back(i - 2 * sz2);
    }
    return v;
}
int main(){
    string t,s;
    cin >> s >> t;
    vector<ll> occr=KMP(s,t);
    if(occr.empty()) {cout << "-1" << endl;return 0;}
    for(auto i:occr) cout << i << ' ';
    cout << endl; return 0;
}