#include<iostream>
using namespace std;
class Cat;
class Boat;
class Cat{
public:
    Cat(int _w=0):weight(_w){}
    friend int getTotalWeight(const Cat&,const Boat&);
private:
    int weight;
};//Cat
class Boat{
public:
    Boat(int _w=0):weight(_w){}
    friend int getTotalWeight(const Cat&,const Boat&);
private:
    int weight;
};//Boat
int getTotalWeight(const Cat &c,const Boat &b){
    return c.weight+b.weight;
}//定义友元函数
int main(){
    Cat cat(5);
    Boat boat(500);
    cout << "Total Weight:" << getTotalWeight(cat,boat) << endl;
    return 0;
}