//  g++ --std=gnu++0x -o stackPointerEXE stackPointer.cxx
//  ./stackPointerEXE
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

int* aux() {
    int a = 4;
    return &a;
}

int main() {
    int* ptr = aux();
    cout << ptr << endl;   //Should be NULL
    cout << *ptr << endl;  //Segfault
    return 1;
}
