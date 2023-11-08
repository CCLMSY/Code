#include<iostream>
using namespace std;
int main() {
    int a=0;
    int *p=&a;
    int &r=a;
    cout << "a=" << a << endl;
    *p=10;//通过指针修改a的值
    cout << "a=" << a << endl;
    r=5;//通过引用修改a的值
    cout << "a=" << a << endl;
    return 0;
}