#include <iostream>
using namespace std;

class Mammal {
public:
    virtual void speak() {
        cout << "Mammal speaks" << endl;
    }
};

class Dog : public Mammal {
public:
    void speak() {
        cout << "Dog barks" << endl;
    }
};

int main() {
    Mammal *p=new Dog;
    p->speak();
    return 0;
}
