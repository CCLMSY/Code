#include <bits/stdc++.h>
using namespace std;
void solv() {
    string s;cin >> s;
    vector<int> sum3(s.size() + 1) , sum5(s.size() + 1) ;
    for(int i = 1;i <= s.size();i++) {
        sum3[i] = sum3[i - 1];
        sum5[i] = sum5[i - 1];
        if(s[i - 1] == '3') sum3[i]++ ;
        if(s[i - 1] == '5' || s[i - 1] == 'U') sum5[i]++ ;
    }
    for(int i = 10 ; i <= s.size() ;i++) {
        if(sum3[i] - sum3[i - 10] == 10) {
            cout<<"invalid\n" ; return ;
        }
    }
    for(int i = 90 ; i <= s.size() ;i++) {
        if(sum5[i] - sum5[i - 90] == 0) {
            cout << "invalid\n" ; return ;
        }
    }
    char lst = 'U';
    for(int i = 0;i < s.size();i++) {
        if(s[i] == '5' || s[i] == 'U') {
            if(s[i] == '5' && lst == '5') {
                cout << "invalid\n";return ;
            }
            lst = s[i];
        }
    }
    cout << "valid\n" ; return ;
}
int main() {
    // freopen("in.txt","r",stdin) ;
    ios::sync_with_stdio(false) ; cin.tie(0) ;
    int t ;cin >> t;
    while(t--) solv() ;
    return 0;
}
