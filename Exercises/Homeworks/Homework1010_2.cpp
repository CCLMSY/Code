#include<bits/stdc++.h>
using namespace std;
const double pi=acos(-1);

class Circle{
public:
    //构造函数
    Circle(double _radium):radium(_radium){}
    Circle():radium(0){}

    //成员函数
    inline double getArea(){
        return pi*radium*radium;
    }
private:
    double radium;
};

int main(){
    double r;
    cout << "Radium:"; cin >> r;
    Circle C(r);
    cout << "Area:" << C.getArea() << endl;
    return 0;
}