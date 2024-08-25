#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

struct int128{
    __int128_t value;

    int128():value(0){}
    int128(ll _val):value(_val){}
    int128(__int128_t _val):value(_val){}

    static int128 trans(string input) {
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

    friend istream& operator>>(istream& in,int128& x){
        string Input; in >> Input;
        x=trans(Input);  return in;
    }
    friend ostream& operator<<(ostream& out,const int128& x){
        x.print(); return out;
    }

    int128 operator + (const int128 &b)const{return value+b.value;}
    int128 operator - (const int128 &b)const{return value-b.value;}
    int128 operator * (const int128 &b)const{return value*b.value;}
    int128 operator / (const int128 &b)const{return value/b.value;}
    int128 operator % (const int128 &b)const{
        if(value<0)return value-value/b.value*b.value+b.value;
        return value-value/b.value*b.value;
    }

    bool operator < (const int128 &b)const{return value<b.value;}
    bool operator > (const int128 &b)const{return value>b.value;}
    bool operator == (const int128 &b)const{return value==b.value;}
    bool operator != (const int128 &b)const{return value!=b.value;}
    bool operator <= (const int128 &b)const{return value<=b.value;}
    bool operator >= (const int128 &b)const{return value>=b.value;}

    void operator = (const int128 &b){value=b.value;}
    void operator = (const ll &b){value=b;}

    operator bool()const{return value!=0;}
};


int main(){
    int128 a,b;
    cin >> a >> b;
    cout << a+b << endl << a-b << endl << a*b << endl << a/b << endl << a%b << endl;
    return 0;
}