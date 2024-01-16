//Illustration of the rise of various void-related errors in functions
//  g++ --std=gnu++0x -o voidEXE voidInvalidUse.cxx
//  ./voidEXE
#include <iostream>
#include <fstream>
#include <map>
#include <math.h>
#include <string>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>


using namespace std;

void func(int a) {
    cout << a << endl;
}

void func2(void* v) {
    //cout << *v << endl;    //error: ‘void*’ is not a pointer-to-object type
    //cout << v[0] << endl;  //^-||-
    cout << v << endl;       //Prints a ptr
}

//error: return-statement with a value, in function returning 'void'
//void func3() {
//    cout << "Random number chosen by a fair dice roll: " << endl;
//    return 4;
//}

auto func4() {
    return 1;
}

int main() {
    func(1);
    //func2(1);  //error: invalid conversion from ‘int’ to ‘void*’
    func2((void*)1);

    auto fx = [](int x) {
        return 137.;
    };
    func2(fx);  //error: invalid user-defined conversion from ‘main()::<lambda(int)>’ to ‘void*’
    
    return 1;
}
