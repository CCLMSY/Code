#include<iostream>
using namespace std;
int main(){
    // int *p;
    // *p=9;
    //尝试对一个未初始化的指针进行解引用,是未定义的行为
    int num=9;
    int *p=&num;//使用指针前必须初始化
    cout << "The value of p: " << *p << endl;
    return 0;
}