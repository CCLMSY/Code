#include <iostream>

using namespace std;

class Object {
public:
    Object(double w) : weight(w) {
        cout << "Object constructor called" << endl;
    }
    ~Object() {
        cout << "Object destructor called" << endl;
    }
    double getWeight() const {
        return weight;
    }
private:
    double weight;
};

class Box : public Object {
public:
    Box(double w, double h, double wd) : Object(w), height(h), width(wd) {
        cout << "Box constructor called" << endl;
    }
    ~Box() {
        cout << "Box destructor called" << endl;
    }
    double getHeight() const {
        return height;
    }
    double getWidth() const {
        return width;
    }
private:
    double height;
    double width;
};

int main() {
    Box box(10.0, 20.0, 30.0);
    cout << "Box weight: " << box.getWeight() << endl;
    cout << "Box height: " << box.getHeight() << endl;
    cout << "Box width: " << box.getWidth() << endl;
    return 0;
}
