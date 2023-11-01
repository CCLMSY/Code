#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

struct int128{
    __int128_t value;

    int128():value(0){}
    int128(ll _val):value(_val){}
    int128(__int128_t _val):value(_val){}

    static int128 read() {
        string input;cin >> input;
        bool isNegative = false;
        if (input[0] == '-') {isNegative = true;input = input.substr(1);}
        __int128_t result=0;
        for (char c : input) {result = result * 10 + (c - '0');}
        if (isNegative) {result = -result;}
        return int128(result);
    }

    void print() const {
        __int128_t x = value;
        if (x < 0) {putchar('-');x = -x;}
        if (x > 9) {int128(x / 10).print();}
        putchar(x % 10 + '0');
    }

    int128 operator + (const int128 &b)const{return value+b.value;}
    int128 operator - (const int128 &b)const{return value-b.value;}
    int128 operator * (const int128 &b)const{return value*b.value;}
    int128 operator / (const int128 &b)const{return value/b.value;}

};

int main(){
    int128 i;
    i=0x3fffffffffffffff;
    ll t;cin >> t;
    ll x;
    while(t--){
        cin >> x;i=i/x;
        i.print();putchar('\n');
    }
    return 0;
}