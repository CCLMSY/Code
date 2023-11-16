#include<iostream>
using namespace std;

class A{
public:
    A(int a=0,int ax=0):a(a),ax(ax){cout << "A " << a << endl;}
    ~A(){cout << "NA " << a << endl;}
    int ax;
private:
    int a;
};

class B{
public:
    B(int b=0,int bx=0):b(b),bx(bx){cout << "B " << this->b << endl;}
    ~B(){cout << "NB " << b << endl;}
    int bx;
private:
    int b;
};

class C:public A,private B{
public:
    C(int a,int b,int c):c(c){cout << "C " << c << endl;}
    ~C(){cout << "NC " << c << endl;}
private:
    int c;
};

int main(){
    C CC(1,2,3);
    CC.ax=10;
    // CC.bx=10;
    // CC.A::a=10;
    // CC.B::b=10;
    return 0;
}