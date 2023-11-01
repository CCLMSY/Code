#include<bits/stdc++.h>
using namespace std;

inline short Div(unsigned short a,unsigned short b){
    return b?a/b:-1;
}

int main(){
    unsigned short a,b;
    cin >> a >> b;
    cout << Div(a,b) << endl;
    return 0;
}//Powered by CC