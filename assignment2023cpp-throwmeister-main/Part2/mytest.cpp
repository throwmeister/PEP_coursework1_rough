#include "StringConstruction.h"
#include <iostream>
#include <string>
using std::string;
using std::cout;

int main(){
    string str = "xzxpzxzxpq";
    int x = stringConstruction(str, 11, 10);
    cout << "total count: " << x << "\n";
    return 0;
}