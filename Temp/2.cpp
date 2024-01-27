#include <iostream>

int main(){
    int i=1;
    int j=(i++)+(++i);
    std::cout<< j <<std::endl;
}