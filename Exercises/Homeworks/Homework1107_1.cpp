#include <iostream>
using namespace std;
int main() {
    int a = 10;
    const int* p1 = &a; // p1是指向const int的指针，指针指向的值不能被修改
    int* const p2 = &a; // p2是指向int的const指针，指针本身不能被修改

    cout << "p1指向的值为：" << *p1 << endl;
    cout << "p2指向的值为：" << *p2 << endl;

    // 尝试修改指针指向的值
    // *p1 = 20; // 编译错误，p1指向的值是const的
    *p2 = 20; // 可以修改，p2指向的值不是const的

    // 尝试修改指针本身
    p1 = nullptr; // 可以修改，p1本身不是const的
    // p2 = nullptr; // 编译错误，p2本身是const的

    return 0;
}
