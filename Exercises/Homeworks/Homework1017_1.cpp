#include<bits/stdc++.h>
using namespace std;
class Tree{
public:
    Tree(int _ages=0):ages(_ages){}

    void grow(int years){ages+=years;}//生长
    void age(){cout << "Age:" << ages << endl;}//显示树龄

private:
    int ages;//树龄
};

int main(){
    Tree t(10);//初始为10
    t.age();
    t.grow(5);
    t.age();
    return 0;
}