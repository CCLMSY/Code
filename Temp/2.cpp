#include <iostream>
#include <string>

using namespace std;

class CPerson {
public:
    CPerson(string n, string i, int g, int a) : name(n), id(i), gender(g), age(a) {
        cout << "CPerson constructor called." << endl;
    }
    ~CPerson() {
        cout << "CPerson destructor called." << endl;
    }
    void print() {
        cout << "Name: " << name << endl;
        cout << "ID: " << id << endl;
        cout << "Gender: " << gender << endl;
        cout << "Age: " << age << endl;
    }
private:
    string name;
    string id;
    int gender;
    int age;
};

class CEmployee :public CPerson {
public:
    CEmployee(string n, string i, int g, int a, string d, float s) : CPerson(n, i, g, a), department(d), salary(s) {
        cout << "CEmployee constructor called." << endl;
    }
    ~CEmployee() {
        cout << "CEmployee destructor called." << endl;
    }
    void print() {
        CPerson::print();
        cout << "Department: " << department << endl;
        cout << "Salary: " << salary << endl;
    }
private:
    string department;
    float salary;
};

int main()  {  
    string name,id,department;  
    int sex,age;  
    float salary;  
    cout<<"input employee's name,id,sex(0:women,1:man),age,department,salary:\n";  
    cin>>name>>id>>sex>>age>>department>>salary;
    CEmployee employee1(name,id,sex,age,department,salary);
    employee1.print();
    return 0;
} 