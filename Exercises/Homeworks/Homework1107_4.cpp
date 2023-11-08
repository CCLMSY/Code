#include<iostream>
using namespace std;
int fn1(){
    int *p=new int(5);
    int num=*p;
    delete p;//释放指针指向的内存
    return num;
}
int main(){
    int a=fn1();
    cout << "The value of a is:" << a << endl;
    return 0;
}