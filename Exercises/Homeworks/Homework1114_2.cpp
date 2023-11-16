#include <iostream>
#include <string>

using namespace std;

class Base{
public:
    void fn1(){
        cout << "Base fn1" << endl;
    }
    void fn2(){
        cout << "Base fn2" << endl;
    }
};
class Derived : private Base{
public:
    using Base::fn1;
    void fn(){
        fn1();
        fn2();
    }
};
int main(){
    Derived d;
    d.fn();
    d.fn1();
    //d.fn2(); 
    
    return 0;
}