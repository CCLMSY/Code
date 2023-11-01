#include<bits/stdc++.h>
using namespace std;
class Cat{
public:
    Cat(){numOfCats++;}
    ~Cat(){numOfCats--;}

    static int getNumOfCats(){
        return numOfCats;
    }

private:
    static int numOfCats;
};

int Cat::numOfCats=0;

int main(){
    Cat cat1;
    Cat cat2;
    cout << Cat::getNumOfCats() << endl;
    {
    Cat cat3;
    cout << Cat::getNumOfCats() << endl;
    }
    cout << Cat::getNumOfCats() << endl;
    return 0;
}