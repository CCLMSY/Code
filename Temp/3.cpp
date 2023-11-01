#include"4.cpp"

#ifndef STD
    #include<bits/stdc++.h>
    using namespace std;
    #define STD
#endif

extern int i;
using ll=long long;
using pll=pair<ll,ll>;
void next(){
    i++;
}

int main(){
    i++;
    cout << "-----Main()-----" << endl;
    cout << "i:" << i << endl;
    next();
    cout << "After Next():" << i << endl;
    other();
    cout << "After Other():" << i << endl;
    return 0;
}