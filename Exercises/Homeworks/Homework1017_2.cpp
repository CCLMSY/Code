#include<bits/stdc++.h>
using namespace std;
class Complex{
public:
    Complex(double _real=0,double _imag=0):Imag(_imag),Real(_real){}
    void add(const Complex&);
    void show();

private:
    const double eps=1e-6;
    double Real;//实部
    double Imag;//虚部
};
void Complex::add(const Complex &c){
    Real+=c.Real;
    Imag+=c.Imag;
}
void Complex::show(){
    if(fabs(Real)>Real*eps){//防止精度问题
        cout << Real; //实部不为0，输出实部
        if(fabs(Imag)>Imag*eps) cout << "+" << Imag << "i"; //若虚部不为0，输出“+虚部”
    }
    else if(fabs(Imag)>Imag*eps) cout << Imag << "i";//实部为0，虚部不为0，输出虚部
    else cout << 0;//都为0，输出0
    cout << endl;
}

int main(){
    Complex c1(3,5);
    Complex c2=4.5;
    c1.add(c2);
    c1.show();
    return 0;
}