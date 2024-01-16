//Illustrating passing arguments by reference
//  g++ --std=gnu++0x -o passByRefEXE passByRef.cxx
//  ./passByRefEXE
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

void func(int i) {
    i = 137;
}

void funcRef(int& i) {
    i = 137;
}

void funcArr(int arr[2]) {
    arr[0] = 42;
}

void funcVec(vector<int>& vec) {
    vec.push_back(137);
}

int main(int argc, char* argv[]) {

    int i = 0;
    cout << "Init: i = " << i << endl;
    func(i);
    cout << "Not passing by reference: i = " << i << endl;
    funcRef(i);
    cout << "Passing by reference: i = " << i << endl;
    
    //With arrays, this is not necessary
    int arr[2] = {0, 0};
    funcArr(arr);
    cout << "arr = {" << arr[0] << ", " << arr[1] << "}" << endl;

    //Appending to an input vector
    vector<int> vec;
    funcVec(vec);
    cout << "vec contents:" << endl;
    for (auto v : vec) cout << v << endl;
    
    return 1;
}
